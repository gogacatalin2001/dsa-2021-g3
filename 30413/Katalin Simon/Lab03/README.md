 Lab 03

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

