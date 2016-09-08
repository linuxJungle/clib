#ifndef HASHTABLE_H
#define HASHTABLE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HASH_TABLE_MAX_SIZE 10000

#define hash_pos(skey) \
    hash_table_hash_str((skey)) % HASH_TABLE_MAX_SIZE

#define hashTable_is_full(hashtable) \
    (((hashtable)->hash_size) > ((hashtable)->hash_table_max_size))

#define hashTable_is_empty(hashtable) \
    (((hashtable)->hash_size) == 0)

#define hashNode_for_each(hashnode) \
    for (; (hashnode); (hashnode) = (hashnode)->pNext)

#define hashTable_size(hashtable) \
    ((hashtable)->hash_size)

#define hashTable_max_size(hashtable) \
    (hashtable)->hash_table_max_size

#define zvalue(hashnode) \
    (hashnode)->pValue->value

#define zStrValue(hashnode) \
    (zvalue(hashnode)).string.value

#define zStrLen(hashnode) \
    (zvalue(hashnode)).string.len

#define zIntegerValue(hashnode) \
    (zvalue(hashnode)).integer

#define mallocStr(str) \
    (char*) calloc (sizeof(char), strlen (str) + 1)


typedef enum {
    INTEGER,
    BOOL,
    STRING
} Type;

typedef struct zvalue {
    union {
        unsigned long  integer;
        struct {
            char *value;
            unsigned long len;
        } string;
    } value;
} zValue;

typedef struct hashnode HashNode;
struct hashnode {
    char      *sKey;
    zValue    *pValue;
    Type       type;
    HashNode  *pNext;
};

typedef struct hashtable {
    HashNode **hashnode;
    size_t     hash_table_max_size;
    size_t     hash_size;
} HashTable;

void hash_table_init (HashTable *hashtable);

unsigned int hash_table_hash_str (const char* skey);

void hash_table_insert_long (HashTable *hashtable, const char* skey, long nvalue);

void hash_table_insert_str (HashTable *hashtable, const char* skey, char* pValue);

void hash_table_insert_bool (HashTable *hashtable, const char* skey, bool value);

void hash_table_remove (HashTable *hashtable, const char* skey);

HashNode* hash_table_lookup (HashTable *hashtable, const char* skey);

void hash_node_print (HashNode *hashnode);

void hash_table_print (HashTable *hashtable);

void hash_table_release (HashTable *hashtable);

#endif /* !HASHTABLE_H */
