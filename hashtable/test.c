#include "hashtable.h"

int
main (void)
{
    HashTable *hashtable = malloc (sizeof (HashTable));
    hash_table_init(hashtable);

    char *key = "abcdefghijklmnopqrstuvwxyz";
    char *tmp;
    for (tmp = key; strlen(key); key++) {
        hash_table_insert_long (hashtable, key, 112);
    }

    //hash_table_insert_long(hashtable, "world", 11111);
    //hash_table_insert_bool(hashtable, "world", true);
    //hash_table_insert_double(hashtable, "world", 1.111);
    //hash_table_insert_long(hashtable, "world", 1111111111111111111);
    //hash_table_insert_str(hashtable, "world", "hello");

    hash_table_print (hashtable);

    //HashNode * node = hash_table_lookup (hashtable, "world");
    //if (node)
    //    hash_node_print (node);
    //else
    //    printf ("key not exists\n");

    //printf ("hashtable size = %ld\n", hashTable_size (hashtable));
    //hash_table_remove (hashtable, "z");

    //printf("----------------\n");

    //printf ("hashtable size = %ld\n", hashTable_size (hashtable));

    hash_table_release (hashtable);


    free (hashtable);
    return 0;
}

