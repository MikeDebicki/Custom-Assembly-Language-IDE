#include <iostream>
#include <QString>
using namespace std;

#include <QDebug>

#include "declintstmt.h"
#include "program.h"

DeclIntStmt::DeclIntStmt(Program* parentProgram) : Statement(parentProgram, "dci", 1)  //Constructor passes needed values to parent class
{

}

void DeclIntStmt::compile(QString inputString)
{
  int operandsCreated = 0;
  QString stringToBuild;
  for(int i = 0; i < inputString.size(); i += 1)    // WE loop through the string array
  {

    if(inputString.at(i) == ' ')                // spaces mean we seperate the string
    {
      operand1->setIdentifier(parentProgram->createVariable(stringToBuild, 1));   // populate the operand
      stringToBuild.clear();
      operandsCreated += 1;
    }
    else
    {
      stringToBuild.append(inputString.at(i));            // we add to our string
    }
    if(i + 1 == inputString.size() && operandsCreated == 1)         // we make a label
    {
      label = parentProgram->getLabel(stringToBuild);
    }
    else if(i + 1 == inputString.size() && operandsCreated == 0)            // we end without making a label
    {
      operand1->setIdentifier(parentProgram->createVariable(stringToBuild, 1)); // populate the operand

      operandsCreated += 1;
      stringToBuild.clear();
    }
  }
}

void DeclIntStmt::printVariables()
{
  parentProgram->send_to_runcontrol(operand1->getIdentifier()->getName());
}


void DeclIntStmt::run()
{

}
