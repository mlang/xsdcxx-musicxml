CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)
project(xsdcxx-musicxml CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
add_definitions(-std=c++11)

find_package(XSDCXX REQUIRED)
set(XSDCXX_FLAGS cxx-tree
    --output-dir ${PROJECT_BINARY_DIR}
    --std c++11 --generate-ostream --generate-serialization)

foreach(BASENAME xml xlink)
  add_custom_command(
    OUTPUT ${PROJECT_BINARY_DIR}/${BASENAME}.cxx
           ${PROJECT_BINARY_DIR}/${BASENAME}.hxx
    COMMAND ${XSDCXX_EXECUTABLE} ${XSDCXX_FLAGS} ${BASENAME}.xsd
    DEPENDS ${PROJECT_SOURCE_DIR}/${BASENAME}.xsd
  )
endforeach(BASENAME xml xlink)
add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/musicxml-0.cxx
         ${PROJECT_BINARY_DIR}/musicxml-1.cxx
         ${PROJECT_BINARY_DIR}/musicxml-2.cxx
         ${PROJECT_BINARY_DIR}/musicxml-3.cxx
         ${PROJECT_BINARY_DIR}/musicxml.hxx
  COMMAND ${XSDCXX_EXECUTABLE} ${XSDCXX_FLAGS} --generate-doxygen
    --namespace-map =musicxml --location-regex '%http://.+/\(.+\)%$$1%'
    --root-element-all --ordered-type measure1 --ordered-type part1
    --custom-type note=/note_base --hxx-epilogue '\#include \"note.hxx\"'
    --parts 4
    musicxml.xsd
  DEPENDS ${CMAKE_BINARY_DIR}/musicxml.xsd
)

add_library(xsdcxx-musicxml
  dom-parse.cxx note.cxx
  musicxml-0.cxx musicxml-1.cxx musicxml-2.cxx musicxml-3.cxx xlink.cxx xml.cxx
)
target_link_libraries(xsdcxx-musicxml ${XERCESC_LIBRARY})

add_executable(generate generate.cxx)
target_link_libraries(generate xsdcxx-musicxml)
add_executable(roundtrip roundtrip.cxx)
target_link_libraries(roundtrip xsdcxx-musicxml)

