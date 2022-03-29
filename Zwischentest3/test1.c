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

node* createOperatorNode(char operator_, struct node* nodes_);
node* createNumberNode(int number_, struct node* nodes_);
#define ADD_NODE(a, b) _Generic(a, char: createOperatorNode, int: createNumberNode)(a, b)

node* scanInput(node* nodes_);




void printList(node *head)
{
    while (head != NULL)
    {
        printf("%d->", head->number);
        head = head->next;
        if (head == NULL) break;
        printf("%c->", head->operator);
        head = head->next;
    }
}

int main()
{
    node* nodes = NULL;
    nodes = scanInput(nodes);

    printList(nodes);

    //calculateNodes(nodes);
    return 0;
}

node* scanInput(node* nodes_)
{
    int numChar = 0;
    while(1) {
        if(numChar == 0) {
            int num;
            scanf(" %d", &num);
            nodes_ = ADD_NODE(num, nodes_);
            numChar++;
        } else {
            char op;
            scanf(" %c", &op);
            if (op == '=') { break; }
            nodes_ = ADD_NODE(op, nodes_);
            numChar--;
        }
    }
    return nodes_;
}

struct node* createOperatorNode(char operator_, struct node* nodes_)
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

struct node* createNumberNode(int number_, struct node* nodes_)
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
