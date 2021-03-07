# Lab 3

> In this doubly linked list exercise I read the text from the textfile character by character. When I encountered
a space then I made a new node, checked if the word in the node already existed with the function findduplicate.
If it did, then I did not add it to the list. Only increased the nr variable in which I counted the nr of apprearances.
If the word did not appear earlier then i checked the list where to insert it. The function find returns 0 if we need to insert
it at front, returns -1 if we need to insert at rear, and other value if we insert by key. I used the strcmpi function that is
not case sensitive. However, when the letters coincide but one is upper and one is a lower case character then I insert the
upper case one after the lower case letter.
If the string is not made up of letters then it automatically returns 0.
At the end I use the traverse functions to print the dll forwards and backwards.
A problem that I encountered was that the main function doesn't perform any operation that I write after the while loop.
I couldn't figure out why. So it doesn't print the lists either, only if i print them inside the while after every step



