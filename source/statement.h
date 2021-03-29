#ifndef STATEMENT_H
#define STATEMENT_H

#include <QString>
#include "label.h"
#include "operand.h"

class Program;
class Statement
{
  public:
    Statement(Program*, QString, int);
    virtual ~Statement() = 0;
    virtual void compile(QString) = 0;
    virtual void run() = 0;
    Identifier* getLabel();
    Operand* getOperand1();
    Operand* getOperand2();
    bool getArrayAnswer(int);
    void setArrayAnswer(bool, int);
    void setArrayPosition(int, int);
    int getArrayPosition(int);
    QString getType();
    virtual void printVariables(){};


  protected:
    Program* parentProgram;
    Identifier* label;
    QString type;
    Operand* operand1;
    Operand* operand2;
    int arrayPosition1 = 0;
    int arrayPosition2 = 0;
    bool isArray1 = false;
    bool isArray2 = false;

};

#endif
