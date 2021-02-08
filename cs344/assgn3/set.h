#ifndef SET
#define SET

#define SET_TYPE int

/**
  Single linked list (null terminated)
*/
struct LNode {
  SET_TYPE val;
  struct LNode *next;
};

struct Set {
  struct LNode *head;
  struct LNode *tail;
  int size;
};

typedef struct LNode LNode;
typedef struct Set Set;

Set *set_init();

Set *set_add(Set *s, SET_TYPE val);
Set *set_remove(Set *s, SET_TYPE val);
int set_contains(Set *s, SET_TYPE val);

void set_free(Set *s);

#endif
