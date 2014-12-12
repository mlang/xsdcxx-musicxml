#include "musicxml.hpp"

namespace musicxml {

::musicxml::score_timewise::measure_sequence
convert(::musicxml::score_partwise::part_sequence const &ps) {
  score_timewise::measure_sequence ms;

  if (ps.empty()) return ms;

  for (unsigned i = 0; i < ps.front().measure().size(); ++i) {
    const score_partwise::part_type::measure_type &pwm =
      ps.front().measure()[i];
    score_timewise::measure_type twm{pwm.number()};
    twm.implicit(pwm.implicit());
    twm.non_controlling(pwm.non_controlling());
    twm.width(pwm.width());

    for (const auto &pwp : ps) {
      score_timewise::measure_type::part_type twp{pwp.id()};

      twp.music_data(pwp.measure()[i].music_data());

      twm.part().push_back(twp);
    }

    ms.push_back(twm);
  }

  return ms;
}

::musicxml::score_partwise::part_sequence
convert(::musicxml::score_timewise::measure_sequence const &ms) {
  score_partwise::part_sequence ps;

  if (ms.empty()) return ps;

  for (unsigned i = 0; i < ms.front().part().size(); ++i) {
    const score_timewise::measure_type::part_type &twp = ms.front().part()[i];
    score_partwise::part_type pwp{twp.id()};

    for (const auto &twm : ms) {
      score_partwise::part_type::measure_type pwm{twm.number()};

      pwm.implicit(twm.implicit());
      pwm.non_controlling(twm.non_controlling());
      pwm.width(twm.width());

      pwm.music_data(twm.part()[i].music_data());

      pwp.measure().push_back(pwm);
    }

    ps.push_back(pwp);
  }

  return ps;
}

score_timewise convert(score_partwise const &pw) {
  score_timewise tw{pw.part_list()};
  tw.work(pw.work());
  tw.movement_number(pw.movement_number());
  tw.movement_title(pw.movement_title());
  tw.identification(pw.identification());
  tw.defaults(pw.defaults());
  tw.credit(pw.credit());
  tw.version(pw.version());

  tw.measure(convert(pw.part()));

  return tw;
}

score_partwise convert(score_timewise const &tw) {
  score_partwise pw{tw.part_list()};
  pw.work(tw.work());
  pw.movement_number(tw.movement_number());
  pw.movement_title(tw.movement_title());
  pw.identification(tw.identification());
  pw.defaults(tw.defaults());
  pw.credit(tw.credit());
  pw.version(tw.version());

  pw.part(convert(tw.measure()));

  return pw;
}

} // namespace musicxml
