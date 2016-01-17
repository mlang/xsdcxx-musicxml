cmake_minimum_required(VERSION 3.4.1 FATAL_ERROR)
project(xsdcxx-musicxml VERSION 0.1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")

# Find Boost only if a potential parent project hasn't done so already.
if(NOT ${Boost_FOUND})
  find_package(Boost REQUIRED)
endif()
find_package(XercesC REQUIRED)
find_package(XSDCXX REQUIRED)

include_directories(
  ${Boost_INCLUDE_DIRS}
  ${XercesC_INCLUDE_DIR} ${XSDCXX_INCLUDE_DIR}
)

# Generate musicxml-schema.{cpp,hpp}
add_executable(xsdbin xsdbin.cpp)
target_compile_features(xsdbin PRIVATE cxx_range_for)
target_link_libraries(xsdbin ${XercesC_LIBRARY})
add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/musicxml-schema.cpp
         ${PROJECT_BINARY_DIR}/musicxml-schema.hpp
  COMMAND xsdbin --cxx-suffix -schema.cpp --hxx-suffix -schema.hpp
                 --output-dir ${PROJECT_BINARY_DIR}
                 ${PROJECT_SOURCE_DIR}/musicxml.xsd
  DEPENDS ${PROJECT_SOURCE_DIR}/musicxml.xsd
)

# Generate musicxml-dtd.{cpp,hpp}
add_executable(dtdbin dtdbin.cpp)
target_compile_features(dtdbin PRIVATE cxx_generalized_initializers)
add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/musicxml-dtd.cpp
         ${PROJECT_BINARY_DIR}/musicxml-dtd.hpp
  COMMAND dtdbin ${PROJECT_SOURCE_DIR}/dtd/
)

set(XSDCXX_FLAGS cxx-tree
    --output-dir ${PROJECT_BINARY_DIR}
    --std c++11 --cxx-suffix .cpp --hxx-suffix .hpp --ixx-suffix .ipp
    --generate-inline --generate-serialization
)

# Generate bindings from XSD files:
foreach(BASENAME xml xlink)
  add_custom_command(
    OUTPUT ${PROJECT_BINARY_DIR}/${BASENAME}.cpp
           ${PROJECT_BINARY_DIR}/${BASENAME}.hpp
           ${PROJECT_BINARY_DIR}/${BASENAME}.ipp
    COMMAND ${XSDCXX_EXECUTABLE} ${XSDCXX_FLAGS} ${PROJECT_SOURCE_DIR}/${BASENAME}.xsd
    DEPENDS ${PROJECT_SOURCE_DIR}/${BASENAME}.xsd
  )
endforeach(BASENAME xml xlink)
add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/musicxml-0.cpp
         ${PROJECT_BINARY_DIR}/musicxml-1.cpp
         ${PROJECT_BINARY_DIR}/musicxml-2.cpp
         ${PROJECT_BINARY_DIR}/musicxml-3.cpp
         ${PROJECT_BINARY_DIR}/musicxml.hpp
         ${PROJECT_BINARY_DIR}/musicxml.ipp
  COMMAND ${XSDCXX_EXECUTABLE} ${XSDCXX_FLAGS} --generate-doxygen
    --namespace-map =musicxml
    --root-element-all
    --custom-type note=/note_base --hxx-epilogue \"\#include <note.hpp>\"
    --custom-type measure1= --hxx-epilogue \"\#include <measure1.hpp>\"
    --custom-type part1= --hxx-epilogue \"\#include <part1.hpp>\"
    --hxx-epilogue \"\#include <utilities.hpp>\"
    --parts 4
    ${PROJECT_SOURCE_DIR}/musicxml.xsd
  DEPENDS ${PROJECT_SOURCE_DIR}/musicxml.xsd
)

set(SOURCES note.cpp measure1.cpp part1.cpp utilities.cpp grammar-input-stream.cpp
    ${PROJECT_BINARY_DIR}/musicxml-0.cpp
    ${PROJECT_BINARY_DIR}/musicxml-1.cpp
    ${PROJECT_BINARY_DIR}/musicxml-2.cpp
    ${PROJECT_BINARY_DIR}/musicxml-3.cpp
    ${PROJECT_BINARY_DIR}/xlink.cpp
    ${PROJECT_BINARY_DIR}/xml.cpp
    ${PROJECT_BINARY_DIR}/musicxml-dtd.cpp
    ${PROJECT_BINARY_DIR}/musicxml-schema.cpp
)
set(HEADERS
    note.hpp part1.hpp measure1.hpp utilities.hpp
    music_data.hpp music_data_serialization_visitor.hpp
)
set(GENERATED_HEADERS
    ${PROJECT_BINARY_DIR}/musicxml.hpp
    ${PROJECT_BINARY_DIR}/xlink.hpp
    ${PROJECT_BINARY_DIR}/xml.hpp
    ${PROJECT_BINARY_DIR}/musicxml.ipp
    ${PROJECT_BINARY_DIR}/xlink.ipp
    ${PROJECT_BINARY_DIR}/xml.ipp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_auto_type cxx_range_for)
target_link_libraries(${PROJECT_NAME} ${XercesC_LIBRARY})
set_target_properties(${PROJECT_NAME} PROPERTIES
  SOVERSION 0
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER "${HEADERS};${GENERATED_HEADERS}"
)
add_library(${PROJECT_NAME}-static STATIC ${SOURCES} ${HEADERS})
target_compile_features(${PROJECT_NAME}-static PRIVATE cxx_auto_type cxx_range_for)
target_link_libraries(${PROJECT_NAME}-static ${XercesC_LIBRARY})
set_target_properties(${PROJECT_NAME}-static PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER "${HEADERS};${GENERATED_HEADERS}"
)
foreach(PROG generate partwise timewise)
  add_executable(${PROG} ${PROG}.cpp)
  target_compile_features(${PROG} PRIVATE cxx_range_for)
  target_link_libraries(${PROG} ${PROJECT_NAME})
endforeach(PROG generate partwise timewise)

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}-static
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
)
install(EXPORT ${PROJECT_NAME} DESTINATION share/${PROJECT_NAME})

set_directory_properties(PROPERTIES
  ADDITIONAL_MAKE_CLEAN_FILES
  "xml.ipp;xlink.ipp;musicxml.ipp;musicxml-0.cpp;musicxml-1.cpp;musicxml-2.cpp;musicxml-3.cpp;xml.cpp;xlink.cpp;musicxml-schema.cpp;musicxml-schema.hpp;musicxml-dtd.cpp;musicxml-dtd.hpp"
)

