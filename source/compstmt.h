#ifndef COMPSTMT_H
#define COMPSTMT_H


#include "statement.h"
#include "declintstmt.h"
#include "operand.h"


class CompStmt : public Statement // inherits from statement
{
  public:
    CompStmt(Program*);
    void compile(QString);      // pure virtual function to compile
    void run();                 // pure virtual function to run

  private:


};

#endif
