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




int isEmpty(struct pqueue* pqueue)
{
    return pqueue->amount <= -1 ? 1 : 0;
}

int isFull(struct pqueue* pqueue)
{
    return pqueue->amount >= 9 ? 1 : 0;
}

void enqueue(struct pqueue* pqueue, struct entry entry)
{
    printf("\nenter enqueue");
    if (isFull(pqueue)) {
        printf("\npriority queue already full!");
    } else if (isEmpty(pqueue)) {
        printf("\nenter sec if");
        pqueue->entries[0] = entry;
        printf("\npriority queue now contains %d entries", ++pqueue->amount+1 );
    } else {
        printf("\nenter third if");
        for (int i = 0; i <= pqueue->amount+1; i++) {
            printf("\n%d < %d\nif %d <= %d", i, pqueue->amount, entry.priority, pqueue->entries[i].priority);
            if (entry.priority <= pqueue->entries[i].priority){
                printf("\nenter pre-for-loop");
                for (int j = pqueue->amount+1 ; j > i; j--) {
                    //int index = pqueue->amount + 9 - j;
                    //printf("\n%d", index);
                    pqueue->entries[j] = pqueue->entries[j-1];
                }
                pqueue->entries[i] = entry;
                printf("\npriority queue now contains %d entries", ++pqueue->amount+1 );
                i = 10;
            }
        }
    }

}

void dequeue(struct pqueue* pqueue)
{
    for (int i = 0; i <= pqueue->amount; i++) {
        pqueue->entries[i] = pqueue->entries[i+1];
    }
    pqueue->amount--;
    printf("\npriority queue now contains %d entries", pqueue->amount+1 );
}

char convertPriorityToChar(int priority)
{
    switch (priority) {
        case 1: return 'H';
        case 2: return 'h';
        case 3: return 'n';
        case 4: return 'l';
        case 5: return 'L';
    }
}

int convertCharToPriority(char charToConvert)
{
    switch (charToConvert) {
        case 'H': return 1;
        case 'h': return 2;
        case 'n': return 3;
        case 'l': return 4;
        case 'L': return 5;
    }
}

void printQueue(pqueue* pqueue)
{
    for (int i = 0; i < pqueue->amount+1; i++) {
        if (pqueue->entries[i].priority != 0)
        {
            printf("%c: %s.\n", convertPriorityToChar(pqueue->entries[i].priority), pqueue->entries[i].message);
        }
    }
}

void printError()
{
    printf("\nInput invalid! Try again: ");
}

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

struct entry getNewEntry()
{
    printf("\nChoose priority: lowest(L), low (l), normal (n), high (h), highest (H): ");
    char choice;
    int bool = 1;
    while (bool) {
        scanf(" %c", &choice);
        if (choice != 'L' && choice != 'l' && choice != 'n' && choice != 'h' && choice != 'H'){
            printError();
        } else {
            bool = 0;
            // continue;
        }
    }
    entry newEntry;
    newEntry.priority = convertCharToPriority(choice);
    printf("\nChoose message: ");
    scanf(" %s", newEntry.message);
    return newEntry;
}



int main()
{
    pqueue queue, *queuePtr = &queue;
    // initialize with 0 ?
    queue.amount = -1;
    for (int i = 0; i < 10; i++) {
        queue.entries[i].priority = 6;
    }

    // printf("%d\n", isEmpty(queuePtr));
    // printf("%d\n", isFull(queuePtr));
    // for (int i = 0; i < 10; i++) {
    //   queue.entries[i] = getNewEntry();
    //   queue.amount++;
    // }
    // printf("%d\n", isEmpty(queuePtr));
    // printf("%d\n", isFull(queuePtr));
    while (1) {
        char choice = getMenu();
        entry newEntry;
        switch (choice) {
            case 'p': printQueue(queuePtr); break;
            case 'e': newEntry = getNewEntry();
                enqueue(queuePtr, newEntry); break;
            case 'd': dequeue(queuePtr); break;
            case 'x': printf("\nChoosen: %c\n", choice); break;
            default: break;
        }

    }


}
