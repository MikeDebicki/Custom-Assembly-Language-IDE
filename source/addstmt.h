#ifndef ADDSTMT_H
#define ADDSTMT_H

#include "statement.h"
#include "label.h"
#include "operand.h"


class AddStmt : public Statement
{
public:
    AddStmt(Program*);
    void compile(QString);
    void run();
private:

};

#endif // ADDSTMT_H
