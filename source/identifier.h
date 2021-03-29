#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <QString>

class Identifier
{
public:
    Identifier(QString);
    QString getName();
    virtual int getValue();
    virtual int getValue(int);
    virtual void setValue(int);
    virtual void setValue(int, int);

protected:
    QString name;
};

#endif // IDENTIFIER_H
