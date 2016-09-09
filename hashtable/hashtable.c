#include "hashtable.h"

static void __free_str_value (HashNode *node);

/*if key is exists and type is STRING, free string's value memory*/
void __free_str_value (HashNode *node)
{
    if (node->type == STRING) free (zStrValue (node));
}


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
    /*  
     * This is the popular `times 33' hash algorithm which is used by  
     * perl and also appears in Berkeley DB. This is one of the best  
     * known hash functions for strings because it is both computed  
     * very fast and distributes very well.  
     *  
     * The originator may be Dan Bernstein but the code in Berkeley DB  
     * cites Chris Torek as the source. The best citation I have found  
     * is "Chris Torek, Hash function for text in C, Usenet message  
     * <27038@mimsy.umd.edu> in comp.lang.c , October, 1990." in Rich  
     * Salz's USENIX 1992 paper about INN which can be found at  
     * <http://citeseer.nj.nec.com/salz92internetnews.html>.  
     *  
     * The magic of number 33, i.e. why it works better than many other  
     * constants, prime or not, has never been adequately explained by  
     * anyone. So I try an explanation: if one experimentally tests all  
     * multipliers between 1 and 256 (as I did while writing a low-level  
     * data structure library some time ago) one detects that even  
     * numbers are not useable at all. The remaining 128 odd numbers  
     * (except for the number 1) work more or less all equally well.  
     * They all distribute in an acceptable way and this way fill a hash  
     * table with an average percent of approx. 86%.  
     *  
     * If one compares the chi^2 values of the variants (see  
     * Bob Jenkins ``Hashing Frequently Asked Questions'' at  
     * http://burtleburtle.net/bob/hash/hashfaq.html for a description  
     * of chi^2), the number 33 not even has the best value. But the  
     * number 33 and a few other equally good numbers like 17, 31, 63,  
     * 127 and 129 have nevertheless a great advantage to the remaining  
     * numbers in the large set of possible multipliers: their multiply  
     * operation can be replaced by a faster operation based on just one  
     * shift plus either a single addition or subtraction operation. And  
     * because a hash function has to both distribute good _and_ has to  
     * be very fast to compute, those few numbers should be preferred.  
     *  
     *                  -- Ralf S. Engelschall <rse@engelschall.com>  
     */   
    const char   *p;
    unsigned int  hash;

    p = (const char*)skey;
    hash = *p;
    if (hash) {
        for (p += 1; *p != '\0'; p++)
            hash = (hash << 5) - hash + *p;
    }
    return hash;
}

/*insert key-value into hash table, if key is exist, 
 *it will overwrite old value, use link list to slove 
 *hash conflict,*/
void
hash_table_insert_long (HashTable *hashtable, const char* skey, long nvalue)
{
    size_t          pos;
    HashNode       *pHead;
    HashNode       *pNewNode;

    if (hashTable_is_full (hashtable)) {
        fprintf(stderr, "out of hash table memory!\n");
        return;
    }
    pos = hash_pos (skey);

    pHead = (hashtable->hashnode)[pos];
    while (pHead) {
        if (strcmp (pHead->sKey, skey) == 0) {
            __free_str_value (pHead);
            r_set_zlval (pHead, nvalue);
        }
        pHead = pHead->pNext;
    }

    pNewNode = (HashNode*) calloc (sizeof (HashNode), 1);

    pNewNode->sKey = mallocStr (skey);
    strcpy (pNewNode->sKey, skey);

    pNewNode->pValue = (void *) malloc (sizeof(zValue));
    set_zlval (pNewNode, nvalue);

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
        fprintf(stderr, "out of hash table memory!\n");
        return;
    }
    pos = hash_pos (skey);

    pHead =  (hashtable->hashnode)[pos];
    while (pHead) {
        if (strcmp (pHead->sKey, skey) == 0) {
            __free_str_value (pHead);
            r_set_zStrval (pHead, pValue);
        }
        pHead = pHead->pNext;
    }

    pNewNode = (HashNode*) calloc (sizeof (HashNode), 1);

    pNewNode->sKey = mallocStr (skey);
    strcpy (pNewNode->sKey, skey);

    pNewNode->pValue = (zValue *) malloc (sizeof(zValue));
    set_zStrval (pNewNode, pValue);

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
        fprintf(stderr, "out of hash table memory!\n");
        return;
    }
    pos = hash_pos (skey);

    pHead =  (hashtable->hashnode)[pos];
    while (pHead) {
        if (strcmp (pHead->sKey, skey) == 0) {
            __free_str_value (pHead);
            r_set_zbval (pHead, value);
        }
        pHead = pHead->pNext;
    }

    pNewNode = (HashNode*) calloc (sizeof (HashNode), 1);

    pNewNode->sKey = mallocStr (skey);
    strcpy (pNewNode->sKey, skey);

    pNewNode->pValue = (zValue *) malloc (sizeof(zValue));
    set_zbval (pNewNode, value);

    pNewNode->pNext = (hashtable->hashnode)[pos];
    (hashtable->hashnode)[pos] = pNewNode;

    hashtable->hash_size++;
}

void
hash_table_insert_double (HashTable *hashtable, const char* skey, double dval)
{
    size_t          pos;
    HashNode       *pHead;
    HashNode       *pNewNode;

    if (hashTable_is_full (hashtable)) {
        fprintf(stderr, "out of hash table memory!\n");
        return;
    }
    pos = hash_pos (skey);

    pHead =  (hashtable->hashnode)[pos];
    while (pHead) {
        if (strcmp (pHead->sKey, skey) == 0) {
            __free_str_value (pHead);
            r_set_zdval (pHead, dval);
        }
        pHead = pHead->pNext;
    }

    pNewNode = (HashNode*) calloc (sizeof (HashNode), 1);

    pNewNode->sKey = mallocStr (skey);
    strcpy (pNewNode->sKey, skey);

    pNewNode->pValue = (zValue *) malloc (sizeof(zValue));
    set_zdval (pNewNode, dval);

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

            case LONG:
            case BOOL:
            case DOUBLE:
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

    case LONG:
        printf ("%s => LONG(%ld)\n", hashnode->sKey, zlval (hashnode));
        break;
    case STRING:
        printf ("%s => STRING(%ld) %s\n", hashnode->sKey, zStrLen(hashnode), zStrValue (hashnode));
        break;
    case BOOL:
        printf ("%s => BOOL(%s)\n", hashnode->sKey, zlval (hashnode)? "true": "false");
        break;
    case DOUBLE:
        printf ("%s => DOUBLE(%lf)\n", hashnode->sKey, zdval (hashnode));
        break;
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
                    
                    case LONG:
                    case BOOL:
                    case DOUBLE:
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
