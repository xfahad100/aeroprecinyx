/******************************************************************************/
// License:  GPLv3
// Author:   David Culp, daveculp@cox.net
// Date:     15 Dec 2015
/******************************************************************************/

#include "viewer.h"
#include "ui_viewer.h"

Viewer::Viewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Viewer)
{
    ui->setupUi(this);
    ui->CloseButton->setEnabled(true);
    Aircraft = new aircraft(this);
    frame = ui->webView->page()->mainFrame();

    // can't share the C++ object until the javascript environment is ready for it
    connect(frame, &QWebFrame::javaScriptWindowObjectCleared, this, &Viewer::shareAircraftObject);

    // HUD
    hudScene = new QGraphicsScene;
    hudBasePixmap = new QPixmap;
    hudVisible = false;
    hudBasePixmap->load(":/images/hud/hud_base.png");
    hudScene->addPixmap(*hudBasePixmap);
    ui->HUDView->setStyleSheet("background-color : rgba(0,0,0,0)");
    ui->HUDView->setScene(hudScene);

}

Viewer::~Viewer()
{
    delete ui;
    delete Aircraft;
    delete hudScene;
    delete hudBasePixmap;
}

void Viewer::load(QUrl url)
{
    ui->webView->load(url);
}

void Viewer::updateData(double lat, double lon, double alt,
                        double pitch, double roll, double yaw)
{
    // this data is shared to the Cesium viewer
    Aircraft->setLat(lat);
    Aircraft->setLon(lon);
    Aircraft->setAlt(alt);
    Aircraft->setPitch(pitch);
    Aircraft->setRoll(roll);
    Aircraft->setHdgTrue(yaw);

    // Heads Up Display
    if (hudVisible) {
       ui->HUDView->show();
    } else {
       ui->HUDView->hide();
    }

}

void Viewer::shareAircraftObject()
{
    frame->addToJavaScriptWindowObject("aircraft", Aircraft);
}

void Viewer::on_CloseButton_clicked()
{
    this->close();
}

// Toggle the HUD on/off
void Viewer::on_Button5_clicked()
{
    hudVisible = !hudVisible;
}
