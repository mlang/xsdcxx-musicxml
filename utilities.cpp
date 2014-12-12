// Copyright (c) 2014 Mario Lang
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception,
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.

#include "musicxml.hpp"

musicxml::score_timewise::measure_sequence
musicxml::convert(musicxml::score_partwise::part_sequence const &ps) {
  musicxml::score_timewise::measure_sequence ms;

  if (ps.empty()) return ms;

  for (unsigned i = 0; i < ps.front().measure().size(); ++i) {
    const musicxml::score_partwise::part_type::measure_type &pwm =
      ps.front().measure()[i];
    musicxml::score_timewise::measure_type twm{pwm.number()};
    twm.implicit(pwm.implicit());
    twm.non_controlling(pwm.non_controlling());
    twm.width(pwm.width());

    for (const auto &pwp : ps) {
      musicxml::score_timewise::measure_type::part_type twp{pwp.id()};

      twp.music_data(pwp.measure()[i].music_data());

      twm.part().push_back(twp);
    }

    ms.push_back(twm);
  }

  return ms;
}

musicxml::score_partwise::part_sequence
musicxml::convert(musicxml::score_timewise::measure_sequence const &ms) {
  musicxml::score_partwise::part_sequence ps;

  if (ms.empty()) return ps;

  for (unsigned i = 0; i < ms.front().part().size(); ++i) {
    const musicxml::score_timewise::measure_type::part_type &twp =
      ms.front().part()[i];
    musicxml::score_partwise::part_type pwp{twp.id()};

    for (const auto &twm : ms) {
      musicxml::score_partwise::part_type::measure_type pwm{twm.number()};

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

musicxml::score_timewise musicxml::convert(score_partwise const &pw) {
  musicxml::score_timewise tw{pw.part_list()};

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

musicxml::score_partwise musicxml::convert(musicxml::score_timewise const &tw) {
  musicxml::score_partwise pw{tw.part_list()};

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
