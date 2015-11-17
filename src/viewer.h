#ifndef VIEWER_H
#define VIEWER_H

#include <QDialog>
#include <QWebFrame>


// The aircraft class contains the data that is made available to the javascript
// environment in the QWebView object.  This is used to update the camera position.
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
class viewer;
}

class viewer : public QDialog
{
    Q_OBJECT

public:
    explicit viewer(QWidget *parent = 0);
    ~viewer();
    QWebFrame* frame;
    void load(QUrl url);
    void shareAircraftObject();
    void updateData(double lat, double lon, double alt,
                    double pitch, double roll, double yaw);
    aircraft* Aircraft;

private:
    Ui::viewer *ui;

};

#endif // VIEWER_H
