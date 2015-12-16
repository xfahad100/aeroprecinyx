/******************************************************************************/
// License:  GPLv3
// Author:   David Culp, daveculp@cox.net
// Date:     15 Dec 2015
//
// Purpose:  Encapsulates the JSBSim app as a QProcess, mainly so that the
//           stdout can be captured and displayed in a console widget.
/******************************************************************************/

#ifndef JSBSIM_H
#define JSBSIM_H

#include <QObject>
#include <QProcess>


class jsbsim : public QProcess {

    Q_OBJECT

  public:
    jsbsim();
    ~jsbsim();

  signals:
    void logString(const QString &str);

  public slots:
    void logOutput();

  private:
    QString process(const QString &str);
};

#endif // JSBSIM_H

