# Binary Tree
This program demonstrates a binary tree data structure where nodes can be inserted and removed from the tree. 
Each node holds a value and up to two child nodes, a left and a right. The binary tree is usful for searching for
and sorting data. this program sorts intergers in the tree.

## How to Download
- Download the latest version
- Unzip the file
- Double click BinaryTree.exe

## How to Use
The user can insert or remove integers from the binary tree. It's simple enough, all the user should do is type
a number into the box and choose to insert or remove the number. When inserting the number it will appear on 
the console as a circle. When inserting another number, it will be placed either to the left or the right of the first 
number depending on if it is greater than or less than the first number. You will notice that each number that is inserted
will highlight green. This is keeping track of the current node, until a number is inserted that has already been inserted. 
It will search for that number and highlight it green. When removeing a node, if the node has one child, the child node will replace 
the node that is being removed. If the node has two children, it should be replaced with the left childs furthest right node, if the left 
child has a right node, otherwise the left child will replace the node that is being removed.
