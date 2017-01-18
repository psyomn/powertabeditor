/*
 * Copyright (C) 2016 Simon Symeonidis
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "textexporter.h"
#include <score/score.h>
#include <formats/fileformat.h>

// TODO remove stuff when done
#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stringstream;

TextExporter::TextExporter()
    : FileFormatExporter(FileFormat("Text Tablature", {"txt"}))
{}

void TextExporter::writeStaff(Staff const & staff)
{
  int stringCount = staff.getStringCount();
  vector<stringstream> tab(stringCount);

  /* we should just export the staves, as they are in the tablature. */
  for (auto &voice : staff.getVoices()) {
    for (auto &pos : voice.getPositions()) {
      size_t noteIndex = 0;

      for (auto &note : pos.getNotes()) {
        tab[noteIndex] << note.getFretNumber() << "-";
        noteIndex++;
      }

      for (size_t n = noteIndex; n < stringCount; ++n) {
        /* fill in any remaining string that doesn't have a note */
        tab[n] << "---";
      }

    }

    for (auto &st : tab) {
      cout << st.str() << endl;
    }
    cout << endl;
  }
}

void TextExporter::writeSystem(System const & sys)
{
    for (auto &staff : sys.getStaves()) {
      writeStaff(staff);
    }
}


void TextExporter::save(const std::string &filename, const Score &score)
{
    cout << "Will export to file: " << filename << endl;

    SongData info = score.getScoreInfo().getSongData();

    cout << "title : " << info.getTitle() << endl;
    cout << "artist : " << info.getArtist() << endl;


    for (auto &e : score.getInstruments()) {
      cout << "Instrument: " << e.getDescription() << endl;
    }

    for (auto &sys : score.getSystems()) {
      writeSystem(sys);
    }
}
