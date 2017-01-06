#include "hashtable.h"
#include <time.h>

int
main (void)
{
    HashTable *hashtable = malloc (sizeof (HashTable));
    hash_table_init(hashtable);

    char buf[4096];
    int i = 0;
    srand((unsigned)time(0));
    for(i = 0; i < 10000000; i++) {
        sprintf(buf, "%d", rand());
        //printf("%s\n", buf);
        hash_table_insert(string)(hashtable, buf, buf);
    } 
    //char *key = "1234567890abcdefghijklmnopqrstuvwxyz";
    //char *tmp;
    //for (tmp = key; strlen(key); key++) {
    //    hash_table_insert_long (hashtable, key, i++);
    //}
    ////hash_table_print (hashtable);
    //key = "1234567890abcdefghijklmnopqrstuvwxyz";
    //for (tmp = key; strlen(key); key++) {
    //    hash_table_insert_long (hashtable, key, i++);
    //}
    //printf ("hashtable size = %ld\thashtable max size = %ld\n", hashTable_size (hashtable), hashtable->hash_table_max_size);
    //hash_table_insert_long (hashtable, "ijklmnopqrstuvwxyz", 222);
    //hash_table_insert_str (hashtable, "klmnopqrstuvwxyz", "222");
    //hash_table_insert_long (hashtable, "opqrstuvwxyz", 222);
    //printf ("hashtable size = %ld\thashtable max size = %ld\n", hashTable_size (hashtable), hashtable->hash_table_max_size);

    //hash_table_insert_long(hashtable, "world", 11111);
    //hash_table_insert_double(hashtable, "world", 1.111);
    //hash_table_insert_long(hashtable, "klmnopqrstuvwxyz", 1111111111111111111);

    //hash_table_print (hashtable);

    hash_table_insert(long)(hashtable, "1111", 1111);
    HashNode * node = hash_table_lookup (hashtable, "1111");
    if (node)
        hash_node_print (node);
    else
        printf ("key not exists\n");

    printf ("hashtable size = %ld\thashtable max size = %ld\n", hashTable_size (hashtable), hashtable->hash_table_max_size);
    hash_table_remove (hashtable, "1111");

    //printf("----------------\n");

    //printf ("hashtable size = %ld\n", hashTable_size (hashtable));

    hash_table_release (hashtable);


    free (hashtable);
    return 0;
}

