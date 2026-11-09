/******************************************************************************/
// License:  GPLv3
// Author:   David Culp, daveculp@cox.net
// Date:     15 Dec 2015
/******************************************************************************/

#include "debugtable.h"
#include "ui_debugtable.h"
#include <QHeaderView>

debugTable::debugTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::debugTable)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->horizontalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

debugTable::~debugTable()
{
    vItems.clear();
    delete ui;
}

void debugTable::addItem(QString name, double* var)
{
   vItems.append(var);
   int rowNumber = ui->tableWidget->rowCount();
   ui->tableWidget->insertRow(rowNumber);
   ui->tableWidget->setItem(rowNumber, 0, new QTableWidgetItem(name));
   ui->tableWidget->setItem(rowNumber, 1, new QTableWidgetItem(QString::number( *var, 'f', 8)));
}

void debugTable::update()
{
   for (int i=0; i<vItems.size(); i++) {
      QTableWidgetItem* item = ui->tableWidget->item(i,1);
      item->setText(QString::number( *vItems[i], 'f', 8));
   }
}

