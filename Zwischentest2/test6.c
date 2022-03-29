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

void printAmount(int amount)
{
    if (amount == 1){
      printf("\npriority queue now contains 1 entry");
    } else {
      printf("\npriority queue now contains %d entries", amount);
    }
}

void enqueue(struct pqueue* pqueue, struct entry entry)
{
    if (isFull(pqueue)) {
        printf("\npriority queue already full!");
    } else if (isEmpty(pqueue)) {
        pqueue->entries[0] = entry;
        printAmount(++pqueue->amount+1);
    } else {
        for (int i = 0; i <= pqueue->amount+1; i++) {
            if (entry.priority < pqueue->entries[i].priority){
                for (int j = pqueue->amount+1 ; j > i; j--) {
                    pqueue->entries[j] = pqueue->entries[j-1];
                }
                pqueue->entries[i] = entry;
                printAmount(++pqueue->amount+1);
                break;
            }
        }
    }
}

void dequeue(struct pqueue* pqueue)
{
    if (isEmpty(pqueue)){
      printf("\npriority queue is empty!");
    } else {
      printf("\nMessage: %s", pqueue->entries[0].message);
      for (int i = 0; i <= pqueue->amount; i++) {
          pqueue->entries[i] = pqueue->entries[i+1];
      }
      pqueue->amount--;
      printAmount(pqueue->amount+1);
    }
}

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

void printQueue(pqueue* pqueue)
{
  if (isEmpty(pqueue)) {
    printf("\nempty queue");
  }

    for (int i = 0; i < pqueue->amount+1; i++) {
        if (pqueue->entries[i].priority != 0)
        {
            printf("\n%c: %s", convertPriorityToChar(pqueue->entries[i].priority), pqueue->entries[i].message);
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
    scanf(" %s", newEntry.message);
    return newEntry;
}

int main()
{
    pqueue queue, *queuePtr = &queue;
    queue.amount = -1;
    for (int i = 0; i < 10; i++) {
        queue.entries[i].priority = 6;
    }

    int bool = 1;
    while (bool) {
        char choice = getMenu();
        entry newEntry;
        switch (choice) {
            case 'p': printQueue(queuePtr); break;
            case 'e': newEntry = getNewEntry();
                enqueue(queuePtr, newEntry); break;
            case 'd': dequeue(queuePtr); break;
            case 'x': bool = 0; break;
            default: break;
        }
    }
}
