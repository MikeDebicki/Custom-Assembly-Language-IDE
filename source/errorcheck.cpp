#include "errorcheck.h"


ErrorCheck::ErrorCheck(QObject *parent) :QObject (parent)
{
    //    connect(  ui->plainTextEdit, SIGNAL( sendText( const QString & ) ), identifier, SLOT( updateText( const QString & ) ) );

}

void ErrorCheck::errorcheck(QString *list) {

     QTextStream stream(list);

    word=stream.readAll().split("\n");
     for (int j=0; j<word.size();j++) {

         //remove the white space from each index
         Toword=word[j].split(" ",QString::SkipEmptyParts);

         //skips empty lines
         if (word[j]!="") {




        }

     }


}
//check if string is a comment
bool ErrorCheck::check_for_comment(QString *string){

    if(string[0].at(0)!="#"){
        return true;
    }

    return false;
}

//check if the string is cmp
bool ErrorCheck::check_for_cmp_instruction(QStringList &list){

    if(list.size()==3 && cmp_operand.contains(list[0],Qt::CaseSensitive)){
        qDebug()<<"3 operands";
        return true;


    }
    return false;

}

//checks for the variables of cmp if they are inisialized before
QString ErrorCheck::check_for_cmp(QStringList *word,QStringList *Toword,int *j) {

    /*
    QStringList otherwords = (*word)[*j].split(" ");
    QStringList literal=otherwords;
    QString output="";
   qDebug()<<"otherwords"<<otherwords;
   int counter=0;
   QRegExp re("\\d*");
   //check if operand1 is integar

    if(re.exactMatch(literal[1].remove('"'))){

        //check if  operand1 is a literal
       if(otherwords[1].at(0)=='"' && otherwords[1].at(otherwords[1].size()-1)=='"' ){

            output+="literal";
       }
   }
    if (re.exactMatch(literal[2].remove('"'))) {
        if(otherwords[2].at(0)=='"' && otherwords[2].at(otherwords[2].size()-1)=='"' ){

             output+="literal";
        }
    }
    else{

    //qDebug()<<Toword.size();
    for (int k = (*j) - 1; k >= 0; k--) {

        QStringList otherwords = (*word)[k].split(" ");

        // qDebug() <<"otherwords:  "<<otherwords[0];
        if (check_for_dci_instruction(otherwords) or check_for_dca_instruction(otherwords)) {
        qDebug()<<"TOWORD"<<Toword;

            if ((*Toword)[1] == otherwords[1]) {
                counter++;
                // qDebug() <<"Found the word";
            }
//                       else {
                //       qDebug ()<<"not Found";
//                     }
            //         }
            //  qDebug() <<"otherwords: "<<otherwords;
        }
        //                             qDebug()<<"line "<<j<<", "<<Toword.size();
    }
    for (int k = (*j) - 1; k >= 0; k--) {

        QStringList otherwords = (*word)[k].split(" ");
        // qDebug() <<"otherwords:  "<<otherwords[0];
        if (check_for_dci_instruction(otherwords) or check_for_dca_instruction(otherwords)) {

            if ((*Toword)[2] == otherwords[1]) {
                counter++;
                //qDebug() <<"Found the word";
            }
        //    else {
                //  qDebug ()<<"not Found";
      //      }
            //         }
            //  qDebug() <<"otherwords: "<<otherwords;
        }
        //                             qDebug()<<"line "<<j<<", "<<Toword.size();
    }
    if(counter==2){

        return "arrayvariable";
    }
   }
    return output;
*/
    QString output="";

    QStringList otherwords = (*word)[*j].split(" ",QString::SkipEmptyParts);
    QStringList literal=*Toword;
   qDebug()<<"literal"<<literal;
   QStringList dca_operand1=(*Toword);
   QString is_number1=dca_operand1[1].mid(dca_operand1[1].indexOf("+")+1);
   QString is_number2=dca_operand1[2].mid(dca_operand1[2].indexOf("+")+1);
   dca_operand1[1].remove(0,1);
   dca_operand1[1].remove(dca_operand1[1].indexOf("+"),dca_operand1[1].size());
   dca_operand1[2].remove(0,1);
   dca_operand1[2].remove(dca_operand1[2].indexOf("+"),dca_operand1[2].size());


   QRegExp re("\\d*");
   //check if operand1 is integar
    if(re.exactMatch(literal[1])) {
        qDebug()<<"INSIDE LITERAL 1";
        //check if  operand1 is a literal

            output+="literal";

    }

    for (int k = (*j) - 1; k >= 0; k--) {

        QStringList otherwords = (*word)[k].split(" ",QString::SkipEmptyParts);

       if((*word)[k]!=""){
        if (check_for_dci_instruction(otherwords)) {


            if ((*Toword)[1] == otherwords[1]) {
                output+="dci";
                // qDebug() <<"Found the word";
            }
            else if (((otherwords.size() == 2 or otherwords.size() == 3 or otherwords.size()==4) && otherwords[0].at((otherwords)[0].size()-1)==":") ) {
                if ((*Toword)[1] == otherwords[2]) {
                    output+="dci";
                    //qDebug() <<"Found the word";
                }
            }
//                       else {
                //       qDebug ()<<"not Found";
//                     }
            //         }
            //  qDebug() <<"otherwords: "<<otherwords;
        }
        if (check_for_dca_instruction(otherwords)) {
            if(re.exactMatch(is_number1)){
                if (dca_operand1[1] == otherwords[1]) {
                    output+="dca";
                    // qDebug() <<"Found the word";
                }
            }

        }
    }
        //                             qDebug()<<"line "<<j<<", "<<Toword.size();
    }
    if(re.exactMatch(literal[2])) {

        //check if  operand1 is a literal

            output+="literal";

    }

    for (int k = (*j) - 1; k >= 0; k--) {

        QStringList otherwords = (*word)[k].split(" ",QString::SkipEmptyParts);
        // qDebug() <<"otherwords:  "<<otherwords[0];
        if((*word)[k]!=""){
        if (check_for_dci_instruction(otherwords)) {
  //           qDebug()<<"TOWORDadasdasdadada"<<(*Toword)[2];
            qDebug() <<"otherwords2:  "<<otherwords[1]<<"Towords2: "<<(*Toword)[2];
            if ((*Toword)[2] == otherwords[1]) {
                output+="dci";
                //qDebug() <<"Found the word";
            }
            else if (((otherwords.size() == 2 or otherwords.size() == 3 or otherwords.size()==4) && otherwords[0].at((otherwords)[0].size()-1)==":") ) {
                if ((*Toword)[2] == otherwords[2]) {
                    output+="dci";
                    //qDebug() <<"Found the word";
                }
            }
        //    else {
                //  qDebug ()<<"not Found";
      //      }
            //         }
            //  qDebug() <<"otherwords: "<<otherwords;
        }
        else if (check_for_dca_instruction(otherwords)) {
            if(re.exactMatch(is_number2)){
                if ( dca_operand1[2]== otherwords[1]) {
                   output+="dca";
                    // qDebug() <<"Found the word";
                }
            }
        }
        }
        //                             qDebug()<<"line "<<j<<", "<<Toword.size();
    }

    qDebug()<<"OUTPUTt: "<<output;
    return output;
}
//check for dci if its a string
bool ErrorCheck::check_for_dci_instruction(QStringList &string) {
    qDebug()<<"DCI WORD "<<string;
    if (string[0]=="dci"){
        return true;


}
    return false;


}


bool ErrorCheck::check_for_otheroperands_instructions(QStringList &list){

    if(list.size()==2 && instructions.contains(list[0],Qt::CaseSensitive)){

        return true;

    }
        return  false;


}


//checks for j statments instructions
bool ErrorCheck::check_for_jstatments_instructions(QStringList &list){

    if(list.size()==2 && j_instructions.contains(list[0],Qt::CaseSensitive)){

        return true;

    }
    return false;

}

//check the operands check for j_statments
int ErrorCheck::check_for_jstatments(QStringList *word, QStringList *Toword, int *j){
    int counter=0;
    for (int z = 0; z < (*word).size(); z++) {
        if ((*word)[z] != "") {
        QStringList j_check=(*word)[z].split(" ");
        qDebug()<<"j_check"<<j_check[0].chopped(1);
             if((*j)!=z){

                qDebug()<<"I am  inside the second if";
                if((*Toword)[1]==j_check[0].chopped(1)){
                    qDebug()<<"I am  inside the third if";
                    counter++;
                }

            }

        }
    }

    return counter;
}

//check the other operands
int ErrorCheck::check_for_otheroperands(QStringList *word,QStringList *Toword,int *j){
    int counter=0;
    QStringList dca_operand1=(*Toword);
    dca_operand1[1].indexOf("+");
    //is number is to check if the string after the + is an int or not
    QString is_number=dca_operand1[1].mid(dca_operand1[1].indexOf("+")+1);

    dca_operand1[1].remove(0,1);
    //remove the + and the string after it to check for the array if it exists
    qDebug()<<"dca_operand1[1] "<<dca_operand1[1].remove(dca_operand1[1].indexOf("+"),dca_operand1[1].size());
    qDebug()<<"dca_operand1[1] "<<dca_operand1[1];
    for (int k = (*j) - 1; k >= 0; k--) {

        QStringList otherwords = (*word)[k].split(" ",QString::SkipEmptyParts);
        // qDebug() <<"otherwords:  "<<otherwords[0];
        if((*word)[k]!=""){
        if (check_for_dci_instruction(otherwords) || check_for_dca_instruction(otherwords)) {
            qDebug()<<"check_for_otheroperands"<<otherwords;
            if ((*Toword)[1] == otherwords[1]) {

                qDebug() << "Found the word";
                counter++;

            }
            else if((dca_operand1[1]==otherwords[1])){

              counter++;
            }

        //    else {
          //      qDebug() << "not Found";
           // }
            //         }
            //  qDebug() <<"otherwords: "<<otherwords;
        }

    }
    }
      return counter;



}


//check for duplictes for dci
int ErrorCheck::check_for_dci(QStringList *word, QStringList *Toword, int *j){
    int counter=1;


    for (int z = 0; z < (*word).size(); z++) {
        QStringList dci_check=(*word)[z].split(" ",QString::SkipEmptyParts);
        if((*word)[z]!=""){
        if(*j!=z){

            if(check_for_dci_instruction(dci_check) or check_for_dca_instruction(dci_check)){

                if((*Toword)[1]==dci_check[1]){

                    counter++;
                }
            }
        }
}
    }
    return counter;

}
//check if string is a label
int ErrorCheck::check_for_label(QStringList *word, QStringList *Toword, int *j) {
    int counter=1;

    for (int z = 0; z < (*word).size(); z++) {
        QStringList dci_check=(*word)[z].split(" ",QString::SkipEmptyParts);


       if((*word)[z]!=""){
        if((*j)!=z){


                    if((*Toword)[1]==dci_check[1]){

                        counter++;
                    }


        }
}
    }
    return counter;
}
/*
NEW STUFF GOOD STUFF
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////
bool ErrorCheck::check_for_dca_instruction(QStringList &list){
    if(list.size()==3 && list[0]=="dca"){
        return true;


    }
    return false;


}

int ErrorCheck::check_for_dca(QStringList *word,QStringList *Toword,int *j){

    int counter=1;
    QRegExp re("\\d*");
    //checks if the second paramter is a number
    QString number=(*Toword)[2];
    //checks if the first paramter isnot a number
    QString string=(*Toword)[1];
   if (re.exactMatch(number) && !re.exactMatch(string)){
        for (int z = 0; z < (*word).size(); z++) {
            QStringList dci_check=(*word)[z].split(" ",QString::SkipEmptyParts);
        if((*word)[z]!=""){
            if(*j!=z){

                if(check_for_dca_instruction(dci_check) or check_for_dci_instruction(dci_check)){

                    if((*Toword)[1]==dci_check[1]){

                        counter++;
                    }
                }
            }

        }
        }
    }
   else{ counter--;}
   qDebug()<<"counter"<<counter;
    return counter;


}

bool ErrorCheck::check_for_prt_instruction(QStringList &string){

    if(prt_instruction.contains(string[0],Qt::CaseSensitive)){
        qDebug()<<"its a pritn statment";
        return true;

    }
        return  false;


}

//check the other operands
int ErrorCheck::check_for_prt(QStringList *word,QStringList *Toword,int *j) {
    int counter=0;

     QStringList otherwords = *Toword;
    qDebug()<<"print "<< otherwords;

    if(otherwords[1].at(0)=='"'){// && otherwords[1].at(otherwords[1].size()-1)=='"' ){
        counter++;
        qDebug()<<"CAKE "<<*Toword;
        return counter;
    }

    QStringList dca_operand1=(*Toword);
    QRegExp re("\\d*");
    //create a qstring to chopp it and check for $ and + sign for an array
    qDebug()<<"dca_operand1 "<<dca_operand1[1];
    qDebug()<<"dca_operand1[1].indexOf()"<<dca_operand1[1].indexOf("+");
    //is number is to check if the string after the + is an int or not
    QString is_number=dca_operand1[1].mid(dca_operand1[1].indexOf("+")+1);
    qDebug()<<"is_numbe "<<is_number;
    //remove the + sign
    qDebug()<<"dca_operand1[1] "<<dca_operand1[1].remove(0,1);
    //remove the + and the string after it to check for the array if it exists
    qDebug()<<"dca_operand1[1] "<<dca_operand1[1].remove(dca_operand1[1].indexOf("+"),dca_operand1[1].size());
    qDebug()<<"dca_operand1[1] "<<dca_operand1[1];

 // qDebug()<<"otherwords"<<otherwords[1];
    for (int k = (*j) - 1; k >= 0; k--) {
        qDebug()<<"THIS IS k"<<k;
        QStringList otherwords = (*word)[k].split(" ",QString::SkipEmptyParts);
        qDebug()<<"PRINT INSTRUCTION "<<otherwords;
        if((*word)[k]!=""){
        if (check_for_dci_instruction(otherwords)) {

            if ((*Toword)[1] == otherwords[1]) {

                qDebug() << "Found the word";
                counter++;
            }

        //    else {
          //      qDebug() << "not Found";
           // }
            //         }
            //  qDebug() <<"otherwords: "<<otherwords;
        }

      //  if(re.exactMatch(is_number)){
            if (check_for_dca_instruction(otherwords) ) {

                    if (dca_operand1[1]== otherwords[1]) {

                        qDebug() << "Found the word";
                        counter++;
                    }

                //    else {
                  //      qDebug() << "not Found";
                   // }
                    //         }
                    //  qDebug() <<"otherwords: "<<otherwords;
      //          }

        }
    }
      }
      qDebug()<<"COUNTER"<<counter;
      return counter;



}


bool ErrorCheck::check_for_add_and_move_instruction(QStringList &string){

    if(string.size()==3 && add_and_remove_instructions.contains(string[0],Qt::CaseSensitive)){

        return true;


    }
    return false;


}


QString ErrorCheck::check_for_add_and_move(QStringList *word, QStringList *Toword, int *j) {

     QStringList otherwords = (*word)[*j].split(" ");
     QStringList literal=otherwords;
  //  qDebug()<<"otherwords"<<otherwords;
    int counter=0;
    QRegExp re("\\d*");
    //check if operand1 is integar

     if(re.exactMatch(literal[1]) || re.exactMatch(literal[2])){

         //check if  operand1 is a literal


            //check if operand 2 is a varialbe or dca
            QRegExp re("\\d*");
            QStringList dca_operand1=(*Toword);
            QString is_number=dca_operand1[2].mid(dca_operand1[2].indexOf("+")+1);
            qDebug()<<"dca_operand1[1] "<<dca_operand1[2].remove(0,1);
            qDebug()<<"dca_operand1[1] "<<dca_operand1[2].remove(dca_operand1[2].indexOf("+"),dca_operand1[2].size());
            qDebug()<<"dca_operand1[1] "<<dca_operand1[2];
            for (int k = (*j) - 1; k >= 0; k--) {

                QStringList otherwords = (*word)[k].split(" ",QString::SkipEmptyParts);;
                // qDebug() <<"otherwords:  "<<otherwords[0];
                if((*word)[k]!=""){
                if (check_for_dci_instruction(otherwords)) {
          //           qDebug()<<"TOWORDadasdasdadada"<<(*Toword)[2];
               //     qDebug() <<"otherwords2:  "<<otherwords[1]<<"Towords2: "<<(*Toword)[2];
                    if ((*Toword)[2] == otherwords[1]) {
                        counter++;
                        //qDebug() <<"Found the word";
                    }
                //    else {
                        //  qDebug ()<<"not Found";
              //      }
                    //         }
                    //  qDebug() <<"otherwords: "<<otherwords;
                }
                else if (check_for_dca_instruction(otherwords)) {
                    if(re.exactMatch(is_number)){
                        if ( dca_operand1[2]== otherwords[1]) {
                            counter++;
                            // qDebug() <<"Found the word";
                        }
                    }
                }
            }
                //                             qDebug()<<"line "<<j<<", "<<Toword.size();
            }

            if(counter==1){

                return "literaldci";
            }


        }

     else {
      qDebug()<<"TOWORDdasdasdasda1"<<(*Toword)[1]<<" TOWORDdasdasdasda1 "<<(*Toword)[2];
     //qDebug()<<Toword.size();
      QStringList dca_operand1=(*Toword);
/*
            qDebug()<<"dca_operand1[1] "<<dca_operand1[2].remove(0,1);
            qDebug()<<"dca_operand1[1] "<<dca_operand1[2].remove(dca_operand1[2].indexOf("+"),dca_operand1[2].size());
  */
      QString is_number1=dca_operand1[1].mid(dca_operand1[1].indexOf("+")+1);
      QString is_number2=dca_operand1[2].mid(dca_operand1[2].indexOf("+")+1);
      qDebug()<<"dca_operand1[1] "<<dca_operand1[1].remove(0,1);
      qDebug()<<"dca_operand1[1] "<<dca_operand1[1].remove(dca_operand1[1].indexOf("+"),dca_operand1[1].size());
      qDebug()<<"dca_operand1[1] "<<dca_operand1[2].remove(0,1);
       qDebug()<<"dca_operand1[1] "<<dca_operand1[2].remove(dca_operand1[2].indexOf("+"),dca_operand1[2].size());
      qDebug()<<"dca_operand1[1] "<<dca_operand1[1];
     for (int k = (*j) - 1; k >= 0; k--) {

         QStringList otherwords = (*word)[k].split(" ",QString::SkipEmptyParts);;

         if((*word)[k]!=""){
         if (check_for_dci_instruction(otherwords)) {


             if ((*Toword)[1] == otherwords[1]) {
                 counter++;
                 // qDebug() <<"Found the word";
             }
 //                       else {
                 //       qDebug ()<<"not Found";
 //                     }
             //         }
             //  qDebug() <<"otherwords: "<<otherwords;
         }
         else if (check_for_dca_instruction(otherwords)) {
            if(re.exactMatch(is_number1)){
                 if (dca_operand1[1] == otherwords[1]) {
                     counter++;
                     // qDebug() <<"Found the word";
                 }

            }
         }
        }
         //                             qDebug()<<"line "<<j<<", "<<Toword.size();
     }

     for (int k = (*j) - 1; k >= 0; k--) {

         QStringList otherwords = (*word)[k].split(" ",QString::SkipEmptyParts);;
         // qDebug() <<"otherwords:  "<<otherwords[0];
         if((*word)[k]!=""){
         if (check_for_dci_instruction(otherwords)) {
   //           qDebug()<<"TOWORDadasdasdadada"<<(*Toword)[2];
             qDebug() <<"otherwords2:  "<<otherwords[1]<<"Towords2: "<<(*Toword)[2];
             if ((*Toword)[2] == otherwords[1]) {
                 counter++;
                 //qDebug() <<"Found the word";
             }
         //    else {
                 //  qDebug ()<<"not Found";
       //      }
             //         }
             //  qDebug() <<"otherwords: "<<otherwords;
         }
         else if (check_for_dca_instruction(otherwords)) {
            if(re.exactMatch(is_number2)){
                 if ( dca_operand1[2]== otherwords[1]) {
                     counter++;
                     // qDebug() <<"Found the word";
                 }
            }
         }
     }
         //                             qDebug()<<"line "<<j<<", "<<Toword.size();
     }
    qDebug()<<"Counter>>>"<<counter;

     if(counter==2){
         return "variableorarray";
     }

     }
        return "error";
}

bool ErrorCheck::check_for_rdi_instruction(QStringList &list){
    qDebug()<<"ERROR CHECKING RDI "<<list;
    if (list[0]=="rdi"){
        return true;


    }
    else if ((list.size() == 2 or list.size() == 3 or list.size()==4) && list[0].at(list[0].size()-1)==":") {
        qDebug()<<"I am INSIDE CHECK FOR RDI ";
        if (list[1]=="rdi"){
        qDebug()<<"I am INSIDE CHECK FOR RDI PART 2 ";
            return true;
        }

    }
    return false;

}
