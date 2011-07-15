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

struct e(execution) {
  e(ll)                       content;
  e(node)                     position;
    struct e(juxtaposee) *    juxtaposees; };


struct E(Execution) {
    typeRepresentation    Execution;
  
  // Functions ==============
  
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
