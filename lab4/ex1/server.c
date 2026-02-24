#include <stdio.h>
#include<stdlib.h>
#include<string.h>

/* To be written. This file needs to be sumitted to canvas */

extern char *processRequest (char *);

char* make_copy_on_heap(const char* pch)
{
    int len = strlen(pch) + 1;
    char* copy = malloc(len);
    strncpy(copy, pch, len);
    return copy;
}

typedef struct _rule 
{
    unsigned int ips;
    unsigned int ipe;
    unsigned short ports;
    unsigned short porte;
    struct _rule* next;
} Rule;

Rule* rules_head;

Rule* extract_rule(char* pchrule)
{
    return (Rule*) pchrule;
}

char* process_add(char* request)
{
    Rule* newRule = extract_rule(request+2);
    if (!newRule)
        return make_copy_on_heap("Invalid rule");
    
    if (!rules_head)
        rules_head = newRule;
    else
    {
        newRule->next = rules_head;
        rules_head = newRule;
    }
    return make_copy_on_heap("Rule added");
}

char* process_check(char* request)
{

}

char *processRequest (char *request) {
    if (!request || !request[0])
        return NULL;
    char* resp = NULL;
    switch(request[0])
    {
        case 'A':
            resp = process_add(request);
            break;
        case 'C':
            resp = process_check(request);
            break;
        case 'R':
        case 'D':
        case 'L':
            break;
        default:
            resp = make_copy_on_heap("Invalid rule");
    }
    return resp; 
}
