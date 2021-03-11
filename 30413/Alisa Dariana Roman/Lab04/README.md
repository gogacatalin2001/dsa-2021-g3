# Lab 4

> I learned about algorithm complexity and how to compute it then i was intoduced to binary trees and started
solving the mandatory problem 4.2:
- to interchange left and right subtrees i used a new auxiliary node aux 
	-aux = left
	-left = right
	-right = aux
- to compute the height: choose max height of each node's children, add 1 (the node level) 
																			(recursively)
- to count the leaves:
	- if p NULL return 0
	- if p has NULL children return 1 (is leaf)
	- else return nrLeaves(left) + nrLeaves(right)