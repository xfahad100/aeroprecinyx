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

