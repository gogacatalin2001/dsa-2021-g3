# Lab 4

> I have the necessary functions for creating a binary tree and traversing in pre-, in- and postorder a binary tree
///interchanging
> for this I had to find the given node first and then simply changing the two branches using an auxiliary node
///height-of-tree
> I needed a max() function for comparing the heights of the left and right branches
> when we have a NULL pointer, it means that we reached "the end" of a tree, so from here, starting with 0 we construct the height of the tree
> at each level we add 1 to the maximum height between the left and right branches
///number-of-leaves-in-a-tree
> we have already talked about this at the laboratory, at each node we add the number of leaves from the 2 branches

# Extra
> I created a binary tree (the one from the example) so I could test my functions
> I needed a new struct type so I could return it as a pointer in my function (because I had to return 2 different values: sum and count)
> The function findManagerWithHighestTenure() will return a pointer to the node with the heighest tenure
> The function needForAverage is the one which actually does the work:
> for each node it returns both sum and count (using struct)
> this helps us to find the average for each node and compare it to the maximal average
> we decompose to left and right branch and compute the sum and count
> sum must be equal to the sum of months in: root, sum of left branch and sum of right branch
> count must be equal to 1 (representing the manager) + count on left + count on right


