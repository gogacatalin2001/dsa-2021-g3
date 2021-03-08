# Lab 3

> learned how memory is allocated stack/heap, I was introduced to doubly linked lists and solved 3.2
algorithm used at 3.2
    -create empty doubly linked list
    -while reading the words from text file named argv[1] :
        -check if the word is contained already in the d. l. list
            -if yes increase keyCount with 1
            -else use function insertNode : this function creates a node with 
            key = s, keyCount = 1, compares s with first node key, last node key and with the node
            inbetween and places s corespondingly: at every step the list is sorted in ascending order
	-display list in text file named argv[2]

