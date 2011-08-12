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
  
#ifndef TUNINGDIALOG_H
#define TUNINGDIALOG_H

#include <QDialog>

#include <vector>
#include <memory>

class Tuning;
class QComboBox;
class QLineEdit;
class QCheckBox;
class QSpinBox;
class Guitar;

class TuningDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TuningDialog(std::shared_ptr<Guitar> guitar, QWidget *parent = 0);

public slots:
    void accept();

private slots:
    void toggleSharps(bool usesSharps);
    void updateEnabledStrings(int numStrings);

private:
    std::shared_ptr<Guitar> guitar;
    const Tuning& tuning;
    
    QStringList noteNames;
    
    QLineEdit* tuningNameEditor;
    QCheckBox* usesSharpsSelector;
    QSpinBox* numStringsSelector;
    QSpinBox* notationOffsetSelector;

    std::vector<QComboBox*> stringSelectors;

    void initStringSelectors();
    void generateNoteNames(bool usesSharps);
};

#endif // TUNINGDIALOG_H
