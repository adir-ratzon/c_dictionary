#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

void init_dictionary_methods(Dictionary* dict)
{
    dict->new_node          =   new_node;
    dict->remove_node       =   remove_node;
    dict->get_value         =   get_value;
    dict->clear_dictionary  =   clear_dictionary;
}

void init_dictionary_nodes(Dictionary* self)
{
    unsigned long i;
    for (i=0; i<self->dictionary_length; i++)
    {
        self->nodes[i]          =   (Node*) malloc(sizeof(struct Node));
        self->nodes[i]->next    =   NULL;
        self->nodes[i]->in_use  =   0;
    }
}

const unsigned long create_hash(const unsigned char *str, const unsigned long size)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % size;
}

// methods below
Dictionary* new_dictionary(unsigned long size)
{
    Dictionary* dict = (Dictionary*) malloc(sizeof(struct Dictionary));
    dict->nodes = (Node**) malloc(sizeof(struct Node*) * size);
    dict->dictionary_length = size;
    init_dictionary_methods(dict);
    init_dictionary_nodes(dict);
    return dict;
}

int new_node(Dictionary* self, const unsigned char* key, const unsigned char* value)
{
    const unsigned long hashed_key = create_hash(key, self->dictionary_length);
    const unsigned long key_length = strlen((const char*)key),
                        value_length = strlen((const char*)value);
    Node* current_node = self->nodes[hashed_key];
    Node* parent_node = NULL;

    while (current_node != NULL && current_node->in_use)
    {
        if (strcmp((const char*)current_node->key, (const char*)key) == 0) return -1;
        parent_node = current_node;
        current_node = current_node->next;
    }

    if (current_node == NULL)
        current_node = malloc(sizeof(struct Node));

    if (parent_node != NULL)
        parent_node->next = current_node;

    current_node->next = NULL;
    current_node->key = (unsigned char*) malloc(key_length);
    current_node->val = (unsigned char*) malloc(value_length);

    memcpy((void*)current_node->key, (void*)key, key_length);
    memcpy((void*)current_node->val, (void*)value, value_length);

    current_node->key[key_length] = '\0';
    current_node->val[value_length] = '\0';

    current_node->in_use = 1;
    return 1;
}

const unsigned char* get_value(Dictionary* self, const unsigned char* key)
{
    const unsigned long hashed_key = create_hash(key, self->dictionary_length);
    Node* current_node = self->nodes[hashed_key];
    while (current_node != NULL && current_node->in_use)
    {
        if (strcmp((const char*)current_node->key, (const char*)key) == 0)
            return current_node->val;
        current_node = current_node->next;
    }
    return NULL;
}

int remove_node(Dictionary* self, const unsigned char* key)
{
    const unsigned long hashed_key = create_hash(key, self->dictionary_length);
    Node* current_node = self->nodes[hashed_key];
    Node* parent_node = NULL;
    while (current_node != NULL && current_node->in_use)
    {
        if (strcmp((const char*)current_node->key, (const char*)key) == 0)
        {
            if (parent_node != NULL) parent_node->next = current_node->next;
            else self->nodes[hashed_key] = self->nodes[hashed_key]->next;

            free(current_node->key);
            free(current_node->val);
            current_node->in_use = 0;
            return 1;
        }
        parent_node = current_node;
        current_node = current_node->next;
    }
    return 0;
}

int clear_dictionary(struct Dictionary* self)
{
    unsigned int i, k, redundancy;
    Node* current_node = NULL;
    Node* last_current_node = NULL;
    Node* next_node = NULL;

    for (i=0; i<self->dictionary_length; i++) {
        current_node = last_current_node = self->nodes[i];
        redundancy = 0;
        if (current_node->next != NULL)
        {
            printf("freeing linked list of key: {%s}\n", current_node->key);
            while (current_node != NULL && current_node->in_use)
            {
                for (k=0; k<redundancy; k++) printf("-");
                printf("-> {%s}\n", current_node->key);
                free(current_node->key);
                free(current_node->val);
                current_node = current_node->next;
                redundancy++;
            }

            current_node = last_current_node;
            while (current_node != NULL && current_node->in_use)
            {
                next_node = current_node->next;
                free(current_node);
                current_node = next_node;
            }
        }
    }
    free(self->nodes);
    free(self);
    printf("free finished\n");
    return 1;
}

