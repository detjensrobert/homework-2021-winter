#include "set.h"

#include <stdlib.h>

Set *set_init() {
  Set *s = calloc(1, sizeof(Set));
  return s;
}

Set *set_add(Set *s, SET_TYPE val) {
  // noop if set already has value
  if (set_contains(s, val)) {
    return s;
  }

  LNode *new = calloc(1, sizeof(LNode));
  new->val = val;
  new->next = NULL;

  if (!s->head) {  // if set is empty
    s->head = new;
    s->tail = new;
  } else {
    s->tail->next = new;
    s->tail = new;
  }

  s->size++;
  return s;
}

Set *set_remove(Set *s, SET_TYPE val) {
  // if set is empty, noop
  if (!s->size) {
    return s;
  }

  if (s->head->val == val) {
    // head needs special case
    LNode *old = s->head;
    s->head = old->next;
    free(old);

  } else {
    // walk list and remove any values that match
    LNode *walker = s->head->next;
    LNode *prev = s->head;

    while (walker) {
      if (walker->val == val) {
        prev->next = walker->next;
        free(walker);
      }
      prev = walker;
      walker = walker->next;
    }
  }

  s->size--;
  return s;
}

int set_contains(Set *s, SET_TYPE val) {
  LNode *walker = s->head;

  while (walker) {
    if (walker->val == val) {
      return 1;
    }
    walker = walker->next;
  }

  return 0;
}

void set_free(Set *s) {
  while (s->head) {
    LNode *old = s->head;
    s->head = old->next;
    free(old);
  }
  free(s);
}
