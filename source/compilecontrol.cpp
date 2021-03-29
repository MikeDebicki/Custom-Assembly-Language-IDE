#include "compilecontrol.h"

CompileControl::CompileControl(QObject* parent) : QObject(parent)
{


}

CompileControl::~CompileControl()
{

}

void CompileControl::launch(QString* data)
{
    Program *program = new Program();
    connect(program,SIGNAL(send_print_errors(QString)),this,SLOT(connect_program_to_mainwindow(QString)));
    program->parse(data);
    program->serialize();
}


void CompileControl::connect_program_to_mainwindow(QString errorText){


    error_calling_function(&errorText);

}

void CompileControl::error_calling_function(QString *text){

     emit send_print_errors_to_mainwindow(*text);


}

