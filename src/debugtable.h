#ifndef DEBUGTABLE_H
#define DEBUGTABLE_H

#include <QWidget>
#include <QVector>
#include <QTableWidgetItem>

namespace Ui {
class debugTable;
}


class debugTable : public QWidget
{
    Q_OBJECT

public:
    explicit debugTable(QWidget *parent = 0);
    ~debugTable();
    void addItem(QString name, double* var);
    void update();

private:
    Ui::debugTable *ui;

    QVector<double*> vItems;
};

#endif // DEBUGTABLE_H
