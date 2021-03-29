#ifndef OPERAND_H
#define OPERAND_H

#include "identifier.h"


class Operand
{
public:
    Operand();
    ~Operand();
    void setIdentifier(Identifier*);
    Identifier* getIdentifier();
private:
    Identifier* identifier;
};

#endif // OPERAND_H
