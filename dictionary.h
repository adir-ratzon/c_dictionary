#ifndef DICTIONARY_H

typedef struct Node {
    unsigned char*      key;
    unsigned char*      val;
    char                in_use;
    struct Node*        next;
}
Node;

// dictionary methods definitions
typedef int (*new_node__m)(struct Dictionary* self, const unsigned char* key, const unsigned char* value);
typedef int (*remove_node__m)(struct Dictionary* self, const unsigned char* key);
typedef const unsigned char* (*get_value__m)(struct Dictionary* self, const unsigned char* key);
typedef int (*dtor__m)(struct Dictionary* self);

typedef struct Dictionary {
    struct Node**       nodes;
    unsigned long       dictionary_length;
    new_node__m         new_node;
    remove_node__m      remove_node;
    get_value__m        get_value;
    dtor__m             clear_dictionary;
}
Dictionary;

void init_dictionary_nodes(Dictionary* self);
const unsigned long create_hash(const unsigned char *str, const unsigned long size);

// methods below
Dictionary* new_dictionary(unsigned long size);
int new_node(Dictionary* self, const unsigned char* key, const unsigned char* value);
const unsigned char* get_value(Dictionary* self, const unsigned char* key);
int remove_node(Dictionary* self, const unsigned char* key);
int clear_dictionary(struct Dictionary* self);

#endif