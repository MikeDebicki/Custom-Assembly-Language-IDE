#include <string>
using namespace std;

#include "statement.h"
#include "operand.h"
#include <QDebug>


Statement::Statement(Program* parentObject, QString typeString, int numOfOperands)        // this is the parent constructor that each statement class uses
{
  parentProgram = parentObject;           // we set the pointer to program so that we can reference it
  type = typeString;
  label=NULL;
  if(numOfOperands == 1)                  // we make operands and pointers when we make the objects
  {

    Operand *newOperand = new Operand();
    operand1 = newOperand;
    operand2 = NULL;

  }
  else if(numOfOperands == 2)                 // when we need two operands
  {
    Operand *newOperand = new Operand();
    operand1 = newOperand;
    Operand *newOperand2 = new Operand();
    operand2 = newOperand2;
  }
  else                                        // no operands to make
  {
    operand1 = NULL;
    operand2 = NULL;
  }
}
Statement::~Statement()
{
    delete operand1;
    delete operand2;
}

Identifier* Statement::getLabel()
{
  return label;
}

QString Statement::getType()
{
  return type;
}

Operand* Statement::getOperand1()
{
  return operand1;
}

Operand* Statement::getOperand2()
{
  return operand2;
}

void Statement::setArrayPosition(int operand, int arrayPosition)
{
  if(operand == 1)
  {
    arrayPosition1 = arrayPosition;

  }
  else
  {
    arrayPosition2 = arrayPosition;
  }
}

int Statement::getArrayPosition(int operand)
{
  if(operand == 1)
  {
    qDebug() << arrayPosition1;
    return arrayPosition1;
  }
  else
  {
    qDebug() << arrayPosition2;
    qDebug() << "FADFDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD2";
    return arrayPosition2;
  }
}



void Statement::setArrayAnswer(bool answer, int operand)
{
  if(operand == 1){
    isArray1 = answer;
  }
  else
  {
    isArray2 = answer;
  }
}

bool Statement::getArrayAnswer(int operand)
{
  if(operand == 1)
  {
    return isArray1;
  }
  else
  {
    return isArray2;
  }
}
