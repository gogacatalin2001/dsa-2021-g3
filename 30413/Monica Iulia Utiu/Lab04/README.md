# Lab 04

Am luat si am adaptat functiile din laborator necesare.
Am creat si o functie de aflare a nivelului arborelui, cu mentiunea ca incepe de la nivelul 0 (cel al radacinei) si una pentru numararea frunzelor.
Pentru functia height(), am creat doua variabile care numara inaltimea pe latura stanga, respectiv cea dreapta ale nodului curent si returneaza valoarea mai mare, respectiv -1 pentru cand nodul e null.
Ca functia sa returneze inaltimea cu conventia ca primul nivel e 1, ar trebui doar sa returnam 0 cand nodul e nul.
Pentru numararea frunzelor am creat o functie recursiva care returneaza 1 daca nodul nu are fii sau suma numarului fiilor fiului din stanga si a celui din dreapta daca nu.
Cand nodul este nul, se intoarce la "parintele" lui.
In main am facut un switch ca sa creez un meniu din care poti selecta ce vrei sa vezi de la tastatura, dar afisarea se face in date.out .
O mica problema am, imi afiseaza ultima comanda facuta de doua ori si n-am reusit sa o dibuiesc. 
O alta problema ar fi ca nu-mi iese nicicum chestia cu command lineu si am renuntat la ea.


