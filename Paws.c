#include <stdlib.h>
#include <stdbool.h>

union  thing; /* A union representing any core Paws datatype */

struct ll; /* The data storage system (a linked-list) behind `list` */
struct node; /* A single node of the linked-list consisting a `ll` */

struct list; /* The actual struct representing Paws’ core datatype,
              * `infrastructure list`.
              * NOTE: Most methods return `union thing`s instead! You’ll have
              *       to manually retreive the `list` from that union. */

union thing
{
  struct list*  list;
};

/* =====
= `ll` =
===== */

/* ### Data Types & Structures ### */

/* This implements a pseudo-linked-list structure that is the data storage
 * system responsible for `infrastructure list`, and every other core
 * datatype based thereupon.
 * 
 * NOTE: This is not a traditional linked-list. We don’t iterate elements
 *       until reaching a NULL pointer; instead, we store (and maintain) the
 *       length (in nodes) and iterate based on that. This means that
 *       ‘trailing nodes’ (or, if you’re morbid, ‘zombie nodes’) can occur -
 *       nodes appearing *after* the node at the last index (as according to
 *       our stored length). This is acceptable; they’ll simply be dropped
 *       when we append elements by adding a new link to the last node.
 */
typedef unsigned long int ll_size;
struct ll
{
  struct node*  root; /* A pointer to the first `node` in this `ll` */
  ll_size       length; /* The total number of `node`s in this `ll` */
};
struct node
{
  union thing*  e; /* The `thing` stored at this location in the `ll` */
  struct node*  next; /* A pointer to the next `node` in the `ll` */
};

/* ### Method Declarations ### */

struct ll     ll__create();
void          ll__affix (struct ll, union thing);
struct node*  ll__at    (struct ll, ll_size);
struct /* ll_methods */
{
  struct ll     (*create)();
  void          (*affix) (struct ll, union thing);
  struct node*  (*at)    (struct ll, ll_size);
} const ll = { ll__create, ll__affix, ll__at };

struct node* node__create   (union thing*);
void         node__attach_to(struct node, struct node*);
struct /* node_methods */
{
  struct node* (*create)   (union thing*);
  void         (*attach_to)(struct node, struct node*);
} const node = { node__create, node__attach_to };


/* ### Method Implementations ### */

/* This method initializes a new ll, with no nodes. The `root` is set to a
 * `NULL` pointer.
 */
struct ll ll__create()
{
  struct ll this;
  
  this.root   = NULL;
  this.length = 0;
  
  return this;
}

/* This method affixes a new child onto a ll.
 * 
 * Takes two arguments, the affixee, and something to be appended as a child.
 */
void ll__affix(struct ll this, union thing thing)
{
  
}

/* This method returns a pointer to the node at a given index in an `ll`.
 * 
 * Takes two arguments, the indexee (`this`), and an integer `index`.
 */
struct node* ll__at(struct ll this, ll_size index)
{
  /* This will give us either a `NULL` pointer (if this has no root, i.e. is
   * an empty list), or the first `node` (if this *has* a `root`, i.e. is
   * *not* an empty list). */
  struct node* last = this.root;
  
  /* We iterate starting at `i = 1`, because `last` will already point to the
   * first `node` in the list, if it has any `node`s at all. */
  for(ll_size i = 1; i < this.length; ++i)
    last = last->next;
  
  return last;
}

/* This method creates a new `node` for a given `thing`. `next` will also be
 * initialized to a `NULL` pointer.
 * 
 * Expects a `thing` as an argument, to be stored on this `node` as `e`.
 */
struct node* node__create(union thing* thing)
{
  struct node this;
  
  this.e    = thing;
  this.next = NULL;
  
  return &this;
}

void node__attach_to(struct node this, struct node* to)
{
  to->e = &this;
}


/* ======================
= `infrastructure list` =
====================== */

/* `infrastructure list`, the core data element of Paws, is here implemented
 * as a linked-list, referencing other `list`s as elements.
 * 
 * For now, we’re not considering the storage of native data types, such as
 * `infrastructure string` and `infrastructure numeric`. That could get messy.
 */
struct list
{
  struct ll*  naughty; /* The ll behind this `list` */
};


/* =======
= main() =
======= */

int main()
{
  struct ll root;
  
  root = ll.create(NULL);
  
  return 0;
}
