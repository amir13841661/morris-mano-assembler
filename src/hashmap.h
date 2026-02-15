#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR 0.75

// Node for chaining in case of hash collisions
typedef struct HashNode
{
    char *key;
    int value;
    struct HashNode *next;
} HashNode;

// HashMap structure
typedef struct HashMap
{
    HashNode **table;
    size_t capacity;
    size_t size;
} HashMap;

// Hash function to map keys to hash values
unsigned long hash(const char *key)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *key++))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// Initialize a new HashMap
HashMap *create_hashmap(size_t capacity)
{
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    map->capacity = capacity;
    map->size = 0;
    map->table = (HashNode **)malloc(capacity * sizeof(HashNode *));

    for (size_t i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }

    return map;
}

// Resize the HashMap if the load factor exceeds the threshold
void resize_hashmap(HashMap *map)
{
    size_t new_capacity = map->capacity * 2;
    HashNode **new_table = (HashNode **)malloc(new_capacity * sizeof(HashNode *));

    for (size_t i = 0; i < new_capacity; i++)
    {
        new_table[i] = NULL;
    }

    // Rehash all existing nodes to the new table
    for (size_t i = 0; i < map->capacity; i++)
    {
        HashNode *node = map->table[i];
        while (node)
        {
            unsigned long index = hash(node->key) % new_capacity;
            HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));
            new_node->key = strdup(node->key);
            new_node->value = node->value;
            new_node->next = new_table[index];
            new_table[index] = new_node;

            HashNode *tmp = node;
            node = node->next;
            free(tmp->key);
            free(tmp);
        }
    }

    free(map->table);
    map->table = new_table;
    map->capacity = new_capacity;
}

// Insert a key-value pair into the HashMap
void insert(HashMap *map, const char *key, int value)
{
    if ((float)map->size / map->capacity >= LOAD_FACTOR)
    {
        resize_hashmap(map);
    }

    unsigned long index = hash(key) % map->capacity;

    // Check if key already exists, if so update the value
    HashNode *node = map->table[index];
    while (node)
    {
        if (strcmp(node->key, key) == 0)
        {
            node->value = value;
            return;
        }
        node = node->next;
    }

    // Key doesn't exist, create a new node
    HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = map->table[index];
    map->table[index] = new_node;
    map->size++;
}

// Search for a key in the HashMap and return its value, or -1 if not found
int search(HashMap *map, const char *key)
{
    unsigned long index = hash(key) % map->capacity;

    HashNode *node = map->table[index];
    while (node)
    {
        if (strcmp(node->key, key) == 0)
        {
            return node->value;
        }
        node = node->next;
    }

    return -1; // Return -1 if the key is not found
}

// Delete a key-value pair from the HashMap
// void delete (HashMap *map, const char *key)
// {
//     unsigned long index = hash(key) % map->capacity;

//     HashNode *node = map->table[index];
//     HashNode *prev = NULL;

//     while (node)
//     {
//         if (strcmp(node->key, key) == 0)
//         {
//             if (prev)
//             {
//                 prev->next = node->next;
//             }
//             else
//             {
//                 map->table[index] = node->next;
//             }
//             free(node->key);
//             free(node);
//             map->size--;
//             return;
//         }
//         prev = node;
//         node = node->next;
//     }
// }

// Free the HashMap memory
void free_hashmap(HashMap *map)
{
    for (size_t i = 0; i < map->capacity; i++)
    {
        HashNode *node = map->table[i];
        while (node)
        {
            HashNode *tmp = node;
            node = node->next;
            free(tmp->key);
            free(tmp);
        }
    }
    free(map->table);
    free(map);
}
