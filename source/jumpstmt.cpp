#include <QString>
using namespace std;
#include "program.h"


#include "jumpstmt.h"

JumpStmt::JumpStmt(Program* parentProgram) : Statement(parentProgram, "jmp", 1) // our constructor calls the parent with required variables

{

}

void JumpStmt::compile(QString inputString)
{
  int operandsCreated = 0;
  QString stringToBuild;
  for(int i = 0; i < inputString.size(); i += 1) // we loop through the array
  {
    if(inputString.at(i) == ' ')
    {
      operand1->setIdentifier(parentProgram->createLabel(stringToBuild));      // we populate the operand
      stringToBuild.clear();
      operandsCreated += 1;
    }
    else
    {
      stringToBuild.append(inputString.at(i));          // we build the string
    }
    if(i + 1 == inputString.size() && operandsCreated == 1)       // this case is when we have a label
    {
      label = parentProgram->getLabel(stringToBuild);
    }
    else if(i + 1 == inputString.size() && operandsCreated == 0)        // this case is when we end with no label
    {
      operand1->setIdentifier(parentProgram->createLabel(stringToBuild));
      operandsCreated += 1;
      stringToBuild.clear();
    }
  }
  run();
}


void JumpStmt::run()
{
  parentProgram->setRuntimePosition(operand1->getIdentifier()->getValue());
}
