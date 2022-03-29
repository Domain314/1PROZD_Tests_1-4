/*
* Queuer314 by Artjom Moisejev - Copyright (C) 2021 <domain_69@hotmail.de>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>

typedef enum priority
{
    HIGHEST = 1,
    HIGH,
    NORAML,
    LOW,
    LOWEST
}priority;

typedef struct entry
{
    char message[31];
    priority priority;
}entry;

typedef struct pqueue
{
    entry entries[10];
    int amount;
}pqueue;

// return 1, when pqueue.amount <= -1
// return 0, when pqueue.amount > -1
// see in main() why -1
int isEmpty(struct pqueue* pqueue)
{
    return pqueue->amount <= -1 ? 1 : 0;
}

// return 1, when pqueue.amount >= 9
// return 0, when pqueue.amount < 9
int isFull(struct pqueue* pqueue)
{
    return pqueue->amount >= 9 ? 1 : 0;
}

// decides between "1 entry" or "n entries" (including 0)
void printAmount(int amount)
{
    if (amount == 1){
        printf("\npriority queue now contains 1 entry");
    } else {
        printf("\npriority queue now contains %d entries", amount);
    }
}

// add entry and squish it between two entries, if needed
void enqueue(struct pqueue* pqueue, struct entry entry)
{
    // check whether queue is full..
    if (isFull(pqueue)) {
        printf("\npriority queue already full!");
    } else if (isEmpty(pqueue)) {      // ..or empty..
        pqueue->entries[0] = entry;
        printAmount(++pqueue->amount+1);
    } else {                          //  ..else squish:
        // loop through all queue entries (until break;)
        for (int i = 0; i <= pqueue->amount+1; i++) {
            // compare priorities until needed position is found
            if (entry.priority < pqueue->entries[i].priority) {
                // loop backwards through entries
                for (int j = pqueue->amount+1 ; j > i; j--) {
                    // move every entry upwards, until i is reached (and freed)
                    // (i = position the for-loop is at, when reached the needed position)
                    pqueue->entries[j] = pqueue->entries[j-1];
                }
                // place newEntry on the freed position i of the for-loop
                pqueue->entries[i] = entry;
                // print (amount+1), but increment before using it
                printAmount(++pqueue->amount+1);
                // end for-loop
                break;
            }
        }
    }
}

// print highest priority message, delete it and move up all entries
void dequeue(struct pqueue* pqueue)
{
    // check whether the queue is empty
    if (isEmpty(pqueue)){
        printf("\npriority queue is empty!");
    } else {
        // print highest message
        printf("\nMessage: %s", pqueue->entries[0].message);
        // move up all entries
        for (int i = 0; i <= pqueue->amount; i++) {
            pqueue->entries[i] = pqueue->entries[i+1];
        }
        // decrease and print new amount
        printAmount(--pqueue->amount+1);
    }
}

// convert enum to char
char convertPriorityToChar(int priority)
{
    switch (priority) {
        case 1: return 'H'; break;
        case 2: return 'h'; break;
        case 3: return 'n'; break;
        case 4: return 'l'; break;
        case 5: return 'L'; break;
        default: return '0'; break;
    }
}

// convert char to enum
int convertCharToPriority(char charToConvert)
{
    switch (charToConvert) {
        case 'H': return 1; break;
        case 'h': return 2; break;
        case 'n': return 3; break;
        case 'l': return 4; break;
        case 'L': return 5; break;
        default: return 0; break;
    }
}

// print all entries
void printQueue(pqueue* pqueue)
{
    // check whether the queue is empty
    if (isEmpty(pqueue)) {
        printf("\nempty queue");
    }
    // print all entries with priority != 6 (initialized with 6)
    for (int i = 0; i < pqueue->amount+1; i++) {
        if (pqueue->entries[i].priority != 6)
        {
            printf("\n%c: %s", convertPriorityToChar(pqueue->entries[i].priority), pqueue->entries[i].message);
        }
    }
}

// print error message
void printError()
{
    printf("\nInput invalid! Try again: ");
}

// print main menu and ask for choice
char getMenu()
{
    printf("\nChoose action: print queue (p), enqueue entry (e), dequeue entry (d) or exit (x): ");
    char choice;
    while (1) {
        scanf(" %c", &choice);
        if (choice != 'p' && choice != 'e' && choice != 'd' && choice != 'x'){
            printError();
        } else {
            return choice;
        }
    }
    return choice;
}

// generate new entry with user input
struct entry getNewEntry()
{
    printf("\nChoose priority: lowest (L), low (l), normal (n), high (h), highest (H): ");
    char choice;

    while (1) {
        scanf(" %c", &choice);
        if (choice != 'L' && choice != 'l' && choice != 'n' && choice != 'h' && choice != 'H'){
            printError();
        } else {
            break;
        }
    }
    entry newEntry;
    newEntry.priority = convertCharToPriority(choice);
    printf("\nChoose message: ");
    scanf(" %s", newEntry.message); // %31s
    return newEntry;
}

int main()
{
    pqueue queue, *queuePtr = &queue;
    // set amount of entries to -1 to sync it with array index
    // first entry = [0], amount = 0
    // second entry = [1], amount = 1
    queue.amount = -1;
    // set priorities of all entries to 6 ("LOWEST" = 5)
    for (int i = 0; i < 10; i++) {
        queue.entries[i].priority = 6;
    }
    // endless loop, until input: 'x'
    int loop = 1;
    while (loop) {
        char choice = getMenu();
        entry newEntry;
        switch (choice) {
            case 'p': printQueue(queuePtr); break;    // &pqueue statt queuePtr
            case 'e': newEntry = getNewEntry(); enqueue(queuePtr, newEntry); break;
            case 'd': dequeue(queuePtr); break;
            case 'x': loop = 0; break;
            default: break;
        }
    }
}
