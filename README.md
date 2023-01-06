#Assignment 3


## Binary Expression Tree

This C program takes as input a fully parenthesized, arithmetic expression of binary operators +, −, ∗, /, and converts the expression into a binary expression tree


### Getting Started


#### Executing Question 2

* To build the program, in your terminal head to the directory that contains the project files. In the command line type:
```
make
```
* The programs should build successfully. Now to execute the program, type:
```
./q1 [command-line expression]
```
* The program takes an expression as a command-line argument. The program should now be running and your menu options should be displayed.

* For example, to calculate (((1.56+4.26)*(x1-2.23))/x2), enter:
```
./q1 \(\(2.00*\(x1-1.00\)\)+\(x2/3.00\)\)
```

* Output: 
```
The argument/inorder is (((1.56+4.26)*(x1-2.23))/x2)


Menu options: 

1. Display
2. Preorder
3. Inorder
4. Postorder
5. Exit Program

Choose a menu option: 2
PreOrder: + * 2.00 - x1 1.00 / x2 3.00

Choose a menu option: 4

PostOrder: 2.00 x1 1.00 - * x2 3.00 / + 
```

* Please Note: in order to conduct multiplication operations, it must in between double quotes("*") for IOS.


## Author Information

* Name: Manu Konnur
* Email: mkonnur@uoguelph.ca
* ID: 1178498
