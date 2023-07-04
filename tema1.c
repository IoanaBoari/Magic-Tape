/*BOARI Ioana-Ruxandra - 312CD*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char Item;
#include "tema1.h"
#define CMAX 20

int main() {
    TBanda *banda = createBanda();  // se creeaza banda //
    Stack *undoStack = createStack();  // se creeaza stiva pentru UNDO //
    Stack *redoStack = createStack();  // se creeaza stiva pentru REDO //
    Queue *coada = createQueue();  // se creeaza coada pentru operatiile UPDATE //

    char input_filename[] = "tema1.in";
    FILE *in = fopen(input_filename, "rt");  // se deschide fisierul de input //
    char output_filename[] = "tema1.out";
    FILE *out = fopen(output_filename, "wt");  // se deschide fisierul de output //
    int n;
    char operatie[CMAX];  // vector de caractere in care se retine fiecare operatie //
    fscanf(in, "%d\n", &n);  // se citeste numarul de operatii //
    for (int i = 0; i < n; i++) {
        fgets(operatie, CMAX, in);  // se citeste fiecare operatie pe rand //
        if (strncmp(operatie, "MOVE_RIGHT", 10) == 0) {
            enqueue(coada, operatie);  // operatia se adauga in coada //
        } else if (strncmp(operatie, "MOVE_LEFT", 9) == 0) {
            enqueue(coada, operatie);  // operatia se adauga in coada //
        } else if (strncmp(operatie, "MOVE_RIGHT_CHAR", 15) == 0) {
            enqueue(coada, operatie);  // operatia se adauga in coada //
        } else if (strncmp(operatie, "MOVE_LEFT_CHAR", 14) == 0) {
            enqueue(coada, operatie);  // operatia se adauga in coada //
        } else if (strncmp(operatie, "WRITE", 5) == 0) {
            enqueue(coada, operatie);  // operatia se adauga in coada //
        } else if (strncmp(operatie, "INSERT_RIGHT", 12) == 0) {
            enqueue(coada, operatie);  // operatia se adauga in coada //
        } else if (strncmp(operatie, "INSERT_LEFT", 11) == 0) {
            enqueue(coada, operatie);  // operatia se adauga in coada //
        } else if (strncmp(operatie, "SHOW_CURRENT", 12) == 0) {
            show_current(banda, out);  // operatia se executa direct //
        } else if (strncmp(operatie, "SHOW", 4) == 0) {
            show(banda, out);  // operatia se executa direct //
        } else if (strncmp(operatie, "UNDO", 4) == 0) {
            undo(banda, undoStack, redoStack);  // operatia se executa direct //
        } else if (strncmp(operatie, "REDO", 4) == 0) {
            redo(banda, undoStack, redoStack);  // operatia se executa direct //
        } else if (strncmp(operatie, "EXECUTE", 7) == 0) {
            Item *instructiune = front(coada);  // se extrage prima operatie din coada //
            if (strncmp(instructiune, "MOVE_RIGHT_CHAR", 15) == 0) {
                Item ultimul_caracter = instructiune[16];  // se retine caracterul cautat //
                moveRight_char(banda, ultimul_caracter);
            } else if (strncmp(instructiune, "MOVE_LEFT_CHAR", 14) == 0) {
                Item ultimul_caracter = instructiune[15];  // se retine caracterul cautat //
                moveLeft_char(banda, ultimul_caracter, out);
            } else if (strncmp(instructiune, "MOVE_RIGHT", 10) == 0) {
                push(undoStack, banda->deget);  // se adauga pointer la pozitia curenta in stiva de UNDO //
                moveRight(banda);
            } else if (strncmp(instructiune, "MOVE_LEFT", 9) == 0) {
                if (banda->sentinel->next == banda->deget) {
                    // daca degetul se afla pe prima pozitie nu trebuie sa se retina pointerul //
                    moveLeft(banda);
                } else {
                    push(undoStack, banda->deget);  // se adauga pointer la pozitia curenta in stiva de UNDO //
                    moveLeft(banda);
                }
            } else if (strncmp(instructiune, "WRITE", 5) == 0) {
                Item ultimul_caracter = instructiune[6];
                // se retine caracterul cu care va fi inlocuit cel de la pozitia curenta //
                write_char(banda, ultimul_caracter);
                if (!isStackEmpty(undoStack)) {
                    while (!isStackEmpty(undoStack)) {
                    StackNode *temp = undoStack->head;
                    undoStack->head = undoStack->head->next;
                    free(temp);
                }
                undoStack->size = 0;
                }
                if (!isStackEmpty(redoStack)) {
                    while (!isStackEmpty(redoStack)) {
                    StackNode *temp = redoStack->head;
                    redoStack->head = redoStack->head->next;
                    free(temp);
                }
                redoStack->size = 0;
                }
                // dupa operatia WRITE se golesc stivele de UNDO si REDO //
            } else if (strncmp(instructiune, "INSERT_RIGHT", 12) == 0) {
                Item ultimul_caracter = instructiune[13];  // se retine caracterul de inserat //
                insertRight_char(banda, ultimul_caracter);
            } else if (strncmp(instructiune, "INSERT_LEFT", 11) == 0) {
                Item ultimul_caracter = instructiune[12];  // se retine caracterul de inserat //
                insertLeft_char(banda, ultimul_caracter, out);
            }
            dequeue(coada);  // se elimina operatia din coada //
        }
    }
    destroyStack(undoStack);  // se elibereaza memoria pentru stiva de UNDO //
    destroyStack(redoStack);  // se elibereaza memoria pentru stiva de REDO //
    destroyQueue(coada);  // se elibereaza memoria pentru coada de operatii //
    destroyBanda(banda);  // se elibereaza memoria pentru banda //
    fclose(in);  // se inchide fisierul de input //
    fclose(out);  // se inchide fisierul de output //
    return 0;
}
