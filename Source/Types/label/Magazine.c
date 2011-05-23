# if !defined(MAGAZINE_DECLARATIONS)
#   define    MAGAZINE_DECLARATIONS

# if !defined(DECLARATIONS)
#   define MAGAZINE_C__BEHEST
#   define DECLARATIONS
# endif
#     include "Core.h"
#     include "Types/Types.h"
# if defined(MAGAZINE_C__BEHEST)
#   undef DECLARATIONS
# endif


          struct e(unique);
          struct e(magazine);
typedef   struct e(unique) *      e(unique);
typedef   struct e(magazine) *    e(magazine);

struct e(unique) { void* nothing; };
struct e(magazine) { void* nothing; };


struct E(Unique) {
  // Functions ==============
  /// `Unique` family functions
  e(unique)              (*create)(void);
    struct e(unique) *   (*allocate)(void);
  e(unique)              (*initialize)         ( struct e(unique)* this);
  
  /// `struct unique` instance functions
} IF_INTERNALIZED(extern *Unique);

struct E(Magazine) {
  // Functions ==============
  /// `Magazine` family functions
  e(magazine)                   (*create)(void);
    struct e(magazine) *        (*allocate)(void);
  e(magazine)                   (*initialize)         ( struct e(magazine)* this );
  
  /// `struct magazine` instance functions
} IF_INTERNALIZED(extern *Magazine);

extern    void MAKE_EXTERNAL(register_Unique)(void);
extern    void MAKE_EXTERNAL(register_Magazine)(void);



# endif //!defined(MAGAZINE_DECLARATIONS)
# if !defined(MAGAZINE_IMPLEMENTATION) && !defined(DECLARATIONS) /* ===================================== BODY */
#   define    MAGAZINE_IMPLEMENTATION

# define DECLARATIONS
#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


static unique            Unique__create(void);
static struct unique *   Unique__allocate(void);
static unique            Unique__initialize        (struct unique* this);


    IF_EXTERNALIZED(static) struct Unique * // »
                                   Unique     = NULL;
void Paws__register_Unique(void) { Unique     = malloc(sizeof( struct Unique ));
  
  auto struct Unique // »
  data = {
    .create       = Unique__create,
    .allocate     = Unique__allocate,
    .initialize   = Unique__initialize };
  
  memcpy(Unique, &data, sizeof( struct Unique )); }


static magazine             Magazine__create(void);
static struct magazine *    Magazine__allocate(void);
static magazine             Magazine__initialize         (struct magazine* this);


      IF_EXTERNALIZED(static) struct Magazine * // »
                                     Magazine     = NULL;
void Paws__register_Magazine(void) { Magazine     = malloc(sizeof( struct Magazine ));
  
  auto struct Magazine // »
  data = {
    .create             = Magazine__create,
    .allocate           = Magazine__allocate,
    .initialize         = Magazine__initialize };
  
  memcpy(Magazine, &data, sizeof( struct Magazine )); }


unique Unique__create(void) {
  return Unique->initialize(Unique->allocate()); }

struct unique * Unique__allocate(void) {
  return malloc(sizeof( struct unique )); }

unique Unique__initialize(struct unique* this) {
  
  return this; }


magazine Magazine__create(void) {
  return Magazine->initialize(Magazine->allocate()); }

struct magazine * Magazine__allocate(void) {
  return malloc(sizeof( struct magazine )); }

magazine Magazine__initialize(struct magazine* this) {
  
  return this; }


# endif //!defined(MAGAZINE_IMPLEMENTATION) && !defined(DECLARATIONS)
