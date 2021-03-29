#ifndef JMORESTMT_H
#define JMORESTMT_H

#include "statement.h"
#include "compstmt.h"
#include "label.h"
#include "program.h"

class JMoreStmt : public Statement
{
  public:
    JMoreStmt(Program*);
    void compile(QString);
    void run();

  private:
    //Operand* operand1;

};

#endif

