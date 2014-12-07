CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)
project(xsdcxx-musicxml CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
add_definitions(-std=c++11)
find_package(XSDCXX REQUIRED)
set(XSDCXX_FLAGS cxx-tree
    --std c++11 --generate-ostream --generate-serialization)

add_custom_target(xsdcxx
  COMMAND ${XSDCXX_EXECUTABLE} ${XSDCXX_FLAGS} xml.xsd
  COMMAND ${XSDCXX_EXECUTABLE} ${XSDCXX_FLAGS} xlink.xsd
  COMMAND ${XSDCXX_EXECUTABLE} ${XSDCXX_FLAGS} --generate-doxygen
    --namespace-map =musicxml --location-regex '%http://.+/\(.+\)%$$1%'
    --root-element-all --ordered-type measure1 --ordered-type part1
    musicxml.xsd
)
add_custom_target(modernize
  COMMAND clang-modernize-3.6 --risk=risky --include . xml.cxx xlink.cxx musicxml.cxx -- -std=c++11 -I .
)
add_custom_target(tidy
  COMMAND clang-tidy-3.6 -fix xml.cxx xlink.cxx musicxml.cxx
)
add_custom_target(format
  COMMAND clang-format-3.6 -i xml.hxx xml.cxx xlink.hxx xlink.cxx musicxml.hxx musicxml.cxx
)
add_library(xsdcxx-musicxml dom-parse.cxx musicxml.cxx xlink.cxx xml.cxx)
target_link_libraries(xsdcxx-musicxml ${XERCESC_LIBRARY})

add_executable(generate generate.cxx)
target_link_libraries(generate xsdcxx-musicxml)
add_executable(roundtrip roundtrip.cxx)
target_link_libraries(roundtrip xsdcxx-musicxml)

