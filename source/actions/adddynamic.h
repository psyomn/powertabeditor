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
  
#ifndef ADDDYNAMIC_H
#define ADDDYNAMIC_H

#include <QUndoCommand>
#include <memory>

class Score;
class Dynamic;

class AddDynamic : public QUndoCommand
{
public:
    AddDynamic(Score* score, std::shared_ptr<Dynamic> dynamic);

    void redo();
    void undo();

private:
    Score* score;
    std::shared_ptr<Dynamic> dynamic;
};

#endif // ADDDYNAMIC_H
