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
#include "viewer/viewer.h"
#include "debug/debugtable.h"
#include <plib/js.h>
#include "jsbsim/jsbsim.h"
#include "nav/navigation.h"
#include "autopilot/autopilot.h"


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
    int elevator_axis, aileron_axis, rudder_axis, throttle_axis;
    int aileron_trim_axis, elevator_trim_axis;
    void get_joystick_inputs(void);
    void update_joystick_display(void);

    // JSBSim
    jsbsim* JSBSim;
    QString JSBSimExecutable;
    QStringList JSBSimArgs;
    QString JSBSimWorkingDir;
    QUdpSocket* jsbsimDataSocket;
    QUdpSocket* jsbsimControlsSocket;
    QFile* AircraftConfig;
    QFile* InitFile;

    // Cesium-powered viewer
    Viewer* viewer;
    QUrl localURL, remoteURL;
    bool useLocal;

    void getJSBSimData(void);

    double aileron, elevator, rudder, throttle;
    double pitch_trim, aileron_trim, rudder_trim;
    float  pitch_trim_rate;
    double pitch_trim_pos, aileron_trim_pos, rudder_trim_pos;
    double aoa, beta, pitch, roll, yaw;
    double phi, theta, psi, P, Q, R;
    double altitude, latitude, longitude, GeoLat;
    double GeoAlt, altAGL, altTerrain, ECRadius, CGRadius;
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
    double jsbsim_dt, jsbsimTerminate, jsbsimPause;
    float  ui_rate, output_rate;
    int counter;
    bool firstTime;
    double rEllipse;
    bool FPM_enabled;
    bool FDvisible;
    double ap_elevator_cmd, ap_aileron_cmd;

    quint16 outputPort, inputPort, telnetPort;
    QHostAddress hostAddress;

    navigation* nav;
    autopilot* ap;

    // temporary debug variables
    double intercept;
    double dist;
    double gserror;

public slots:

    void MainLoop(void);
    void processError(QProcess::ProcessError err);
    void StartJSBSim(void);
    void setJSBSimControls(void);

protected:

    void UpdateDisplays(void);
    void UpdateNavigation(void);
    void UpdateAutopilot(void);
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
    void on_helpButton_clicked();
    void on_PauseJSBSimButton_clicked();
    void on_ILSButton_clicked();

    void on_spinBox_2_valueChanged(int arg1);

    void on_FPMButton_toggled(bool checked);

    void on_spinBox_3_valueChanged(int arg1);

    void on_spinBox_4_valueChanged(int arg1);


    void on_FDButton_clicked(bool checked);

    void on_HDGButton_clicked(bool checked);

    void on_AltHoldButton_clicked(bool checked);

    void on_VSButton_clicked(bool checked);

    void on_FLCHButton_clicked(bool checked);

    void on_GSButton_clicked(bool checked);

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
    debugTable* debug;

    void readSettings(void);
    void writeSettings(void);
    void setDebugWatch(void);
    void doDebugCalculations(void);

};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
