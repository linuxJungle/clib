#include "hashtable.h"

int
main (void)
{
    HashTable *hashtable = malloc (sizeof (HashTable));
    hash_table_init(hashtable);

    char *key = "1234567890abcdefghijklmnopqrstuvwxyz";
    char *tmp;
    int i = 0;
    for (tmp = key; strlen(key); key++) {
        hash_table_insert_long (hashtable, key, i++);
    }
    printf ("hashtable size = %ld\thashtable max size = %ld\n", hashTable_size (hashtable), hashtable->hash_table_max_size);
    hash_table_insert_long (hashtable, "ijklmnopqrstuvwxyz", 222);
    hash_table_insert_str (hashtable, "klmnopqrstuvwxyz", "222");
    hash_table_insert_long (hashtable, "opqrstuvwxyz", 222);
    printf ("hashtable size = %ld\thashtable max size = %ld\n", hashTable_size (hashtable), hashtable->hash_table_max_size);

    //hash_table_insert_long(hashtable, "world", 11111);
    //hash_table_insert_double(hashtable, "world", 1.111);
    //hash_table_insert_long(hashtable, "klmnopqrstuvwxyz", 1111111111111111111);

    hash_table_print (hashtable);

    //HashNode * node = hash_table_lookup (hashtable, "world");
    //if (node)
    //    hash_node_print (node);
    //else
    //    printf ("key not exists\n");

    printf ("hashtable size = %ld\thashtable max size = %ld\n", hashTable_size (hashtable), hashtable->hash_table_max_size);
    //hash_table_remove (hashtable, "z");

    //printf("----------------\n");

    //printf ("hashtable size = %ld\n", hashTable_size (hashtable));

    hash_table_release (hashtable);


    free (hashtable);
    return 0;
}

