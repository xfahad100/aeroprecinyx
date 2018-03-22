#include "helpdialog.h"
#include "ui_helpdialog.h"


HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
}

HelpDialog::~HelpDialog()
{
    delete ui;
}

void HelpDialog::on_CloseButton_clicked()
{
    this->close();
}

void HelpDialog::resizeEvent(QResizeEvent *event)
{
    int h = this->height();
    int w = this->width();
    ui->CloseButton->setGeometry(w-110, h-40, 89, 25);
    ui->webView->setGeometry(7, 7, w-14, h-79);
}

void HelpDialog::setInstallPath(QString path)
{
    installPath = path;
}

void HelpDialog::loadDefaultPage()
{
    defaultURL = QUrl("file://" + installPath + "/docs/en/home.html");
    ui->webView->load(defaultURL);
}
