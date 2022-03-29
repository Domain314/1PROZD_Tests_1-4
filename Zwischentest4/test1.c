#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct InnerNode {
    char letter;
    struct InnerNode* next;
} InnerNode;

typedef struct Node {
    InnerNode* word;
    struct Node* next;
    int letterAmount;
} Node;

typedef struct Holder {
    Node* nodes;
    int wordAmount;
} Holder;

int compare_alphabethically(Node* m, Node* n) {
    int valueM = m->word?m->word->letter:0;
    int valueN = n->word?n->word->letter:0;
    int diff = valueM - valueN;
    if(diff==0){
        if(m!=NULL && n!=NULL){
            //return compare_alphabethically(m->next, n->next);
        }
    }
    return diff;
}

int compare_byLength(Node* m, Node* n) {
    int valueM = m?m->letterAmount:0;
    int valueN = n?n->letterAmount:0;
    int diff = valueM - valueN;
    if(diff==0){
        if(m!=NULL && n!=NULL){
            //return compare_byLength(m->next, n->next);
        }
    }
    return diff;
}
void changePlace(Node* first, Node* second) {
    InnerNode* temp = first->word;
    int tAmount = first->letterAmount;
    first->word = second->word;
    first->letterAmount = second->letterAmount;
    second->word = temp;
    second->letterAmount = tAmount;

}
void sort (Node* head_, int (*compare)(Node*, Node*), int descending_, int wordAmount) {

    for (int i = 0; i < wordAmount-1; i++) {
        for (int j = 0; j < wordAmount; j++) {
            Node* temp1 = head_, *temp2;
            for (int k = 0; k < j; ++k) {
                temp1 = temp1->next;
            }
            temp2 = temp1->next;
            if (temp2 == NULL) {
                continue;
            }
            int diff = compare(temp1, temp2);
            if (diff < 0 && descending_ == 0) {
                changePlace(temp1, temp2);
            } else if (diff > 0 && descending_ == 1) {
                changePlace(temp1, temp2);
            }
        }
    }
}
void initializeSort(Holder* holder_) {
    char choiceS, choiceC;
    int desc = 0;
    printf("\nSort (a)lphabetically or by (l)ength?");
    scanf(" %c", &choiceS);
    printf("\nSort (a)scending or (d)escending?");
    scanf(" %c", &choiceC);
    if (choiceC == 'a') { desc = 1; }
    if (choiceS == 'a') {
        sort(holder_->nodes, compare_alphabethically, desc, holder_->wordAmount);
    } else {
        sort(holder_->nodes, compare_byLength, desc, holder_->wordAmount);
    }
}
InnerNode* createInnerNode(char buf[]) {
    InnerNode* iNode = (InnerNode*)malloc(sizeof(InnerNode)), *tmp = iNode;
    tmp->letter = buf[0];
    for (int i = 1; i < strlen(buf); i++) {
        InnerNode* newNode = malloc(sizeof(InnerNode));
        newNode->letter = buf[i];
        newNode->next = NULL;
        tmp->next = newNode;
        tmp = tmp->next;
    }
    return iNode;
}
Node* createNode(char buf[]) {
    Node* oNode = (Node*)malloc(sizeof(Node)); //*tmp = oNode;
    oNode->word = createInnerNode(buf);
    oNode->letterAmount = strlen(buf);
    return oNode;
}
void appendWord(Holder* holder_) {
    printf("\nEnter Word: ");
    char buf[100];
    scanf(" %99s", buf);

    Node* tmp = holder_->nodes;
    if (tmp->word == NULL) {
        tmp->word = createInnerNode(buf);
        tmp->letterAmount = strlen(buf);
    } else {
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = createNode(buf);
        tmp->next->next = NULL;
    }
    holder_->wordAmount++;
}
void insertWord(Holder* holder_) {
    int index;
    char buf[100];
    printf("\nEnter Index: ");
    scanf(" %d", &index);
    if (index == 0 && holder_->wordAmount == 0) {
        appendWord(holder_);
    } else {
        printf("\nEnter Word: ");
        scanf(" %99s", buf);
        Node* tmp = holder_->nodes;
        if (index == 0) {
            Node* newNode = createNode(buf);
            newNode->next = tmp;
            holder_->nodes = newNode;
        } else {
            for (int i = 0; i < index-1; i++) {
                tmp = tmp->next;
            }
            Node* newNode = createNode(buf), *secNode;
            secNode = tmp->next;
            tmp->next = newNode;
            newNode->next = secNode;
        }
        holder_->wordAmount++;
    }
}
void printList(Holder* holder_) {
    if (holder_->wordAmount == 0) {
        printf("\nempty list");
    } else {
        printf("\n");
        Node* nodes = holder_->nodes;
        while (1) {
            InnerNode* iNode = nodes->word;
            while (1) {
                printf("%c", iNode->letter);
                if (iNode->next == NULL) break;
                iNode = iNode->next;

            }
            nodes = nodes->next;
            if (nodes == NULL) break;
            printf(" ");
        }
    }
}
void RecFree(InnerNode* iNode) {
    if (iNode->next != NULL) {
        RecFree(iNode->next);
    }
    free(iNode);
}
void recFree(Node* node) {
    if (node->next != NULL) {
        recFree(node->next);
    }
    RecFree(node->word);
    free(node);
}
void freeAll(Holder* holder_) {
    if (holder_->nodes != NULL) {
        recFree(holder_->nodes);
    }
    free(holder_);
}
void deleteWord(Holder* holder_) {
    int index;
    Node* tmp = holder_->nodes;
    printf("\nEnter Index: ");
    scanf(" %d", &index);
    if (index == 0) {
        holder_->nodes = holder_->nodes->next;
        RecFree(tmp->word);
        free (tmp);
    } else {
        for (int i = 0; i < index-1; i++) {
            tmp = tmp->next;
        }
        Node* secNode;
        if (NULL == (secNode = tmp->next->next)) {
            RecFree(tmp->next->word);
            free(tmp->next);
            tmp->next = NULL;
        } else {
            RecFree(tmp->next->word);
            free(tmp->next);
            tmp->next = secNode;
        }

    }
    holder_->wordAmount--;
    if (holder_->nodes == NULL) {
        Node* nodes = (Node*)calloc(1, sizeof(Node));
        holder_->nodes = nodes;
    }
}
void printMenu(Holder* holder_) {
    printf("\nChoose action: (a)ppend, (i)nsert, (d)elete, (s)ort, (p)rint, e(x)it: ");
    char choice;
    scanf(" %c", &choice);
    switch (choice) {
        case 'a': appendWord(holder_); break;
        case 'i': insertWord(holder_); break;
        case 'd': deleteWord(holder_); break;
        case 's': initializeSort(holder_); break;
        case 'p': printList(holder_); break;
        case 'x': holder_->wordAmount = -1; break;
    }
}
int main() {
    Node* nodes = (Node*)calloc(1, sizeof(Node));
    Holder* holder = (Holder*)malloc(sizeof(Holder));
    holder->nodes = nodes;
    holder->wordAmount = 0;
    while (1) {
        printMenu(holder);
        if (holder->wordAmount == -1) break;
    }
    freeAll(holder);
    return 0;
}
