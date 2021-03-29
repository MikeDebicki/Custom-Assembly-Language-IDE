
#ifndef DECLINTSTMT_H
#define DECLINTSTMT_H

#include "statement.h"
#include "label.h"
#include "operand.h"

class DeclIntStmt : public Statement
{
  public:
    DeclIntStmt(Program*);
    void compile(QString);
    void run();
    QString getType();
    void printVariables();

  private:



};

#endif
