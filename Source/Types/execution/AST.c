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

/*  There are three basic types of `node`s in a cPaws `AST`:
 *  
 *  - `PHRASE` nodes, the most basic, are generally a single ‘word’ in the code: the `AST` representing
 *    `foo bar baz` contains three `PHRASE` nodes, `“foo”`, `“bar”`, and `“baz”`. They need not, however, be a
 *    single ‘word’; `PHRASE` nodes may contain multiple ‘words’ when surrounded by double-quotes
 *    (e.g. `foo “bar baz”` contains only two `PHRASE` nodes: `“foo”` and `“bar baz”`)
 *  
 *  - `EXPRESSION` nodes consist of a series of juxtaposed sub-nodes, which may be any of the three `node_type`s.
 *    Their sub-nodes are juxtaposed by dint of seperation by whitespace (which may not include newlines, if the
 *    `EXPRESSION` node in question is the direct descendant of a new `SCOPE`, as newlines imply new
 *    sub-expressions.)
 *    - A `PHRASE` node inside an `EXPRESSION` node is obviously the basic build block of the language; it
 *      implies a juxtaposition with the previous node (or, if there is no previous node in *this* `EXPRESSION`,
 *      then instead implies a juxtaposition with the closest parent `SCOPE`)
 *    - Another `EXPRESSION` node as a child of this `EXPRESSION` comprises a sub-expression, which implies a
 *      juxtaposition of the *result* of said sub-expression with the the previous node (or alternatively, the
 *      closest parent `SCOPE`; see above.) Sub-expressions are denoted by opening and closing parenthesis within
 *      the parent `EXPRESSION` (e.g. `foo (bar baz)` is an `EXPRESSION` with two nodes: the `PHRASE` `foo` and
 *      the (sub-)`EXPRESSION` `bar baz`, which itself contains two `PHRASE` nodes, `“bar”` and `“baz”`. )
 *    - A new `SCOPE` node as a child of the `EXPRESSION` comprises a new sub-scope
 *  
 *  - `SCOPE` nodes indicate sub-sections of a program within which the juxtapositions of the first sub-node of
 *    each `EXPRESSION` and sub-expression within that `SCOPE` are resolved against that `SCOPE`.
 *    
 *    In libspace terms, this implies that within a given `execution`, instantiated for a given `SCOPE`, all
 *    `EXPRESSION`s evalulated will have their first node effectively juxtaposed against that `execution`’s
 *    `locals`-`fork`.
 */
enum e(node_type) { e(PHRASE) = 0, e(EXPRESSION), e(SCOPE) };

/*  `node` is the core of our `AST` implementation. A given document, read into `Paws.c`, is represented by an
 *  impure singly-linked-list of these “nodes.” Each node includes a pointer to the `next` linear `node` in the
 *  parent document.
 *  
 *  Two `node_type`s (`EXPRESSION` and `SCOPE`) are capable of having children, and such `node` instances also
 *  encapsulate a pointer to the first such child. The `last` child in an enclosing node is boolean-flagged as
 *  such, with its `next` pointer referencing said enclosing `node` instead of the laterally subsequent node.
 *  
 *  The last node in a `SCOPE` sourcing from a foreign Iunit may be missing its `next` pointer if the subsequent
 *  node (parent node) from the original document was irrelevant to the portions of the stuffspace shared with
 *  this interpreter.
 *  
 *  Every node includes unsigned, numeric `ast_index`es for the first and last character *of that node*. These
 *  indexes are not necessarily undivided, and do not encompass the entire document. Meaningless whitespace is
 *  usually not included in the `ast_index`-range of any terminal `node`. The range between the `start` and `end`
 *  indicies for the `node_type`s with children will fully encompass the ranges for each of their children nodes.
 *  
 *  `PHRASE`s, as terminal nodes, provide a pointer to their static libspace representation in the stead of a
 *  pointer to `child`ren. Currently, this means only a pointer to a preallocated libspace `label` for that
 *  `PHRASE`. This pointer is typecast as a `thing` to be future-proof, but need not currently be annotated, as
 *  the `thing` annotation will be ignored, and the pointer’s referencee memory treated as a `label` instance.
 */
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
  /*  `allocate()` simply allocates memory for a new `struct node` instance on the heap, and returns a `node`
   *  pointer. `initialize()` accepts such a pointer to an uninitialized heap structure and initializes the
   *  individual regions of that structure to sane defaults. It may take other arguments necessary to initialize
   *  the data correctly; check the function signature. (FIXME: Move a comprehensive discussion of the basic
   *  `initialize()` and `allocate()` functions to a single place in the codebase, and then refer to it
   *  elsewhere. Too much opportunity for senseless duplication, as all these functions are essentially the
   *  same.)
   *  
   *  The `phrase()`, `expression()`, and `scope()` functions are convenience constructors that `allocate()`
   *  and `initialize()` `node`s of the relevant `node_type`. (FIXME: Reference `create()`.)
   *  
   *  `phrase()` may eventually be re-implemented to take a `char*` and a `label_index` instead of a constructed
   *  `label` as it currently does. I’m attempting to keep `label` implementation details outside of the Paws.c
   *  core right now, but the convenience of simply passing a chunk of characters to it from the parser may
   *  outweigh that design goal in the long term.
   *  
   *  ...
   *  
   *  `affix()` will attach the given `sibling` `node` (or series of `node`s) immediately after `this`. It
   *  maintains chains of `node`s at the same level as much as it can. It will also move the `last` flag
   *  “forward” to later `node`s if necessary. For instance, if you attach a new chain of `node`s to the `last`
   *  `node` of of a given ancestor, then the `last` flag will be removed from the old `node` and be applied to
   *  the last `node` in the new sibling’s chain.
   *  
   *  `descend()` will append a new `descendant` `node` immediately “below” `this` in the virtual tree of
   *  `node`s. If this node has no `child` `node`, then the `descendant` will be made this `node`’s immediate
   *  `child`; if one already exists, then the new `descendant` will be `affix()`ed to the last `node` in the
   *  current `child`’s chain. The `last` flag will be “carried through” with the modifications, and added to the
   *  last `node` in the chain if necessary.
   */
  
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
