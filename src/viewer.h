/******************************************************************************/
// License:  GPLv3
// Author:   David Culp, daveculp@cox.net
// Date:     15 Dec 2015
/******************************************************************************/
#ifndef VIEWER_H
#define VIEWER_H

#include <QDialog>
#include <QWebFrame>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>


////////////////////////////////////////////////////////////////////////////////
// The aircraft class contains the data that is made available to the javascript
// environment in the QWebView object.  This is used to update the camera position.
//
class aircraft : public QObject
{
    Q_OBJECT

public:
    aircraft(QObject* parent=0) : QObject(parent) {
        a_lat=a_lon=a_alt=a_pitch=a_roll=a_hdg_true=0;
    }

    Q_INVOKABLE inline double lat()      {return a_lat;}
    Q_INVOKABLE inline double lon()      {return a_lon;}
    Q_INVOKABLE inline double alt()      {return a_alt;}
    Q_INVOKABLE inline double pitch()    {return a_pitch;}
    Q_INVOKABLE inline double roll()     {return a_roll;}
    Q_INVOKABLE inline double hdg_true() {return a_hdg_true;}
    inline void setLat(double lat)          { a_lat = lat; }
    inline void setLon(double lon)          { a_lon = lon; }
    inline void setAlt(double alt)          { a_alt = alt; }
    inline void setPitch(double pitch)      { a_pitch = pitch; }
    inline void setRoll(double roll)        { a_roll = roll; }
    inline void setHdgTrue(double hdg_true) { a_hdg_true = hdg_true; }

private:
    double a_lat, a_lon, a_alt, a_pitch, a_roll, a_hdg_true;
};



namespace Ui {
class Viewer;
}

class Viewer : public QDialog
{
    Q_OBJECT

public:
    explicit Viewer(QWidget *parent = 0);
    ~Viewer();
    QWebFrame* frame;
    void load(QUrl url);
    void shareAircraftObject();
    void updateData(double lat,    // geocentric latitude in degrees
                    double lon,    // geocentric longitude in degrees
                    double alt,    // altitude MSL in feet
                    double pitch,  // degrees
                    double roll,   // degrees
                    double yaw);   // degrees
    aircraft* Aircraft;

private slots:
    void on_CloseButton_clicked();

    void on_Button5_clicked();

private:
    Ui::Viewer *ui;

    // HUD
    QGraphicsScene* hudScene;
    bool hudVisible;
    QPixmap* hudBasePixmap;

};

#endif // VIEWER_H
