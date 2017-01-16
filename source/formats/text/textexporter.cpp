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
#include <iostream>
#include <string>
#include <sstream>

TextExporter::TextExporter()
    : FileFormatExporter(FileFormat("Text Tablature", {"txt"}))
{}

void TextExporter::save(const std::string &filename, const Score &score)
{
  using std::cout;
  using std::endl;

  cout << "Will export to file: " << filename << endl;

  SongData info = score.getScoreInfo().getSongData();

  cout << "title : " << info.getTitle() << endl;
  cout << "artist : " << info.getArtist() << endl;


  for (auto &e : score.getInstruments()) {
    cout << "Instrument: " << e.getDescription() << endl;
  }

  for (auto &sys : score.getSystems()) {
    cout << "Amount of staves: " << endl;
    for (auto &stave : sys.getStaves()) {

      for (auto &voice : stave.getVoices()) {

        for (auto &pos : voice.getPositions()) {
          for (auto &note : pos.getNotes()) {
            cout <<  note.getFretNumber() << " ";
          }

          cout << endl;
        }
      }
    }
  }
}
