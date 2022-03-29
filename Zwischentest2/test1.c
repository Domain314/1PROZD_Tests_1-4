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
}pqueue;

char getMenu()
{
  printf("\nChoose action: print queue (p), enqueue entry (e), dequeue entry (d) or exit (x): ");
  char choice;
  while (1) {
    scanf(" %c", &choice);
    if (choice != 'p' && choice != 'e' && choice != 'd' && choice != 'x'){
      printf("Input invalid! Try again: ");
    } else {
      return choice;
    }
  }

  return choice;
}

struct entry getNewEntry(pqueue *_nQueue, int _index)
{
  return _nQueue->entries[_index];
  _nQueue.entries
}

int main()
{
  pqueue newQueue;
  pqueue *nQ = &newQueue;

  
  for (int i = 0; i < 10; i++) {
    printf("%s\n", getNewEntry(nQ, i).message);
  }

  char choice = getMenu();

  switch (choice) {
    case 'p': printf("Choosen: %c\n", choice); break;
    case 'e': printf("Choosen: %c\n", choice); break;
    case 'd': printf("Choosen: %c\n", choice); break;
    case 'x': printf("Choosen: %c\n", choice); break;
    default: break;
  }


}
