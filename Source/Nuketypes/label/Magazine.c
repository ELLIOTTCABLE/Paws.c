# if !defined(MAGAZINE_DECLARATIONS)
#   define    MAGAZINE_DECLARATIONS

# if !defined(DECLARATIONS)
#   define MAGAZINE_C__BEHEST
#   define DECLARATIONS
# endif
#     include "Core.h"
#     include "Nuketypes/Nuketypes.h"
# if defined(MAGAZINE_C__BEHEST)
#   undef DECLARATIONS
# endif


          struct e(unique);
          struct e(magazine);
typedef   struct e(unique) *      e(unique);
typedef   struct e(magazine) *    e(magazine);

typedef   unsigned int            e(unique_size);
typedef   unsigned int            e(magazine_length);

struct e(unique) {
  e(pointer)        content;
  e(unique_size)    bytes;
  e(unique)         overflow; };
struct e(magazine) {
  e(unique) *           uniques;
  e(byte)               bits; };


struct E(Unique) {
  // Functions ==============
  /// `Unique` family functions
  e(unique)                   (*create)                                     ( e(pointer) content, e(unique_size) bytes );
    struct e(unique) *        (*allocate)(void);
  e(unique)                   (*initialize)         ( struct e(unique)* this, e(pointer) content, e(unique_size) bytes );
  
  /// `struct unique` instance functions
  e(unique)                   (*of)                        ( e(unique)  this, e(pointer) content, e(unique_size) bytes );
                         void (*affix)                     ( e(unique)  this, e(unique) sibling );
} IF_INTERNALIZED(extern *Unique);

struct E(Magazine) {
  // Functions ==============
  /// `Magazine` family functions
  //  
  //  
  //  NOTE: `->initialize()` truncates its `extent` argument to the closest power of two below the given integer.
  e(magazine)               (*create)             ( e(magazine_length) extent );
    struct e(magazine) *    (*allocate)(void);
  e(magazine)               (*initialize)         ( struct e(magazine)* this, e(magazine_length) extent );
  
  /// `struct magazine` instance functions
  e(unique)                 (*of)                        ( e(magazine)  this, e(pointer) content, e(unique_size) bytes );
} IF_INTERNALIZED(extern *Magazine);

extern    void MAKE_EXTERNAL(register_Unique)(void);
extern    void MAKE_EXTERNAL(register_Magazine)(void);



# endif //!defined(MAGAZINE_DECLARATIONS)
# if !defined(MAGAZINE_IMPLEMENTATION) && !defined(DECLARATIONS) /* ===================================== BODY */
#   define    MAGAZINE_IMPLEMENTATION

# define DECLARATIONS
#   include <stdlib.h>
#   include <string.h>
#   include <math.h>
# undef  DECLARATIONS

static const magazine_length offset_basis = 2166136261;
static const magazine_length FNV_prime = (1 << 24) + (1 << 8) + 0x93;


static unique             Unique__create             (                     pointer content, unique_size bytes);
static struct unique *    Unique__allocate(void);
static unique             Unique__initialize         (struct unique* this, pointer content, unique_size bytes);

static unique             unique__of                 (unique this,         pointer content, unique_size bytes);


    IF_EXTERNALIZED(static) struct Unique * // »
                                   Unique     = NULL;
void Paws__register_Unique(void) { Unique     = malloc(sizeof( struct Unique ));
  
  auto struct Unique // »
  data = {
    .create       = Unique__create,
    .allocate     = Unique__allocate,
    .initialize   = Unique__initialize,
    
    .of           = unique__of };
  
  memcpy(Unique, &data, sizeof( struct Unique )); }


static magazine             Magazine__create             (magazine_length extent);
static struct magazine *    Magazine__allocate(void);
static magazine             Magazine__initialize         (struct magazine* this, magazine_length extent);

static unique               magazine__of                 (magazine this, pointer content, unique_size bytes);
static magazine_length     _magazine__hash               (magazine this, pointer content, unique_size bytes);

      IF_EXTERNALIZED(static) struct Magazine * // »
                                     Magazine     = NULL;
void Paws__register_Magazine(void) { Magazine     = malloc(sizeof( struct Magazine ));
  
  auto struct Magazine // »
  data = {
    .create       = Magazine__create,
    .allocate     = Magazine__allocate,
    .initialize   = Magazine__initialize,
    
    .of           = magazine__of };
  
  memcpy(Magazine, &data, sizeof( struct Magazine )); }


unique Unique__create(pointer content, unique_size bytes) {
  return Unique->initialize(Unique->allocate(), content, bytes); }

struct unique * Unique__allocate(void) {
  return malloc(sizeof( struct unique )); }

unique Unique__initialize(struct unique* this, pointer content, unique_size bytes) {
  
  this->content = content;
  this->bytes   = bytes;
  
  return this; }

unique unique__of(unique this, pointer content, unique_size bytes) {
  if (this->bytes == bytes && memcmp(this->content, content, bytes) == 0)
    return this;
  else if (this->overflow == NULL) 
    return this->overflow = Unique->create(content, bytes);
    return unique__of(this->overflow, content, bytes); }

magazine Magazine__create(magazine_length extent) {
  return Magazine->initialize(Magazine->allocate(), extent); }

struct magazine * Magazine__allocate(void) {
  return malloc(sizeof( struct magazine )); }

magazine Magazine__initialize(struct magazine* this, magazine_length extent) {
  
  this->bits    = (byte)log2(extent);
  this->uniques = malloc((1 << this->bits) * sizeof( struct unique* ));
  
  return this; }

unique magazine__of(magazine this, pointer content, unique_size bytes) { unique it; magazine_length // »
  hash = _magazine__hash(    this,         content,             bytes);
  
  if ( (it = this->uniques[hash]) != NULL )
    return Unique->of(it, content, bytes); else
    return this->uniques[hash] = Unique->create(content, bytes); }

static // »
magazine_length _magazine__hash(magazine this, pointer content, unique_size bytes) { bytes--; magazine_length // »
  hash = offset_basis;
  
  while (bytes--) { hash = (hash ^ ((byte*)content)[bytes]) * FNV_prime; }
  return ((hash >> this->bits) ^ hash) & (((magazine_length)1 << this->bits) - 1); }


# endif //!defined(MAGAZINE_IMPLEMENTATION) && !defined(DECLARATIONS)
