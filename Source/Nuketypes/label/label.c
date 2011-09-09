# if !defined(LABEL_DECLARATIONS)
#   define    LABEL_DECLARATIONS

# if !defined(DECLARATIONS)
#   define LABEL_C__BEHEST
#   define DECLARATIONS
# endif
#     include "Core.h"
#     include "Nuketypes/Nuketypes.h"

#     include "Magazine.c"
#     include "Metadata/LL.c"

#     include <stdbool.h>
# if defined(LABEL_C__BEHEST)
#   undef DECLARATIONS
# endif


struct e(label) {
  e(ll)       content;
  e(unique)   characters; };
  


struct E(Label) {
    typeRepresentation          Label;
  
  // Functions ==============
  /// `Label` family functions
  e(label)              (*create)             ( e(magazine) with, e(charray) characters );
    struct e(label) *   (*allocate)(void);
  e(label)              (*initialize)         ( struct e(label)* this, e(magazine) with, e(charray) characters );
  
  /// `struct label` instance functions
  e(thing)              (*thing)              ( e(label) this );
  e(charray)            (*characters)         ( e(label) this );
    bool                (*equal)              ( e(label) this, e(label) that );
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

# define STRNLEN(STRING, N) \
    (charray)memchr(STRING, '\0', N) - STRING//;

# define UNIQUE_SIZE_MAX UINT_MAX


static label            Label__create            (magazine with, charray characters);
static struct label *   Label__allocate(void);
static label            Label__initialize        (struct label* this, magazine with, charray characters);

static thing            label__thing             (label this);
static charray          label__characters        (label this);
static bool             label__equal             (label this, label that);


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
    
    .thing        = label__thing,
    .characters   = label__characters,
    .equal        = label__equal };
  
  memcpy(data.Label, &type, sizeof( struct typeRepresentation ));
  memcpy(Label,      &data, sizeof( struct Label )); }


label Label__create(magazine with, charray characters) {
  return Label->initialize(Label->allocate(), with, characters); }

struct label * Label__allocate(void) {
  return malloc(sizeof( struct label )); }

label Label__initialize(struct label* this, magazine with, charray characters) {
  this->content = LL->create();
  this->characters = Magazine->of(with, characters, STRNLEN(characters, UNIQUE_SIZE_MAX));
  
  return this; }

thing label__thing(label this) { auto struct thing // »
  something = { .pointer = this, .isa = Label->Label };
  
  return something; }

charray label__characters(label this) {
  return this->characters->content; }

bool label__equal(label this, label that) {
  return this->characters == that->characters; }

# endif //!defined(LABEL_IMPLEMENTATION) && !defined(DECLARATIONS)
