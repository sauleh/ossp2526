#include<stdio.h>
#include "linkedlist.h"
#include<stdlib.h>

 Node* make_node(int value, Node* pnext)
 {
    Node* pn = malloc(sizeof(Node));
    pn->value = value;
    pn->next = pnext;
    return pn;
 }

Node* append(Node* phead, Node* pnew)
{
    pnew->next = phead;
    return pnew;
}

 void print_node(Node* n)
 {
    while (NULL != n)
    {
        printf("node(%p): value: %d, next: %p \n", n, n->value, n->next);
        n = n->next;
    }
 }

int main()
{
    Node* head = make_node(5, NULL);
    for(int i=0; i<5; i++)
    {
        Node* pnew = make_node(i+0xaaaaaaa00, NULL);
        head = append(head, pnew);
    }
    print_node(head);
    return 0;
}