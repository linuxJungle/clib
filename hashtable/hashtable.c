#include "hashtable.h"

/* initialize hash table */
void
hash_table_init (HashTable *hashtable)
{
    hashtable->hash_table_max_size = HASH_TABLE_MAX_SIZE;
    hashtable->hash_size = 0;
    hashtable->hashnode = (HashNode **)calloc (sizeof(HashNode*), \
            HASH_TABLE_MAX_SIZE);
}


/* string hash function */
unsigned int
hash_table_hash_str (const char* skey)
{
    const char   *p;
    unsigned int  h;

    p = (const char*)skey;
    h = *p;
    if (h) {
        for (p += 1; *p != '\0'; p++)
            h = (h << 5) - h + *p;
    }
    return h;
}

/*insert key-value into hash table*/
void
hash_table_insert_long (HashTable *hashtable, const char* skey, long nvalue)
{
    size_t          pos;
    HashNode       *pHead;
    HashNode       *pNewNode;

    if (hashTable_is_full (hashtable)) {
        printf("out of hash table memory!\n");
        return;
    }
    pos = hash_pos (skey);

    pHead = (hashtable->hashnode)[pos];
    while (pHead) {
        if (strcmp (pHead->sKey, skey) == 0) {
            printf ("%s already exists!\n", skey);
            return ;
        }
        pHead = pHead->pNext;
    }

    pNewNode = (HashNode*) calloc (sizeof (HashNode), 1);

    pNewNode->sKey = mallocStr (skey);
    strcpy (pNewNode->sKey, skey);

    pNewNode->pValue = (zValue *) malloc (sizeof(zValue));
    zIntegerValue (pNewNode) = nvalue;
    pNewNode->type = INTEGER;

    pNewNode->pNext = (hashtable->hashnode)[pos];
    (hashtable->hashnode)[pos] = pNewNode;

    hashtable->hash_size++;
}

void
hash_table_insert_str (HashTable *hashtable, const char* skey, char* pValue)
{
    size_t          pos;
    HashNode       *pHead;
    HashNode       *pNewNode;

    if (hashTable_is_full (hashtable)) {
        printf("out of hash table memory!\n");
        return;
    }
    pos = hash_pos (skey);

    pHead =  (hashtable->hashnode)[pos];
    while (pHead) {
        if (strcmp (pHead->sKey, skey) == 0) {
            printf ("%s already exists!\n", skey);
            return ;
        }
        pHead = pHead->pNext;
    }

    pNewNode = (HashNode*) calloc (sizeof (HashNode), 1);

    pNewNode->sKey = mallocStr (skey);
    strcpy (pNewNode->sKey, skey);

    pNewNode->pValue = (zValue *) malloc (sizeof(zValue));
    zStrValue (pNewNode) = mallocStr (pValue);
    strcpy (zStrValue (pNewNode), pValue);
    zStrLen (pNewNode) = strlen (pValue);
    pNewNode->type = STRING;

    pNewNode->pNext = (hashtable->hashnode)[pos];
    (hashtable->hashnode)[pos] = pNewNode;

    hashtable->hash_size++;
}

void
hash_table_insert_bool (HashTable *hashtable, const char* skey, bool value)
{
    size_t          pos;
    HashNode       *pHead;
    HashNode       *pNewNode;

    if (hashTable_is_full (hashtable)) {
        printf("out of hash table memory!\n");
        return;
    }
    pos = hash_pos (skey);

    pHead =  (hashtable->hashnode)[pos];
    while (pHead) {
        if (strcmp (pHead->sKey, skey) == 0) {
            printf ("%s already exists!\n", skey);
            return ;
        }
        pHead = pHead->pNext;
    }

    pNewNode = (HashNode*) calloc (sizeof (HashNode), 1);

    pNewNode->sKey = mallocStr (skey);
    strcpy (pNewNode->sKey, skey);

    pNewNode->pValue = (zValue *) malloc (sizeof(zValue));
    zIntegerValue (pNewNode) = value? 1: 0;
    pNewNode->type = BOOL;

    pNewNode->pNext = (hashtable->hashnode)[pos];
    (hashtable->hashnode)[pos] = pNewNode;

    hashtable->hash_size++;
}

/*remove key-value frome the hash table*/
void
hash_table_remove (HashTable *hashtable, const char* skey)
{
    unsigned int    pos;

    pos = hash_pos (skey);
    if (hashtable->hashnode[pos]) {
        HashNode* pHead = (hashtable->hashnode)[pos];
        HashNode* pLast = NULL;
        HashNode* pRemove = NULL;

        while (pHead) {
            if (strcmp (skey, pHead->sKey) == 0) {
                pRemove = pHead;
                break;
            }
            pLast = pHead;
            pHead = pHead->pNext;
        }
        if (pRemove) {
            if (pLast)
                pLast->pNext = pRemove->pNext;
            else 
                (hashtable->hashnode)[pos] = NULL;

            switch (pRemove->type) {

            case INTEGER:
            case BOOL:
                break;
            case STRING:
                free (zStrValue (pRemove));
                break;
            default:
                break;
            }
            hashtable->hash_size--;

            free (pRemove->pValue);
            free (pRemove->sKey);
            free (pRemove);
        }
    }
}

/* lookup a key in the hash table */
HashNode*
hash_table_lookup (HashTable *hashtable, const char* skey)
{
    unsigned int    pos;

    pos = hash_pos (skey);

    if ((hashtable->hashnode)[pos]) {
        HashNode* pHead = (hashtable->hashnode)[pos];
        while (pHead) {
            if (strcmp (skey, pHead->sKey) == 0)
                return pHead;
            pHead = pHead->pNext;
        }
    }
    return NULL;
}

void
hash_node_print (HashNode *hashnode) {
    switch (hashnode->type) {

    case INTEGER:
        printf ("%s => INTEGER(%ld)", hashnode->sKey, zIntegerValue (hashnode));
        break;
    case STRING:
        printf ("%s => STRING(%ld) %s", hashnode->sKey, zStrLen(hashnode), zStrValue (hashnode));
        break;
    case BOOL:
        printf ("%s => BOOL(%s)", hashnode->sKey, zIntegerValue (hashnode)? "true": "false");
    default:
        break;
    }
}
         

/*print the content in the hash table*/
void 
hash_table_print (HashTable *hashtable)
{
    size_t     i;
    HashNode  *pHead; 

    for (i = 0; i < hashTable_max_size (hashtable); i++)
        if ((hashtable->hashnode)[i]) {
            pHead = (hashtable->hashnode)[i];
            //printf ("%ld => ", i);
            hashNode_for_each (pHead) {
                hash_node_print (pHead);
            }
            printf("\n");
        }
}

/*free the memory of the hash table*/
void
hash_table_release (HashTable *hashtable)
{
    size_t      i;
    HashNode   *pHead, *pTemp;

    for (i = 0; i < hashtable->hash_table_max_size; i++) {
        if ((pHead = (hashtable->hashnode)[i])) {
            while (pHead) {
                pTemp = pHead;
                pHead = pHead->pNext;
                if (pTemp) {
                    switch (pTemp->type) {
                    
                    case INTEGER:
                    case BOOL:
                        break;
                    case STRING:
                        free (zStrValue (pTemp));
                        break;
                    default:
                        break;
                    }    
                    free (pTemp->sKey);
                    free (pTemp);
                }
            }
        }
    }
    free (hashtable->hashnode);
}
