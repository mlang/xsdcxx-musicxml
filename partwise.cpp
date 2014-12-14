#include "musicxml.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  int r = EXIT_SUCCESS;

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

  return r;
}
