#ifndef READSTMT_H
#define READSTMT_H

#include "statement.h"
#include "declintstmt.h"
#include "label.h"
#include "program.h"

class ReadStmt : public Statement
{
public:
  ReadStmt(Program*);
  void compile(QString);
  void run();
private:
  //Operand* operand1;
  int arrayPosition = 0;

};

#endif
