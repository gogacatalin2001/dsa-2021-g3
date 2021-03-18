#include <stdio.h>
#include <stdlib.h>

typedef struct node_type
{
    int months;
    struct node_type *left, *right;
}NodeT;

typedef struct employee_type
{
    int reportees;
    int totalMonths;
}EmployeeT;

void error(const char *msg)
{
    printf(msg);
    exit(1);
}

NodeT *createBinTree(FILE *in)
{
    NodeT *p ;
    int months = 0;
    //read the months of the employee
    fscanf(in,"%d",&months);
    if(months == 0)
        return NULL;
    p = (NodeT*)calloc(1,sizeof(NodeT));
    if(p == NULL)
    {
        error("Not enought space to create the tree!");
        return NULL;
    }
    //create
    p->months = months;
    p->left = createBinTree(in);
    p->right = createBinTree(in);
    return p;
}

// tree traversals
void preorder(FILE *out, NodeT *p, int level)
{
    if(p != NULL)
    {
        for(int i=0; i<level; i++)
            fprintf(out,"   ");
        fprintf(out,"%2.2d\n",p->months);
        preorder(out,p->left,level + 1);
        preorder(out,p->right,level + 1);
    }
}

void inorder(FILE *out, NodeT *p, int level)
{
    if(p != NULL)
    {
        inorder(out,p->left,level + 1);
        for(int i=0; i<level; i++)
            fprintf(out,"   ");
        fprintf(out,"%2.2d\n",p->months);
        inorder(out,p->right,level + 1);
    }
}

void postorder(FILE *out, NodeT *p, int level)
{
    if(p != NULL)
    {
        postorder(out,p->left,level + 1);
        postorder(out,p->right,level + 1);
        for(int i=0; i<level; i++)
            fprintf(out,"   ");
        fprintf(out,"%2.2d\n",p->months);
    }
}

void computeParameters(NodeT *p, EmployeeT *emp)
{
    if(p->left == NULL && p->right == NULL)
    {
        emp->reportees += 1;
        emp->totalMonths += p->months;
        return;
    }
    else
    {
        computeParameters(p->left,emp);
        computeParameters(p->right,emp);
        emp->totalMonths += p->months;
        emp->reportees += 1;
    }
}

EmployeeT *createEmployee()
{
   EmployeeT *emp = (EmployeeT*)calloc(1,sizeof(EmployeeT));
   if(emp == NULL)
        error("Not enough space for employee!");
   emp->reportees = 0;
   emp->totalMonths = 0;
   return emp;
}

NodeT *highestTeamTenture(NodeT *root)
{
    EmployeeT *leftTeam = createEmployee();
    EmployeeT *rightTeam = createEmployee();
    computeParameters(root->right,rightTeam);
    computeParameters(root->left,leftTeam);
    double leftTeamTenture,rightTeamTenture,wholeTeamTenture;
    leftTeamTenture = (leftTeam->totalMonths) / leftTeam->reportees;
    rightTeamTenture = (rightTeam->totalMonths) / rightTeam->reportees;
    wholeTeamTenture = (leftTeam->totalMonths + rightTeam->totalMonths
                        + root->months) / (leftTeam->reportees + leftTeam->reportees + 1);
    if(leftTeamTenture > rightTeamTenture)
    {
        if(leftTeamTenture > wholeTeamTenture)
            return root;
        else
            return root->left;
    }
    else if (rightTeamTenture > wholeTeamTenture)
        return root->right;
    else
        return root;
}

int main(int argc, char **argv)
{
    FILE *in,*out;
    //check for correct file opening
    if((in = fopen(argv[1],"r")) == NULL)
        error("Couldn't open input file!");
    if((out = fopen(argv[2],"w")) == NULL)
        error("Couldn't open output file!");

    NodeT *t = createBinTree(in);
    fprintf(out,"Preorder:\n");
    preorder(out,t,0);\
    fprintf(out,"Inorder:\n");
    inorder(out,t,0);
    fprintf(out,"Postorder:\n");
    postorder(out,t,0);
    fprintf(out,"\n");

    //return the manager of the team with the highest tenture
    //NodeT *manager = (NodeT*)calloc(1,sizeof(NodeT));
    //manager = highestTeamTenture(t);
    fprintf(out,"The team with the highest tenture is lead by: %d\n",
            highestTeamTenture(t)->months);

    //close the files
    fclose(in);
    fclose(out);
    return 0;
}
