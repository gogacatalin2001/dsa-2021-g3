# Lab 02

I have installed Git, learned how to use the GitHub platform, how to use them together to submit my work.

SLL-> studied the lab resources and practiced the basic SLL operations, using the ideas from the code snippets.

lab02_problem 1: For the SLL operations i have used functions similar with the ones presented in the labPDF,
developed some auxiliary ones (to check if a truck is on the road, to convert a string to an int, to print the list).
in/out files are passed as arguments to the main function (printed them to make sure they are read correclty).
I have stored the "road" as a normal SLL; The "garage" is basically a stack, since it operates according to the LIFO algorithm,
so i named my operations push, pop, top.

lab02_problem 2: I mostly used the same functions as in the "problem 1", same ideas. This time around, the "garage" must operate FIFO,
so i had to use a "addRear" function (enqueue) and a "deleteFirst"(dequeue)(i named it "out"). The structure of the program is the same as my first problem.


extra 1: We had to implement pretty clear, straightforward operations on SLLs, same structure as in the other problems. It probably isn't the most efficient
 (I traversed the whole list in order to print the "last x terms"...)