# Lab 2
Problem 1: I treated the garage as a stuck (LIFO), the road as a simply linked list and the trucks as the nodes.
In case R we need to place a truck on the road so I inserted the given node at the front (insertAtFrontRoad).
In case E we need to take a certain truck from the road and insert it in the garage so i first verified if 
the given truck exists on the road and if it did i deleted it from the road (deleteByKye) and insert it in the
garage (Push).
In case X we need to take a certain truck out of the garage, on the road. So I first verified if that truck was
 placed at the exit of the garage and if it was I deleted it form the garage (Pop) and added it to the road 
(insertAtFrontRoad).
In cases S(G)/S(R) I displayed the nodes of G/R in order.
Problem 2: I treated the garage and the road as queues, and the trucks as the nodes.
In case R we need to place a truck on the road so I inserted the given node at the end (enqeueRoad).
In case E we need to take a certain truck from the road and insert it in the garage so i first verified if 
the given truck exists on the road and if it was situated at the front of the queue and if it was i deleted 
it from the road (deqeueRoad) and insert it in the garage (enqeueGarage).
In case X we need to take a certain truck out of the garage, on the road. So I first verified if that truck was
 placed at the exit of the garage (front of the queue) and if it was I deleted it form the garage (dequeueGarage) 
 and added it to the road (enqueueRoad).
In cases S(G)/S(R) I displayed the nodes of G/R in order.
