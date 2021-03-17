# Lab 3

> First of all, I had to open the files - make function for it
> After that I had to create a node type containing a word, how many times this word appears and link to the previous and next node
> The header cell is a structure - here we have a link to the first and last node in the list
> We had to create a doubly linked list, so we have a function for creating such an empty list
> We also need a function for filling the nodes for each distinct word
> In the find() function I wanted to find out where I have to insert the new word or where to increase the frequency by comparing the words
> (by this way, my list remains sorted all the time)
> To insert between to certain positions I've made another function before (I had to use this function in more cases)
> I also made a function for displaying the list in ascending/descending order depending on the given variable asc
> A function for purging the list was also made
>
> In the meantime I realised that it was not enough to compare the words with the strcmp() function, because by this way the words
> starting with uppercase letters were put in the front of the list. This is why I modified my program. So in the node type I created
> a variable which had to contain 1 if the word was starting with an uppercase letter and 0 otherwise. After I assigned 0 or 1 to this 
> variable, I transformed the word to start with a lowercase letter, so when comparing two words the function wouldn't care if a word started 
> with lower- or uppercase letters. It was important to know at the end (when displaying the list) if a word was actually starting with 
> lower- or uppercase letters and changing back to normal a word if needed.

# Extra

*intersection*
> In this problem my first idea was to take to pointers and go through the list with 2 loops, comparing the element. This seemed simple,
> so I tried to search for a more efficient algorithm. After I took some examples on paper, I realised that it's enough to compare the 
> elements in such a way that we only start from the shorter list and from the same level from the end at the longer list. For this, I
> calculated the difference between the no. of elements in each list (the head type containing this). By this way, I could go through the
> lists with a single for loop, comparing the elemnts on the same "level".
*duplicates*
> Here I couldn't think about any better algorithm without making it too complicated, but I'm sure it has to exist one.
> I transversed the list using 2 while loops, comparing an element with the ones after it. If I met duplicates, I made the new linkage 
> and delete the duplicate.

> In both problems I made some lists to test my functions.