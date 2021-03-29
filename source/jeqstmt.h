#ifndef JEQSTMT_H
#define JEQSTMT_H


#include "statement.h"
#include "compstmt.h"
#include "label.h"
#include "program.h"

class JEQStmt : public Statement
{
public:
    JEQStmt(Program*);
    void compile(QString);
    void run();
};

#endif // JEQSTMT_H
