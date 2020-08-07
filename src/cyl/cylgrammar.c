#include "cylgrammar.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void insertRule(struct CylGrammar *digest, const char *rule) {
    struct RuleList *new = malloc(sizeof(struct RuleList));
    new->str = strdup(rule);
    new->next = NULL;

    if(digest->rule_tail == NULL)
        digest->rule_head = new;
    else
        digest->rule_tail->next = new;

    digest->rule_tail = new;

    printf("new rule: %s\n", rule);
}

void insertVariable(struct CylGrammar *digest, const char *var, const char *patt) {
    struct VariableList *new = malloc(sizeof(struct VariableList));
    new->id = strdup(var);
    new->pattern = strdup(patt);
    new->next = NULL;

    if(digest->variable_tail == NULL)
        digest->variable_head = new;
    else
        digest->variable_tail->next = new;

    digest->variable_tail = new;

    printf("new variable: %s = %s\n", var, patt);
}

void setFileType(struct CylGrammar *digest, const char *file_type) {
    digest->file_type = strdup(file_type);
    printf("filetype set: %s\n", file_type);
}