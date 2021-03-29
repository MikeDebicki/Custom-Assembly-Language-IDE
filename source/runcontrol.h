#ifndef RUNCONTROL_H
#define RUNCONTROL_H
#include <QObject>

#include "program.h"
using namespace std;


class RunControl: public QObject
{
    Q_OBJECT
public:
     explicit RunControl(QObject *parent=nullptr);
     ~RunControl();
     void launch();
     void connection();
     void passing_rdi_from_gui(int* );
     void setProgram(Program* p);
     Program *prog;
     Program* getProgram();
     void error_calling_function(QString *text);
private slots:
     void connect_program_to_runcontrol();
     void connect_program_to_mainwindow(QString errorText);

signals:
    void send_rdi_command_to_mainwindow();
    void send_output_to_mainwindow(QString message);
};

#endif // RUNCONTROL_H



