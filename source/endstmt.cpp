#include <string>
using namespace std;

#include "endstmt.h"

EndStmt::EndStmt(Program* parentProgram) : Statement(parentProgram, "end", 0) // we call the parent class with needed variables
{

}

void EndStmt::compile(QString objectName)               // our compiler is very simple. we only need to check if there is a label
{
  if(objectName != NULL)
  {
    label = parentProgram->getLabel(objectName);      // we add a label if there is one
  }
}

void EndStmt::run()
{
  parentProgram->endProgram();
}
