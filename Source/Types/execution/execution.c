# if !defined(EXECUTION_DECLARATIONS)
#   define    EXECUTION_DECLARATIONS

# if !defined(DECLARATIONS)
#   define EXECUTION_C__BEHEST
#   define DECLARATIONS
# endif
#     include "Core.h"
#     include "Types/Types.h"
      
#     include "Types/fork/ll.c"
#     include "AST.c"
# if defined(EXECUTION_C__BEHEST)
#   undef DECLARATIONS
# endif

struct e(juxtaposee) {
  e(thing)                    payload;
  e(node)                     from;
    struct e(juxtaposee) *    out; };

/*  The `execution` nuketype stores a reference to one of our ubiquitous `ll`s for the associated `fork`‐
 *  `content` storage, a reference to the `next` `node` to be handled when this `execution` again reaches a stage
 *  (that is, when it is ‘resumed’), and finally, a “stack” (really, a reverse linked-list) of preceding nodes’
 *  `juxtaposees`.
 *  
 *  - `content` is an `ll` representing the libside-visible `fork` interface to this `execution`. As with any
 *    Paws object, this `execution` can be treated as a `fork` without consequence.
 *  - `position` is a pointer to a `struct node` representing a particular node in a Paws routine’s AST. It
 *    the node currently “being processed,” so to speak, by the `execution`, and the node *for which* the staging
 *    value will be added to `juxtaposees` when this `execution` is resumed.
 *  - `juxtaposees` is a ‘stack’ (stored in a linked-list of `juxtaposee` nodes) which represents the staging
 *    results for each “enclosing sub-expression” in the AST above the current `position` (including the
 *    antecedent node to the one currently being processed). When a particular sub-expression is completed, that
 *    sub-expression (the innermost, and thus first in the `juxtaposees` stack) will be removed from
 *    `juxtaposees`, replaced by the next `juxtaposee` (representing the next-outer parent-`node`); the
 *    aggreagate result of said sub-expression (the ‘value’ of the last juxtaposition) will itself be juxtaposed
 *    against the `payload` of the next-outer `juxtaposee`.
 * --
 *  TODO: document purpose
 */
struct e(execution) {
  e(ll)                       content;
  e(node)                     position;
    struct e(juxtaposee) *    juxtaposees; };


struct E(Execution) {
    typeRepresentation    Execution;
  
  // Functions ==============
  /*  (For the moment, see `ast.c` for documentation of the basic `create()`/`allocate()`/`initialize()`
   *  functions. I need some way to avoid W.E.T. documentation-writing for these repetitive APIs. Ideas abound…)
   *  
   *  `advance()` is the basic purpose of the `execution` data-structure. Effectively all interpretation
   *  functionality not implemented in `advance()` is implemented elsewhere in the codebase (in the `Threading`,
   *  `Stage`, or `Unit` families.)
   *  
   *  `advance()` will …
   */
  
  /// `Execution` family functions
  e(execution)                    (*create)             (                            e(node) first );
    struct e(execution) *         (*allocate)(void);
  e(execution)                    (*initialize)         ( struct e(execution)* this, e(node) first );
  
  /// `struct execution` instance functions
  e(thing)                        (*thing)              ( e(execution) this );
                             void (*advance)            ( e(execution) this );
} IF_INTERNALIZED(extern *Execution);

extern    void MAKE_EXTERNAL(register_Execution)(void);



# endif //!defined(EXECUTION_DECLARATIONS)
# if !defined(EXECUTION_IMPLEMENTATION) && !defined(DECLARATIONS) /* ==================================== BODY */
#   define    EXECUTION_IMPLEMENTATION

# define DECLARATIONS
#   include "Paws.c"
#   include "ast.c"
    
#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


static execution                  Execution__create            (node first);
static struct execution *         Execution__allocate(void);
static execution                  Execution__initialize        (execution this, node first);

static thing                      execution__thing             (execution this);
static                       void execution__advance           (execution this);


       IF_EXTERNALIZED(static) struct Execution * // »
                                      Execution   = NULL;
void Paws__register_Execution(void) { Execution   = malloc(sizeof( struct Execution ));
                                Paws->Execution   = Execution;
  Paws__register_Node();
  Paws__register_AST();
  
  auto struct typeRepresentation // »
  type = { .family = Execution, .name = "execution" };
  
  auto struct Execution // »
  data = {
    .Execution    = malloc(sizeof( struct typeRepresentation )),
    
    .create       = Execution__create,
    .allocate     = Execution__allocate,
    .initialize   = Execution__initialize,
    
    .thing        = execution__thing,
    .advance      = execution__advance };
  
  memcpy(data.Execution, &type, sizeof( struct typeRepresentation ));
  memcpy(Execution,      &data, sizeof( struct Execution )); }


execution Execution__create(node first) {
  return Execution->initialize(Execution->allocate(), first); }

struct execution * Execution__allocate(void) {
  return malloc(sizeof( struct execution )); }

execution Execution__initialize(execution this, node first) {
  this->content = LL->create();
  
  this->position = first;
  this->juxtaposees = NULL;
  
  return this; }

thing execution__thing(execution this) { auto struct thing // »
  something = { .pointer = this, .isa = Execution->Execution };
  
  return something; }

void execution__advance(execution this) {
  
  // TODO: implement.
  
  return; }

# endif //!defined(EXECUTION_IMPLEMENTATION) && !defined(DECLARATIONS)
