# if !defined(SCRIPT_DECLARATIONS)
#   define    SCRIPT_DECLARATIONS

# if !defined(DECLARATIONS)
#   define SCRIPT_C__BEHEST
#   define DECLARATIONS
# endif
#     include "Core.h"
#     include "Nuketypes/Nuketypes.h"
      
#     include <stdbool.h>
# if defined(SCRIPT_C__BEHEST)
#   undef DECLARATIONS
# endif


          struct e(node);
          struct e(terminal);
          struct e(expression);
typedef   struct e(node) *    e(node);
typedef   struct e(node) *    e(terminal);
typedef   struct e(node) *    e(expression);

enum e(node_type) { e(EXPRESSION) = 0, e(TERMINAL) };

struct e(node) {
  e(node)               next;
    enum e(node_type)   isa;
    bool                last;
  
  union {
    e(node)               skip;
    e(blob)               blob; } // »
                        _; };


struct E(Node) {
  //  Functions ============
  
  /// `Node` family functions
  e(terminal)               (*terminal)                                       ( e(blob) it );
  e(expression)             (*expression)(void);
  struct e(node) *          (*allocate)(void);
  e(terminal)               (*initialize_terminal)      ( struct e(node)* this, e(blob) it );
  e(expression)             (*initialize_expression)    ( struct e(node)* this );
  
  /// `node` instance functions
                     void (*affix)                             ( e(node)  this, e(node) it );
                     void (*descend)                     ( e(expression)  this, e(node) it );
} IF_INTERNALIZED(extern *Node);

extern    void MAKE_EXTERNAL(register_Node)(void);



# endif //!defined(SCRIPT_DECLARATIONS)
# if !defined(SCRIPT_IMPLEMENTATION) && !defined(DECLARATIONS) /* ======================================= BODY */
#   define    SCRIPT_IMPLEMENTATION

# define DECLARATIONS
#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


static terminal              Node__terminal                                    (blob it);
static expression            Node__expression(void);
static struct node *         Node__allocate(void);
static terminal              Node__initialize_terminal      (struct node* this, blob it);
static expression            Node__initialize_expression    (struct node* this);

static                  void node__affix                           (node  this, node it);
static                  void node__descend                   (expression  this, node it);


  IF_EXTERNALIZED(static) struct Node * // »
                                 Node   = NULL;
void Paws__register_Node(void) { Node   = malloc(sizeof( struct Node ));
  
  auto struct Node _ = // »
  { .terminal                 = Node__terminal
  , .expression               = Node__expression
  , .allocate                 = Node__allocate
  , .initialize_terminal      = Node__initialize_terminal
  , .initialize_expression    = Node__initialize_expression
    
  , .affix                    = node__affix
  , .descend                  = node__descend };
  
  memcpy(Node, &_, sizeof( struct Node )); }


terminal   Node__terminal(blob it) { return Node->initialize_terminal  (Node->allocate(), it); }
expression Node__expression(void) {  return Node->initialize_expression(Node->allocate()); }

struct node* Node__allocate(void) {
  return malloc(sizeof( struct node )); }

static // »
node      _Node__initialize           (struct node* this, enum node_type isa);
terminal   Node__initialize_terminal  (struct node* this, blob it) {
          _Node__initialize           (this, TERMINAL);
                                       this->_.blob = it;
                                return this; }
expression Node__initialize_expression(struct node* this) {
          _Node__initialize           (this, EXPRESSION);
                                       this->_.skip = NULL;
                                return this; }

node _Node__initialize           (struct node* this, enum node_type isa) { auto struct node _ = // »
  { .next     = NULL
  , .isa      = isa
  , .last     = false };
  
  memcpy(this, &_, sizeof( struct node ));
  return this; }

static inline // »
node _node__last(node this) { auto node // »
      next = this->isa? this->next:this->_.skip;
  if (next == NULL) return this;
  if (this->last)   return this;
               else return _node__last(next); }

void node__affix(node this, node it) { auto node // »
  last = _node__last(it)
, next = this->isa? this->next:this->_.skip;
  if (_node__last(this) != this)
    last->isa? (last->next = next) : (last->_.skip = next);
  if (this->last)
    last->last =! (this->last = false);
  this->isa? (this->next = it) : (this->_.skip = it); }

void node__descend(expression this, node it) {
  if (this->next != NULL)
    Node->affix(_node__last(this->next), it);
  else {
    this->next = it;
    _node__last(this->next)->last = true; } }


# endif //!defined(SCRIPT_IMPLEMENTATION) && !defined(DECLARATIONS)
