/*
  * Copyright (C) 2011 Cameron White
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
  
#ifndef CHORDTEXTPAINTER_H
#define CHORDTEXTPAINTER_H

#include "painterbase.h"

#include <QFont>
#include <QStaticText>
#include <memory>

class ChordText;

class ChordTextPainter : public PainterBase
{
public:
    ChordTextPainter(std::shared_ptr<const ChordText> chordText);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void init();

    std::shared_ptr<const ChordText> chordText;
    static QFont displayFont;
    QStaticText displayText;
};

#endif // CHORDTEXTPAINTER_H
