#include "statementfactory.h"
#include "operand.h"
#include "statement.h"
#include <QDebug>
#include <iostream>
#include <QString>
#include "identifier.h"
#include "declintstmt.h"
#include "endstmt.h"
#include "printstmt.h"
#include "readstmt.h"
#include "compstmt.h"
#include "jmorestmt.h"
#include "jumpstmt.h"
#include "jeqstmt.h"
#include "jlessstmt.h"
#include "addstmt.h"
#include "movstmt.h"
#include "declarrstmt.h"
using namespace std;



Statementfactory::Statementfactory(){

}

Statementfactory::~Statementfactory(){

}


//if its end string, create an end statement and return it
Statement* Statementfactory::createStatement(QString instruction_operator,Program* program_pointer,QString if_label){
        if((instruction_operator.compare("end")) == 0) {
                        cout << "end operator selected!" << endl;  //indicates it that the operator is dci has been recognized

                        //Determines if end comes with a label
                        Statement *endstatement = new EndStmt(program_pointer);
                        if(!(if_label.isNull())){
                            //dcistatement->compile("L1");
                            endstatement->compile(if_label);
                            Statement *endptr = endstatement;
                            return endptr;
                        }

                        //Determines if end doesn't come with a label
                        else{
                            endstatement->compile("");
                            Statement *endptr = endstatement;
                            return endptr;
                        }


        }
}




//if its either dci, prt, rdi, jmr, jmp string, create an that statement and return it
Statement* Statementfactory::createStatement(QString instruction_operator,QString op1,Program* program_pointer,QString if_label){


        //Determines if it comes with a label
        if((instruction_operator.compare("dci")) == 0) {
                        cout << "dci operator selected!" << endl;  //indicates it that the operator is dci has been recognized
                        Statement *dcistatement = new DeclIntStmt(program_pointer);

                        //if its a label
                        if(!(if_label.isNull())){
                            QString dci_with_label = op1 + " " + if_label;
                            //dcistatement->compile("a L1");
                            dcistatement->compile(dci_with_label);
                            Statement *dciptr = dcistatement;
                            return dciptr;
                        }

                        //Determines if it comes with a label
                        else{
                            qDebug()<<"op1"<<op1;
                            dcistatement->compile(op1);
                            qDebug()<<"AFter the statment";
                            Statement *dciptr = dcistatement;
                            return dciptr;
                            }

        }


        //Determines if its prt
        if((instruction_operator.compare("prt")) == 0) {
                       cout << "prt operator selected!" << endl;  //indicates it that the operator is dci has been recognized
                        //create prt obj
                       Statement *printstatement = new PrintStmt(program_pointer);
                       if(!(if_label.isNull())){
                           QString prt_with_label = op1 + " " + if_label;
                           //dcistatement->compile("a L1");
                           printstatement->compile(prt_with_label);
                           Statement *printptr = printstatement;
                           return printptr;
                       }
                       else{
                           qDebug() << "BEFORE COMPILE: prt statementfactory op: " << op1;
                           printstatement->compile(op1);
                           qDebug() << "AFTER COMPILE";
                           Statement *printptr = printstatement;
                           return printptr;
                       }
        }

        //create rdi statement object
        if((instruction_operator.compare("rdi")) == 0){
                       cout << "rdi operator selected!" << endl;
                       Statement *rdiinstruction = new ReadStmt(program_pointer);
                       if(!(if_label.isNull())){
                           QString rdi_with_label = op1 + " " + if_label;
                           //dcistatement->compile("a L1");
                           rdiinstruction->compile(rdi_with_label);
                           Statement *rdiptr = rdiinstruction;
                           return rdiptr;
                       }
                       else{
                       rdiinstruction->compile(op1);
                       Statement *rdiptr = rdiinstruction;
                       return rdiptr;
                       }
        }


        //create jmr statement object
        if((instruction_operator.compare("jmr")) == 0){  //JMoreStmt
                       cout << "jmr operator selected!" << endl;
                       Statement *jmrinstruction = new JMoreStmt(program_pointer);
                       if(!(if_label.isNull())){
                           QString jmr_with_label = op1 + " " + if_label;
                           //dcistatement->compile("a L1");
                           jmrinstruction->compile(jmr_with_label);
                           Statement *jmrptr = jmrinstruction;
                           return jmrptr;
                       }
                       else{
                           jmrinstruction->compile(op1);
                           Statement *jmrptr = jmrinstruction;
                           return jmrptr;
                       }
        }

        //create jmp statement object
        if((instruction_operator.compare("jmp")) == 0){  //JumpStmt
                       cout << "jmp operator selected!" << endl;
                       Statement *jmpinstruction = new JumpStmt(program_pointer);
                        if(!(if_label.isNull())){
                           QString jmp_with_label = op1 + " " + if_label;
                           //dcistatement->compile("a L1");
                           jmpinstruction->compile(jmp_with_label);
                           Statement *jmpptr = jmpinstruction;
                           return jmpptr;
                        }
                        else{
                           jmpinstruction->compile(op1);
                           Statement *jmpptr = jmpinstruction;
                           return jmpptr;
                        }
         }

        //create jls statement object (new)
        if((instruction_operator.compare("jls")) == 0){  //JumpStmt
                       cout << "jls operator selected!" << endl;
                       Statement *jlsinstruction = new JLessStmt(program_pointer);
                        if(!(if_label.isNull())){
                           QString jmp_with_label = op1 + " " + if_label;
                           //dcistatement->compile("a L1");
                           jlsinstruction->compile(jmp_with_label);
                           Statement *jlsptr = jlsinstruction;
                           return jlsptr;
                        }
                        else{
                           jlsinstruction->compile(op1);
                           Statement *jlsptr = jlsinstruction;
                           return jlsptr;
                        }
         }



        //create jeq statement object (new)
        if((instruction_operator.compare("jeq")) == 0){  //JumpStmt
                       cout << "jeq operator selected!" << endl;
                       Statement *jeqinstruction = new JEQStmt(program_pointer);
                        if(!(if_label.isNull())){
                           QString jmp_with_label = op1 + " " + if_label;
                           //dcistatement->compile("a L1");
                           jeqinstruction->compile(jmp_with_label);
                           Statement *jeqptr = jeqinstruction;
                           return jeqptr;
                        }
                        else{
                           jeqinstruction->compile(op1);
                           Statement *jeqptr = jeqinstruction;
                           return jeqptr;
                        }
         }
}


//if its cmp or mov or add, create its operands and whether it contains a label
Statement* Statementfactory::createStatement(QString instruction_operator,QString op1,QString op2,Program* program_pointer,QString if_label){
      cout << "cmp operator selected within the Statementfactory!!!!!!!!!!!!!!!!!" << endl;
      if((instruction_operator.compare("cmp")) == 0){ //CompStmt
               cout << "cmp operator selected!" << endl;
               qDebug() << "if_label: " << if_label;
               qDebug() << "program_pointer"  << program_pointer;
               Statement *compinstruction = new CompStmt(program_pointer);
               if(!(if_label.isNull())){
                   QString cmp_with_label = op1 + " " + op2 + " " + if_label;
                   qDebug() << "passed into compile and label" << cmp_with_label;
                   compinstruction->compile(cmp_with_label);
                   Statement *cmpptr = compinstruction;
                   return cmpptr;
               }
               else{
                   qDebug() << "Statementfactory::createStatement  cmp";
                   QString cmp_with_label = op1 + " " + op2;
                   qDebug() << "passed into compile" << cmp_with_label;
                   compinstruction->compile(cmp_with_label);
                   qDebug("cmp compile completed!");
                   Statement *cmpptr = compinstruction;
                   return cmpptr;
               }
        }


      //mov instruction selected (new)
      if((instruction_operator.compare("mov")) == 0){ //MovStmt
               cout << "mov operator selected!" << endl;
               qDebug() << "if_label: " << if_label;
               qDebug() << "program_pointer"  << program_pointer;
               Statement *movinstruction = new MovStmt(program_pointer);
               if(!(if_label.isNull())){
                   QString mov_with_label = op1 + " " + op2 + " " + if_label;
                   qDebug() << "passed into compile and label" << mov_with_label;
                   movinstruction->compile(mov_with_label);
                   Statement *movptr = movinstruction;
                   return movptr;
               }
               else{
                   qDebug() << "Statementfactory::createStatement  mov";
                   QString mov_with_label = op1 + " " + op2;
                   qDebug() << "passed into compile" << mov_with_label;
                   movinstruction->compile(mov_with_label);
                   qDebug("mov compile completed!");
                   Statement *movptr = movinstruction;
                   return movptr;
               }
        }



      //add instruction selected (new)
      if((instruction_operator.compare("add")) == 0){ //AddStmt
               cout << "Add operator selected!" << endl;
               qDebug() << "if_label: " << if_label;
               qDebug() << "program_pointer"  << program_pointer;
               Statement *addinstruction = new AddStmt(program_pointer);
               if(!(if_label.isNull())){
                   QString add_with_label = op1 + " " + op2 + " " + if_label;
                   qDebug() << "passed into compile and label" << add_with_label;
                   addinstruction->compile(add_with_label);
                   Statement *compptr = addinstruction;
                   return compptr;
               }
               else{
                    qDebug() << "Statementfactory::createStatement add";
                    QString add_with_label = op1 + " " + op2;
                    qDebug() << "passed into compile" << add_with_label;
                    addinstruction->compile(add_with_label);
                    qDebug("add compile completed!");
                    Statement *addptr = addinstruction;
                    return addptr;
               }
        }


      //(QString instruction_operator,QString op1,QString op2,Program* program_pointer,QString if_label)
        //add instruction selected (new)   //op1 = nameofarray   op2 = size of array (received and given as a string)
        if((instruction_operator.compare("dca")) == 0){ //dcastmt
                     cout << "dca operator selected!" << endl;
                     qDebug() << "if_label: " << if_label;
                     qDebug() << "program_pointer"  << program_pointer;
                     Statement *decArrinstruction = new DeclArrStmt(program_pointer);
                     if(!(if_label.isNull())){
                         QString dec_with_label = op1 + " " + " " + if_label;
                         //qDebug() << "passed into compile and label" << dec_with_label;
                         decArrinstruction->compile(dec_with_label);
                         Statement *decArrptr = decArrinstruction;
                         return decArrptr;
                     }
                     else{
                         qDebug() << "Statementfactory::createStatement  dca";
                         QString decArr_with_label = op1 + " " + op2;
                         qDebug() << "op1: " << op1;
                         qDebug() << "op2: " << op2;
                         qDebug() << "passed into compile" << decArr_with_label;
                         decArrinstruction->compile(decArr_with_label);
                         qDebug("dca compile completed!");
                         Statement *decArrptr = decArrinstruction;
                         return decArrptr;

                     }
              }

      }


/*
//if its dca
Statement* Statementfactory::createStatement(QString instruction_operator,QString op1,int SizeofArray,Program* program_pointer,QString if_label){
      cout << "dca operator selected within the Statementfactory!!!!!!!!!!!!!!!!!" << endl;
      if((instruction_operator.compare("dca")) == 0){ //dcastmt
               cout << "dca operator selected!" << endl;
               qDebug() << "if_label: " << if_label;
               qDebug() << "program_pointer"  << program_pointer;
               Statement *decArrinstruction = new DeclArrStmt(program_pointer);
               if(!(if_label.isNull())){
                   QString dec_with_label = op1 + " " + " " + if_label;
                   //qDebug() << "passed into compile and label" << dec_with_label;
                   decArrinstruction->compile(dec_with_label);
                   Statement *decArrptr = decArrinstruction;
                   return decArrptr;
               }
               else{
                   qDebug() << "Statementfactory::createStatement  dca";

                   qDebug() << "Statementfactory::createStatement dca";
                   QString dec_with_label = op1 + " ";
                   qDebug() << "passed into compile" << dec_with_label;
                   decArrinstruction->compile(dec_with_label);
                   qDebug("dca compile completed!");
                   Statement *decArrptr = decArrinstruction;
                   return decArrptr;

               }
        }

}
*/

