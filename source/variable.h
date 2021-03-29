#ifndef VARIABLE_H
#define VARIABLE_H

#include "identifier.h"


class Variable : public Identifier
{
public:
    Variable(QString);
    Variable(QString, int);
   ~Variable();
    int getValue(int);
    int getValue();
    void setValue(int);
    void setValue(int, int);
private:
    int *value;
    int arraySize;
};

#endif // VARIABLE_H
