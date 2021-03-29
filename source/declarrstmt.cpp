#include <QString>
#include "declarrstmt.h"
#include "program.h"

DeclArrStmt::DeclArrStmt(Program* parentProgram) : Statement(parentProgram, "dca", 2)
{

}


void DeclArrStmt::compile(QString inputString)   // Compile function takes one string and parses and creates objects that it needs
{
  int operandsCreated = 0;                    // helps keep track of which operands have been created and which need to be created
  QString stringToBuild;                        // this is used to build each string used to request statementObjects
  QString arrayName;
  int arraySize;
  for(int i = 0; i < inputString.size(); i += 1)    // i loop through the entire string
  {
    if(inputString.at(i) == ' ' && operandsCreated == 0)    // This checks for the first operand in the case that it has not populated operand1
    {
      arrayName = stringToBuild;
      stringToBuild.clear();
      operandsCreated += 1;
    }
    else if(inputString.at(i) == ' ' && operandsCreated == 1)           // This makes the second operand
    {
      arraySize = stringToBuild.toInt();
      stringToBuild.clear();              // reset for next instruction
      operandsCreated += 1;
    }
    else
    {
      stringToBuild.append(inputString.at(i));            // After all the ' ' char logic we add to our stringToBuild (we dont want to add ' ')
    }
    if(i + 1 == inputString.size() && operandsCreated == 2)     // this case is if we have cmp a b l1, we have a label to request
    {
      label = parentProgram->getLabel(stringToBuild);         // Program makes the label
    }
    else if(i + 1 == inputString.size() && operandsCreated == 1)
    {
      operand2->setIdentifier(parentProgram->getIdentifier(stringToBuild));
      arraySize = stringToBuild.toInt();
      stringToBuild.clear();              // reset for next instruction
      operandsCreated += 1;
    }
  }
  operand1->setIdentifier(parentProgram->createVariable(arrayName, arraySize));       // Operands are created already so we just populate them
}

void DeclArrStmt::printVariables()
{
  for(int i = 0; i < ((operand2->getIdentifier()->getName().toInt()));i += 1)
  {
    //parentProgram->send_to_runcontrol(QStringLiteral("%1").arg(operand1->getIdentifier()->getValue(i)));
    parentProgram->send_to_runcontrol(QStringLiteral("%1").arg(i));
  }
}


void DeclArrStmt::run()
{
}
