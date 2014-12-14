CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)
project(xsdcxx-musicxml CXX)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
add_definitions(-std=c++11)

find_package(XSDCXX REQUIRED)
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
    --root-element-all
    --custom-type note=/note_base --hxx-epilogue '\#include \"note.hpp\"'
    --custom-type measure1= --hxx-epilogue '\#include \"measure1.hpp\"'
    --custom-type part1= --hxx-epilogue '\#include \"part1.hpp\"'
    --hxx-epilogue '\#include \"utilities.hpp\"'
    --parts 4
    musicxml.xsd
  DEPENDS ${CMAKE_SOURCE_DIR}/musicxml.xsd
)

set(SCHEMAS musicxml.xsd xml.xsd xlink.xsd)
set(SOURCES
    note.cpp measure1.cpp part1.cpp utilities.cpp
    musicxml-0.cpp musicxml-1.cpp musicxml-2.cpp musicxml-3.cpp
    xlink.cpp xml.cpp
)
set(HEADERS
    musicxml.hpp
    note.hpp part1.hpp measure1.hpp utilities.hpp
    xml.hpp xlink.hpp
    musicxml.ipp xml.ipp xlink.ipp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${XERCESC_LIBRARY})
set_target_properties(${PROJECT_NAME} PROPERTIES
  SOVERSION 0
  VERSION 0.1
  PUBLIC_HEADER "${HEADERS}"
  RESOURCE "${SCHEMAS}"
)
add_library(${PROJECT_NAME}-static STATIC ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME}-static ${XERCESC_LIBRARY})
set_target_properties(${PROJECT_NAME}-static PROPERTIES
  VERSION 0.1
  PUBLIC_HEADER "${HEADERS}"
  RESOURCE "${SCHEMAS}"
)
foreach(PROG generate partwise timewise)
  add_executable(${PROG} ${PROG}.cpp)
  target_link_libraries(${PROG} ${PROJECT_NAME})
endforeach(PROG generate partwise timewise)

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}-static
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
  RESOURCE DESTINATION share/${PROJECT_NAME}
)
install(EXPORT ${PROJECT_NAME} DESTINATION share/${PROJECT_NAME})
