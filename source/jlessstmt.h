#ifndef JLESSSTMT_H
#define JLESSSTMT_H

#include "statement.h"
#include "compstmt.h"
#include "label.h"
#include "program.h"


class JLessStmt : public Statement
{
public:
    JLessStmt(Program*);
    void compile(QString);
    void run();
  private:


};

#endif // JLESSSTMT_H
