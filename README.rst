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

Known Problems
--------------

* Serialisation crashes clang.
* partwise/timewise transformation not implemented yet.

