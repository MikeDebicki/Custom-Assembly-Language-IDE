#include<iostream>
#include<string>
using namespace std;

 #include "readstmt.h"

 ReadStmt::ReadStmt(Program* parentProgram) : Statement(parentProgram, "rdi", 1)
 {

 }


 void ReadStmt::compile(QString inputString)
 {
   qDebug() << inputString;
   bool arrayElement = false;
   int operandsCreated = 0;
   QString stringToBuild;
   for(int i = 0; i < inputString.size(); i += 1)           // WE loop through the string
   {
     if(inputString.at(i) == '$')
     {
       arrayElement = true;
     }
     else if(inputString.at(i) == ' ')                           // this helps us seperate operands and lables
     {
       if(arrayElement == true)
       {
         QString variableName;
         QString position;
         bool positionCreation = false;
         for(int i = 0; i <= stringToBuild.length() - 1; i += 1)
         {
           //qDebug() << stringToBuild;
           if (stringToBuild.at(i) == '+')
           {
             positionCreation = true;
           }
           else if(positionCreation == false)
           {
             variableName.append(stringToBuild.at(i));
           }
           else
           {
             position.append(stringToBuild.at(i));

           }
         }
         operand1->setIdentifier(parentProgram->getVariable(variableName));
         setArrayPosition(1, position.toInt());
         setArrayAnswer(true, 1);
         arrayElement = false;
         stringToBuild.clear();
         operandsCreated += 1;
       }
       else
       {
         operand1->setIdentifier(parentProgram->getVariable(stringToBuild));
         stringToBuild.clear();
         operandsCreated += 1;
       }
     }
     else                                                   // we dont want to include ' ' in our strings
     {
       stringToBuild.append(inputString.at(i));
     }
     if(i + 1 == inputString.size() && operandsCreated == 1)          // if we have a label to build
     {
       label = parentProgram->getLabel(stringToBuild);
     }
     else if(i + 1 == inputString.size() && operandsCreated == 0)             // if we finished the string with no label left to make
     {
       if(arrayElement == true)
       {
         QString variableName;
         QString position;
         bool positionCreation = false;
         for(int i = 0; i <= stringToBuild.length() - 1; i += 1)
         {
           //qDebug() << stringToBuild;
           if (stringToBuild.at(i) == '+')
           {
             positionCreation = true;
           }
           else if(positionCreation == false)
           {
             variableName.append(stringToBuild.at(i));
           }
           else
           {
             position.append(stringToBuild.at(i));
           }
         }
         operand1->setIdentifier(parentProgram->getVariable(variableName));
         setArrayPosition(1, position.toInt());
         arrayElement = false;
         setArrayAnswer(true, 1);
         stringToBuild.clear();
         operandsCreated += 1;
       }
       else
       {
         operand1->setIdentifier(parentProgram->getVariable(stringToBuild));
         operandsCreated += 1;
         stringToBuild.clear();
       }
     }
   }
 }


void ReadStmt::run()
{
  operand1->getIdentifier()->setValue(parentProgram->getUserWindowInput(), arrayPosition);
  qDebug() << "PRINTINNGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG";
  qDebug() << operand1->getIdentifier()->getValue(arrayPosition);
  qDebug() << "PRINTINNGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG";
}
