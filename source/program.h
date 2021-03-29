#ifndef PROGRAM_H
#define PROGRAM_H
#include <QObject>
#include <QList>
#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QDir>
#include "label.h"
#include "variable.h"
#include "statementfactory.h"
#include "statement.h"
#include "errorcheck.h"
#include "identifier.h"


class Statementfactory;
class Program: public QObject
{
    Q_OBJECT
public:
    explicit Program(QObject *parent=nullptr);
    ~Program();
    //QList<Statement*> statement_list;

    void parse(QString *list);
    void print_errors(QString error_message);
    Identifier* getLabel(QString);
    Identifier* getVariable(QString);
    Identifier* getIdentifier(QString);
    void serialize();
    void notify (QJsonDocument* );
    void read();
    void runthroughstatementarray();

    void addList(Statement*);
    void printexecutionflow();

    //mikes new
    void setFlag(int);
    int getFlag();
    void setRuntimePosition(int);
    void printToWindow(QString);
    int getUserWindowInput();
    Identifier* createVariable(QString, int);
    void trigger_rdi_window();
    void getNuse_rdi(int* );
    Identifier* getVariable(QString, int);
    Identifier* createLabel(QString);
    void send_to_runcontrol(QString error_message);
    void printVariables();
    void endProgram();

signals:
    void send_print_errors(QString message);
    void send_rdi_window();
    void send_rdi(QString message);
private:
    Statementfactory* statementfactory_ptr;
    QStringList instructions={"dci","rdi","prt","cmp","jmr","jmp","jeq","end","#","dca","jls","jmp","mov","add"};
    QStringList Toword;
    QStringList word;
    bool result;
    QString data;
    int Oneoperand=2;
    int Twooperand=3;
    ErrorCheck errorcheck;

   // Program* ptr_program;

   // QList<Identifier*> idlist;


    QList<Statement*> statement_List;
    //QList<Identifier*> idlist;
    QList<Identifier*>  idlist;
    int statement_array_index = 0;

    int N;
    QString number;
    //mikes new variables
    int comparisonFlag;
    int runtimeArrayPosition;

    bool programJumped = false;



};

#endif // PROGRAM_H
