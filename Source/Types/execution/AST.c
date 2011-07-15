# if !defined(AST_DECLARATIONS)
#   define    AST_DECLARATIONS

# if !defined(DECLARATIONS)
#   define AST_C__BEHEST
#   define DECLARATIONS
# endif
#     include "Core.h"
#     include "Types/Types.h"
      
#     include <stdbool.h>
# if defined(AST_C__BEHEST)
#   undef DECLARATIONS
# endif


          struct e(node);
          struct e(ast);
typedef   struct e(node) *    e(node);
typedef   struct e(ast) *     e(ast);

/*  FIXME:  I am slightly uncomfortable imposing a hard limit on the maximum size of “documents” that this Paws
 *          interpreter can handle. I’d love to use some sort of arbitrary-integer representation for this, but
 *          at the moment, that’s extra work I cannot afford. */
typedef   unsigned long long int    e(ast_index);

enum e(node_type) { e(PHRASE) = 0, e(EXPRESSION), e(SCOPE) };

struct e(node) {
  e(node)               next;
    enum e(node_type)   isa;
    bool                last;
  
  e(ast_index)          start;
  e(ast_index)          end;
  
  union {
    e(node)               child;
    e(thing)              payload; } // »
                        content; };

struct e(ast) { void* nothing; }; // Reserved


struct E(Node) {
  //  Functions ============
  
  /// `Node` family functions
  e(node)                   (*phrase)                   (                       e(thing) payload );
  e(node)                   (*expression)(void);
  e(node)                   (*scope)(void);
  struct e(node) *          (*allocate)(void);
  e(node)                   (*initialize_phrase)        ( struct e(node)* this, e(thing) payload );
  e(node)                   (*initialize_expression)    ( struct e(node)* this );
  e(node)                   (*initialize_scope)         ( struct e(node)* this );
  
  /// `node` instance functions
  e(node)                   (*parent)                   ( e(node) this );
  e(node)                   (*child)                    ( e(node) this );
  e(thing)                  (*payload)                  ( e(node) this );
                       void (*affix)                    ( e(node) this, e(node) sibling );
                       void (*descend)                  ( e(node) this, e(node) child );
} IF_INTERNALIZED(extern *Node);

struct E(AST) { void* nothing; } IF_INTERNALIZED(extern *AST); // Reserved

extern    void MAKE_EXTERNAL(register_Node)(void);
extern    void MAKE_EXTERNAL(register_AST)(void);



# endif //!defined(AST_DECLARATIONS)
# if !defined(AST_IMPLEMENTATION) && !defined(DECLARATIONS) /* ========================================== BODY */
#   define    AST_IMPLEMENTATION

# define DECLARATIONS
#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


node                  Node__phrase                   (thing payload);
node                  Node__expression(void);
node                  Node__scope(void);
struct node *         Node__allocate(void);
node                  Node__initialize_phrase        (struct node* this, thing payload);
node                  Node__initialize_expression    (struct node* this);
node                  Node__initialize_scope         (struct node* this);

node                  node__parent                   (node this);
node                  node__child                    (node this);
thing                 node__payload                  (node this);
                 void node__affix                    (node this, node sibling);
                 void node__descend                  (node this, node child);


  IF_EXTERNALIZED(static) struct Node * // »
                                 Node   = NULL;
void Paws__register_Node(void) { Node   = malloc(sizeof( struct Node ));
  
  auto struct Node // »
  data = {
    .phrase                   = Node__phrase,
    .expression               = Node__expression,
    .scope                    = Node__scope,
    .allocate                 = Node__allocate,
    .initialize_phrase        = Node__initialize_phrase,
    .initialize_expression    = Node__initialize_expression,
    .initialize_scope         = Node__initialize_scope,
    
    .parent                   = node__parent,
    .child                    = node__child,
    .payload                  = node__payload,
    .affix                    = node__affix,
    .descend                  = node__descend };
  
  memcpy(Node, &data, sizeof( struct Node )); }

 IF_EXTERNALIZED(static) struct AST * // »
                                AST   = NULL;
void Paws__register_AST(void) { AST   = malloc(sizeof( struct AST ));

  auto struct AST // »
  data = { .nothing = NULL };

  memcpy(AST, &data, sizeof( struct AST )); }


node Node__phrase(thing payload) { return Node->initialize_phrase    (Node->allocate(), payload); }
node Node__expression(void) {      return Node->initialize_expression(Node->allocate()); }
node Node__scope(void) {           return Node->initialize_scope     (Node->allocate()); }

struct node* Node__allocate(void) {
  return malloc(sizeof( struct node )); }

node _Node__initialize           (struct node* this);
node  Node__initialize_phrase    (struct node* this, thing payload) {
     _Node__initialize           (             this);
                                               this->isa = PHRASE;
                                               this->content.payload = payload;
                                        return this; }
node  Node__initialize_expression(struct node* this) {
     _Node__initialize           (             this);
                                               this->isa = EXPRESSION;
                                               this->content.child = NULL;
                                        return this; }
node  Node__initialize_scope     (struct node* this) {
     _Node__initialize           (             this);
                                               this->isa = SCOPE;
                                               this->content.child = NULL;
                                        return this; }

node _Node__initialize           (struct node* this) { auto struct node // »
  data = {
    .next     = NULL,
  //.isa      = ?
    .last     = false,
    
    .start    = 0,
    .end      = 0,
    
    .content = { .child = NULL } };
  
  memcpy(this, &data, sizeof( struct node ));
  return this; }

node _node__last   (node this);
node  node__parent (node this) { this = _node__last(this);
  if (this->next == NULL) return NULL;
                     else return this->next; }
node _node__last   (node this) {
  if (this->next == NULL) return this;
  if (this->last)         return this;
                     else return _node__last(this->next); }

node  node__child  (node this) {
  if (this->isa == PHRASE) return NULL; // TODO: Error
                      else return this->content.child; }

thing node__payload(node this) {
  if (this->isa != PHRASE) return (thing){ NULL }; // TODO: Error
                      else return this->content.payload; }

void node__affix(node this, node sibling) {
  if (_node__last(this) != this)
    _node__last(sibling)->next = this->next;
  if (this->last)
    _node__last(sibling)->last =! (this->last = false);
  this->next = sibling; }

void node__descend(node this, node descendant) {
  if (Node->child(this) != NULL)
    Node->affix(_node__last(Node->child(this)), descendant);
  else {
    this->content.child = descendant;
    _node__last(this->content.child)->last = true; } }


# endif //!defined(AST_IMPLEMENTATION) && !defined(DECLARATIONS)
