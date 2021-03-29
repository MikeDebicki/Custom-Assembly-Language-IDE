#include <QString>
using namespace std;

#include "label.h"

Label::Label(QString objectName) : Identifier(objectName)   // constructor makes a call to set the identifier name
{
}

/*
Label::~Label()
{

}
*/


QString Label::getName()          // get name to check what identifier we are
{
  return name;
}

int Label::getValue()
{
  return runtimePosition;
}

void Label::setValue(int positionToSet)
{
  runtimePosition = positionToSet;
}
