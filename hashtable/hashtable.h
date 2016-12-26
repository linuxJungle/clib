#ifndef HASHTABLE_H
#define HASHTABLE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HASH_TABLE_MAX_SIZE (1 << 10)

#define hash_pos(skey) \
    hash_func((skey)) % HASH_TABLE_MAX_SIZE

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
    ((zValue *)(hashnode)->pValue)->value

#define zStrValue(hashnode) \
    (zvalue(hashnode)).str.value

#define zStrLen(hashnode) \
    (zvalue(hashnode)).str.len

#define zlval(hashnode) \
    (zvalue(hashnode)).lval

#define zdval(hashnode) \
    (zvalue(hashnode)).dval

#define mallocStr(str) \
    (char*) malloc (strlen (str) + 1)

#define set_zlval(hashnode, lval) \
    { zlval ((hashnode)) = lval;  \
    (hashnode)->type   = LONG; }

#define set_key(hashnode, str)            \
    { (hashnode)->sKey = mallocStr (str); \
      strcpy ((hashnode)->sKey, str); }

#define set_zStrval(hashnode, str)            \
    { zStrValue (hashnode) = mallocStr (str); \
    strcpy (zStrValue (hashnode), str);       \
    zStrLen (hashnode) = strlen (str);        \
    (hashnode)->type = STRING; }

#define Bool(bval) (bval)? 1: 0;

#define set_zbval(hashnode, bval)    \
    { zlval (hashnode) = Bool(bval); \
      (hashnode)->type = BOOL; }

#define set_zdval(hashnode, dval) \
    { zdval (hashnode) = (dval);  \
      (hashnode)->type = DOUBLE; }

#define r_set_zStrval(hashnode, str) \
    set_zStrval((hashnode), (str)) return;

#define r_set_zlval(hashnode, lval) \
    set_zlval((hashnode), (lval)) return;

#define r_set_zbval(hashnode, bval) \
    set_zbval((hashnode), (bval)) return;

#define r_set_zdval(hashnode, dval) \
    set_zdval((hashnode), (dval)) return;


typedef enum {
    LONG,
    BOOL,
    STRING,
    DOUBLE,
} Type;

typedef struct zvalue {
    union {
        long   lval;
        double dval;
        struct {
            char *value;
            unsigned long len;
        } str;
    } value;
} zValue;

typedef struct hashnode HashNode;
struct hashnode {
    char      *sKey;
    void      *pValue;
    Type       type;
    HashNode  *pNext;
};

typedef struct hashtable {
    HashNode **hashnode;
    size_t     hash_table_max_size;
    size_t     hash_size;
} HashTable;

void hash_table_init (HashTable *hashtable);

/* unsigned int hash_table_hash_str (const char* skey); */

unsigned long hash_func (const char* skey);

void hash_table_insert_long (HashTable *hashtable, 
        const char* skey, long nvalue);

void hash_table_insert_str (HashTable *hashtable, 
        const char* skey, char* pValue);

void hash_table_insert_bool (HashTable *hashtable, 
        const char* skey, bool value);

void hash_table_insert_double (HashTable *hashtable, 
        const char* skey, double dval);

void hash_table_remove (HashTable *hashtable, const char* skey);

HashNode* hash_table_lookup (HashTable *hashtable, const char* skey);

void hash_node_print (HashNode *hashnode);

void hash_table_print (HashTable *hashtable);

void hash_table_release (HashTable *hashtable);

#endif /* !HASHTABLE_H */
