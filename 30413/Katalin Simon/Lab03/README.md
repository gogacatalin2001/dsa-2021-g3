 Lab 03
<<<<<<< HEAD

> tried to use some structure like this(this is the format for when I was trying to figure it out) for reading the input ch by ch
char *sequence=(char*)malloc(sizeof(char));
    i=0;
    while (ch!=EOF)
    {
=======

> My insert at ront is not yet working
> A little summary: I commented a lot on the code, maybe more than I should have, and left there parts which I should't have or when I look back at my code to see the process
>  
> tried to use some structure like this(this is the format for when I was trying to figure it out) for reading the input ch by ch
char *sequence=(char*)malloc(sizeof(char));
    i=0;
    while (ch!=EOF)
    {

       ch = fgetc ( input ) ;
       if(ch!=' ')//append
       {
            sequence[i]=ch;
            i++;
            //printf(" %s space\n", sequence);
            printf ( "%c", ch ) ;
            fputc(ch, output);
       }
       else
        {
            printf(" %s space", sequence);
            sequence="";
            printf("-%s should be empty\n", sequence+i);
            i=0;
            //sequence="";
            //free(sequence);
           // p=createDLLNode();
        }
        //strcasecmp, for searching in list
   }

>>>>>>> 2a6ee26508b43850641fac1ab7b6da7dd888656b

       ch = fgetc ( input ) ;
       if(ch!=' ')//append
       {
            sequence[i]=ch;
            i++;
            //printf(" %s space\n", sequence);
            printf ( "%c", ch ) ;
            fputc(ch, output);
       }
       else
        {
            printf(" %s space", sequence);
            sequence="";
            printf("-%s should be empty\n", sequence+i);
            i=0;
            //sequence="";
            //free(sequence);
           // p=createDLLNode();
        }
        //strcasecmp, for searching in list
   }

