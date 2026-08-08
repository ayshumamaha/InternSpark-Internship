#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 101

typedef struct CacheNode {
    int key;
    int value;
    struct CacheNode *prev;
    struct CacheNode *next;
    struct CacheNode *hash_next;
} CacheNode;

typedef struct {
    int capacity;
    int size;
    CacheNode *head;
    CacheNode *tail;
    CacheNode *table[TABLE_SIZE];

    int requests;
    int hits;
    int misses;
} LRUCache;

/* Hash function */
int hash_function(int key) {
    if (key < 0)
        key = -key;

    return key % TABLE_SIZE;
}

/* Initialize cache */
void initialize_cache(LRUCache *cache, int capacity) {
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = NULL;
    cache->tail = NULL;
    cache->requests = 0;
    cache->hits = 0;
    cache->misses = 0;

    for (int i = 0; i < TABLE_SIZE; i++)
        cache->table[i] = NULL;
}

/* Find node in hash table */
CacheNode *find_node(LRUCache *cache, int key) {
    int index = hash_function(key);

    CacheNode *current = cache->table[index];

    while (current != NULL) {
        if (current->key == key)
            return current;

        current = current->hash_next;
    }

    return NULL;
}

/* Remove node from hash table */
void remove_from_hash(LRUCache *cache, CacheNode *node) {
    int index = hash_function(node->key);

    CacheNode *current = cache->table[index];
    CacheNode *previous = NULL;

    while (current != NULL) {
        if (current == node) {
            if (previous == NULL)
                cache->table[index] = current->hash_next;
            else
                previous->hash_next = current->hash_next;

            return;
        }

        previous = current;
        current = current->hash_next;
    }
}

/* Insert node into hash table */
void insert_into_hash(LRUCache *cache, CacheNode *node) {
    int index = hash_function(node->key);

    node->hash_next = cache->table[index];
    cache->table[index] = node;
}

/* Remove node from doubly linked list */
void remove_from_list(LRUCache *cache, CacheNode *node) {
    if (node->prev != NULL)
        node->prev->next = node->next;
    else
        cache->head = node->next;

    if (node->next != NULL)
        node->next->prev = node->prev;
    else
        cache->tail = node->prev;

    node->prev = NULL;
    node->next = NULL;
}

/* Add node to front */
void add_to_front(LRUCache *cache, CacheNode *node) {
    node->prev = NULL;
    node->next = cache->head;

    if (cache->head != NULL)
        cache->head->prev = node;
    else
        cache->tail = node;

    cache->head = node;
}

/* Move node to front */
void move_to_front(LRUCache *cache, CacheNode *node) {
    if (cache->head == node)
        return;

    remove_from_list(cache, node);
    add_to_front(cache, node);
}

/* Evict least recently used node */
void evict_lru(LRUCache *cache) {
    if (cache->tail == NULL)
        return;

    CacheNode *victim = cache->tail;

    remove_from_list(cache, victim);
    remove_from_hash(cache, victim);

    free(victim);

    cache->size--;
}

/* Put key-value pair */
void cache_put(LRUCache *cache, int key, int value) {
    CacheNode *existing = find_node(cache, key);

    if (existing != NULL) {
        existing->value = value;
        move_to_front(cache, existing);

        printf("Key %d updated successfully.\n", key);
        return;
    }

    if (cache->size >= cache->capacity)
        evict_lru(cache);

    CacheNode *new_node =
        (CacheNode *)malloc(sizeof(CacheNode));

    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    new_node->key = key;
    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->hash_next = NULL;

    add_to_front(cache, new_node);
    insert_into_hash(cache, new_node);

    cache->size++;

    printf("Key %d inserted successfully.\n", key);
}

/* Get value */
int cache_get(LRUCache *cache, int key, int *value) {
    cache->requests++;

    CacheNode *node = find_node(cache, key);

    if (node == NULL) {
        cache->misses++;
        return 0;
    }

    cache->hits++;

    *value = node->value;

    move_to_front(cache, node);

    return 1;
}

/* Delete key */
void cache_delete(LRUCache *cache, int key) {
    CacheNode *node = find_node(cache, key);

    if (node == NULL) {
        printf("Key not found.\n");
        return;
    }

    remove_from_list(cache, node);
    remove_from_hash(cache, node);

    free(node);

    cache->size--;

    printf("Key %d deleted successfully.\n", key);
}

/* Display cache */
void display_cache(LRUCache *cache) {
    if (cache->head == NULL) {
        printf("\nCache is empty.\n");
        return;
    }

    printf("\nMRU -> ");

    CacheNode *current = cache->head;

    while (current != NULL) {
        printf("[%d : %d]", current->key, current->value);

        if (current->next != NULL)
            printf(" -> ");

        current = current->next;
    }

    printf(" <- LRU\n");
}

/* Display statistics */
void display_statistics(LRUCache *cache) {
    double hit_ratio = 0.0;

    if (cache->requests > 0)
        hit_ratio =
            ((double)cache->hits / cache->requests) * 100.0;

    printf("\n===== CACHE STATISTICS =====\n");
    printf("Capacity      : %d\n", cache->capacity);
    printf("Current Size  : %d\n", cache->size);
    printf("Requests      : %d\n", cache->requests);
    printf("Cache Hits    : %d\n", cache->hits);
    printf("Cache Misses  : %d\n", cache->misses);
    printf("Hit Ratio     : %.2f%%\n", hit_ratio);
}

/* Clear cache */
void clear_cache(LRUCache *cache) {
    CacheNode *current = cache->head;

    while (current != NULL) {
        CacheNode *next = current->next;
        free(current);
        current = next;
    }

    cache->head = NULL;
    cache->tail = NULL;
    cache->size = 0;

    for (int i = 0; i < TABLE_SIZE; i++)
        cache->table[i] = NULL;

    printf("Cache cleared successfully.\n");
}

/* Main */
int main() {
    LRUCache cache;
    int capacity;

    printf("===== LRU CACHE SYSTEM =====\n");

    printf("Enter cache capacity: ");
    scanf("%d", &capacity);

    if (capacity <= 0) {
        printf("Invalid capacity.\n");
        return 1;
    }

    initialize_cache(&cache, capacity);

    int choice;
    int key;
    int value;

    while (1) {
        printf("\n===== MENU =====\n");
        printf("1. Put / Insert\n");
        printf("2. Get / Search\n");
        printf("3. Delete\n");
        printf("4. Display Cache\n");
        printf("5. Statistics\n");
        printf("6. Clear Cache\n");
        printf("7. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter key: ");
                scanf("%d", &key);

                printf("Enter value: ");
                scanf("%d", &value);

                cache_put(&cache, key, value);
                break;

            case 2:
                printf("Enter key: ");
                scanf("%d", &key);

                if (cache_get(&cache, key, &value))
                    printf("CACHE HIT -> Value: %d\n", value);
                else
                    printf("CACHE MISS -> Key not found.\n");

                break;

            case 3:
                printf("Enter key: ");
                scanf("%d", &key);

                cache_delete(&cache, key);
                break;

            case 4:
                display_cache(&cache);
                break;

            case 5:
                display_statistics(&cache);
                break;

            case 6:
                clear_cache(&cache);
                break;

            case 7:
                clear_cache(&cache);
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}