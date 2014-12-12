#include "musicxml.hpp"
#include <string>
#include <iostream>

#include <xercesc/util/PlatformUtils.hpp>

int main(int argc, char *argv[]) {
  int r = EXIT_SUCCESS;

  // We need to initialize the Xerces-C++ runtime because we
  // are doing the XML-to-DOM parsing ourselves.
  //
  xercesc::XMLPlatformUtils::Initialize();

  try {
    musicxml::serialize(
      std::cout, musicxml::parse<musicxml::score_partwise>(std::cin, "-"));
  } catch (const xml_schema::exception &e) {
    std::cerr << e << std::endl;
    r = EXIT_FAILURE;
  } catch (const std::ios_base::failure &) {
    std::cerr << argv[1] << ": unable to open or read failure" << std::endl;
    r = EXIT_FAILURE;
  }

  xercesc::XMLPlatformUtils::Terminate();
  return r;
}
