#ifndef ENDSTMT_H
#define ENDSTMT_H

#include "statement.h"
#include "label.h"
#include "program.h"

class EndStmt : public Statement
{
  public:
    EndStmt(Program*);
    void compile(QString);
    void run();

  private:

};

#endif

