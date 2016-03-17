// Generate an embedded catalog of MusicXML DTDs.

#include <boost/algorithm/string/replace.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <utility>

static std::pair<std::string, std::string> dtds[] = {
{ "ISO 8879:1986//ENTITIES Added Latin 1//EN//XML", "isolat1.ent" },
{ "ISO 8879:1986//ENTITIES Added Latin 2//EN//XML", "isolat2.ent" },
{ "-//Recordare//DTD MusicXML 1.0 Partwise//EN", "1.0/partwise.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 1.0 Common//EN", "1.0/common.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 1.0 Identity//EN", "1.0/identity.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 1.0 Attributes//EN", "1.0/attributes.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 1.0 Link//EN", "1.0/link.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 1.0 Note//EN", "1.0/note.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 1.0 Barline//EN", "1.0/barline.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 1.0 Direction//EN", "1.0/direction.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 1.0 Score//EN", "1.0/score.dtd" },
{ "-//Recordare//DTD MusicXML 1.1 Partwise//EN", "1.1/partwise.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 1.1 Common//EN", "1.1/common.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 1.1 Layout//EN", "1.1/layout.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 1.1 Identity//EN", "1.1/identity.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 1.1 Attributes//EN", "1.1/attributes.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 1.1 Link//EN", "1.1/link.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 1.1 Note//EN", "1.1/note.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 1.1 Barline//EN", "1.1/barline.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 1.1 Direction//EN", "1.1/direction.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 1.1 Score//EN", "1.1/score.dtd" },
{ "-//Recordare//DTD MusicXML 2.0 Partwise//EN", "2.0/partwise.dtd" },
{ "-//Recordare//DTD MusicXML 2.0 Timewise//EN", "2.0/timewise.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 2.0 Common//EN", "2.0/common.mod" },
{ "-//Recordare//ELEMENTS MusicXML 2.0 Layout//EN", "2.0/layout.mod" },
{ "-//Recordare//ELEMENTS MusicXML 2.0 Identity//EN", "2.0/identity.mod" },
{ "-//Recordare//ELEMENTS MusicXML 2.0 Attributes//EN", "2.0/attributes.mod" },
{ "-//Recordare//ELEMENTS MusicXML 2.0 Link//EN", "2.0/link.mod" },
{ "-//Recordare//ELEMENTS MusicXML 2.0 Note//EN", "2.0/note.mod" },
{ "-//Recordare//ELEMENTS MusicXML 2.0 Barline//EN", "2.0/barline.mod" },
{ "-//Recordare//ELEMENTS MusicXML 2.0 Direction//EN", "2.0/direction.mod" },
{ "-//Recordare//ELEMENTS MusicXML 2.0 Score//EN", "2.0/score.mod" },
{ "-//Recordare//DTD MusicXML 3.0 Partwise//EN", "3.0/partwise.dtd" },
{ "-//Recordare//DTD MusicXML 3.0 Timewise//EN", "3.0/timewise.dtd" },
{ "-//Recordare//ELEMENTS MusicXML 3.0 Common//EN", "3.0/common.mod" },
{ "-//Recordare//ELEMENTS MusicXML 3.0 Layout//EN", "3.0/layout.mod" },
{ "-//Recordare//ELEMENTS MusicXML 3.0 Identity//EN", "3.0/identity.mod" },
{ "-//Recordare//ELEMENTS MusicXML 3.0 Attributes//EN", "3.0/attributes.mod" },
{ "-//Recordare//ELEMENTS MusicXML 3.0 Link//EN", "3.0/link.mod" },
{ "-//Recordare//ELEMENTS MusicXML 3.0 Note//EN", "3.0/note.mod" },
{ "-//Recordare//ELEMENTS MusicXML 3.0 Barline//EN", "3.0/barline.mod" },
{ "-//Recordare//ELEMENTS MusicXML 3.0 Direction//EN", "3.0/direction.mod" },
{ "-//Recordare//ELEMENTS MusicXML 3.0 Score//EN", "3.0/score.mod" },
};

static std::string cpp_identifier(std::string string) {
  boost::algorithm::replace_all(string, ".", "_");
  boost::algorithm::replace_all(string, "/", "_");
  boost::algorithm::replace_all(string, "-", "_");

  return "dtd_" + string;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: dtdbin PATH_TO_DTD_FILES" << std::endl;
    return EXIT_FAILURE;
  }

  std::ofstream cpp("musicxml-dtd.cpp"), hpp("musicxml-dtd.hpp");

  hpp << "#ifndef MUSICXML_DTD_HPP" << std::endl
      << "#define MUSICXML_DTD_HPP" << std::endl
      << "#include <map>" << std::endl
      << "#include <string>" << std::endl
      << "#include <xercesc/util/XercesDefs.hpp>" << std::endl
      << std::endl
      << "namespace musicxml {" << std::endl
      << std::endl
      << "extern "
         "std::map<std::string, std::pair<XMLByte const *, XMLSize_t>> const "
         "dtd;" << std::endl
      << std::endl
      << "}" << std::endl
      << std::endl
      << "#endif" << std::endl;

  cpp << "#include \"musicxml-dtd.hpp\"" << std::endl;
  cpp << std::endl;
  for (auto &&pair: dtds) {
    std::string path(argv[1]);
    path += pair.second;
    std::ifstream dtd(path);
    if (!dtd.good()) {
      std::cerr << "DTD file " << path << " not found." << std::endl;
      return EXIT_FAILURE;
    }
    std::istreambuf_iterator<char> dtd_begin(dtd.rdbuf()), dtd_end;
    std::string dtd_string(dtd_begin, dtd_end);
    cpp << "static XMLByte const " << cpp_identifier(pair.second)
        << "[" << std::dec << dtd_string.length() << "UL] = {";
    for (unsigned i = 0; i < dtd_string.length(); ++i) {
      if ((i % 13) == 0) cpp << std::endl << "  ";
      cpp << "0X";
      cpp.width(2); cpp.fill('0');
      cpp << std::hex << int(static_cast<unsigned char>(dtd_string[i]));
      if (i < dtd_string.length() - 1) cpp << ", ";
    }
    cpp << std::endl << "};" << std::endl << std::endl;
  }

  cpp << "std::map<std::string, std::pair<XMLByte const *, XMLSize_t>> const "
         "musicxml::dtd = {" << std::endl;
  for (auto &&pair: dtds) {
    std::string path(argv[1]);
    path += pair.second;
    cpp << "  { \"" << pair.first << "\"," << std::endl
        << "    std::make_pair(&" << cpp_identifier(pair.second) << "[0], sizeof("
        << cpp_identifier(pair.second) << "))" << std::endl << "  },"
        << std::endl;
  }
  cpp << "};" << std::endl;

  return EXIT_SUCCESS;
}

