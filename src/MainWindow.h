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

//#include <qwt_plot.h>
//#include <qwt_plot_curve.h>

#include "viewer/viewer.h"
#include "debug/debugtable.h"
#include "jsbsim/jsbsim.h"
#include "nav/navigation.h"
#include "autopilot/autopilot.h"
#include "autopilot/pid.h"
#include "input/joystick.h"
#include "flightgear/outsocket.h"
#include "math.h"

//#include <qwt_plot.h>
//#include <qwt_plot_curve.h>

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
    void get_joystick_inputs(void);

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

    double pitcharr[100];
    double time[100];

    double aileron, elevator, rudder, throttle;
    double aileronSlider, elevatorSlider, rudderSlider;
    double pitch_trim, aileron_trim, rudder_trim;
    float  pitch_trim_rate;
    double pitch_trim_pos, aileron_trim_pos, rudder_trim_pos;
    double aoa, beta, pitch, roll, yaw;
    double phi, theta, psi, P, Q, R;
    double altitude, latitude, longitude, GeoLat;
    double GeoAlt, altAGL, altTerrain, ECRadius, CGRadius;
    double pix_airspeed, airspeed, vtrue, gs, climb_rate, mach;
    double vN, vE, vD, vU, vV, vW;
    float pixpitch, pixroll, pixyaw;
    double pixalt, pixlat, pixlon;
    double pixaccx, pixaccy, pixaccz;
    double dimu, dold;
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
    float  ui_rate, output_rate, fg_rate;
    int counter;
    bool firstTime;
    double rEllipse;
    bool FPM_enabled;
    bool FDvisible;
    bool senswitch;
    int desired_vs;
    float armed_;
    double ap_elevator_cmd, ap_aileron_cmd, ap_rudder_cmd;
    float battper;
    double des_alt;
    double des_hdg;
    double currentgs;
    bool GSbool=0;
    double elevnorm;

    quint16 outputPort, inputPort, telnetPort;
    QHostAddress hostAddress;

    navigation* nav;
    autopilot* ap;
    PIDImpl* pid;

    // temporary debug variables
    double intercept;
    double dist,dist2;
    double gserror;

public slots:

    void MainLoop(void);
    void processError(QProcess::ProcessError err);
    void StartJSBSim(void);
    void setJSBSimControls(void);
    void sendFlightGearData(void);

protected:

    void UpdateDisplays(void);
    void distancefromIMU(void);
    void UpdateNavigation(void);
    void UpdateAutopilot(void);
    void UpdateFlightGear(void);
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
    void on_FGButton_clicked(bool checked);

    void on_M_elevator_valueChanged(int value);

    void on_M_aileron_valueChanged(int value);

    void on_M_rudder_valueChanged(int value);
    void on_APButton_clicked(bool checked);

    void on_arm_clicked(bool checked);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_doubleSpinBox_3_valueChanged(double arg1);

    void on_doubleSpinBox_4_valueChanged(double arg1);

    void on_sensors_clicked(bool checked);

    void on_progressBar_valueChanged(int value);

    //void on_qwtPlot_itemAttached(QwtPlotItem *plotItem, bool on);

    void on_Mthrottle_valueChanged(int value);

    void on_wingLevel_clicked(bool checked);

    void on_spinBox_5_valueChanged(int arg1);

    void on_Trim_pressed();

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
    QTimer* FGTimer;
    QSettings* settings;
    QButtonGroup* gearCmd;
    QButtonGroup* sbCmd;
    debugTable* debug;
    Joystick* joystick;
    OutSocket* FGSocket;
    bool ConnectToFG;
    bool ptrue;

    void readSettings(void);
    void writeSettings(void);
    void setDebugWatch(void);
    void doDebugCalculations(void);

};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
