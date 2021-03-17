# Lab 2

> In the 1st problem I observed that the garage works in LIFO order.
> This means that a truck could exit only if it entered the garage last.
> 
> In the 2nd problem, the garage worked in FIFO problem.
> The truck which entered first, could leave the garage first.
>
> In each problem I wrote the "basic" functions needed for SLL, such as ListT *createEmptySLL(), NodeT *createAndFillNode(unsigned int truck_id)...
> You will find more explanation about the functions in the main.c
> To read the commands from the file, I read character-by-character.
> First, I decided the type of the command (R,E,X,S) and than extracted the truck_id or G/R