#include <string>
using namespace std;

#include "jmorestmt.h"


JMoreStmt::JMoreStmt(Program* parentProgram) : Statement(parentProgram, "jmr", 1)  // We pass needed variables to the parent class
{

}


void JMoreStmt::compile(QString inputString)
{
  int operandsCreated = 0;
  QString stringToBuild;
  for(int i = 0; i < inputString.size(); i += 1)          // we loop through the string
  {
    if(inputString.at(i) == ' ')
    {
      operand1->setIdentifier(parentProgram->createLabel(stringToBuild));      // we populate the operand
      stringToBuild.clear();
      operandsCreated += 1;
    }
    else
    {
      stringToBuild.append(inputString.at(i));              // we build our string
    }
    if(i + 1 == inputString.size() && operandsCreated == 1)       // this case we have a label
    {
      label = parentProgram->getLabel(stringToBuild);
    }
    else if(i + 1 == inputString.size() && operandsCreated == 0)          // this case we end with no label
    {
      operand1->setIdentifier(parentProgram->createLabel(stringToBuild));
      operandsCreated += 1;
      stringToBuild.clear();
    }
  }
}


void JMoreStmt::run()
{
  if(parentProgram->getFlag() == 1)
  {
    parentProgram->setRuntimePosition(operand1->getIdentifier()->getValue());
  }
}
