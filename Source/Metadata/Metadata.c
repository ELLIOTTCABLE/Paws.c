# if !defined(METADATA_DECLARATIONS)
#   define    METADATA_DECLARATIONS

# if !defined(DECLARATIONS)
#   define METADATA_C__BEHEST
#   define DECLARATIONS
# endif
#     include "Core.h"
#     include "Nuketypes/Nuketypes.h"

#     include "LL.c"
# if defined(METADATA_C__BEHEST)
#   undef DECLARATIONS
# endif

    // e(empty)
struct e(metadata) {
  e(ll)   metadata; };


struct E(Blob) {
  // Functions ==============
  e(empty)                  (*empty)(void);
    struct e(metadata) *    (*allocate)(void);
  
  e(blob)                   (*as_blob)            ( e(empty) this );
} IF_INTERNALIZED(extern *Blob);


struct E(Metadata) {
  // Functions ==============
  /// `Metadata` family functions
  e(metadata)         (*initialize)       ( struct e(metadata)* it );
  
  /// `struct metadata` instance functions
                 void (*insert)           ( e(metadata) this, e(blob) child, e(ll_size) idx );
                 void (*prefix)           ( e(metadata) this, e(blob) child );
                 void (*affix)            ( e(metadata) this, e(blob) child );
  e(blob)             (*at)               ( e(metadata) this,                 e(ll_size) idx );
} IF_INTERNALIZED(extern *Metadata);


extern    void MAKE_EXTERNAL(register_Blob)(void);
extern    void MAKE_EXTERNAL(register_Metadata)(void);



# endif //!defined(METADATA_DECLARATIONS)
# if !defined(METADATA_IMPLEMENTATION) && !defined(DECLARATIONS) /* ===================================== BODY */
#   define    METADATA_IMPLEMENTATION

# define DECLARATIONS
#   include "Paws.c"

#   include <stdlib.h>
#   include <string.h>
#   include <stdbool.h>
# undef  DECLARATIONS

static empty                    Blob__empty(void);
static struct metadata *        Blob__allocate(void);

static blob                     blob__as_blob            (empty this);


static metadata                 Metadata__initialize   (struct metadata* it);

static                     void metadata__insert       (metadata this, blob child, ll_size idx);
static                     void metadata__prefix       (metadata this, blob child);
static                     void metadata__affix        (metadata this, blob child);
static blob                     metadata__at           (metadata this,             ll_size idx);


  IF_EXTERNALIZED(static) struct Blob * // »
                                 Blob     = NULL;
void Paws__register_Blob(void) { Blob     = malloc(sizeof( struct Blob ));
                           Paws->Blob     = Blob;
  auto struct Blob _ =// »
  { .empty      = Blob__initialize
  , .allocate   = Blob__allocate };
  
  memcpy(Blob, &_, sizeof( struct Blob )); }


      IF_EXTERNALIZED(static) struct Metadata * // »
                                     Metadata     = NULL;
void Paws__register_Metadata(void) { Metadata     = malloc(sizeof( struct Metadata ));
                               Paws->Metadata     = Metadata;
  Paws__register_Element();
  Paws__register_LL();
  
  auto struct Metadata _ = // »
  { .initialize   = Metadata__initialize
    
  , .insert       = metadata__insert
  , .prefix       = metadata__prefix
  , .affix        = metadata__affix
  , .at           = metadata__at };
  
  memcpy(Metadata, &_, sizeof( struct Metadata )); }


empty Blob__empty(void) {
  return Metadata__initialize(Blob__allocate()); }

struct metadata* Blob__allocate(void) {
  return malloc(sizeof( struct metadata )); }

blob blob__as_blob(empty this) { return (blob){ .pointer = this, .isa = NULL } }


metadata Metadata__initialize(struct metadata* it) {
  it->metadata = LL->create();
  
  return it; }

void metadata__insert(metadata this, blob it, ll_size idx) {
  if (idx == 0)                           Metadata->prefix(this, it);
  else if (idx == this->metadata->length) Metadata->affix (this, it);
  else
    LL->posterior_insert(this->metadata, Element->create(it), idx); }

void metadata__prefix(metadata this, blob it) {
  LL->prefix(this->metadata, Element->create(it)); }

void metadata__affix(metadata this, blob it)  {
  LL->affix (this->metadata, Element->create(it)); }

blob metadata__at(metadata this, ll_size idx) { auto element // »
  it = LL->at(this->metadata, idx);
  
  if (it == NULL) return (blob){ NULL };
             else return it->blob; }

# endif //!defined(METADATA_IMPLEMENTATION) && !defined(DECLARATIONS)
