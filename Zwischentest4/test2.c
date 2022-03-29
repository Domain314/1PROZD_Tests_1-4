#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct IN {
    char l;
    struct IN* n;
} IN;

typedef struct N {
    IN* w;
    struct N* n;
    int lA;
} N;

typedef struct H {
    N* no;
    int wA;
} H;

int compare_alphabethically(N* m, N* n) {
    int vM = m->w?m->w->l:0;
    int vN = n->w?n->w->l:0;
    int d = vM - vN;
    if(d==0){
        if(m!=NULL && n!=NULL){
            return compare_alphabethically(m->n, n->n);
        }
    }
    return d;
}

int compare_byLength(N* m, N* n) {
    int vM = m?m->lA:0;
    int vN = n?n->lA:0;
    int d = vM - vN;
    if(d==0){
        if(m!=NULL && n!=NULL){
            return compare_byLength(m->n, n->n);
        }
    }
    return d;
}
void changePlace(N* t1, N* t2) {
    IN* t = t1->w;
    int tA = t1->lA;
    t1->w = t2->w;
    t1->lA = t2->lA;
    t2->w = t;
    t2->lA = tA;

}
void sort (N* h, int (*compare)(N*, N*), int de, int wA) {

    for (int i = 0; i < wA; i++) {
        for (int j = 0; j < wA; j++) {
            N* t1 = h, *t2;
            for (int k = 0; k < j; ++k) {
                t1 = t1->n;
            }
            t2 = t1->n;
            if (t2 == NULL) {
                continue;
            }
            int d = compare(t1, t2);
            if (d < 0 && de == 0) {
                changePlace(t1, t2);
            } else if (d > 0 && de == 1) {
                changePlace(t1, t2);
            }
        }
    }
}
void initializeSort(H* h) {
    char cS, cC;
    int d = 0;
    printf("\nSort (a)lphabetically or by (l)ength?");
    scanf(" %c", &cS);
    printf("\nSort (a)scending or (d)escending?");
    scanf(" %c", &cC);
    if (cC == 'a') { d = 1; }
    if (cS == 'a') {
        sort(h->no, compare_alphabethically, d, h->wA);
    } else {
        sort(h->no, compare_byLength, d, h->wA);
    }
}
IN* createInnerNode(char b[]) {
    IN* iN = (IN*)malloc(sizeof(IN)), *t = iN;
    t->l = b[0];
    for (int i = 1; i < strlen(b); i++) {
        IN* nN = malloc(sizeof(IN));
        nN->l = b[i];
        nN->n = NULL;
        t->n = nN;
        t = t->n;
    }
    return iN;
}
N* createNode(char b[]) {
    N* oN = (N*)malloc(sizeof(N)); //*tmp = oNode;
    oN->w = createInnerNode(b);
    oN->lA = strlen(b);
    return oN;
}
void appendWord(H* h) {
    printf("\nEnter Word: ");
    char b[100];
    scanf(" %99s", b);

    N* t = h->no;
    if (t->w == NULL) {
        t->w = createInnerNode(b);
        t->lA = strlen(b);
    } else {
        while (t->n != NULL) {
            t = t->n;
        }
        t->n = createNode(b);
        t->n->n = NULL;
    }
    h->wA++;
}
void insertWord(H* h) {
    int ix;
    char b[100];
    printf("\nEnter Index: ");
    scanf(" %d", &ix);
    if (ix == 0 && h->wA == 0) {
        appendWord(h);
    } else {
        printf("\nEnter Word: ");
        scanf(" %99s", b);
        N* t = h->no;
        if (ix == 0) {
            N* nN = createNode(b);
            nN->n = t;
            h->no = nN;
        } else {
            for (int i = 0; i < ix-1; i++) {
                t = t->n;
            }
            N* nN = createNode(b), *sN;
            sN = t->n;
            t->n = nN;
            nN->n = sN;
        }
    }
    h->wA++;
}
void printList(H* h) {
    if (h->wA == 0) {
        printf("\nempty list");
    } else {
        printf("\n");
        N* no = h->no;
        while (1) {
            IN* iN = no->w;
            while (1) {
                printf("%c", iN->l);
                iN = iN->n;
                if (iN == NULL) break;
            }
            no = no->n;
            if (no == NULL) break;
            printf(" ");
        }
    }
}
void RecFree(IN* n) {
  if (n->n != NULL) {
    RecFree(n->n);
  }
  free(n);
}
void recFree(N* n) {
    if (n->n != NULL) {
        recFree(n->n);
    }
    RecFree(n->w);
    free(n);
}
void freeAll(H* h) {
    if (h->no != NULL) {
      recFree(h->no);
    }
    free(h);
}
void deleteWord(H* h) {
    int ix;
    N* t = h->no;
    printf("\nEnter Index: ");
    scanf(" %d", &ix);
    if (ix == 0) {
        h->no = h->no->n;
        RecFree(t->w);
        free (t);
    } else {
        for (int i = 0; i < ix-1; i++) {
            t = t->n;
        }
        N* sN;
        if (NULL == (sN = t->n->n)) {
            RecFree(t->n->w);
            free(t->n);
            t->n = NULL;
        }
        RecFree(t->n->w);
        free(t->n);
        t->n = sN;
    }
    h->wA--;
}
void printMenu(H* h) {
    printf("\nChoose action: (a)ppend, (i)nsert, (d)elete, (s)ort, (p)rint, e(x)it: ");
    char c;
    scanf(" %c", &c);
    switch (c) {
        case 'a': appendWord(h); break;
        case 'i': insertWord(h); break;
        case 'd': deleteWord(h); break;
        case 's': initializeSort(h); break;
        case 'p': printList(h); break;
        case 'x': h->wA = -1; break;
    }
}
int main() {
    N* n = (N*)calloc(1, sizeof(N));
    H* h = (H*)malloc(sizeof(H));
    h->no = n;
    while (1) {
        printMenu(h);
        if (h->wA == -1) break;
    }
    if (n->w != NULL) {freeAll(h);}
    return 0;
}
