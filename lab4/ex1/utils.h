#include<string.h>
#include<stdlib.h>

typedef struct _rule 
{
    unsigned int ip_start;
    unsigned int ip_end;
    unsigned short int port_start;
    unsigned short int port_end;
    Rule* Next;
} Rule;

Rule* RulesHead = NULL;

char* get_copy_on_heap(char* buf)
{
    int len = strlen(buf);
    char* resp = malloc(len + 1);
    strncpy(resp, buf, len + 1);
    return resp;
}

Rule* ExtractRule(char* pchrule)
{
    return NULL;
}

void add_rule(Rule* newRule)
{
    if (RulesHead == NULL)
        RulesHead = newRule;
    else
    {
        newRule->Next = RulesHead;
        RulesHead = newRule;
    }
}

char* process_add(char* request)
{
    char* pch_rule = request+2;
    Rule* newRule = ExtractRule(pch_rule);
    if (newRule == NULL)
        return get_copy_on_heap("Invalid rule");

    add_rule(newRule);
    return get_copy_on_heap("Rule added");    
}

char* process_check(char* request)
{

}

