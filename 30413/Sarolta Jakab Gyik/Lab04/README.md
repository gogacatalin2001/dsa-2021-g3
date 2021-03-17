# Lab 4

> For the binary tree functions I used 4 different recursive functions. To find a node in the binary tree given its key I wrote
the findNode function that returns a pointer to the node if found, or a null pointer if the node is not part of the tree.
then with the interchange function I did a swap between the subtrees of the node previously found.
To count the nr of leaves in the tree the recursive function calls itself for the left + right nodes until it reaches a leaf,
thus the left and right nodes of the current node are NULL. Then it returns 1.
Finally, for the height of the tree I used a maxLeft and maxRight variable to compare the maximum height of the left and right subtree.
Then the maximum of these 2 goes into the max variable. And at the end the max gets returned.
In all the functions I checked if the current node is 0 first. If the tree in empty, has no nodes, then all functions must return 0.



