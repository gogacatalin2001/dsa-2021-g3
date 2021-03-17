# Lab 02

In these 2 lab exercises I learned to construct linked lists and operate on them. In the first problem, we needed
a way to organize the data for both the road and the garage. In the first version of the problem, trucks could get
on the road and exit without restrictions, and trucks could get in the garage and out in a FIFO order. I built the
necessary functions for creating the lists and operating on them. Then, I developed a way to read the commands from
the input file. For each type of command (R, E, X, S) I created a different case, in which the specific operations
on the two lists were performed. In the second version of the problem, both the road and the garage had to be represented
as queues, so I adapted the code from the first problem to perform this tasks. The functions remained the same, but for
each command type, there were different operations that had to be performed on the lists. (e.g. in the case of X, 
the truck that first got in the garage could get out, and only trough the entrance on the road).


