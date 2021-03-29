#ifndef DECLARRSTMT_H
#define DECLARRSTMT_H


#include "statement.h"


class DeclArrStmt : public Statement
{
public:
    DeclArrStmt(Program*);
    void compile(QString);
    void run();
    void printVariables();
};


#endif // DECLARRSTMT_H
