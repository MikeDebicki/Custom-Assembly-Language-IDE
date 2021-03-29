#ifndef JUMPSTMT_H
#define JUMPSTMT_H

#include "statement.h"
#include "compstmt.h"
#include "label.h"
#include "program.h"

class JumpStmt : public Statement
{
  public:
    JumpStmt(Program*);
    void compile(QString);
    void run();

  private:
    //Operand* operand1;

};

#endif
