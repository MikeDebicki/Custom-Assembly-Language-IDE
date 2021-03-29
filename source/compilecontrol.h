#ifndef COMPILECONTROL_H
#define COMPILECONTROL_H
#include <QObject>

#include "program.h"
using namespace std;

class CompileControl: public QObject
{
     Q_OBJECT
public:
    explicit CompileControl(QObject *parent=nullptr);
    ~CompileControl(); //needed?
    void launch(QString* );
    void error_calling_function(QString *text);

private:
   // Program program;

private slots:
     void connect_program_to_mainwindow(QString errorText);
signals:
    void send_print_errors_to_mainwindow(QString message);

};

#endif // COMPILECONTROL_H
