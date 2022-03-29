#include <stdio.h>

typedef enum priority
{
  HIGHEST = 'H',
  HIGH = 'h',
  NORAML = 'n',
  LOW = 'l',
  LOWEST = 'L'
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
  if (isFull(pqueue)) {
    printf("priority queue already full!");
  } else if (isFull(pqueue)) {
    pqueue->entries[0] = entry;
    printf("priority queue now contains %d entries", pqueue->amount+1 );
  } else {
    for (int i = 0; i < pqueue->amount; i++) {
      if (entry.priority <= pqueue->entries[i].priority){

        for (int j = 0; j == i; j++) {
          int index = pqueue->amount - j;
          pqueue->entries[index+1] = pqueue->entries[index];
        }
        pqueue->entries[i] = entry;
        pqueue->amount++;
        printf("priority queue now contains %d entries", pqueue->amount+1 );
        i = 10;
      }
    }
  }

}

void dequeue(struct pqueue* pqueue)
{
  // todo
}



void printQueue(pqueue* pqueue)
{
  for (int i = 0; i < 10; i++) {
    if (pqueue->entries[i].priority != 0)
    {
      printf("%c: %s.\n", (pqueue->entries[i].priority), (pqueue->entries[i].message));
    }
  }
}

void printError()
{
  printf("Input invalid! Try again: ");
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
  printf("Choose priority: lowest(L), low (l), normal (n), high (h), highest (H): ");
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
  newEntry.priority = choice;
  printf("Choose message: ");
  scanf(" %s", newEntry.message);
  return newEntry;
}

int main()
{
  pqueue queue, *queuePtr = &queue;
  // initialize with 0 ?
  queue.amount = -1;

  printf("%d\n", isEmpty(queuePtr));
  printf("%d\n", isFull(queuePtr));
  for (int i = 0; i < 10; i++) {
    queue.entries[i] = getNewEntry();
    queue.amount++;
  }
  printf("%d\n", isEmpty(queuePtr));
  printf("%d\n", isFull(queuePtr));

  char choice = getMenu();

  switch (choice) {
    case 'p': printQueue(queuePtr); break;
    case 'e': printf("Choosen: %c\n", choice); break;
    case 'd': printf("Choosen: %c\n", choice); break;
    case 'x': printf("Choosen: %c\n", choice); break;
    default: break;
  }


}
