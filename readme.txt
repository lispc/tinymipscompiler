1. Features implemented: 
    a. characters and character strings, including:
       i.  I/O for chars/strings
       ii. comparison and concatenation for strings
           (string operations are implemented by modifying nas)
    b. procedure call:
       i.  pass by value arguments and a single return value
       ii. able to have local variables
       iii.recursion is possible
    c. addtional feature: declaration of variables
       i.  types of variables: int, char, str
       ii. variables need to be declared before use
           (which enabled variables with the same name to be declared in different scopes)

2. How to test separate features:
   execute test.sh in directory "compiler"
   (it will create an "error" directory in "compiler" and do the following
    a. compile nas and mcc and move them to "error"
    b. mv .sc files from "test" to "error"
    c. compile and assembly .sc files and compare the output with sample output
    d. report whether or not the test cases produce the correct output

3. About the large test file for testing (almost) all the features:
   execute test.sh in directory and it will run sorting (which is the test file) automatically

   It is an application designed for sorting various types of elements (int, char, str)
   It takes option choices and input from user ane output the sorted result
