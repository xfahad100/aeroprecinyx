/***************************************************************************//**
 * @file example/MainWindow.h
 * @author  Marek M. Cel <marekcel@mscsim.org>
 *
 * @section LICENSE
 *
 * Copyright (C) 2013 Marek M. Cel
 *
 * This file is part of QFlightInstruments. You can redistribute and modify it
 * under the terms of GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Further information about the GNU General Public License can also be found
 * on the world wide web at http://www.gnu.org.
 *
 * ---
 *
 * Copyright (C) 2013 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/
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
#include <plib/js.h>
#include <jsbsim.h>
#include <JSBSim/FGFDMExec.h>
#include <JSBSim/input_output/net_fdm.hxx>
#include <JSBSim/models/FGPropulsion.h>
#include <JSBSim/models/FGFCS.h>
#include <JSBSim/models/FGAuxiliary.h>
#include <JSBSim/models/FGPropagate.h>
#include <JSBSim/models/FGPropulsion.h>
#include <JSBSim/models/propulsion/FGEngine.h>
#include <JSBSim/models/propulsion/FGPiston.h>
#include <JSBSim/models/propulsion/FGTurbine.h>
#include <JSBSim/models/propulsion/FGPropeller.h>
#include <JSBSim/models/propulsion/FGThruster.h>
#include <JSBSim/initialization/FGTrim.h>

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

    // Path to the QtJSBSim directory, and the ini file.
    QString installPath;
    QString iniPath;

    // Joystick
    jsJoystick* joystick;
    int axes;              // the number of axes on this joystick
    float* ax;             // an array of axis values
    int NumButtons;        // the number of buttons on this joystick
    int buttons;           // contains all button values bitwise
    int* b;                // an array of button values
    void get_joystick_inputs(void);
    void update_joystick_display(void);

    // JSBSim
    jsbsim* JSBSim;
    QString JSBSimExecutable;
    QStringList JSBSimArgs;
    QString JSBSimWorkingDir;
    QUdpSocket* jsbsimDataSocket;
    QUdpSocket* jsbsimControlsSocket;

    void getJSBSimData(void);


    double aileron, elevator, rudder, throttle;
    double pitch_trim, aileron_trim, rudder_trim;
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
    int numEngines;
    double gear_pos, gear_cmd, flap_pos, flap_cmd;
    double speedbrakes_cmd;
    double aileron_pos, elevator_pos, rudder_pos, throttle_pos;
    double speedbrake_pos, simtime;
    double fuel_total, weight, empty_weight, payload, payload_cmd;
    double wind_dir, wind_speed, deltaT;
    double Pt, Qbar, TAT, OAT, Re, g, rho;
    double jsbsim_dt, jsbsimTerminate;
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
    void toggle( double* number);
    void step( double* number, int numsteps, int direction);

private slots:

    void on_GearUpButton_clicked();
    void on_GearDownButton_clicked();
    void on_FlapsUpButton_clicked();
    void on_FlapsDownButton_clicked();
    void on_SBUpButton_clicked();
    void on_SBDownButton_clicked();
    void on_pushButton_clicked();
    void on_pushButton_8_clicked();
    void on_payloadWeightEdit_returnPressed();
    void on_windDirEdit_returnPressed();
    void on_windSpeedEdit_returnPressed();
    void on_temperatureEdit_returnPressed();
    void on_ConnectButton_clicked();

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

};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
