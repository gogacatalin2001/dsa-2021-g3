# Lab 03

>The problem solved is problem 2 with DLL. The name of the folder says cirularlists but it was just a naming mistake.


- I read the input file using strtok and for each new element found i inserted it in the list.
- i tried to solve the problem by inserting each new element at its place depending on the strcmp function, thus sorting it while adding the elements to the list.

writing the code i enocountered no errors only at the end when im using the insert function and it appears there is an error while trying to dynamically allcate a node, but only the second time i am inserting an element:

NodeT *createDLLNode(char *data) //int key
{printf("flag52"); // THIS GETS PRINTED
   NodeT *p = (NodeT *)malloc(sizeof(NodeT));
   printf("flag6"); // THIS DOESNT GET PRINTED
   if (p)
   {
      p->appearances = 1;printf("flag5");
      strcpy(p->data,data);
      p->next = p->prev = NULL;
   }
   return p;
}


--tldr doesnt work, i have a lot of flags trying to figure out where the problem is. so far it appears there is an issue with dynamically allocating a node or memory related