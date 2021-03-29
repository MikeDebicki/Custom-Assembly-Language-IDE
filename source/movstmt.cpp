#include <QString>
#include "movstmt.h"
#include "program.h"

MovStmt::MovStmt(Program* parentProgram) : Statement(parentProgram, "mov", 2)
{

}

void MovStmt::compile(QString inputString)
{
  qDebug() << inputString;
  qDebug() << "MOVE INPUT";
  bool arrayElement = false;
  bool stringLiteral= false;
  int operandsCreated = 0;                    // helps keep track of which operands have been created and which need to be created
  QString stringToBuild;                        // this is used to build each string used to request statementObjects
  for(int i = 0; i < inputString.size(); i += 1)    // i loop through the entire string
  {

    if(inputString.at(i) == ' ' && operandsCreated == 0)    // This checks for the first operand in the case that it has not populated operand1
    {
      if(stringLiteral == true)           // if our string is a literal we build an operand with the name as the literal
      {
        operand1->setIdentifier(parentProgram->getVariable(stringToBuild, stringToBuild.toInt()));
        operand1->getIdentifier()->setValue(stringToBuild.toInt());
        stringLiteral = false;
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
    else if(inputString.at(i) == ' ' && operandsCreated == 1)           // This makes the second operand
    {
      if(arrayElement == true)
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
        operand2->setIdentifier(parentProgram->getVariable(variableName));
        setArrayPosition(2, position.toInt());
        arrayElement = false;
        stringToBuild.clear();
        operandsCreated += 1;
      }
      else                                  // if our string is a variable, we ask our product object to make or find a variable object
      {
        operand2->setIdentifier(parentProgram->getVariable(stringToBuild));
        stringToBuild.clear();
        operandsCreated += 1;
      }
    }
    else if(inputString.at(i) == '$')
    {
      arrayElement = true;
    }
    else if(inputString.at(i) == '"')
    {
      stringLiteral = true;
    }
    else
    {
      stringToBuild.append(inputString.at(i));            // After all the ' ' char logic we add to our stringToBuild (we dont want to add ' ')
    }
    if(i + 1 == inputString.size() && operandsCreated == 2)     // this case is if we have cmp a b l1, we have a label to request
    {
      label = parentProgram->getLabel(stringToBuild);         // Program makes the label
    }
    else if(i + 1 == inputString.size() && operandsCreated == 1)            // This case is no label, cmp a b
    {

      if(arrayElement == true)
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
        operand2->setIdentifier(parentProgram->getVariable(variableName));
        setArrayPosition(2, position.toInt());
        arrayElement = false;
        stringToBuild.clear();
        operandsCreated += 1;
      }
      else                                  // if our string is a variable, we ask our product object to make or find a variable object
      {
        operand2->setIdentifier(parentProgram->getVariable(stringToBuild));
        stringToBuild.clear();
        operandsCreated += 1;
      }
    }
  }
  qDebug() << "MOVE IS DONEEEE";
}

void MovStmt::run()
{
  qDebug() << "MOV STMT RUNNNNNN";
  qDebug() << operand1->getIdentifier()->getValue(getArrayPosition(1));
    operand2->getIdentifier()->setValue(operand1->getIdentifier()->getValue(getArrayPosition(1)), getArrayPosition(2));
}
