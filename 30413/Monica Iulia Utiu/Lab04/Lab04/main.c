#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char id;
    struct node *left, *right;
} NodeT;

NodeT *createBinTree( int branch, NodeT *parent, FILE *pf )
{
    NodeT *p;
    int id;
    fscanf(pf,"%d", &id);
    if( id==0 ) return NULL;
       else {
              p= (NodeT *)malloc(sizeof(NodeT));
              if( p==NULL ) printf("Out of space");
              p->id= id;
              p->left= createBinTree(1, p, pf);
              p->right= createBinTree(2, p, pf);
            }
    return p;
}

void interchange( NodeT *r )
{
    if( r!=NULL )
    {
    NodeT *p=r->left;
    r->left= r->right;
    r->right= p;
    interchange(r->left);
    interchange(r->right);
    }
}

int height(NodeT *p)
{
    if(p!=NULL)
    {
        int lheight= height(p->left);
        int rheight= height(p->right);
        if( lheight>rheight ) return ++lheight;
           else return ++rheight;
    }
    else return -1;
}

void preorder( NodeT *p, int level, FILE *of)
{
    if( p!=NULL )
    {
        for(int i=0;i<=level;i++) fprintf(of," ");
        fprintf(of,"%2.2d\n", p->id);
        preorder(p->left, level+1, of);
        preorder(p->right, level+1, of);
    }
}

void inorder( NodeT *p, int level, FILE *of)
{
    if(p!=NULL)
    {
        inorder( p->left,level+1,of);
        for(int i=0;i<=level;i++) fprintf(of," ");
        fprintf(of,"%2.2d\n", p->id);
        inorder( p->right,level+1,of);
    }
}

void postorder( NodeT *p, int level, FILE *of)
{
    if(p!=NULL)
    {
        postorder( p->left, level+1, of);
        postorder( p->right, level+1, of);
        for( int i=1;i<=level;i++ ) fprintf(of," ");
        fprintf(of,"%2.2d\n", p->id);
    }
}

int NoLeaves( NodeT *p )
{
    if( p==NULL ) return ;
    if( p->left==NULL && p->right==NULL ) return 1;
         else  return NoLeaves(p->left)+NoLeaves(p->right);
}

int main()
{

    FILE *pf=fopen("date.in", "r");
    FILE *of=fopen("date.out", "w");

    NodeT *root=createBinTree(0, NULL, pf);
    int choice,h,k;

    while(getc(stdin) != 'q')
    {
    printf( "\n1.Preorder listing\n" );
    printf( "2.Preorder listing for interchanged subtrees\n" );
    printf( "3.Inorder listing\n" );
    printf( "4.Inorder listing for interchanged subtrees\n" );
    printf( "5.Postorder listing\n" );
    printf( "6.Postorder listing for interchanged subtrees\n" );
    printf( "7.Height of the tree (levels from 0) \n");
    printf( "8.Number of leaves\n");
    printf("\nInput number of what you want to do: ");

    scanf("%d",&choice);
    switch(choice)
    {
        case 1:  preorder( root, 0, of );
                 break;
        case 2:  interchange( root ); preorder( root, 0, of );
                 break;
        case 3:  inorder( root, 0, of );
                 break;
        case 4:  interchange( root ); inorder( root, 0, of );
                 break;
        case 5:  postorder( root, 0, of );
                 break;
        case 6:  interchange( root ); postorder( root, 0, of );
                 break;
        case 7:  h= height( root ); fprintf(of,"\nHeight of tree is %d\n",h);
                 break;
        case 8:  k= NoLeaves( root ); fprintf(of,"\nNumber of leaves is %d\n",k);
                 break;
        default: printf("Try another command");
    }
       printf("\nDo you want to continue? Press enter if yes, and q to exit\n");
       fprintf(of,"\n\n");
    }
    while( '\n' != getc(stdin) );

    fclose(pf);
    fclose(of);
    return 0;
}
