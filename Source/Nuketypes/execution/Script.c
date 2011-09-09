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

enum e(node_type) { e(TERMINAL) = 0, e(EXPRESSION) };

struct e(node) {
  e(node)               next;
    enum e(node_type)   isa;
    bool                last;
  
  union {
    e(node)               child;
    e(thing)              payload; } // »
                        content; };


struct E(Node) {
  //  Functions ============
  
  /// `Node` family functions
  e(terminal)               (*terminal)                 (                       e(thing) payload );
  e(expression)             (*expression)(void);
  struct e(node) *          (*allocate)(void);
  e(terminal)               (*initialize_terminal)      ( struct e(node)* this, e(thing) payload );
  e(expression)             (*initialize_expression)    ( struct e(node)* this );
  
  /// `node` instance functions
  e(expression)         (*parent)                   ( e(node) this );
  e(node)               (*child)                    ( e(expression) this );
  e(thing)              (*payload)                  ( e(terminal) this );
                   void (*affix)                    ( e(node) this,       e(node) sibling );
                   void (*descend)                  ( e(expression) this, e(node) child );
} IF_INTERNALIZED(extern *Node);

extern    void MAKE_EXTERNAL(register_Node)(void);



# endif //!defined(SCRIPT_DECLARATIONS)
# if !defined(SCRIPT_IMPLEMENTATION) && !defined(DECLARATIONS) /* ======================================= BODY */
#   define    SCRIPT_IMPLEMENTATION

# define DECLARATIONS
#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


terminal              Node__terminal                 (thing payload);
expression            Node__expression(void);
struct node *         Node__allocate(void);
terminal              Node__initialize_terminal      (struct node* this, thing payload);
expression            Node__initialize_expression    (struct node* this);

expression            node__parent                   (node this);
node                  node__child                    (expression this);
thing                 node__payload                  (terminal this);
                 void node__affix                    (node this, node sibling);
                 void node__descend                  (expression this, node child);


  IF_EXTERNALIZED(static) struct Node * // »
                                 Node   = NULL;
void Paws__register_Node(void) { Node   = malloc(sizeof( struct Node ));
  
  auto struct Node // »
  data = {
    .terminal                 = Node__terminal,
    .expression               = Node__expression,
    .allocate                 = Node__allocate,
    .initialize_terminal      = Node__initialize_terminal,
    .initialize_expression    = Node__initialize_expression,
    
    .parent                   = node__parent,
    .child                    = node__child,
    .payload                  = node__payload,
    .affix                    = node__affix,
    .descend                  = node__descend };
  
  memcpy(Node, &data, sizeof( struct Node )); }


terminal   Node__terminal(thing payload) { return Node->initialize_terminal  (Node->allocate(), payload); }
expression Node__expression(void) {        return Node->initialize_expression(Node->allocate()); }

struct node* Node__allocate(void) {
  return malloc(sizeof( struct node )); }

node      _Node__initialize           (struct node* this, enum node_type isa);
terminal   Node__initialize_terminal  (struct node* this, thing payload) {
          _Node__initialize           (this, TERMINAL);
                                       this->content.payload = payload;
                                return this; }
expression Node__initialize_expression(struct node* this) {
          _Node__initialize           (this, EXPRESSION);
                                       this->content.child = NULL;
                                return this; }

node _Node__initialize           (struct node* this, enum node_type isa) { auto struct node // »
  data = {
    .next     = NULL,
    .isa      = isa,
    .last     = false };
  
  memcpy(this, &data, sizeof( struct node ));
  return this; }

node _node__last(node this);
expression node__parent(node this) { this = _node__last(this);
  if (this->next == NULL) return NULL;
                     else return this->next; }
node _node__last(node this) {
  if (this->next == NULL) return this;
  if (this->last)         return this;
                     else return _node__last(this->next); }

node node__child(expression this) {
  if (this->isa != EXPRESSION) return NULL; // TODO: Error
                          else return this->content.child; }

thing node__payload(terminal this) {
  if (this->isa != TERMINAL) return (thing){ NULL }; // TODO: Error
                        else return this->content.payload; }

void node__affix(node this, node sibling) {
  if (_node__last(this) != this)
    _node__last(sibling)->next = this->next;
  if (this->last)
    _node__last(sibling)->last =! (this->last = false);
  this->next = sibling; }

void node__descend(expression this, node descendant) {
  if (Node->child(this) != NULL)
    Node->affix(_node__last(Node->child(this)), descendant);
  else {
    this->content.child = descendant;
    _node__last(this->content.child)->last = true; } }


# endif //!defined(SCRIPT_IMPLEMENTATION) && !defined(DECLARATIONS)
