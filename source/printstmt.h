#ifndef PRINTSTMT_H
#define PRINTSTMT_H

#include "statement.h"
#include "operand.h"
#include "label.h"
#include "program.h"

class PrintStmt : public Statement

{
public:
  PrintStmt(Program*);
  void compile(QString);
  void run();
  Label* getLabel();
private:
  //QString stringToPrint;
  //Operand* operand1;
};


#endif
