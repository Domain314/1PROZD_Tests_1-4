/*
 * Lee314 by Artjom Moisejev - Copyright (C) 2021 <domain_69@hotmail.de>
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
#include <stdlib.h>

typedef struct node {
    char operator;
    int number;
    //enum node_type type;    // Don't need this
    struct node* next;
}node;

/* ---------- FUNCTIONS ---------- */
// macros for math calculations, [just for fun]
#define ADD_NUMBERS(a, b) (a + b)
#define SUBTRACT_NUMBERS(a, b) (a - b)
#define MULTIPLY_NUMBERS(a, b) (a * b)
#define DIVIDE_NUMBERS(a, b) (a / b)

// mimic "overloading", [just for fun]
node* createOperatorNode(char operator_, node* nodes_);
node* createNumberNode(int number_, node* nodes_);
#define ADD_NODE(a, b) _Generic(a, char: createOperatorNode, int: createNumberNode)(a, b)

node* scanInput(node* nodes_);
node* calcFirstPointOperator(node* nodes_);
node* calcFirstDashOperator(node* nodes_);
node* findPreviousNode(node* head, node* node);
void removeAfterNode(node* nodes_, node* actualNode_);
void printList(node *nodes_);

/* ---------- MAIN ---------- */
int main()
{
    node* nodes = NULL;
    // scan input and create nodes, until '='
    nodes = scanInput(nodes);

    // calculate all pointer operations
    while(1) {
        node* temp = calcFirstPointOperator(nodes);
        if(temp == NULL) break;
        printList(nodes);
    }
    // calculate all dash operators
    while(1) {
        node* temp = calcFirstDashOperator(nodes);
        if(temp == NULL) break;
        printList(nodes);
    }
    printf("\nFinal result: ");
    printList(nodes);
    free(nodes);
    return 0;
}

/* ---------- INPUT & OUTPUT ---------- */
node* scanInput(node* nodes_)
{
    // ticks up and down for num -> op -> num -> op..
    int numChar = 0;
    while(1) {
        if(numChar == 0) {
            int num;
            printf("\nEnter number: "); scanf(" %d", &num);
            nodes_ = ADD_NODE(num, nodes_);
            printf("\nCurrent list: "); printList(nodes_);
            numChar++;
        } else {
            char op;
            printf("\nEnter operator: "); scanf(" %c", &op);
            if (op == '=') { break; }
            nodes_ = ADD_NODE(op, nodes_);
            printf("\nCurrent list: "); printList(nodes_);
            numChar--;
        }
    }
    return nodes_;
}

void printList(node *nodes_)
{
    // print nums and ops, until op-node == NULL
    while (nodes_ != NULL)
    {
        printf("%d", nodes_->number);
        nodes_ = nodes_->next;
        if (nodes_ == NULL) break;
        printf("%c", nodes_->operator);
        nodes_ = nodes_->next;
    }
    printf("\n");
}

/* ---------- NODE CREATION ---------- */
// create nodes and set it between last node and NULL
// add nodes at end for easier reading and printing afterwards
// ADD_NODE (#define at top) splits into these two functions:
node* createOperatorNode(char operator_, node* nodes_)
{
    node* newNode = (node*)malloc(sizeof(struct node));
    newNode->operator = operator_;
    newNode->next = NULL;
    node* lastNode = nodes_;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    lastNode->next = newNode;
    return nodes_;
}

node* createNumberNode(int number_, node* nodes_)
{
    node* newNode = (node*)malloc(sizeof(struct node));
    newNode->number = number_;
    newNode->next = NULL;
    // if first node, return newNode,
    if (nodes_ == NULL) {
        return newNode;
    } else {
        // else position at end of list and return list
        node* lastNode = nodes_->next;;
        while (lastNode->next != NULL) {
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
        return nodes_;
    }
}

/* ---------- NODE MANIPULATION ---------- */
node* findPreviousNode(node* nodes_, node* actualNode_)
{
    // if actualNode == first node in list
    if (nodes_ == actualNode_) return NULL;
    node* prevNode = nodes_;
    // search list, until ->next == actualNode
    while (prevNode->next != actualNode_) {
        prevNode = prevNode->next;
    }
    return prevNode;
}

void removeAfterNode(node* nodes_, node* actualNode_)
{
    // set previous nodes next-pointer to actualNode;
    node* prevNode = findPreviousNode(nodes_, actualNode_);
    if (prevNode != NULL){
        prevNode->next = actualNode_;
    }

    // if actualNode is new last node, free nodes after actualNode
    if(actualNode_->next->next->next == NULL) {
        free(actualNode_->next->next);
        free(actualNode_->next);
        actualNode_->next = NULL;
    } else {
        // else free next 2 nodes (op + num2) and connect actualNode with 3. node
        node* target = actualNode_->next->next->next;
        free(actualNode_->next->next);
        free(actualNode_->next);
        actualNode_->next = target;
    }
}

/* ---------- NODE CALCULATION ---------- */
node* calcFirstPointOperator(node* nodes_)
{
    // if one node left in list, return NULL
    if (nodes_->next == NULL) return NULL;
    node* tempNum1 = nodes_, *tempNum2, *tempOp;
    // search for pointer ops, until found or return NULL, when reached end.
    while(tempNum1->next->operator != '*' && tempNum1->next->operator != '/') {
        tempNum1 = tempNum1->next->next;
        if(tempNum1->next == NULL) return NULL; // return NULL pointer
    }
    //set op and num2, based on num1
    tempOp = tempNum1->next;
    tempNum2 = tempNum1->next->next;

    // decide between two operators and set result to num1
    switch (tempOp->operator) {
        case '*':
          tempNum1->number = MULTIPLY_NUMBERS(tempNum1->number, tempNum2->number);
          break;
        case '/':
          if(tempNum2->number == 0){
              // divide by 0 => 1 => num1 unchanged
              break;
          } else {
              tempNum1->number = DIVIDE_NUMBERS(tempNum1->number, tempNum2->number);
              break;
              }
        default: printf("\nERROR in %s() @ %d\n", __FUNCTION__, __LINE__); break;
    }
    // remove and free nodes with op and num2. Also connecting num1 with 3. node
    removeAfterNode(nodes_, tempNum1);
    printf("\nPoint operator result: ");
    return nodes_;
}

node* calcFirstDashOperator(node* nodes_)
{
    // if one node left in list, return NULL
    if (nodes_->next == NULL) return NULL;
    node* tempNum1 = nodes_, *tempNum2, *tempOp;
    // search for pointer ops, until found or return NULL, when reached end.
    while(tempNum1->next->operator != '+' && tempNum1->next->operator != '-') {
        tempNum1 = tempNum1->next->next;
        if(tempNum1->next == NULL) return NULL; // return NULL pointer
    }
    //set op and num2, based on num1
    tempOp = tempNum1->next;
    tempNum2 = tempNum1->next->next;

    // decide between two operators and set result to num1
    switch (tempOp->operator) {
        case '+':
          tempNum1->number = ADD_NUMBERS(tempNum1->number, tempNum2->number);
          break;
        case '-':
          tempNum1->number = SUBTRACT_NUMBERS(tempNum1->number, tempNum2->number);
          break;
        default: printf("\nERROR in %s() @ %d\n", __FUNCTION__, __LINE__); break;
    }
    // remove and free nodes with op and num2. Also connecting num1 with 3. node
    removeAfterNode(nodes_, tempNum1);
    printf("\nDash operator result: ");
    return nodes_;
}
