# - Try to find XSD
#
# This module defines
# XSDCXX_INCLUDE_DIR, where to find elements.hxx, etc.
# XSDCXX_EXECUTABLE, the exe file
# XSDCXX_FOUND, If false, XSDCXX was not found.

find_path(XSDCXX_INCLUDE_DIR xsd/cxx/parser/elements.hxx
  PATHS $ENV{XSDDIR} /usr/local /usr
  PATH_SUFFIXES include libxsd xsd
  NO_CMAKE_FIND_ROOT_PATH
)

find_program(XSDCXX_EXECUTABLE
  NAMES xsd xsdcxx
  PATHS $ENV{XSDDIR}/bin /usr/local/bin /usr/bin
  NO_SYSTEM_ENVIRONMENT_PATH
)

if(XSDCXX_INCLUDE_DIR)
  if(XSDCXX_EXECUTABLE)
    find_path(XERCESC_INCLUDE_DIR NAMES xercesc/util/XercesVersion.hpp)
    find_library(XERCESC_LIBRARY NAMES xerces-c xerces-c_3)
  endif(XSDCXX_EXECUTABLE)
endif(XSDCXX_INCLUDE_DIR)

mark_as_advanced(
  XSDCXX_INCLUDE_DIR XSDCXX_EXECUTABLE XERCESC_INCLUDE_DIR XERCESC_LIBRARY
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(XSDCXX
  REQUIRED_VARS XSDCXX_EXECUTABLE XSDCXX_INCLUDE_DIR
                XERCESC_INCLUDE_DIR XERCESC_LIBRARY
)
