#include "musicxml.hpp"
#include <string>
#include <fstream>
#include <iostream>

#include <xercesc/util/PlatformUtils.hpp>

using namespace std;

int main (int argc, char* argv[]) {
  int r = EXIT_SUCCESS;

  // We need to initialize the Xerces-C++ runtime because we
  // are doing the XML-to-DOM parsing ourselves.
  //
  xercesc::XMLPlatformUtils::Initialize ();

  try
  {
    musicxml::score_timewise_(std::cout, musicxml::document<musicxml::score_timewise> (std::cin, "-"));
  } catch (const xml_schema::exception& e) {
    cerr << e << endl;
    r = EXIT_FAILURE;
  } catch (const std::ios_base::failure&) {
    cerr << argv[1] << ": unable to open or read failure" << endl;
    r = EXIT_FAILURE;
  }

  xercesc::XMLPlatformUtils::Terminate ();
  return r;
}
