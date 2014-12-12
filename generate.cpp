#include "musicxml.hpp"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main (int argc, char* argv[]) {
  int r = EXIT_SUCCESS;

  try
  {
    using score_type = musicxml::score_partwise;
    using part_type = score_type::part_type;
    using measure_type = part_type::measure_type;
    musicxml::part_list part_list;
    part_list.score_part().push_back({"Part-1", "P1"});
    score_type score(part_list);
    score.version("3.0");
    score.part().push_back({"P1"});
    part_type &part = score.part().back();

    part.measure().push_back({"1"});
    measure_type &measure = part.measure().back();
    {
      musicxml::attributes attributes {};
      attributes.divisions(768);
      attributes.staves(1);
      measure.variant().push_back(attributes);
    }
    {
      musicxml::note note {
        ::musicxml::pitch{musicxml::step::C, 4},
        ::musicxml::positive_divisions{768*4}
      };
      note.type(musicxml::note_type_value::whole);
      note.voice("1");
      measure.variant().push_back(note);
    }
    measure.variant().push_back(musicxml::backup{768*4});
    {
      musicxml::note note {
        ::musicxml::pitch{musicxml::step::G, 4},
        ::musicxml::positive_divisions{768*4}
      };
      note.type(musicxml::note_type_value::whole);
      note.voice("2");
      measure.variant().push_back(note);
    }

    musicxml::score_partwise_(std::cout, score);
  } catch (const xml_schema::exception& e) {
    cerr << e << endl;
    r = EXIT_FAILURE;
  }

  return r;
}
