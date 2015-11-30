/******************************************************************************/
// License:  GPLv3
// Author:   David Culp, daveculp@cox.net
// Date:     17 Mar 2015
/******************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

////////////////////////////////////////////////////////////////////////////////

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <QKeyEvent>
#include <QProcess>
#include <QMessageBox>
#include <QUdpSocket>
#include <QTextStream>
#include <QVector>
#include <QtNetwork>
#include <QSettings>
#include <QButtonGroup>
#include <QDir>
#include <viewer.h>
#include <plib/js.h>
#include "jsbsim.h"


///////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class MainWindow;
}

////////////////////////////////////////////////////////////////////////////////

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit MainWindow( QWidget * parent = 0 );
    ~MainWindow();
    QWidget * Parent;

    // Path to the qtjsbsim directory, and the ini file.
    QDir    installDir;
    QString getInstallPath(void);
    QString installPath;
    QString iniPath;

    // Joystick
    jsJoystick* joystick;
    int axes;              // the number of axes on this joystick
    float* ax;             // an array of axis values
    int NumButtons;        // the number of buttons on this joystick
    int buttons;           // contains all button values bitwise
    int* b;                // an array of button values
    float* deadband;
    void get_joystick_inputs(void);
    void update_joystick_display(void);

    // JSBSim
    jsbsim* JSBSim;
    QString JSBSimExecutable;
    QStringList JSBSimArgs;
    QString JSBSimWorkingDir;
    QUdpSocket* jsbsimDataSocket;
    QUdpSocket* jsbsimControlsSocket;

    // Cesium-powered viewer
    viewer * Viewer;
    QUrl localURL, remoteURL;
    bool useLocal;

    void getJSBSimData(void);


    double aileron, elevator, rudder, throttle;
    double pitch_trim, aileron_trim, rudder_trim;
    float  pitch_trim_rate;
    double pitch_trim_pos, aileron_trim_pos, rudder_trim_pos;
    double aoa, beta, pitch, roll, yaw;
    double phi, theta, psi, P, Q, R;
    double altitude, latitude, longitude, GeoLat, GeoAlt, altAGL;
    double airspeed, vtrue, gs, climb_rate, mach;
    double vN, vE, vD, vU, vV, vW;
    double thrust[10];
    double n1[10];
    double n2[10];
    double egt[10];
    double ff[10];
    double epr[10];
    double rpm[10];
    double rpm_prop[10];
    double gph[10];
    double power[10];
    double torque[10];
    double prop_angle[10];
    double starter[10];
    double cutoff[10];
    int numEngines;
    double selected_engine;
    double gear_pos, gear_cmd, flap_pos, flap_cmd;
    double speedbrakes_cmd, steering;
    double aileron_pos, elevator_pos, rudder_pos, throttle_pos;
    double speedbrake_pos, simtime;
    double fuel_total, weight, empty_weight, payload, payload_cmd;
    double wind_dir, wind_speed, deltaT;
    double Pt, Qbar, TAT, OAT, Re, g, rho;
    double jsbsim_dt, jsbsimTerminate, pause;
    float  ui_rate, output_rate;
    int counter;

    quint16 outputPort, inputPort, telnetPort;
    QHostAddress hostAddress;

public slots:

    void MainLoop(void);
    void processError(QProcess::ProcessError err);
    void StartJSBSim(void);
    void setJSBSimControls(void);

protected:

    void UpdateDisplays(void);
    void keyPressEvent( QKeyEvent * event);
    double toggle( double* number);
    double step( double* number, int numsteps, int direction);

private slots:

    void on_GearUpButton_clicked();
    void on_GearDownButton_clicked();
    void on_FlapsUpButton_clicked();
    void on_FlapsDownButton_clicked();
    void on_SBUpButton_clicked();
    void on_SBDownButton_clicked();
    void on_payloadWeightEdit_returnPressed();
    void on_windDirEdit_returnPressed();
    void on_windSpeedEdit_returnPressed();
    void on_temperatureEdit_returnPressed();
    void on_ConnectButton_clicked();
    void on_StopJSBSimButton_clicked();
    void on_QuitButton_clicked();

    void on_ViewerButton_clicked();

private:

    Ui::MainWindow * m_ui;
    bool iterating;
    int count;
    bool connected;

    QString line;
    QTime*  UItimer;
    QTime*  timeStamp;
    double framerate;
    double dt;
    QTimer* timer;
    QTimer* UDPOutTimer;
    QSettings* settings;
    QButtonGroup* gearCmd;
    QButtonGroup* sbCmd;

    void readSettings(void);
    void writeSettings(void);
    void pauseJSBSim(double command);

};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
