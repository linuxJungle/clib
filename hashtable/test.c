#include "hashtable.h"

int
main (void)
{
    HashTable *hashtable = malloc (sizeof (HashTable));
    hash_table_init(hashtable);

    char *key = "abcdefghijklmnopqrstuvwxyz";
    char *tmp;
    for (tmp = key; strlen(key); key++) {
        hash_table_insert_long (hashtable, key, 11);
    }
    hash_table_insert_str(hashtable, "hello", "2333");
    hash_table_insert_bool(hashtable, "world", true);
    HashNode * node = hash_table_lookup (hashtable, "world");
    hash_node_print (node);
    hash_table_remove (hashtable, "z");
    printf("\n----------------\n");
    hash_table_print (hashtable);
    hash_table_release (hashtable);
    printf ("hashtable size = %ld\n", hashTable_size (hashtable));

    free (hashtable);
    return 0;
}

