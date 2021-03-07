# Lab 03

During the lab, we went over some details about the way things are saved inside the computer
and why it is useful to use lists. Then we studied some aspects about SLL, circular SLL and DLL.

The assignment (problem 3.2):
Firstly, i have created the usual functions that are needed when working with lists, taking into account
that each node should have: a word, a number of appearences of it, a previous and a next node.
The most difficult part of the problem was to place the words inside the DLL in the right order. For this, i
used some functions to make the insertion easier:
	-insert at front
	-insert at rear
	-insert in the middle, finding the right position
What also had to be taken into account were the cases in which an uppercase letter was different than a lowercase letter.
For this, i made use of 2 functions of finding an existing node (one for each case). 
	example: i have read the word "The"
	-if both functions returned a null vector, it means that there is neither a "The", nor any variation of it inside the list
		=> i inserted the word using case insesitive comparison
	-if there is a variantion of it, for example "the"
		=> i compare the to words (the and The) and place the new one according to the result
	- i also made use of the results in order to increase the number of appearences of a word
In order to read the data, i have, firstly, read all the text counting the white spaces and then read all the text again, 
this time focusing on adding each word inside the list on its correct position.



