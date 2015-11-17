#include "viewer.h"
#include "ui_viewer.h"

viewer::viewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewer)
{
    ui->setupUi(this);
    Aircraft = new aircraft(this);
    frame = ui->webView->page()->mainFrame();
    connect(frame, &QWebFrame::javaScriptWindowObjectCleared, this, &viewer::shareAircraftObject);
}

viewer::~viewer()
{
    delete ui;
    delete Aircraft;
}

void viewer::load(QUrl url)
{
    ui->webView->load(url);
}

void viewer::updateData(double lat, double lon, double alt,
                        double pitch, double roll, double yaw)
{
    Aircraft->setLat(lat);
    Aircraft->setLon(lon);
    Aircraft->setAlt(alt);
    Aircraft->setPitch(pitch);
    Aircraft->setRoll(roll);
    Aircraft->setHdgTrue(yaw);
}

void viewer::shareAircraftObject()
{
    frame->addToJavaScriptWindowObject("aircraft", Aircraft);
}
