#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node_type
{
    char name[20];
    struct node_type *next;
}NodeT;

typedef struct list_type
{
    int count;
    NodeT *first, *last;
    struct list_type *nextCell;
}ListT;

typedef struct
{
    int count;
    ListT *firstCell, *lastCell;
}TableT;

void errorMsg(const char *msg)
{
    printf(msg);// print message
    exit(1);// quit the program
}

NodeT *createListNode(char name[20])
{
    NodeT *p = (NodeT*)calloc(1,sizeof(NodeT));
    if(p)
    {
        // initialize the node values
        strcpy(p->name, name);
        p->next = NULL;
    }
    else
        return NULL;
    return p;
}

ListT *createEmptyList()
{
    ListT *l = (ListT*)calloc(1,sizeof(ListT));
    if(l)
    {
        // initialize the header values
        l->count = 0;
        l->first = l->last = NULL;
        l->nextCell = NULL;
    }
    else
        return NULL;
    return l;
}

int appendNode(ListT *cell, char name[20])
{
    NodeT *p = createListNode(name);
    // if node is created add it to the last position in the chain
    if(p)
    {
        if((cell->first == NULL) && (cell->count == 0))// cell is empty
        {
            cell->first = cell->last = p;
            cell->count = 1;
        }
        else
        {
            cell->last->next = p;
            cell->last = p;
            cell->count++;
        }
        return 1;// success
    }
    return 0;// failure
}

TableT *createEmptyTable()
{
    TableT *t = (TableT*)calloc(1,sizeof(TableT));
    if(t)
    {
        // initialize the table header
        t->count = 0;
        t->firstCell = t->lastCell = NULL;
    }
    else
        return NULL;
    return t;
}

int addTableCell(TableT *table)
{
    ListT *cell = (ListT*)calloc(1,sizeof(ListT));
    // if cell was created add it to the table
    if(cell)
    {
        if((table->firstCell == NULL) || (table->count == 0))// table is empty
        {
            table->firstCell = table->lastCell = cell;
            table->count = 1;
        }
        else
        {
            table->lastCell->nextCell = cell;
            table->lastCell = cell;
            table->count++;
        }
        return 1;
    }
    return 0;// failure
}

int hash(int nbOfCells, char name[20])
{
    /*
        To compute the hash value I sum up the ASCII values of
        the letters of the word and then perform the mod operation
        between the sum and the number of cells in the hash table.
    */
    int sum = 0;
    int index = 0;
    while(name[index] != '\0')
    {
        sum += name[index];
        index++;
    }
    return sum % nbOfCells;
}

int insertIntoTable(TableT *table, char name[20])
{
    int hashValue = hash(table->count, name);// compute the hash value
    int index = 0;
    ListT *cell = table->firstCell;// for looping trough the hash table
    // search the right cell
    while((index != hashValue) && (cell != table->lastCell))
    {
        cell = cell->nextCell;
        index++;
    }
    // try to add the value to the cell
    if(index == hashValue)
        if(appendNode(cell, name))
            return 1;// success
    return 0;// failure
}

NodeT *find(FILE *out,TableT *table, char name[20])
{
    int hashValue = hash(table->count, name);// compute the hash value
    int index = 0;
    ListT *cell = table->firstCell;// for looping trough the hash table
    NodeT *chainElement = NULL;// for looping trough the chain if collision occurs
    // search for the right table cell
    while((index != hashValue) && (cell != table->lastCell))
    {
        cell = cell->nextCell;
        index++;
    }
    if(index == hashValue)
    {
       // search for the value in the chain
        chainElement = cell->first;
        while((strcmp(name, chainElement->name) != 0) &&
              (chainElement != cell->last))
        {
            chainElement = chainElement->next;
        }
        if(strcmp(name, chainElement->name) == 0)
        {
            fprintf(out, "yes %d\n", index);
            return(chainElement);
        }
    }
    fprintf(out, "no\n");
    return NULL;
}

int deleteListNode(ListT *cell, char name[20])
{
    // search the element in the chain
    if(cell->first && (cell->count != 0))
    {
        NodeT *chainElement = cell->first;
        // the node is the first chain element
        if(strcmp(name, chainElement->name) == 0)
        {
            cell->first = chainElement->next;
            free(chainElement);
            cell->count--;
            return 1;// success
        }
        else
        {
           // loop trough the chain
            NodeT *t = chainElement->next;
            while((strcmp(name, t->name) != 0) && (t != cell->last))
            {
                chainElement = t;
                t = chainElement->next;
            }
            // if we found the node, delete it
            if(strcmp(name, t->name) == 0)
            {
                // the node is the last chain element
                if(t == cell->last)
                {
                    chainElement->next = NULL;
                    cell->last = chainElement;
                }// the node is in the middle of the chain
                else
                {
                    chainElement->next = t->next;
                    free(t);
                }
                cell->count--;
                return 1;// success
            }
        }
    }
    return 0;// failure
}

int deleteValue(TableT *table, char name[20])
{
    int hashValue = hash(table->count, name);
    ListT *cell = table->firstCell;
    int index = 0;
    // search for the right cell
    while((index != hashValue) && (cell != table->lastCell))
    {
        cell = cell->nextCell;
        index++;
    }
    if(index == hashValue)
        return deleteListNode(cell, name);
    return 0;// failure
}

void printTable(FILE *out, TableT *table)
{
    if(table->count == 0)
        fprintf(out, "There are no elements in the table.\n");

    ListT *cell = table->firstCell;
    while(cell != NULL)
    {
        if((cell->first == NULL) || (cell->count == 0))
            fprintf(out, "NULL ");
        NodeT *chainElement = cell->first;
        while(chainElement != NULL)
        {
            fprintf(out, "%s ", chainElement->name);
            chainElement = chainElement->next;
        }
        cell = cell->nextCell;
    }
    fprintf(out, "\n");
}

void processInput(FILE *in, FILE *out, TableT *table)
{
    if(table == NULL)
        return;
    char command;
    char name[20];
    while(fscanf(in, "\n%c%s", &command, name) != EOF)
    {
        switch(command)
        {
        case 'i':
            if(insertIntoTable(table, name) == 0)
                errorMsg("Couldn't insert value into table!");
            break;
        case 'd':
            if(deleteValue(table, name) == 0)
                errorMsg("Couldn't delete node!");
            break;
        case 'f':
            find(out, table, name);
            break;
        case 'l':
            printTable(out, table);
            break;
        default :
            fprintf(out, "Done processing the input file!\n");
            break;
        };
    }
}

int main(int argc, char **argv)
{
    FILE *in, *out;
    // open files
    if((in = fopen(argv[1], "r")) == NULL)
        errorMsg("Cannot open input file!");

    if((out = fopen(argv[2], "w")) == NULL)
        errorMsg("Cannot open output file!");

    // create the table
    int numberOfCells = 6;
    /// number of cells can be modified
    //scanf("%d", &numberOfCells);
    TableT *table = createEmptyTable();
    if(table == NULL)
        errorMsg("Not enough memory to create the table!");
    else
    {
        // add table cells
        for(int i = 0; i < numberOfCells; i++)
            addTableCell(table);
    }
    /// TEST VALUES for individual functions
    /*
    insertIntoTable(table, "Maria");
    insertIntoTable(table, "Tudor");
    insertIntoTable(table, "Radu");
    insertIntoTable(table, "Andrei");
    printTable(out, table);
    deleteValue(table, "Tudor");
    find(out, table, "Andrei");
    find(out, table, "Tudor");
    deleteValue(table, "Maria");
    printTable(out, table);
    */
    processInput(in, out, table);

    // close the files
    fclose(in);
    fclose(out);

    return 0;
}
