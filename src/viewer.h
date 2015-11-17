#ifndef VIEWER_H
#define VIEWER_H

#include <QDialog>

namespace Ui {
class viewer;
}

class viewer : public QDialog
{
    Q_OBJECT

public:
    explicit viewer(QWidget *parent = 0);
    ~viewer();

private:
    Ui::viewer *ui;
};

#endif // VIEWER_H
