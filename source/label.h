#ifndef LABEL_H
#define LABEL_H

#include <QString>
#include "identifier.h"


class Label : public Identifier
{
  public:
    Label(QString);
  //  ~Label();
    QString getName();
    int getValue();
    void setValue(int);


  private:
    QString name;
    int runtimePosition = 0;

};

#endif
