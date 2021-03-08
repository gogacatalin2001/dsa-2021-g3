# Lab 3
-learned about doubly linked lists
-in problem 2:
	creating the list
		for creating the list I first checked if the word was already added in the list:
						-added -> increased the frequency of the node in the list by 1
						-not added -> added the new word to the list
	for sorting the list I used the bubble sort algorithm:
		compared the words with strcmp() 
		after each traversal of the list I assigned frequency -1 to the nodes already printed 
