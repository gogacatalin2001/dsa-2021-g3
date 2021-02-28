# Lab 02

> i installed git and,with some help, made it work 

update:
problem 1:

*here i think the example given to us was wrong, because truck 10 was at the "door" when its exit was required and*
*so the action was possible. i think the example works for the second problem* 

at first i created structures for nodes and lists and created 2 new empty lists (one
for the road and another one for the garage)

-the garage will be a stack since only the last truck in can get out
-the road will be a simple list (neither a stack, nor a queue)

the operations which will be performed for each command:
	-R:
		-introduce a new element in the road list. i will insert it at the end so that i maintain the order from the 
		example
	-E:
		-search for an element in the road list
			-if i find it, introduce it in the stack for the garage + delete it from the road list
			-if i don't, write an error message
	-X:
		-check to see if the element i am looking for is at the top of the garage stack
			-if it is, insert it in the road list at the front + delete it from the garage stack
			-if it isn't at the top, but it's in the stack, give a certain error message
			-if it's neither at the top, nor in the stack, give another error message
	-S:
		-print out the elements of the stack or of the list (depending on the request)
		
problem 2:

the majority of the code stays the same, the only thing that's different is that the garage is a queue now
that means that when we want to check if a truck is able to exit the garage, it should be at the end of the queue, 
whilst new elements are added at the front

