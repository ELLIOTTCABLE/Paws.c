# if !defined(EXECUTION_DECLARATIONS)
#   define    EXECUTION_DECLARATIONS

# if !defined(DECLARATIONS)
#   define EXECUTION_C__BEHEST
#   define DECLARATIONS
# endif
#     include "Core.h"
#     include "Nuketypes/Nuketypes.h"
      
#     include "Metadata/Metadata.c"
#     include "Script.c"
# if defined(EXECUTION_C__BEHEST)
#   undef DECLARATIONS
# endif

struct e(juxtaposee) {
  e(blob)                     payload;
  e(node)                     from;
    struct e(juxtaposee) *    out; };

struct e(execution) {
  e(ll)                       metadata;
  
  e(node)                     position;
    struct e(juxtaposee) *    juxtaposees; };


struct E(Execution) {
  e(representation)                 family;
  e(byte)                           name[64];
  
  // Functions ==============
  
  /// `Execution` family functions
  e(execution)                    (*create)             (                            e(node) first );
    struct e(execution) *         (*allocate)(void);
  e(execution)                    (*initialize)         ( struct e(execution)* this, e(node) first );
  
  /// `struct execution` instance functions
  e(blob)                         (*as_blob)            ( e(execution) this );
                             void (*advance)            ( e(execution) this );
} IF_INTERNALIZED(extern *Execution);

extern    void MAKE_EXTERNAL(register_Execution)(void);



# endif //!defined(EXECUTION_DECLARATIONS)
# if !defined(EXECUTION_IMPLEMENTATION) && !defined(DECLARATIONS) /* ==================================== BODY */
#   define    EXECUTION_IMPLEMENTATION

# define DECLARATIONS
#   include "Paws.c"
    
#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


static execution                  Execution__create            (node first);
static struct execution *         Execution__allocate(void);
static execution                  Execution__initialize        (execution this, node first);

static blob                       execution__as_blob           (execution this);
static                       void execution__advance           (execution this);


       IF_EXTERNALIZED(static) struct Execution * // »
                                      Execution     = NULL;
void Paws__register_Execution(void) { Execution     = malloc(sizeof( struct Execution ));
                                Paws->Execution     = Execution;
  Paws__register_Node();
  
  auto struct Execution _ = // »
  { .family       = (representation)Execution
  , .name         = "execution"
    
  , .create       = Execution__create
  , .allocate     = Execution__allocate
  , .initialize   = Execution__initialize
    
  , .as_blob      = execution__as_blob
  , .advance      = execution__advance };
  
  memcpy(Execution, &_, sizeof( struct Execution )); }


execution Execution__create(node first) {
  return Execution->initialize(Execution->allocate(), first); }

struct execution * Execution__allocate(void) {
  return malloc(sizeof( struct execution )); }

execution Execution__initialize(execution this, node first) {
  Metadata->initialize((metadata)this);
  
  this->position = first;
  this->juxtaposees = NULL;
  
  return this; }

blob execution__as_blob(execution this) { auto struct blob // »
  some_blob = { .pointer = this, .isa = (representation)Execution };
  
  return some_blob; }

void execution__advance(execution this) {
  
  // TODO: implement.
  
  return; }

# endif //!defined(EXECUTION_IMPLEMENTATION) && !defined(DECLARATIONS)
