#include "operand.h"

Operand::Operand()
{

}

Operand::~Operand()
{

}

void Operand::setIdentifier(Identifier* identifierToSet)        // we set identifiers in operands after they are created
{

  identifier = identifierToSet;
}

Identifier* Operand::getIdentifier()                  // we need a way to tell what operand it is
{
  return identifier;
}
