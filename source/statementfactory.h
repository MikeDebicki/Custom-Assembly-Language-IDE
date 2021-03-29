#ifndef FACTORY_H

#define FACTORY_H

#include <QString>
#include <iostream>
#include "statement.h"


using namespace std;


class Statementfactory{
public:

    //Statement creation for end
    Statement* createStatement(QString, Program*, QString);

     //Statement creation for jmp, jmr, prt, dci, rdi
    Statement* createStatement(QString, QString, Program*, QString);

     //Statement creation for cmp
    Statement* createStatement(QString, QString, QString, Program*, QString);


    Statement* createStatement(QString,QString,int,Program*,QString);

    Statementfactory();
    ~Statementfactory();
};



#endif // FACTORY_H


