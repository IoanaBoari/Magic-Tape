# Magic Tape - doubly-linked-list
//BOARI Ioana-Ruxandra 312CD					README - TEMA1 SDA                            !

	Pentru implementarea temei am folosit un fisier numit "tema1.h" in care am
definit structurile folosite, functiile de baza pentru banda, stiva si coada si
functiile specifice necesare pentru indeplinirea cerintelor. Am folosit si un
fisier numit "tema1.c" in care am rezolvat cerintele cu ajutorul functiilor
definite in fisierul "tema1.h". Alt fisier a fost "Makefile"-ul folosit pentru
compilarea surselor, crearea executabilului, rularea acestuia si stergerea lui.

			Descrierea fisierului tema1.h:

DESPRE STRUCTURI:

	In rezolvarea temei am folosit 6 structuri. Structura ListNode reprezinta
o lista dublu inlantuita cu elemente de tip "Item". In fisierul "tema1.c" Item
este definit ca fiind char. Structura TBanda este cea ceruta explicit in cerinta.
Aceasta contine 3 pointeri la elemente de tip ListNode. Sentinel este un nod
suplimentar la inceput care nu contine informatie utila. Last indica sfarsitul
benzii. Deget marcheaza pozitia degetului pe banda, asa cum este cerut in enunt.
Structura StackNode reprezinta o lista simplu inlantuita cu elemente de tip
pointeri la nodurile benzii. Structura Stack reprezinta stiva ce contine
elemente de tip StackNode si este necesara pentru a implementa operatiile
de UNDO si REDO. Stuctura QueueNode reprezinta o lista simplu inlantuita
cu elemente de tip vectori de caractere. Structura Queue reprezinta coada ce
contine elemente de tip QueueNode si este necesara pentru a retine operatiile
de tip UPDATE.

DESPRE FUNCTIILE PENTRU BANDA:

	Am implementat functiile createNode, createBanda, isEmpty, eliminate
si destroyBanda.
Functia createNode am folosit-o pentru a crea un element de tip ListNode prin
alocare dinamica.
Functia createBanda pentru a crea banda prin alocare dinamica. Santinela am ales
sa o initializez cu o litera oarecare (A) stiind ca informatia ei nu conteaza.
Degetul l-am initializat cu #, reprezentand primul element din banda.
Functia isEmpty verifica daca toata banda e goala, incepand de la santinela.
Functia eliminate elimina primul element din banda, pornind de la santinela
si elibereaza memoria pentru acesta.
Functia destroyBanda elibereaza memoria pentru intreaga banda.
Functiile isEmpty si eliminate sunt folosite doar in functia destroyBanda 
pentru a fi mai usor de inteles.

DESPRE FUNCTIILE PENTRU STIVA:

	Am folosit functiile clasice si binecunoscute atat din curs cat si din
laborator pentru implementarea unei stive: createStackNode, createStack,
isStackEmpty, push, top, pop, destroyStack.

DESPRE FUNCTIILE PENTRU COADA:

	Am folosit functiile clasice si binecunoscute atat din curs cat si din
laborator pentru implementarea unei cozi: createQueueNode, createQueue,
isQueueEmpty, enqueue, front, dequeue, destroyQueue.

DESPRE OPERATIILE UPDATE:

-- acestea se adauga intr-o coada si nu se executa direct
	Pentru operatiile de tip update am implementat functiile moveLeft,
moveRight, moveLeft_char, moveRight_char, write_char, insertLeft_char,
insertRight_char.
Functia de moveLeft deplaseaza degetul cu o pozitile la stanga. Daca 
degetul se afla pe prima pozitie si se intalneste aceasta operatie nu
se intampla nimic.
Functia de moveRight deplaseaza degetul cu o pozitie la dreapta. Daca
degetul se afla pe ultima pozitie si se intalneste aceasta operatie
se adauga la final un nou nod cu caracterul "#" si degetul se muta pe acel nod.
Functia de moveLeft_char deplaseaza degetul la stanga pana la primul caracter
egal cu simbolul primit ca parametru. Se parcurge toata banda de la pozitia curenta
a degetului in stanga, iar daca se ajunge in margine si caracterul nu s-a gasit
se va afisa "ERROR" si pozitia degetului nu se modifica.
Functia de moveRight_char deplaseaza degetul la dreapta pana la primul caracter
egal cu simbolul primit ca parametru. Se parcurge toata banda de la pozitia curenta
a degetului in dreapta, iar daca se ajunge la limita si caracterul nu s-a gasit
se va insera "#" la final si pozitia degetului va fi pe acest nou nod.
Functia de write_char actualizeaza caracterul curent, schimbandu-l cu cel
primit ca parametru.
 Functia de insertLeft_char implica inserarea unui caracter in stanga pozitiei
degetului si deplasarea pe aceasta pozitie. Daca degetul se afla pe prima pozitie
nu se poate insera la stanga, asadar se va afisa "ERROR", iar banda si pozitia
degetului raman nemodificate.
Functia insertRight_char implica inserarea la dreapta a unui caracter si deplasarea
degetului pe nodul inserat.
Se observa ca singurele operatii care pot avea erori sunt MOVE_LEFT_CHAR si
INSERT LEFT <C>.

DESPRE OPERATIILE DE QUERY:

-- acestea se executa direct atunci cand sunt intalnite
	Pentru operatiile de tip query am implementat functiile show_current si show.
Functia show_current afiseaza caracterul pe care se afla degetul.
Functia show afiseaza intreg continutul benzii, marcand caracterul pe care se
afla degetul intre "|".

DESPRE OPERATIILE DE TIP UNDO/REDO:

-- acestea se executa direct atunci cand sunt intalnite
	Pentru operatiile de tip undo/redo am implementat functiile undo si redo.
Functia de undo primeste ca parametrii banda, stiva de undo si stiva de redo.
Se extrage intr-o variabila numita top pointerul retinut in varful stivei pentru
undo; se adauga pointerul la pozitia curenta a degetului in varful stivei pentru
redo, iar apoi se modifica pozitia degetului pentru a indica spre valoarea
pointerului top.
Functia de redo primeste ca parametrii banda, stiva de undo si stiva de redo.
Se extrage intr-o variabila numita top pointerul retinut in varful stivei pentru
redo; se adauga pointerul la pozitia curenta a degetului in varful stivei pentru
undo, iar apoi se modifica pozitia degetului pentru a indica spre valoarea
pointerului top.

			Descriere fisierului tema1.c:

	Folosind functiile din fisierul tema1.h, am creeat banda, stiva pentru UNDO,
stiva pentru REDO si coada pentru operatiile de tip UPDATE.Apoi am deschis fisierele
de input(tema1.in) si de output(tema1.out). Am folosit o variabila de tip intreg "n"
in care am retinut numarul de operatii, citit de pe primul rand al fisierului
de intrare. Am folosit vectorul de caractere "operatie" in care am retinut fiecare
operatie pe rand in timpul citirii de fisier, folosind functia fgets().
Folosind functia strncmp din biblioteca string.h am identificat fiecare operatie.
Daca identificam operatiile "MOVE_RIGHT", "MOVE_LEFT", "MOVE_RIGHT_CHAR",
"MOVE_LEFT_CHAR", "WRITE", "INSERT_RIGHT", "INSERT_LEFT" le adaugam in coada.
Daca identificam operatiile "SHOW_CURRENT", "SHOW", "UNDO", "REDO" apelam
functiile corespunzatoare si le executam direct.
Daca identificam operatia "EXECUTE" extragem prima operatie din coada. Cu ajutorul
functiei strncmp identificam din nou operatia. Pentru operatiile MOVE_RIGHT
si MOVE_LEFT se adauga pointerul la pozitia curenta in stiva de undo inainte
de a le executa deoarece se stie ca acestea se pot executa mereu cu succes.
Totusi, daca se intalneste MOVE_LEFT si degetul se afla pe prima pozitie,
pointerul nu va fi retinut. Pentru operatiile MOVE_LEFT_CHAR, MOVE_RIGHT_CHAR,
INSERT_LEFT, INSERT_RIGHT se foloseste o variabia de tip Item(adica char)
numita "ultimul_caracter" in care se retine caracterul ce trebuie cautat
sau inserat. Acest lucru se aplica si pentru operatia WRITE unde acest caracter
este folosit pentru a-l actualiza pe cel curent. In plus, dupa operatia de WRITE
se golesc stivele de undo si redo.
La finalul unei operatii EXECUTE aceasta se elimina din coada si se trece la
citirea urmatoarei operatii.
In final se elibereaza toata memoria alocata pentru stiva de undo, stiva de redo,
coada de operatii si banda. Se inchid fisierele de input si output.
///////////////////////////////////////////////////////////////////////////////
Punctajul obtinut la teste la rularea pe calculatorul propriu este:
Total: 100/100
Valgrind: 20/20
