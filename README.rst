XSDCXX based MusicXML bindings
==============================

xsdcxx-musicxml is a MusicXML binding for C++11 based on xsdcxx.
The bulk of the source code is automatically generated from the MusicXML
W3C XML Schema Definition (XSD).  Parsing, manipulation, and serialization
of MusicXML documents is supported.

This library handles both, partwise *and* timewise MusicXML documents in a
uniform way.  Client code is free to work with either of the two object models,
and MusicXML documents are automatically converted to the requested format
during parsing.

    auto timewise = musicxml::parse<musicxml::score_timewise>(std::cin, "-");
    for (auto &measure: timewise.measure()) {
      for (auto &part: measure.part()) {
        //...
      }
    }
    musicxml::serialize(std::cout, timewise);

or

    auto partwise = musicxml::parse<musicxml::score_partwise>(std::cin, "-");
    for (auto &part: partwise.part()) {
      for (auto &measure: part.measure()) {
        //...
      }
    }
    musicxml::serialize(std::cout, partwise);

Alternatively, if you want to save to a different format as you have worked with,
you can use the musicxml::convert function to flip formats:

    // Serialize a score-partwise document.
    musicxml::serialize(std::cout, musicxml::convert(timewise));
    
Both, musicxml::score_partwise::part_type::measure_type and
musicxml::score_timewise::measure_type::part_type use boost::variant to store the
different allowed element types in a heterogeneous container.  This container
can be accessed and set with the music_data() accessors, and its type
is available as member type music_data_sequence.


Building
--------

CMake and XSDCXX are required to build this library.

See generate.cpp, partiwse.cpp and timewise.cpp for very simple usage examples.

To use this library in your program,

    #include "xsdcxx-musicxml/musicxml.hpp"

and link with the xsdcxx-musicxml library.

You can also use the CMake ADD_SUBDIRECTORY command to directly
include this library as a subproject in your CMake based project.

Parent project
--------------

This library is being developed as a sub-project of BMC, the Braille Music Compiler.
See http://github.com/mlang/bmc


