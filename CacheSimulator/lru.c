#include "lru.h"
#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

void lru_init_queue(Set *set) {
  LRUNode *s = NULL;
  LRUNode **pp = &s;  // place to chain in the next node
  for (int i = 0; i < set->line_count; i++) {
    Line *line = &set->lines[i];
    LRUNode *node = (LRUNode *)(malloc(sizeof(LRUNode)));
    node->line = line;
    node->next = NULL;
    (*pp) = node;
    pp = &((*pp)->next);
  }
  set->lru_queue = s;
}

void lru_init(Cache *cache) {
  Set *sets = cache->sets;
  for (int i = 0; i < cache->set_count; i++) {
    lru_init_queue(&sets[i]);
  }
}

void lru_destroy(Cache *cache) {
  Set *sets = cache->sets;
  for (int i = 0; i < cache->set_count; i++) {
    LRUNode *p = sets[i].lru_queue;
    LRUNode *n = p;
    while (p != NULL) {
      p = p->next;
      free(n);
      n = p;
    }
    sets[i].lru_queue = NULL;
  }
}

void lru_fetch(Set *set, unsigned int tag, LRUResult *result) {
  // TODO:
  // Implement the LRU algorithm to determine which line in
  // the cache should be accessed.
  //
  LRUNode* prev = NULL;
  LRUNode* curr = set->lru_queue;
  while (curr) {
    if (curr->line->tag == tag && curr->line->valid == 1) {
      if (prev) {
        prev->next = curr->next;
        curr->next = set->lru_queue;
        set->lru_queue = curr;
      }
      result->line = curr->line;
      result->access = HIT;
      return;
    }
    else if (curr->next == NULL) {
      prev = NULL;
      curr = set->lru_queue;
      while (curr) {
        if (curr->line->valid == 0) {
          curr->line->valid = 1;
          curr->line->tag = tag;
          if (prev) {
            prev->next = curr->next;
            curr->next = set->lru_queue;
            set->lru_queue = curr;
          }
          result->line = curr->line;
          result->access = COLD_MISS;
          return;
        }
        else if (curr->next == NULL) {
          curr->line->valid = 1;
          curr->line->tag = tag;
          if (prev) {
            prev->next = curr->next;
            curr->next = set->lru_queue;
            set->lru_queue = curr;
          }
          result->line = curr->line;
          result->access = CONFLICT_MISS;
          return;       
        }
        else {
          prev = curr;
          curr = curr->next;
        }
      }
    }
    else {
      prev = curr;
      curr = curr->next; 
    }
  }  
}
