#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include <QUrl>
#include <QDir>

namespace Ui {
class HelpDialog;
}

class HelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDialog(QWidget *parent = 0);
    ~HelpDialog();
    void resizeEvent(QResizeEvent *event);
    void setInstallPath(QString path);
    void loadDefaultPage(void);

private slots:
    void on_CloseButton_clicked();

private:
    Ui::HelpDialog *ui;
    QString installPath;
    QUrl defaultURL;
};

#endif // HELPDIALOG_H
