/*BOARI Ioana-Ruxandra - 312CD*/
#ifndef _TEMA_1_H_
#define _TEMA_1_H_
#include <stdlib.h>
// ---------STRUCTURI---------//
typedef struct ListNode {
    Item value;
    struct ListNode *prev;
    struct ListNode *next;
} ListNode;  // structura pentru elementele benzii

typedef struct StackNode {
    ListNode *dataNode;
    struct StackNode *next;
} StackNode;  // structura pentru elementele stivei //

typedef struct QueueNode {
    struct QueueNode *next;
    Item comanda[];
} QueueNode;  // structura pentru elementele cozii //

typedef struct Banda {
    ListNode *sentinel;
    ListNode *last;
    ListNode *deget;
} TBanda;  // structura ce contine banda impreuna cu degetul //

typedef struct Stack {
    StackNode *head;
    long size;
} Stack;  // structura pentru stiva //

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
    long size;
} Queue;  // structura pentru coada //
// ---------SFARSIT STRUCTURI---------//

// ---------FUNCTII PENTRU BANDA---------//
ListNode *createNode(Item value) {
    ListNode *node = malloc(sizeof(struct ListNode));  // se aloca memorie pentru un element //
    node->value = value;
    node->prev = node->next = NULL;
    return node;
}  // functie pentru creerea unui element al benzii //

TBanda *createBanda(void) {
    TBanda *banda = malloc(sizeof(struct Banda));  // se aloca memorie pentru banda //
    banda->sentinel = createNode('A');  // se creeaza elementul santinela care nu contine informatie utila //
    banda->deget = createNode('#');  // se creeaza primul element util al benzii //
    banda->deget->prev = banda->sentinel;
    banda->sentinel->next = banda->deget;
    banda->last = banda->deget;
    banda->last->next = NULL;
    return banda;
}  // functie pentru creerea unei benzi //

int isEmpty(TBanda *banda) {
    if (banda->sentinel == NULL) {
        return 1;
    } else {
        return 0;
    }
}  // functie care verifica daca banda, inclusiv santinela, este sau nu goala //

void eliminate(TBanda *banda) {
    ListNode *temp;
    if (isEmpty(banda)) {
        return;
    }
    temp = banda->sentinel;
    banda->sentinel = banda->sentinel->next;
    free(temp);
    return;
}  // functie care elimina primul element al benzii, pornind de la santinela //

void destroyBanda(TBanda *banda) {
    while (!isEmpty(banda)) {
        eliminate(banda);
    }
    free(banda);
    return;
}  // functie care elibereaza memoria alocata pentru banda //
// ---------SFARSIT FUNCTII PENTRU BANDA---------//

// ---------FUNCTII PENTRU STIVA---------//
StackNode *createStackNode(ListNode *list_node) {
    StackNode *node = malloc(sizeof(struct StackNode));  // se aloca memorie pentru un element //
    node->dataNode = list_node;
    node->next = NULL;
    return node;
}  // functie pentru creerea unui element al stivei //

Stack* createStack(void) {
    Stack *s = malloc(sizeof(struct Stack));
    s->head = NULL;
    s->size = 0;
    return s;
}  // functie care creeaza o stiva prin alocare dinamica //

int isStackEmpty(Stack* stack) {
    if (stack->head == NULL) {
       return 1;
    } else {
       return 0;
    }
}  // functie care verifica daca o stiva este sau nu goala //

void push(Stack *stack, ListNode *list_node) {
    StackNode *top;
    if (isStackEmpty(stack)) {
        stack->head = createStackNode(list_node);
        stack->size++;
        return;
    } else {
        top = createStackNode(list_node);
        top->next = stack->head;
        stack->head = top;
        stack->size++;
        return;
    }
}  // functie care introduce un nou element in stiva, respectand regula LIFO //

ListNode *top(Stack *stack) {
    if (isStackEmpty(stack)) {
        return NULL;
    } else {
        return stack->head->dataNode;
    }
}  // functie care returneaza elementul din varful stivei //

void pop(Stack *stack) {
    StackNode *temp;
    if (isStackEmpty(stack)) {
        return;
    }
    temp = stack->head;
    stack->head = stack->head->next;
    stack->size--;
    free(temp);
    return;
}  // functie care extrage un element din stiva, respectand regula LIFO //

void destroyStack(Stack *stack) {
    while (!isStackEmpty(stack)) {
        pop(stack);
    }
    stack->size = 0;
    free(stack);
    return;
}  // functie care elibereaza memoria alocata pentru stiva //
// ---------SFARSIT FUNCTII PENTRU STIVA---------//

// ---------FUNCTII PENTRU COADA---------//

QueueNode *createQueueNode(Item comanda[]) {
    int length = strlen(comanda);
    QueueNode *node = malloc(sizeof(struct QueueNode) + (length+1) * sizeof(Item));
    // s-a alocat dinamic memorie pentru nod si pentru vectorul de caractere ce reprezinta comanda //
    for (int i = 0; i < length; i++) {
        node->comanda[i] = comanda[i];
    }
    node->comanda[length] = '\0';
    node->next = NULL;
    return node;
}  // functie pentru creerea unui element al cozii //

Queue* createQueue(void) {
    Queue *queue = malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    return queue;
}  // functie care creeaza o coada prin alocare dinamica //

int isQueueEmpty(Queue *queue) {
    if (queue->front == NULL && queue->rear == NULL) {
        return 1;
    } else {
        return 0;
    }
}  // functie care verifica daca o coada este sau nu goala //

void enqueue(Queue *queue, Item comanda[]) {
    QueueNode *top;
    if (isQueueEmpty(queue)) {
        queue->front = queue->rear = createQueueNode(comanda);
        queue->size++;
        return;
    } else {
        top = createQueueNode(comanda);
        queue->rear->next = top;
        queue->rear = top;
        queue->size++;
        return;
    }
}  // functie care introduce un nou element in coada, respectand regula FIFO //

Item *front(Queue *queue) {
    if (isQueueEmpty(queue)) {
        return NULL;
    } else {
        return queue->front->comanda;
    }
}  // functie care returneaza primul element din coada //

void dequeue(Queue *queue) {
    QueueNode *temp;
    if (isQueueEmpty(queue)) {
        return;
    }
	if (queue->front == queue->rear) {
        temp = queue->front;
        queue->front = queue->rear = NULL;
        queue->size = 0;
        free(temp);
        return;
    }
    temp = queue->front;
    queue->front = queue->front->next;
    queue->size--;
    free(temp);
    return;
}  // functie care extrage un element din coada, respectand regula FIFO //

void destroyQueue(Queue *q) {
	while (!isQueueEmpty(q)) {
		dequeue(q);
	}
	q->size = 0;
	free(q);

	return;
}  // functie care elibereaza memoria alocata pentru coada //

// ---------SFARSIT FUNCTII PENTRU COADA---------//

// --------- OPERATII UPDATE---------//

void moveLeft(TBanda *banda) {
    if (banda->sentinel->next == banda->deget) {
        // daca degetul se afla pe prima pozitie nu se intampla nimic //
        return;
    } else {
        banda->deget = banda->deget->prev;
    }
    return;
}  // functie care este folosita pentru a deplasa degetul cu o pozitie la stanga //

void moveRight(TBanda *banda) {
    if (banda->deget->next == NULL) {
        /* daca degetul se afla pe ultima pozitie se insereaza la dreapta
        un nou nod cu caracterul # si degetul se muta acolo */
        ListNode *newNode = createNode('#');
        banda->last->next = newNode;
        newNode->prev = banda->last;
        banda->last = newNode;
        banda->deget = banda->last;
    } else {
        banda->deget = banda->deget->next;
    }
    return;
}  // functie care este folosita pentru a deplasa degetul cu o pozitie la dreapta //

void moveLeft_char(TBanda *banda, Item value, FILE *file) {
    ListNode *iter;
    iter = banda->deget;
    while (iter != banda->sentinel) {
        if (iter->value == value) {
            banda->deget = iter;
            return;
        } else {
            iter = iter->prev;
        }
    }
    /* daca se ajunge la marginea din stanga si nu s-a gasit caracterul
    se afiseaza urmatorul mesaj, iar pozitia degetului nu se modifica */
    fprintf(file, "ERROR\n");
    return;
}  /* functie care este folosita pentru a deplasa degetul la stanga
    pana la primul caracter egal cu simbolul primit ca parametru.
    Cautarea incepe de la pozitia curenta */

void moveRight_char(TBanda *banda, Item value) {
    ListNode *iter;
    iter = banda->deget;
    while (iter != NULL) {
        if (iter->value == value) {
            banda->deget = iter;
            return;
        } else {
            iter = iter->next;
        }
    }
    /* daca se ajunge la limita din dreapta si nu s-a gasit caracterul
    se insereaza un nou nod cu caracterul # la final si pozitia degetului se muta pe acest nod*/
    ListNode *newNode = createNode('#');
    banda->last->next = newNode;
    newNode->prev = banda->last;
    banda->last = newNode;
    banda->deget = banda->last;

    return;
}  /* functie care este folosita pentru a deplasa degetul la dreapta
    pana la primul caracter egal cu simbolul primit ca parametru.
    Cautarea incepe de la pozitia curenta */

void write_char(TBanda *banda, Item value) {
    if (!isEmpty(banda) && banda->deget != banda->sentinel) {
    banda->deget->value = value;
    return;
    }
}  // functie care este folosita pentru a schimba caracterul de la pozitia curenta //
void insertLeft_char(TBanda *banda, Item value, FILE *file) {
    if (banda->deget == banda->sentinel->next) {
        /* daca degetul se afla pe prima pozitie nu se poate face inserarea
        si se afiseaza urmatorul mesaj*/
        fprintf(file, "ERROR\n");
        return;
    } else {
        ListNode *newNode = createNode(value);
        newNode->next = banda->deget;
        newNode->prev = banda->deget->prev;
        banda->deget->prev->next = newNode;
        banda->deget->prev = newNode;
        moveLeft(banda);
        return;
    }
}  /* functie folosita pentru a insera un caracter in stanga pozitiei curente
    si pentru a deplasa degetul pe noua pozitie inserata */

void insertRight_char(TBanda *banda, Item value) {
    Item caracter = value;
    if (banda->deget->next == NULL) {
        moveRight(banda);
        write_char(banda, caracter);
    } else {
        ListNode *newNode = createNode(value);
        newNode->prev = banda->deget;
        newNode->next = banda->deget->next;
        banda->deget->next->prev = newNode;
        banda->deget->next = newNode;
        moveRight(banda);
    }
}  /* functie folosita pentru a insera un caracter in dreapta pozitiei curente
    si pentru a deplasa degetul pe noua pozitie inserata */

//--------- SFARSIT OPERATII UPDATE---------//

//--------- OPERATII QUERY---------//

void show_current(TBanda *banda, FILE *file) {
    fprintf(file, "%c\n", banda->deget->value);
}  // functie folosita pentru a afisa caracterul curent //

void show(TBanda *banda, FILE *file) {
    ListNode *iter = banda->sentinel->next;
     while (iter != NULL) {
        if (iter == banda->deget) {
            fprintf(file, "|%c|", banda->deget->value);
        } else {
            fprintf(file, "%c", iter->value);
        }
            iter = iter->next;
    }
    fprintf(file, "\n");
}  // functie folosita pentru a afisa continutul benzii, cu marcarea pozitiei degetului //

// --------- SFARSIT OPERATII QUERY---------//

// --------- OPERATII UNDO / REDO---------//
void undo(TBanda *banda, Stack *stack_undo, Stack *stack_redo) {
    if (!isStackEmpty(stack_undo)) {
        ListNode *top = stack_undo->head->dataNode;  // se extrage pointerul din varful stivei pentru UNDO //
        pop(stack_undo);  // se elimina pointerul din stiva pentru UNDO //
        push(stack_redo, banda->deget);  // se adauga pointerul la pozitia curenta in varful stivei pentru REDO //
        banda->deget = top;  // degetul va indica spre pointerul extras din stiva pentru UNDO //
    }
}  // functie folosita pentru a anula ultima operatie //

void redo(TBanda *banda, Stack *stack_undo, Stack *stack_redo) {
    if (!isStackEmpty(stack_redo)) {
        ListNode *top = stack_redo->head->dataNode;  // se extrage pointerul din varful stivei pentru REDO //
        pop(stack_redo);  // se elimina pointerul din stiva pentru REDO //
        push(stack_undo, banda->deget);  // se adauga pointerul la pozitia curenta in varful stivei pentru UNDO //
        banda->deget = top;  // degetul va indica spre pointerul extras din stiva pentru REDO //
    }
}  // functie folosita pentru a reface ultima operatie //

// --------- SFARSIT OPERATII UNDO/REDO---------//

#endif  //_TEMA_1_H_
