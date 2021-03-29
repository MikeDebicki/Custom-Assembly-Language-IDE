#include "program.h"
#include <QTextStream>
#include <QDebug>
#include <QList>

#include <QObject>
#include <QFile>

Program::Program(QObject* parent) : QObject(parent)
{
    //    connect(  ui->plainTextEdit, SIGNAL( sendText( const QString & ) ), identifier, SLOT( updateText( const QString & ) ) );
}

Program::~Program()
{
    qDebug()<<"Program::~Program()";

}
//parse function for parsing instructions
void Program::parse(QString* list)
{

    //for reading the text
    QTextStream stream(list);

    errorcheck.errorcheck(list);
    //gets the words from text and splitting them
    word = stream.readAll().split("\n"); //,QString::SkipEmptyParts);

    //looping through the text
    for (int j = 0; j < word.size(); j++) {

        //remove the white space from each index
        Toword = word[j].split(" ", QString::SkipEmptyParts);

        //skips empty lines
        if (word[j] != "") {

            //check if the first char isnot # which is a comment
            if (errorcheck.check_for_comment(&Toword[0])) {

                //returns the instruction if its correct
                result = instructions.contains(Toword[0]);


                if (result) {
////////////////////////////////////////////////////////////////////////////////////////////
                    /*
NEW                     STUFF
 */
                    //prt
                    if (errorcheck.check_for_prt_instruction(Toword)) {

                        int counter=errorcheck.check_for_prt(&word,&Toword,&j);

                        if(counter==0){


                            print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' was never initialized");
                            break;
                        }

                        else if(counter==1){
                            qDebug()<<"PRTPRTPRT:"<<Toword[1];
                            statementfactory_ptr = new Statementfactory();
                            Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[0],Toword[1],this,NULL); //returns a statement
                            statement_List.append(statement_ptr);
                        }

                        else if(counter>1){
                           // qDebug() << "error is dci";
                            print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' was initialized "+QString::number(counter)+" times");
                            break;
                        }


                    }
                    else if (errorcheck.check_for_dca_instruction(Toword)) {

                        int counter=errorcheck.check_for_dca(&word,&Toword,&j);
                        if(counter==1){
                            qDebug()<<"this is a dca";
                            statementfactory_ptr = new Statementfactory();
                            Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[0],Toword[1],Toword[2],this,NULL); //returns a statement
                            statement_List.append(statement_ptr);

                        }
                        else if (counter==0) {
                              print_errors("Syntax error: line " + QString::number(j) + ", dca' " + Toword[1] + "' array size was never initialized correctly");
                            break;
                        }
                        else{

                            print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' was initialized "+QString::number(counter)+" times");
                            break;
                        }

                    }

                    //add and mov instruction
                    else if (errorcheck.check_for_add_and_move_instruction(Toword)) {
                            QString output_string=errorcheck.check_for_add_and_move(&word,&Toword,&j);


                            if (output_string=="variableorarray"){

                                statementfactory_ptr = new Statementfactory();
                                Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[0],Toword[1],Toword[2],this,NULL); //returns a statement
                                statement_List.append(statement_ptr);


                            }
                            else if (output_string=="literaldci" ) {
                                statementfactory_ptr = new Statementfactory();
                                Toword[1] = '"' + Toword[1] + '"'; //stringify the first operand as a literal
                                Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[0],Toword[1],Toword[2],this,NULL); //returns a statement
                                statement_List.append(statement_ptr);

                            }
                            else if(output_string=="error"){

                                print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' or Variable '"+Toword[2]+ "' was never initialized");
                                break;
                            }
                    }

                    //checks if cmp instruction
                    else if (errorcheck.check_for_cmp_instruction(Toword)) {

                        QString output = errorcheck.check_for_cmp(&word,&Toword,&j);


                        //cmp without any literals
                        if (output == "dcidci") {
                            statementfactory_ptr = new Statementfactory();
                            Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[0],Toword[1],Toword[2],this,NULL); //returns a statement
                            statement_List.append(statement_ptr);

                        }

                        //cmp with first operand as integer literal
                        else if (output == "literaldci") {
                            statementfactory_ptr = new Statementfactory();
                            Toword[1] = '"' + Toword[1] + '"'; //stringify the first operand as a literal
                            Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[0],Toword[1],Toword[2],this,NULL); //returns a statement
                            statement_List.append(statement_ptr);

                        }

                        //cmp with second operand as integer literal
                        else if (output == "dciliteral") {
                            statementfactory_ptr = new Statementfactory();
                            Toword[2] = '"' + Toword[2] + '"'; //stringify the second operand as a literal
                            Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[0],Toword[1],Toword[2],this,NULL); //returns a statement
                            statement_List.append(statement_ptr);

                        }

                        //cmp with first operand and second operand as integer literals
                        else if (output == "literalliteral") {
                            statementfactory_ptr = new Statementfactory();
                            Toword[1] = '"' + Toword[1] + '"'; //stringify both the first operand and the second as a literal
                            Toword[2] = '"' + Toword[2] + '"';
                            Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[0],Toword[1],Toword[2],this,NULL); //returns a statement
                            statement_List.append(statement_ptr);

                        }
                        else if(output == "literaldca"){
                            statementfactory_ptr = new Statementfactory();
                            Toword[1] = '"' + Toword[1] + '"'; //stringify both the first operand and the second as a literal

                            Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[0],Toword[1],Toword[2],this,NULL); //returns a statement
                            statement_List.append(statement_ptr);

                        }
                        else if(output == "dcaliteral"){
                            statementfactory_ptr = new Statementfactory();
                     //stringify both the first operand and the second as a literal
                            Toword[2] = '"' + Toword[2] + '"';
                            Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[0],Toword[1],Toword[2],this,NULL); //returns a statement
                            statement_List.append(statement_ptr);

                        }

                        else if (output == "dcadca"  or output == "dcidca"  or output == "dcadci"){

                            statementfactory_ptr = new Statementfactory();
                            Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[0],Toword[1],Toword[2],this,NULL); //returns a statement
                            statement_List.append(statement_ptr);
                        }
                        else {

                            qDebug() << "couldn't Find Comp";
                            print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' or Variable '"+Toword[2]+ "' was never initialized");
                            break;
                        }

                    }


                    //if its an end object, create a new statement of type end object and store it in a list of statements
                    else if (Toword[0] == "end" or Toword[0] == "#" or Toword[0].at(0) == '#') {
                        if(Toword[0]=="end"){

                            statementfactory_ptr = new Statementfactory();
                            Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[0],this,NULL); //returns a statement
                            statement_List.append(statement_ptr);

                        }
                    }

                    //check the instruction sizem check if instruction is jstatments
                    else if ( Toword.size() == 2 && errorcheck.check_for_jstatments_instructions(Toword)) {

                        int counter=errorcheck.check_for_jstatments(&word,&Toword,&j);
                        if(counter==0){


                            print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' was never initialized");
                            break;
                        }
                        if(counter>1){

                            print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' was initialized "+QString::number(counter)+" times");
                            break;
                        }

                        //jmp or jmr
                        else {

                            statementfactory_ptr = new Statementfactory();
                            Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[0],Toword[1],this,NULL); //returns a statement
                            statement_List.append(statement_ptr);

                        }


                    }
                    //checks for the other instructions
                    else if (errorcheck.check_for_otheroperands_instructions(Toword)) {
                        //   QStringList words2=stream.readAll().split("\n",QString::SkipEmptyParts);

                        int counter=errorcheck.check_for_otheroperands(&word,&Toword,&j);


                        if(counter==0){


                            print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' was never initialized");
                            break;
                        }

                        //rdi
                        else if(counter==1){

                            statementfactory_ptr = new Statementfactory();
                            Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[0],Toword[1],this,NULL); //returns a statement
                            statement_List.append(statement_ptr);
                        }

                        else if(counter>1){

                            print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' was initialized "+QString::number(counter)+" times");
                            break;
                        }
                    }
                    else if (Toword.size() == 2 && errorcheck.check_for_dci_instruction(Toword)) {
                        int counter=errorcheck.check_for_dci(&word, &Toword,&j);


                        //if its a dci object, create a new statement of type dci object and store it in a list of statements
                        if(counter==1){


                            statementfactory_ptr = new Statementfactory();
                            Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[0],Toword[1],this,NULL); //returns a statement
                            statement_List.append(statement_ptr);


                        }
                        else if(counter>1){
                           // qDebug() << "error is dci";
                            print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' was initialized "+QString::number(counter)+" times");
                            break;
                        }
                    }
                    else {
                        print_errors("error: line " + QString::number(j) + ", Incorrect number of Operands for '" + Toword[0] + "'");
                        break;
                    }
                }

                //checking for labels
                else if ((Toword.size() == 2 or Toword.size() == 3 or Toword.size()==4) && Toword[0].at(Toword[0].size()-1)==":") {


                    //check for cmp
                    if(Toword.size()==4){
                     //stringfining the Toward
                     QStringList sample;
                     sample.append((Toword)[1]);
                     sample.append((Toword)[2]);
                     sample.append((Toword)[3]);
                     //checks if cmp instruction
                      if (errorcheck.check_for_cmp_instruction(sample)) {

                         QString output = errorcheck.check_for_cmp(&word,&sample,&j);

                         qDebug()<<"output "<<output;
                         //cmp without any literals
                         if (output == "dcidci") {
                             statementfactory_ptr = new Statementfactory();
                             Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[1],Toword[2],Toword[3],this,Toword[0].chopped(1)); //returns a statement
                             statement_List.append(statement_ptr);
                             qDebug() << "Found Comp ";
                         }

                         //cmp with first operand as integer literal
                         else if (output == "literaldci") {
                             statementfactory_ptr = new Statementfactory();
                             Toword[1] = '"' + Toword[1] + '"'; //stringify the first operand as a literal
                             Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[1],Toword[2],Toword[3],this,Toword[0].chopped(1)); //returns a statement
                             statement_List.append(statement_ptr);
                             qDebug() << "Found Comp ";
                         }

                         //cmp with second operand as integer literal
                         else if (output == "dciliteral") {
                             statementfactory_ptr = new Statementfactory();
                             Toword[2] = '"' + Toword[2] + '"'; //stringify the second operand as a literal
                             Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[1],Toword[2],Toword[3],this,Toword[0].chopped(1)); //returns a statement
                             statement_List.append(statement_ptr);
                             qDebug() << "Found Comp ";
                         }

                         //cmp with first operand and second operand as integer literals
                         else if (output == "literalliteral") {
                             statementfactory_ptr = new Statementfactory();
                             Toword[1] = '"' + Toword[1] + '"'; //stringify both the first operand and the second as a literal
                             Toword[2] = '"' + Toword[2] + '"';
                             Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[1],Toword[2],Toword[3],this,Toword[0].chopped(1)); //returns a statement
                             statement_List.append(statement_ptr);
                             qDebug() << "Found Comp ";
                         }
                         else if(output == "literaldca"){
                             statementfactory_ptr = new Statementfactory();
                             Toword[1] = '"' + Toword[1] + '"'; //stringify both the first operand and the second as a literal

                             Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[1],Toword[2],Toword[3],this,Toword[0].chopped(1)); //returns a statement
                             statement_List.append(statement_ptr);

                         }
                         else if(output == "dcaliteral"){
                             statementfactory_ptr = new Statementfactory();
                      //stringify both the first operand and the second as a literal
                             Toword[2] = '"' + Toword[2] + '"';
                             Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[1],Toword[2],Toword[3],this,Toword[0].chopped(1)); //returns a statement
                             statement_List.append(statement_ptr);

                         }

                         else if (output == "dcadca"  or output == "dcidca"  or output == "dcadci"){

                             statementfactory_ptr = new Statementfactory();
                             Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[1],Toword[2],Toword[3],this,Toword[0].chopped(1)); //returns a statement
                             statement_List.append(statement_ptr);
                         }
                         else {

                             qDebug() << "couldn't Find Comp";
                             print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' or Variable '"+Toword[2]+ "' was never initialized");
                             break;
                         }
                     }
                      else if (errorcheck.check_for_add_and_move_instruction(sample)) {

                              QString output=errorcheck.check_for_add_and_move(&word,&sample,&j);
                              if (output=="literaldci" or output=="variableorarray"){
                                  statementfactory_ptr = new Statementfactory();
                                  Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[1],Toword[2],Toword[3],this,Toword[0].chopped(1)); //returns a statement
                                  statement_List.append(statement_ptr);
                                  qDebug() << "Found Comp ";
                              }

                              else if(output=="error"){

                                  print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' or Variable '"+Toword[2]+ "' was never initialized");
                                  break;
                              }
                      }
                 }

                    else if (Toword.size()==3) {
                        QStringList sample;
                        sample.append((Toword)[1]);
                        sample.append((Toword)[2]);

                        if(errorcheck.check_for_dci_instruction(sample)) {
/*
                           int  counter=errorcheck.check_for_dci(&word,&sample,&j);
                           if(counter==1){


                            //if its an dci object in a label, create a new statement of type end object and store it in a list of statements
                            statementfactory_ptr = new Statementfactory();
                            Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[1],Toword[2],this,Toword[0].chopped(1));
                            statement_List.append(statement_ptr);
                         //  for (int i = 0; i < statement_List.size();i++){
                         //       delete statement_List[i];
                         //   }

                           }
                           else if(counter>1){
                               //qDebug() << "error is dci";
                               print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' was initialized "+QString::number(counter)+" times");
                               break;
                           }
                           */
                            print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[2] + " Dci Instruction can't be used in labels");
                            break;
                        }
                        else if (errorcheck.check_for_otheroperands_instructions(sample)) {


                        int counter=errorcheck.check_for_otheroperands(&word,&sample,&j);
                        if(counter==0){

                            //qDebug() << "dci couldn't be found ";
                            print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[2] + "' was never initialized");
                            break;
                        }

                        //if its an rdi object with label, create a new statement of type rdi and prt object and store it in a list of statements
                        else if (counter==1) {
                            //insert rdi
                            statementfactory_ptr = new Statementfactory();
                            Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[1],Toword[2],this,Toword[0].chopped(1)); //returns a statement
                            statement_List.append(statement_ptr);
                        }
                        if(counter>1){

                            print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' was initialized "+QString::number(counter)+" times");
                            break;
                        }

                        }
                        else if (errorcheck.check_for_jstatments_instructions(sample)) {
                            qDebug()<<"i am here";
                        int counter=errorcheck.check_for_jstatments(&word,&sample,&j);
                        if(counter==0){

                           // qDebug() << "label for jump couldn't be found ";
                            print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' was never initialized");
                            break;
                        }

                        //if its jmp or jmr object in a label, create a new statement of type jmr or jmp object and store it in a list of statements
                        if(counter==1){
                            statementfactory_ptr = new Statementfactory();
                            Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[1],Toword[2],this,Toword[0].chopped(1)); //returns a statement
                            statement_List.append(statement_ptr);
                        }
                        if(counter>1){

                            print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' was initialized "+QString::number(counter)+" times");
                            break;
                        }
                        else {
                          //  qDebug()<<"found label";
                        }
                    }

                        else if (errorcheck.check_for_prt_instruction(sample)) {

                            int counter=errorcheck.check_for_prt(&word,&sample,&j);

                            if(counter==0){


                                print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' was never initialized");
                                break;
                            }

                            //if its a dci object, create a new statement of type dci object and store it in a list of statements
                            else if(counter==1){
                             //qDebug() << "this is dci";
                                qDebug()<<"PRTPRTPRT:"<<Toword[1];
                                statementfactory_ptr = new Statementfactory();
                                Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[1],Toword[2],this,Toword[0].chopped(1)); //returns a statement
                                statement_List.append(statement_ptr);
                            }

                            else if(counter>1){
                               // qDebug() << "error is dci";
                                print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' was initialized "+QString::number(counter)+" times");
                                break;
                            }

                        }
                        else if (errorcheck.check_for_dca_instruction(sample)) {

                            int counter=errorcheck.check_for_dca(&word,&sample,&j);

                            if(counter==1){
                                qDebug()<<"this is a dca";
                                statementfactory_ptr = new Statementfactory();
                                Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[1],Toword[2],Toword[3],this,Toword[0].chopped(1)); //returns a statement
                                statement_List.append(statement_ptr);
                                qDebug() << "Found Comp ";
                            }
                            else if (counter==0) {
                                  print_errors("Syntax error: line " + QString::number(j) + ", dca' " + Toword[1] + "' array size was never initialized correctly");
                                break;
                            }
                            else{

                                print_errors("Syntax error: line " + QString::number(j) + ", Variable' " + Toword[1] + "' was initialized "+QString::number(counter)+" times");
                                break;
                            }

                        }



                    }


                    //if its an end object in a label, create a new statement of type end object and store it in a list of statements
                    else if (Toword.size()==2) {
                        if(Toword[1]=="end"){

                            statementfactory_ptr = new Statementfactory();
                            Statement *statement_ptr = statementfactory_ptr->createStatement(Toword[1],this,Toword[0].chopped(1)); //returns a statement
                            statement_List.append(statement_ptr);
                        }

                    }

                }
                else {
                    QString line_number = QString::number(j);
                    print_errors("Syntax error: line " + line_number + " '" + Toword[0] + "' Unknow Instruction");
                    break;
                }
            }
        }
    }
}
//send signal to display error on textedit
void Program::print_errors(QString error_message)
{

    qDebug()<<"qlist:"<<idlist.size();
    emit send_print_errors(error_message);
}
void Program::send_to_runcontrol(QString message){
    qDebug()<<"send_to_runcontrol "<<message;
    emit send_rdi(message);

}


Identifier* Program::getLabel(QString labelName)
{

  for(int i = 0; i < idlist.size(); i += 1)
  {
    if(idlist[i]->getName() == labelName)
    {
      idlist[i]->setValue(statement_List.size());
      return idlist[i];
    }
  }
  Identifier *newLabel = new Label(labelName);
  newLabel->setValue(statement_List.size());
  idlist.append(newLabel);
  return newLabel;
}

void Program::addList(Statement* news)
{
  statement_List.append(news);
}


Identifier* Program::getVariable(QString variableName)
{

  for(int i = 0; i < idlist.size(); i += 1)
  {

    if(idlist[i]->getName() == variableName)
    {
      return idlist[i];
    }
  }

  Identifier *newVariable = new Variable(variableName);
  idlist.append(newVariable);

  return newVariable;
}

Identifier* Program::getVariable(QString variableName, int value)
{

  for(int i = 0; i < idlist.size(); i += 1)
  {

    if(idlist[i]->getName() == variableName)
    {
      return idlist[i];
    }
  }

  Identifier *newVariable = new Variable(variableName, 1);
  newVariable->setValue(0,value);
  idlist.append(newVariable);

  return newVariable;
}

Identifier* Program::getIdentifier(QString variableName)
{

  for(int i = 0; i < idlist.size(); i += 1)
  {
    if(idlist[i]->getName() == variableName)
    {
      return idlist[i];
    }
  }

  Identifier *newIdentifier = new Identifier(variableName);
  idlist.append(newIdentifier);
  return newIdentifier;
}


void Program::serialize()
{

  QJsonObject statementObjects;

  for(int i = 0; i < statement_List.size(); i += 1)
  {

    QJsonObject statement;
    statement.insert("Type", statement_List[i]->getType());
    if(statement_List[i]->getOperand1() != NULL)
    {
      if(statement_List[i]->getArrayPosition(1) != 0)
      {
        statement.insert("Operand1", "$" + statement_List[i]->getOperand1()->getIdentifier()->getName() + QStringLiteral("+%1").arg(statement_List[i]->getArrayPosition(1)));
      }
      else
      {
        statement.insert("Operand1", statement_List[i]->getOperand1()->getIdentifier()->getName());
      }
    }
    else
    {
      statement.insert("Operand1", "");
    }
    if(statement_List[i]->getOperand2() != NULL)
    {
      if(statement_List[i]->getArrayPosition(2) != 0)
      {
        statement.insert("Operand2", "$" + statement_List[i]->getOperand2()->getIdentifier()->getName() + QStringLiteral("+%1").arg(statement_List[i]->getArrayPosition(2)));
      }
      else
      {
        statement.insert("Operand2", statement_List[i]->getOperand2()->getIdentifier()->getName());
      }
    }
    else
    {
      statement.insert("Operand2", "");
    }
    if(statement_List[i]->getLabel() != NULL)
    {

      statement.insert("Label", statement_List[i]->getLabel()->getName());
    }
    else
    {
      statement.insert("Label", "");
    }

    statementObjects.insert(QString("Statement %1").arg(i+1), statement);
  }
//  QJsonDocument doc(statementObjects);
  QJsonDocument doc(statementObjects);
  for (int j=0;statementObjects.size();j++) {
      qDebug()<<statementObjects.take(QString("Statement %1").arg(j+1));
  }


  notify(&doc);

}
void Program::notify(QJsonDocument* document){

    const QDir home = QDir::home();

    if (QFileInfo::exists(home.absoluteFilePath("SCAPES.json")))
    {
        qDebug() << "file exists";
        QFile::resize(home.absoluteFilePath("SCAPES.json"), 0);
    }

    QFile jsonFile(home.absoluteFilePath("SCAPES.json"));
    jsonFile.open(QFile::WriteOnly);
    jsonFile.write(document->toJson());
    jsonFile.close();

}

void Program::read()
{
    const QDir home = QDir::home();
    if (QFileInfo::exists(home.absoluteFilePath("SCAPES.json")))
    {

        QFile jsonFile(home.absoluteFilePath("SCAPES.json"));
        jsonFile.open(QFile::ReadOnly);
        QByteArray byteData = jsonFile.readAll();
        jsonFile.close();
        auto jsonDoc = QJsonDocument::fromJson(byteData);
        QJsonObject statementObjects = jsonDoc.object();

        for (int j=0; statementObjects.size();j++) {
            QJsonObject obj = statementObjects.take(QString("Statement %1").arg(j+1)).toObject();
            QString type = obj.value("Type").toString();
            QString op1 = obj.value("Operand1").toString();
            QString op2 = obj.value("Operand2").toString();
            QString label = obj.value("Label").toString();
            QString dca_size = obj.value("Array").toString();

            //if it's either dci, rdi, prt, jmr, jmp, jeq, jls
            if ((type.compare("dci") ==0) || (type.compare("rdi") ==0) || (type.compare("prt") ==0)
                    || (type.compare("jmr") ==0) || (type.compare("jmp") ==0) || (type.compare("jeq") ==0)
                    || (type.compare("jls") ==0))  {

                //if there's a label
                if (!(label.isEmpty())){
                    statementfactory_ptr= new Statementfactory();
                    Statement *statement_ptr = statementfactory_ptr->createStatement(type, op1, this, label);
                    statement_List.append(statement_ptr);
                }

                //if there's no label
                else {
                    statementfactory_ptr= new Statementfactory();
                    Statement *statement_ptr = statementfactory_ptr->createStatement(type, op1, this, NULL);
                    statement_List.append(statement_ptr);
                }
            }

            //if it's cmp or mov or add
            else if ((type.compare("cmp") ==0) || (type.compare("mov") ==0) || (type.compare("add") ==0) ){

                //if there's a label
                if (!(label.isEmpty())){
                    QStringList operan1=op1.split(" ");
                    QStringList operan2=op2.split(" ");
                    //if either operand 1 or operand 2 for cmp is a literal, add strings around it
                    if ((type.compare("cmp") == 0) and (operan1[0].compare("LITERAL") == 0)){
                        operan1[1] = '"' + operan1[1] + '"';
                        statementfactory_ptr= new Statementfactory();
                        Statement *statement_ptr = statementfactory_ptr->createStatement(type, operan1[1], op2, this, label);
                        statement_List.append(statement_ptr);
                    }
                    else if ((type.compare("cmp") == 0) and operan2[0].compare("LITERAL") == 0){
                        operan2[1] = '"' + operan2[1] + '"';
                        statementfactory_ptr= new Statementfactory();
                        Statement *statement_ptr = statementfactory_ptr->createStatement(type, op1, operan2[1], this, label);
                        statement_List.append(statement_ptr);
                    }
                    else if ((type.compare("cmp") == 0) and (operan1[0].compare("LITERAL") == 0) and operan2[0].compare("LITERAL") == 0){
                        operan1[1] = '"' + operan1[1] + '"';
                        operan2[1] = '"' + operan2[1] + '"';
                        statementfactory_ptr= new Statementfactory();
                        Statement *statement_ptr = statementfactory_ptr->createStatement(type, operan1[1], operan2[1], this, label);
                        statement_List.append(statement_ptr);
                    }
                    else if ((type.compare("mov") == 0) and (operan1[0].compare("LITERAL") == 0)){
                        operan1[1] = '"' + operan1[1] + '"';
                        statementfactory_ptr= new Statementfactory();
                        Statement *statement_ptr = statementfactory_ptr->createStatement(type, operan1[1], op2, this, label);
                        statement_List.append(statement_ptr);
                    }
                    else if ((type.compare("add") == 0) and (operan1[0].compare("LITERAL") == 0)){
                        operan1[1] = '"' + operan1[1] + '"';
                        statementfactory_ptr= new Statementfactory();
                        Statement *statement_ptr = statementfactory_ptr->createStatement(type, operan1[1], op2, this, label);
                        statement_List.append(statement_ptr);
                    }

                    //not neither operands are literals
                    else{
                        statementfactory_ptr= new Statementfactory();
                        Statement *statement_ptr = statementfactory_ptr->createStatement(type, op1, op2, this, label);
                        statement_List.append(statement_ptr);
                    }

                }

                //if there's no label for cmp
                else {
                    QStringList operan1=op1.split(" ");
                    QStringList operan2=op2.split(" ");
                    //if either operand 1 or operand 2 for cmp is a literal, add strings around it
                    if ((type.compare("cmp") == 0) and (operan1[0].compare("LITERAL") == 0) and operan2[0].compare("LITERAL") == 0){
                        operan1[1] = '"' + operan1[1] + '"';
                        operan2[1] = '"' + operan2[1] + '"';
                        statementfactory_ptr= new Statementfactory();
                        Statement *statement_ptr = statementfactory_ptr->createStatement(type, operan1[1], operan2[1], this, NULL);
                        statement_List.append(statement_ptr);
                    }
                    else if ((type.compare("cmp") == 0) and (operan1[0].compare("LITERAL") == 0)){
                        operan1[1] = '"' + operan1[1] + '"';
                        statementfactory_ptr= new Statementfactory();
                        Statement *statement_ptr = statementfactory_ptr->createStatement(type, operan1[1], op2, this, NULL);
                        statement_List.append(statement_ptr);
                    }
                    else if ((type.compare("cmp") == 0) and operan2[0].compare("LITERAL") == 0){
                        operan2[1] = '"' + operan2[1] + '"';
                        statementfactory_ptr= new Statementfactory();
                        Statement *statement_ptr = statementfactory_ptr->createStatement(type, op1, operan2[1], this, NULL);
                        statement_List.append(statement_ptr);
                    }

                    else if ((type.compare("mov") == 0) and (operan1[0].compare("LITERAL") == 0)){
                        operan1[1] = '"' + operan1[1] + '"';
                        statementfactory_ptr= new Statementfactory();
                        Statement *statement_ptr = statementfactory_ptr->createStatement(type, operan1[1], op2, this, NULL);
                        statement_List.append(statement_ptr);
                    }
                    else if ((type.compare("add") == 0) and (operan1[0].compare("LITERAL") == 0)){
                        operan1[1] = '"' + operan1[1] + '"';
                        statementfactory_ptr= new Statementfactory();
                        Statement *statement_ptr = statementfactory_ptr->createStatement(type, operan1[1], op2, this, NULL);
                        statement_List.append(statement_ptr);
                    }

                    else{
                        statementfactory_ptr= new Statementfactory();
                        Statement *statement_ptr = statementfactory_ptr->createStatement(type, op1, op2, this, NULL);
                        statement_List.append(statement_ptr);
                    }
                }
            }

            //if it's dca
            else if ((type.compare("dca") ==0)){
            //dca + a label
            if (!(label.isNull())){
                statementfactory_ptr= new Statementfactory();
                Statement *statement_ptr = statementfactory_ptr->createStatement(type, op1, dca_size, this, label);
             }
            //dca +  no label
            else {
                statementfactory_ptr= new Statementfactory();
                Statement *statement_ptr = statementfactory_ptr->createStatement(type, op1, dca_size, this, NULL);
              }
            }


            // if it's end
            else if ((type.compare("end") ==0)){

                // end + label
                if (!(label.isEmpty())){
                    qDebug() <<"end is with label";
                    statementfactory_ptr= new Statementfactory();
                    Statement *statement_ptr = statementfactory_ptr->createStatement(type, this, label);
                    statement_List.append(statement_ptr);
                }

                // end + no label
                else {
                    statementfactory_ptr= new Statementfactory();
                    Statement *statement_ptr = statementfactory_ptr->createStatement(type, this, NULL);
                    statement_List.append(statement_ptr);
                }
            }

        }
    }
}


//iterates through the statementarray
void Program::runthroughstatementarray(){
    while(statement_array_index < statement_List.size()){

        //if operand2 is empty, increment index and go to next iteration of loop
        if (statement_List[statement_array_index]->getOperand2() == NULL && statement_List[statement_array_index] != NULL){
            statement_List[statement_array_index]->run();
            send_to_runcontrol("Execution of: " + statement_List[statement_array_index]->getType());
            send_to_runcontrol("with the first value of: ");
            send_to_runcontrol(statement_List[statement_array_index]->getOperand1()->getIdentifier()->getName());

            if(programJumped == false)
            {
              statement_array_index++;
            }
            else
            {
              programJumped = false;
            }
            continue;

        }

        //if operand 2 is NOT empty, increment index and go to next iteration of loop
        if (statement_List[statement_array_index]->getOperand2() != NULL && statement_List[statement_array_index] != NULL){
            statement_List[statement_array_index]->run();
            send_to_runcontrol("Execution of: " + statement_List[statement_array_index]->getType());
            send_to_runcontrol("with the first value of: ");
            send_to_runcontrol(statement_List[statement_array_index]->getOperand1()->getIdentifier()->getName());
            send_to_runcontrol("and the second value of: ");
            send_to_runcontrol(statement_List[statement_array_index]->getOperand2()->getIdentifier()->getName());
            if(programJumped == false)
            {
              statement_array_index++;
            }
            else
            {
              programJumped = false;
            }
            continue;
        }


        //if it does throw a NULL, then we reached end of array and we break the while loop
        else{break;}

    }
}

void Program::printVariables(){
    for(int i = 0; i < idlist.size(); i++){ 
        if (statement_List[statement_array_index]->getOperand2() == NULL && statement_List[statement_array_index] != NULL){
            send_to_runcontrol("Variable value of: "+ idlist[i]->getName() + " is " + statement_List[i]->getOperand1()->getIdentifier()->getValue());
        }
     }
}



void Program::trigger_rdi_window(){


    emit send_rdi_window();

}

void Program::getNuse_rdi(int* n){

    qDebug() << "n value in Program::getNuse_rdi" <<*n;
    qDebug() << "stmt list size Program::getNuse_rdi = " << statement_List.size();
    N=*n;

}

// new functions

void Program::setFlag(int newFlagState)
{
  comparisonFlag = newFlagState;
}

void Program::setRuntimePosition(int jumpLocation)
{
  statement_array_index = jumpLocation;
  programJumped = true;
}

int Program::getFlag()
{
  return comparisonFlag;
}



void Program::printToWindow(QString printable)
{
 /*
  qDebug() << printable;
  qDebug() << "PRINTINNGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG";
 */
}

int Program::getUserWindowInput()
{
  trigger_rdi_window();
  qDebug() << N;

  return N;
}

Identifier* Program::createVariable(QString variableName, int arraySize)
{
    Identifier *newVariable = new Variable(variableName, arraySize);
    idlist.append(newVariable);
    return newVariable;
}

Identifier* Program::createLabel(QString labelName)
{

  for(int i = 0; i < idlist.size(); i += 1)
  {
    if(idlist[i]->getName() == labelName)
    {
      return idlist[i];
    }
  }
  Identifier *newLabel = new Label(labelName);
  idlist.append(newLabel);
  return newLabel;
}

void Program::endProgram()
{
  statement_array_index = (statement_List.size() + 1 );
}
