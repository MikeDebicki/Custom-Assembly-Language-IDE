#include "variable.h"
#include <QDebug>


Variable::Variable(QString objectName) : Identifier(objectName)
{

  value = new int;

}

Variable::Variable(QString objectName, int sizeToCreate) : Identifier(objectName)
{
  arraySize = sizeToCreate;
  value = new int [arraySize];

}



Variable::~Variable()
{
  if(arraySize != NULL)
  {
    delete [] value;
  }
  else
  {
    delete value;
  }
}


int Variable::getValue(int arrayPosition)
{
  return value[arrayPosition];
}

int Variable::getValue()
{
  return *value;
}

void Variable::setValue(int newValue)
{
  *value = newValue;
}

void Variable::setValue(int newValue, int arrayPoition)
{
  value[arrayPoition] = newValue;
}
