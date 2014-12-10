CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)
project(xsdcxx-musicxml CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
add_definitions(-std=c++11)

find_package(XSDCXX REQUIRED)
set(XSDCXX_FLAGS cxx-tree
    --output-dir ${PROJECT_BINARY_DIR}
    --std c++11 --cxx-suffix .cpp --hxx-suffix .hpp
    --generate-ostream --generate-serialization
)

foreach(BASENAME xml xlink)
  add_custom_command(
    OUTPUT ${PROJECT_BINARY_DIR}/${BASENAME}.cpp
           ${PROJECT_BINARY_DIR}/${BASENAME}.hpp
    COMMAND ${XSDCXX_EXECUTABLE} ${XSDCXX_FLAGS} ${BASENAME}.xsd
    DEPENDS ${PROJECT_SOURCE_DIR}/${BASENAME}.xsd
  )
endforeach(BASENAME xml xlink)
add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/musicxml-0.cpp
         ${PROJECT_BINARY_DIR}/musicxml-1.cpp
         ${PROJECT_BINARY_DIR}/musicxml-2.cpp
         ${PROJECT_BINARY_DIR}/musicxml-3.cpp
         ${PROJECT_BINARY_DIR}/musicxml.hpp
  COMMAND ${XSDCXX_EXECUTABLE} ${XSDCXX_FLAGS} --generate-doxygen
    --namespace-map =musicxml --location-regex '%http://.+/\(.+\)%$$1%'
    --root-element-all --ordered-type measure1 --ordered-type part1
    --custom-type note=/note_base
    --hxx-epilogue '\#include \"note.hpp\"'
    --hxx-epilogue '\#include \"utilities.hpp\"'
    --parts 4
    musicxml.xsd
  DEPENDS ${CMAKE_SOURCE_DIR}/musicxml.xsd
)

add_library(xsdcxx-musicxml
  dom-parse.cpp note.cpp
  musicxml-0.cpp musicxml-1.cpp musicxml-2.cpp musicxml-3.cpp xlink.cpp xml.cpp
)
target_link_libraries(xsdcxx-musicxml ${XERCESC_LIBRARY})

add_executable(generate generate.cpp)
target_link_libraries(generate xsdcxx-musicxml)
add_executable(roundtrip roundtrip.cpp)
target_link_libraries(roundtrip xsdcxx-musicxml)

