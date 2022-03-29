#include <stdio.h>
#include <stdlib.h>

typedef enum node_type{
    OPERATOR_TYPE,
    NUMBER_TYPE
}node_type;

typedef struct node {
    char operator;
    int number;
    enum node_type type;
    struct node* next;
}node;

#define ADD_NUMBERS(a, b) (a + b)
#define SUBTRACT_NUMBERS(a, b) (a - b)
#define MULTIPLY_NUMBERS(a, b) (a * b)
#define DIVIDE_NUMBERS(a, b) (a / b)

node* createOperatorNode(char operator_, struct node* nodes_);
node* createNumberNode(int number_, struct node* nodes_);
#define ADD_NODE(a, b) _Generic(a, char: createOperatorNode, int: createNumberNode)(a, b)

node* scanInput(node* nodes_);

node* calcFirstPointOperator(struct node* nodes_);
node* calcFirstDashOperator(struct node* nodes_);

node* findPreviousNode(struct node* head, struct node* node);

void printList(node *nodes_);
void recursiveFree(node *nodes_);

int main()
{
    node* nodes = NULL;
    nodes = scanInput(nodes);

    while(1) {
        node* temp = calcFirstPointOperator(nodes);
        if(temp == NULL) break;
        printList(nodes);
    }
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

void recursiveFree(node *nodes_)
{
  if (nodes_->next != NULL){
    recursiveFree(nodes_->next);
  }
  free(nodes_);
}

node* scanInput(node* nodes_)
{
    int numChar = 0;
    while(1) {
        if(numChar == 0) {
            int num;
            printf("\nEnter number: ");
            scanf(" %d", &num);
            nodes_ = ADD_NODE(num, nodes_);
            printf("\nCurrent list: ");
            printList(nodes_);
            numChar++;
        } else {
            char op;
            printf("\nEnter operator: ");
            scanf(" %c", &op);
            if (op == '=') { break; }
            nodes_ = ADD_NODE(op, nodes_);
            printf("\nCurrent list: ");
            printList(nodes_);
            numChar--;
        }
    }
    return nodes_;
}

void printList(node *nodes_)
{
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

node* createOperatorNode(char operator_, struct node* nodes_)
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->operator = operator_;
    newNode->type = OPERATOR_TYPE;
    newNode->next = NULL;
    node* lastNode = nodes_;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    lastNode->next = newNode;
    return nodes_;
}

node* createNumberNode(int number_, struct node* nodes_)
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->number = number_;
    newNode->type = NUMBER_TYPE;
    newNode->next = NULL;
    if (nodes_ == NULL) {
        return newNode;
    } else {
        node* lastNode = nodes_->next;;
        while (lastNode->next != NULL) {
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
        return nodes_;
    }

}

node* findPreviousNode(struct node* nodes_, struct node* actualNode_)
{
    if (nodes_ == actualNode_) return NULL;
    node* prevNode = nodes_;
    while (prevNode->next != actualNode_) {
        prevNode = prevNode->next;
    }
    return prevNode;
}

node* calcFirstPointOperator(struct node* nodes_)
{
    if (nodes_->next == NULL) return NULL;
    node* tempNum1 = nodes_, *tempNum2, *tempOp;
    while(tempNum1->next->operator != '*' && tempNum1->next->operator != '/') {
        tempNum1 = tempNum1->next->next;
        if(tempNum1->next == NULL) return NULL; // return NULL pointer
    }
    tempOp = tempNum1->next;
    tempNum2 = tempNum1->next->next;

    switch (tempOp->operator) {
        case '*': tempNum1->number = MULTIPLY_NUMBERS(tempNum1->number, tempNum2->number); break;
        case '/': if(tempNum2->number == 0){
                break;
            } else {
                tempNum1->number = DIVIDE_NUMBERS(tempNum1->number, tempNum2->number); break;
            }
        default: printf("\nERROR in %s() @ %d\n", __FUNCTION__, __LINE__); break;
    }
    node* prevNode = findPreviousNode(nodes_, tempNum1);
    if (prevNode != NULL){
        prevNode->next = tempNum1;
    }

    if(tempNum1->next->next->next == NULL) {
        free(tempNum1->next->next);
        free(tempNum1->next);
        tempNum1->next = NULL;
    } else {
        free(tempNum1->next->next);
        free(tempNum1->next);
        tempNum1->next = tempNum1->next->next->next;
    }
    printf("\nPoint operator result: ");
    return nodes_;
}

node* calcFirstDashOperator(struct node* nodes_)
{
    if (nodes_->next == NULL) return NULL;
    node* tempNum1 = nodes_, *tempNum2, *tempOp;
    while(tempNum1->next->operator != '+' && tempNum1->next->operator != '-') {
        tempNum1 = tempNum1->next->next;
        if(tempNum1->next == NULL) return NULL; // return NULL pointer
    }
    tempOp = tempNum1->next;
    tempNum2 = tempNum1->next->next;

    switch (tempOp->operator) {
        case '+': tempNum1->number = ADD_NUMBERS(tempNum1->number, tempNum2->number); break;
        case '-': tempNum1->number = SUBTRACT_NUMBERS(tempNum1->number, tempNum2->number); break;
        default: printf("\nERROR in %s() @ %d\n", __FUNCTION__, __LINE__); break;
    }
    node* prevNode = findPreviousNode(nodes_, tempNum1);
    if (prevNode != NULL){
        prevNode->next = tempNum1;
    }

    if(tempNum1->next->next->next == NULL) {
        free(tempNum1->next->next);
        free(tempNum1->next);
        tempNum1->next = NULL;
    } else {
        free(tempNum1->next->next);
        free(tempNum1->next);
        tempNum1->next = tempNum1->next->next->next;
    }
    printf("\nDash operator result: ");
    return nodes_;
}
