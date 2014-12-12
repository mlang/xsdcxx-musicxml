XSDCXX based MusicXML bindings
==============================

xsdcxx-musicxml is a MusicXML binding for C++ based on xsdcxx.
The bulk of the source code is automatically generated from the MusicXML
W3C XML Schema Definition (XSD).

Building
--------

CMake and XSDCXX are required to build this library.

See generate.cpp and roundtrip.cpp for very simple usage examples.

To use this library in your program,

    #include "xsdcxx-musicxml/musicxml.hpp"

and link with the xsdcxx-musicxml library.

You can also use the CMake ADD_SUBDIRECTORY command to directly
include this library as a subproject in your CMake based project.


