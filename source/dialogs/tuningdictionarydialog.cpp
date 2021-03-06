/*
  * Copyright (C) 2012 Cameron White
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

#include "tuningdictionarydialog.h"
#include "ui_tuningdictionarydialog.h"

#include <app/tuningdictionary.h>
#include <dialogs/tuningdialog.h>
#include <util/tostring.h>

Q_DECLARE_METATYPE(Tuning *)

TuningDictionaryDialog::TuningDictionaryDialog(QWidget *parent,
                                               TuningDictionary &dictionary)
    : QDialog(parent),
      ui(new Ui::TuningDictionaryDialog),
      myDictionary(dictionary)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    ui->tuningsList->setColumnCount(2);
    ui->tuningsList->setHeaderLabels(
        { tr("Name"), tr("Tuning (Low to High)") });
    ui->tuningsList->header()->sectionResizeMode(QHeaderView::ResizeToContents);

    for (int i = Tuning::MIN_STRING_COUNT; i <= Tuning::MAX_STRING_COUNT; ++i)
        ui->stringsComboBox->addItem(QString::number(i), i);

    connect(ui->stringsComboBox,
            qOverload<int>(&QComboBox::currentIndexChanged), this,
            &TuningDictionaryDialog::onNumStringsChanged);
    connect(ui->tuningsList, &QTreeWidget::currentItemChanged, this,
            &TuningDictionaryDialog::onCurrentTuningChanged);
    connect(ui->newTuningButton, &QPushButton::clicked, this,
            &TuningDictionaryDialog::onNewTuning);
    connect(ui->editTuningButton, &QPushButton::clicked, this,
            &TuningDictionaryDialog::onEditTuning);
    connect(ui->deleteTuningButton, &QPushButton::clicked, this,
            &TuningDictionaryDialog::onDeleteTuning);

    // Select the "6 Strings" option by default.
    ui->stringsComboBox->setCurrentIndex(3);
}

TuningDictionaryDialog::~TuningDictionaryDialog()
{
    delete ui;
}

void TuningDictionaryDialog::onNumStringsChanged(int index)
{
    const int numStrings = ui->stringsComboBox->itemData(index).toInt();

    ui->tuningsList->clear();

    std::vector<Tuning *> tunings;
    myDictionary.findTunings(numStrings, tunings);

    for (Tuning *tuning : tunings)
    {
        auto item = new QTreeWidgetItem(
            QStringList({ QString::fromStdString(tuning->getName()),
                          QString::fromStdString(Util::toString(*tuning)) }));

        item->setData(0, Qt::UserRole, QVariant::fromValue(tuning));
        ui->tuningsList->addTopLevelItem(item);
    }
}

void TuningDictionaryDialog::onNewTuning()
{
    Tuning tuning;
    TuningDialog dialog(this, tuning, myDictionary);

    if (dialog.exec() == QDialog::Accepted)
    {
        myDictionary.addTuning(dialog.getTuning());
        onTuningModified();
    }
}

void TuningDictionaryDialog::onDeleteTuning()
{
    myDictionary.removeTuning(*selectedTuning());
    onTuningModified();
}

void TuningDictionaryDialog::onCurrentTuningChanged(QTreeWidgetItem *current,
                                                    QTreeWidgetItem *)
{
    ui->deleteTuningButton->setEnabled(current != nullptr);
    ui->editTuningButton->setEnabled(current != nullptr);
}

void TuningDictionaryDialog::onEditTuning()
{
    Tuning *tuning = selectedTuning();
    TuningDialog dialog(this, *tuning, myDictionary);

    if (dialog.exec() == QDialog::Accepted)
    {
        *tuning = dialog.getTuning();
        onTuningModified();
    }
}

void TuningDictionaryDialog::onTuningModified()
{
    onNumStringsChanged(ui->stringsComboBox->currentIndex());
}

Tuning *TuningDictionaryDialog::selectedTuning() const
{
    return ui->tuningsList->currentItem()->data(
                0, Qt::UserRole).value<Tuning *>();
}
