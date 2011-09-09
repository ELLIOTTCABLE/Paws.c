# if !defined(LABEL_DECLARATIONS)
#   define    LABEL_DECLARATIONS

# if !defined(DECLARATIONS)
#   define LABEL_C__BEHEST
#   define DECLARATIONS
# endif
#     include "Core.h"
#     include "Nuketypes/Nuketypes.h"

#     include "Magazine.c"
#     include "Metadata/Metadata.c"

#     include <stdbool.h>
# if defined(LABEL_C__BEHEST)
#   undef DECLARATIONS
# endif


struct e(label) {
  e(ll)       metadata;
  
  e(unique)   characters; };
  


struct E(Label) {
  e(representation)       family;
  e(byte)                 name[64];
  
  // Functions ==============
  /// `Label` family functions
  e(label)              (*create)             ( e(magazine) with, e(charray) characters );
    struct e(label) *   (*allocate)(void);
  e(label)              (*initialize)         ( struct e(label)* this, e(magazine) with, e(charray) characters );
  
  /// `struct label` instance functions
  e(blob)               (*as_blob)            ( e(label) this );
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

static blob             label__as_blob           (label this);
static charray          label__characters        (label this);
static bool             label__equal             (label this, label that);


   IF_EXTERNALIZED(static) struct Label * // »
                                  Label   = NULL;
void Paws__register_Label(void) { Label   = malloc(sizeof( struct Label ));
                            Paws->Label   = Label;
  Paws__register_Unique();
  Paws__register_Magazine();
  
  auto struct Label _ = // »
  { .family       = (representation)Label
  , .name         = "label"
    
  , .create       = Label__create
  , .allocate     = Label__allocate
  , .initialize   = Label__initialize
    
  , .as_blob      = label__as_blob
  , .characters   = label__characters
  , .equal        = label__equal };
  
  memcpy(Label, &_, sizeof( struct Label )); }


label Label__create(magazine with, charray characters) {
  return Label->initialize(Label->allocate(), with, characters); }

struct label* Label__allocate(void) {
  return malloc(sizeof( struct label )); }

label Label__initialize(struct label* this, magazine with, charray characters) {
  Metadata->initialize((metadata)this);
  
  this->characters = Magazine->of(with, characters, STRNLEN(characters, UNIQUE_SIZE_MAX));
  
  return this; }

blob label__as_blob(label this) { auto struct blob // »
  some_blob = { .pointer = this, .isa = (representation)Label };
  
  return some_blob; }

charray label__characters(label this) {
  return this->characters->content; }

bool label__equal(label this, label that) {
  return this->characters == that->characters; }

# endif //!defined(LABEL_IMPLEMENTATION) && !defined(DECLARATIONS)
