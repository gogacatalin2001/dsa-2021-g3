#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct node
{
    char str[101];
    int cnt;
    struct node *prev, *next;
}nodeT;
nodeT *first=NULL, *last=NULL;
int init(char s[]) //add first
{
    int i;
    first= (nodeT *)malloc(sizeof(nodeT));
    last = first;
    first->prev=NULL;
    first->next=NULL;
   strcpy(first->str,s);
    first->cnt=1;
}
int search(char s[])
{
    nodeT *p=first;
    int found=0;
    while(p!=NULL&&found==0)
    {
        if(strcmp(p->str,s)==0)
        {
            found=1;
        }

        if(found==1)
        {
            p->cnt++;
        }
        p=p->next;
    }
    return found;
}
int add(char s[])
{
    nodeT *p=last;
    nodeT *q;
    int i;
    if(search(s)==0)
    {
      q= (nodeT *)malloc(sizeof(nodeT));
      strcpy(q->str,s);
      q->cnt=1;
      if(strcmp(last->str,s)==-1) //se adauga la final
      {
          last->next=q;
          q->prev=last;
          q->next=NULL;
      }
      else
      {
          while(p!=NULL&&strcmp(p->str,s)==1)
          {
              p=p->prev;
          }
          if(p==NULL) //se adauga la inceput
          {
              first->prev=q;
              q->next=first;
              q->prev=NULL;
              first=q;
          }
          else  //adaugare undeva
          {
              q->next=p->next;
              q->next->prev=q;
              q->prev=p;
              p->next=q;
          }
      }

    }
}
int main()
{
    FILE *fin;
    fin=fopen("txt.in", "r");
    char c;
    char s[101];
    int i,j,ok=0;
    while(c=fgetc(fin))
    {
        if(ok==0&&c!=' ')
        {
            j=0;
            s[j]=c;
            ok=1;
        }
        if(ok==1&&c!=' ')
        {
            j++;
            s[j]=c;
        }
        if(c==' ')
        {
            j++;
            s[j]=0;
            ok=0;
            if(first==NULL)
            {
                init(s);
            }
            else
            {
                if(search(s)==0)
                {
                    add(s);
                }
            }
        }
    }
    j++;
    s[j]=0;
    if(search(s)==0)
    {
        add(s);
    }
    nodeT *p=first;
    while(p!=NULL)
    {
        printf("%s:%d \n",p->str,p->cnt);
        p=p->next;
    }
    p=last;
     while(p!=NULL)
    {
        printf("%s:%d \n",p->str,p->cnt);
        p=p->prev;
    }
}
