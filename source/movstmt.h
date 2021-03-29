#ifndef MOVSTMT_H
#define MOVSTMT_H

#include "program.h"
#include "statement.h"
#include "label.h"


class MovStmt : public Statement
{
public:
    MovStmt(Program*);
    void compile(QString);
    void run();

private:

};

#endif // MOVSTMT_H
