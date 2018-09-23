#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

typedef struct Test {
    const unsigned char key[200];
    const unsigned char value[200];
} Test;

static const struct Test testing [] = {
        {"FYFYFYEzFYFYFYEzFYEzFYFYFYFYFY", "FYFYFYEzFYFYFYEzFYEzFYFYFYFYFY value"},
        {"some1", "some1 value"},
        {"EzFYEzEzEzFYFYFYFYEzEzFYEzEzFY", "EzFYEzEzEzFYFYFYFYEzEzFYEzEzFY collision value"},
        {"some2", "some2 value"},
        {"some3", "some3 value"},
        {"some4", "some4 value"},
        {"some5", "some5 value"},
        {"some6", "some6 value"},
        {"some77", "some77 value"},
        {"some834", "some834 value"},
        {"some901", "some901 value"},
        {"some988", "some988 value"},
        {"some!a", "some!a value"},
        {"somek(", "somek( value"},
        {"someG6s", "someG6s value"},
        {"some0p", "some0p value"},
        {"someLp", "someLp value"},
        {"somecAA", "somecAA value"},
        {"somemL", "somemL value"},
        {"some_a", "some_a value"},
        {"someL", "someL value"},
        {"somed", "somed value"},
        {"someM", "someM value"},
        {"somePOA", "somePOA value"},
        {"some,l", "some,l value"},
        {"someLp", "someLp value"},
        {"someKM", "someKM value"},
        {"some,AAA", "some,AAA value"},
        {"someXX", "someXX value"},
        {"some.A", "some.A value"},
        {NULL, NULL}
};

int main()
{
    int i;
    Dictionary* dict = new_dictionary(1000);
    for (i=0;i<30;i++) dict->new_node(dict, testing[i].key, testing[i].value);
    for (i=0;i<30;i++)
        printf("key: %s, has value: %s\n", testing[i].key, dict->get_value(dict, testing[i].key));
    //dict->remove_node(dict, "some_a");
    dict->clear_dictionary(dict);

    return 0;
}