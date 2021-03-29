#include "runcontrol.h"

RunControl::RunControl(QObject* parent) : QObject(parent)
{

}


RunControl::~RunControl()
{

}

void RunControl::launch()
{
    Program *program = new Program();
    connect(program,SIGNAL(send_rdi_window()),this,SLOT(connect_program_to_runcontrol()));
    setProgram(program);
    qDebug()<<" RunControl::launch()"<<program;
    connect(program,SIGNAL(send_rdi(QString)),this,SLOT(connect_program_to_mainwindow(QString)));

    program->read();

    program->runthroughstatementarray();
    //program->printVariables();

}

void RunControl::connect_program_to_runcontrol(){

    connection();

}

void RunControl::connection(){

    emit send_rdi_command_to_mainwindow();

}

void RunControl::passing_rdi_from_gui(int *n){

   // Program *program;

    qDebug()<<" in RunControl::passing_rdi_from_gui = "<<*n;
    qDebug()<<" passing_rdi_from_gui"<<getProgram();
    getProgram()->getNuse_rdi(n);

}

void RunControl::setProgram(Program *p){
    prog=p;

}

Program* RunControl::getProgram(){
    return prog;

}

void RunControl::connect_program_to_mainwindow(QString errorText){

    qDebug()<<"connect_program_to_mainwindow "<<errorText;
    error_calling_function(&errorText);

}

void RunControl::error_calling_function(QString *text){
     qDebug()<<"error_calling_function "<<*text;
     emit send_output_to_mainwindow(*text);


}

