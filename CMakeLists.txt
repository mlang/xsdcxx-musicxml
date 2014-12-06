CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)
project(xsdcxx-musicxml CXX)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
add_definitions(-std=c++11)
find_package(XSDCXX REQUIRED)
set(XSDCXX_FLAGS cxx-tree
    --std c++11 --generate-ostream --generate-serialization)

foreach(BASENAME xml xlink)
  add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/${BASENAME}.cxx
           ${CMAKE_BINARY_DIR}/${BASENAME}.hxx
    COMMAND ${XSDCXX_EXECUTABLE} ${XSDCXX_FLAGS} ${BASENAME}.xsd
    DEPENDS ${CMAKE_BINARY_DIR}/${BASENAME}.xsd
  )
endforeach(BASENAME xml xlink)
add_custom_command(
  OUTPUT ${CMAKE_BINARY_DIR}/musicxml-0.cxx
         ${CMAKE_BINARY_DIR}/musicxml-1.cxx
         ${CMAKE_BINARY_DIR}/musicxml-2.cxx
         ${CMAKE_BINARY_DIR}/musicxml-3.cxx
         ${CMAKE_BINARY_DIR}/musicxml.hxx
  COMMAND ${XSDCXX_EXECUTABLE} ${XSDCXX_FLAGS}
    --namespace-map =musicxml
    --location-regex '%http://.+/\(.+\)%$$1%'
    --root-element-all --ordered-type measure1 --ordered-type part1 --ordered-type note
    --parts 4
    musicxml.xsd
  DEPENDS ${CMAKE_BINARY_DIR}/musicxml.xsd
)
add_library(xsdcxx-musicxml
  dom-parse.cxx
  musicxml-0.cxx
  musicxml-1.cxx
  musicxml-2.cxx
  musicxml-3.cxx
  xlink.cxx xml.cxx
)
target_link_libraries(xsdcxx-musicxml ${XERCESC_LIBRARY})

add_executable(generate generate.cxx)
target_link_libraries(generate xsdcxx-musicxml)
add_executable(roundtrip roundtrip.cxx)
target_link_libraries(roundtrip xsdcxx-musicxml)

