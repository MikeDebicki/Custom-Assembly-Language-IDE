#include<string>
#include<iostream>

using namespace std;

#include "printstmt.h"

PrintStmt::PrintStmt(Program* parentProgram) : Statement(parentProgram, "prt", 1)       // call parent constructor
{

}


void PrintStmt::compile(QString inputString)
{
  bool stringLiteral = false;
  bool arrayElement = false;
  int operandsCreated = 0;
  QString stringToBuild;
  for(int i = 0; i < inputString.size(); i += 1)      // we loops through the string
  {
    if(inputString.at(i) == '"')          // if we have a string literal we set our bool to keep track
    {
      stringLiteral = true;
    }
    if(inputString.at(i) == '$')
    {
      arrayElement = true;
    }
    else if(inputString.at(i) == ' ')          // if we have a label we handle that here
    {
      if(stringLiteral == true)           // if our string is a literal we build an operand with the name as the literal
      {
        operand1->setIdentifier(parentProgram->getIdentifier(stringToBuild));
        stringToBuild.clear();
        operandsCreated += 1;
      }
      else if(arrayElement == true)
      {
        QString variableName;
        QString position;
        bool positionCreation = false;
        for(int i = 0; i <= stringToBuild.length() - 1; i += 1)
        {
          //qDebug() << stringToBuild;
          if (stringToBuild.at(i) == '+')
          {
            positionCreation = true;
          }
          else if(positionCreation == false)
          {
            variableName.append(stringToBuild.at(i));
          }
          else
          {
            position.append(stringToBuild.at(i));
          }
        }
        operand1->setIdentifier(parentProgram->getVariable(variableName));
        setArrayPosition(1, position.toInt());
        setArrayAnswer(true, 1);
        arrayElement = false;
        stringToBuild.clear();
        operandsCreated += 1;
      }
      else                                  // if our string is a variable, we ask our product object to make or find a variable object
      {
        operand1->setIdentifier(parentProgram->getVariable(stringToBuild));
        stringToBuild.clear();
        operandsCreated += 1;
      }

    }
    else
    {
      stringToBuild.append(inputString.at(i));
    }
    if(i + 1 == inputString.size() && operandsCreated == 1)         // if we have to make a label well use this code
    {
      label = parentProgram->getLabel(stringToBuild);
    }
    else if(i + 1 == inputString.size() && operandsCreated == 0)      // here we finish with the string with no label
    {
      if(stringLiteral == true)                       // if its a literal string
      {
        operand1->setIdentifier(parentProgram->getIdentifier(stringToBuild));       // we set the operand name to the string literal
        stringToBuild.clear();
      }
      else if(arrayElement == true)
      {
        QString variableName;
        QString position;
        bool positionCreation = false;
        for(int i = 0; i <= stringToBuild.length() - 1; i += 1)
        {
          //qDebug() << stringToBuild;
          if (stringToBuild.at(i) == '+')
          {
            positionCreation = true;
          }
          else if(positionCreation == false)
          {
            variableName.append(stringToBuild.at(i));
          }
          else
          {
            position.append(stringToBuild.at(i));
          }
        }
        operand1->setIdentifier(parentProgram->getVariable(variableName));
        setArrayPosition(1, position.toInt());
        setArrayAnswer(true, 1);
        arrayElement = false;
        stringToBuild.clear();
        operandsCreated += 1;

      }
      else
      {
        operand1->setIdentifier(parentProgram->getVariable(stringToBuild));
        stringToBuild.clear();
        operandsCreated += 1;
      }
    }
  }
}


void PrintStmt::run()
{
  if(operand1->getIdentifier()->getName().startsWith("\"") == true)
  {
    parentProgram->send_to_runcontrol(operand1->getIdentifier()->getName());

  }
  else
  {
    parentProgram->send_to_runcontrol(QStringLiteral("%1").arg(operand1->getIdentifier()->getValue(getArrayPosition(0))));
  }
}
