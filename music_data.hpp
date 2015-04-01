#include <boost/variant/variant.hpp>

namespace musicxml {

  using music_data = boost::variant<
    ::musicxml::attributes, ::musicxml::note, ::musicxml::backup,
    ::musicxml::forward, ::musicxml::direction, ::musicxml::harmony,
    ::musicxml::figured_bass, ::musicxml::print, ::musicxml::sound,
    ::musicxml::barline, ::musicxml::grouping, ::musicxml::link,
    ::musicxml::bookmark>;

}

