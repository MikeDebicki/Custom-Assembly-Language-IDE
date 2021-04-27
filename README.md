# Custom-Assembly-Language-IDE
An IDE designed to compile and run a custom assembly language based on objects

Purpose of Program
------------------------------------------------------------------------------------------------------------------------------------------
The purpose of this program is to write SCAPL instructions inside the graphical SCAPES system. The SCAPES system allows the user to
write a program in the SCAPL language, the ability to save a program to a file, and the ability to compile an existing program by
translating the program from the SCAPL language instructions into internal data structures that will enable its execution. The SCAPL instructions are then executed and the user can see the execution flow. At the end of the program, the variables used in the program have their values printed out.


------------------------------------------------------------------------------------------------------------------------------------------
Features
------------------------------------------------------------------------------------------------------------------------------------------
-Create a new program
-Save a program to a file
-Compile an existing program that contains ALL of the the following SCAPL instructions only: dci, rdi, prt, cmp, jmr, jmp, end, dca, mov, add, jeq, jls
-Can determine the line number of the compilation error
-Can serialize the program's created objects to a JSON file after compilation has completed
-Can deserialize objects stored in persistent storage and execute the program, showing the execution flow
-values used in the program are shown at the end

------------------------------------------------------------------------------------------------------------------------------------------
Design Pattern
------------------------------------------------------------------------------------------------------------------------------------------
We used the Factory design pattern for SCAPES.
The files and classes where the design pattern is used are statementfactory.cpp and
statementfactory.h.
After reading from persistent storage and knowing which objects we need to make, the statementfactory.cpp is called in the process of creating our objects and calls the relevant subclasses.

------------------------------------------------------------------------------------------------------------------------------------------

Problems/Bugs
------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------


Notes
------------------------------------------------------------------------------------------------------------------------------------------
-to print a String literal, use double quotes, not single quotes
acceptable:     prt "a"
not acceptable: prt 'a'
------------------------------------------------------------------------------------------------------------------------------------------

Source/Header Files
------------------------------------------------------------------------------------------------------------------------------------------
-CompStmt.h          and     CompStmt.cpp
-DeclIntStmt.h       and     DeclIntStmt.cpp
-EndStmt.h           and     EndStmt.cpp
-Identifier.h        and     Identifier.cpp
-JMoreStmt.h         and     JMoreStmt.cpp
-JumpStmt.h          and     JumpStmt.cpp
-Label.h             and     Label.cpp
-MainWindow.h        and     MainWindow.cpp
-operand.h           and     operand.cpp
-PrintStmt.h         and     PrintStmt.cpp
-Program.h           and     Program.cpp
-ReadStmt.h          and     ReadStmt.cpp
-Statement.h         and     Statement.cpp
-Statementfactory.h  and     Statementfactory.cpp
-Variable.h          and     Variable.h
-main.h              and     main.cpp
-MainWindow.h        and     MainWindow.cpp
-addstmt.h           and     addstmt.cpp
-compilecontrol.h    and     compilecontrol.cpp
-declarrstmt.h       and     declarrstmt.cpp
-errorcheck.h        and     errorcheck.cpp
-jeqstmt.h           and     jeqstmt.cpp
-jlessstmt.h         and     jlessstmt.cpp
-movstmt.h           and     movstmt.cpp
-runcontrol.h        and     runcontrol.cpp

------------------------------------------------------------------------------------------------------------------------------------------
Running the Program
------------------------------------------------------------------------------------------------------------------------------------------
-Go to the directory (where the project is)
-make sure you have execute permissions for the script you are running, if not then change the file permissions by running the command:
 chmod 777 <script>
-execute the command ./SCAPESlaunchscript to open the program located in the directory D1
-After compiling, the serialized objects are stored in a file called SCAPES.json in the user's home directory
