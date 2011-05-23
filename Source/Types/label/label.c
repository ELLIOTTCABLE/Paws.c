# if !defined(LABEL_DECLARATIONS)
#   define    LABEL_DECLARATIONS

# if !defined(DECLARATIONS)
#   define LABEL_C__BEHEST
#   define DECLARATIONS
# endif
#     include "Core.h"
#     include "Types/Types.h"

#     include "Magazine.c"
#     include "Types/fork/LL.c"
# if defined(LABEL_C__BEHEST)
#   undef DECLARATIONS
# endif


struct e(label) {
  e(ll)   content; };


struct E(Label) {
    typeRepresentation          Label;
  
  // Functions ==============
  /// `Label` family functions
  e(label)              (*create)(void);
    struct e(label) *   (*allocate)(void);
  e(label)              (*initialize)         ( struct e(label)* this );
  
  /// `struct label` instance functions
  e(thing)              (*thing)              ( e(label) this );
} IF_INTERNALIZED(extern *Label);

extern    void MAKE_EXTERNAL(register_Label)(void);



# endif //!defined(LABEL_DECLARATIONS)
# if !defined(LABEL_IMPLEMENTATION) && !defined(DECLARATIONS) /* ======================================== BODY */
#   define    LABEL_IMPLEMENTATION

# define DECLARATIONS
#   include "Paws.c"

#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


static label            Label__create(void);
static struct label *   Label__allocate(void);
static label            Label__initialize         (label this);

static thing            label__thing              (label this);


   IF_EXTERNALIZED(static) struct Label * // »
                                  Label   = NULL;
void Paws__register_Label(void) { Label   = malloc(sizeof( struct Label ));
                            Paws->Label   = Label;
  Paws__register_Unique();
  Paws__register_Magazine();
  
  auto struct typeRepresentation // »
  type = { .family = Label, .name = "label" };
  
  auto struct Label // »
  data = {
    .Label        = malloc(sizeof( struct typeRepresentation )),
    
    .create       = Label__create,
    .allocate     = Label__allocate,
    .initialize   = Label__initialize,
    
    .thing        = label__thing };
  
  memcpy(data.Label, &type, sizeof( struct typeRepresentation ));
  memcpy(Label,      &data, sizeof( struct Label )); }


label Label__create(void) {
  return Label->initialize(Label->allocate()); }

struct label * Label__allocate(void) {
  return malloc(sizeof( struct label )); }

label Label__initialize(label this) {
  this->content = LL->create();
  
  return this; }

thing label__thing(label this) { auto struct thing // »
  something = { .pointer = this, .isa = Label->Label };
  
  return something; }

# endif //!defined(LABEL_IMPLEMENTATION) && !defined(DECLARATIONS)
