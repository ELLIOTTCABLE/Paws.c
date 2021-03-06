# if !defined(PAWS_DECLARATIONS)
#   define    PAWS_DECLARATIONS


# if defined(DECLARATIONS) && !defined(INTERNALIZE)
#   define PAWS_C__BEHEST__EXTERNALIZE
#   define EXTERNALIZE
# endif
#   if !defined(DECLARATIONS)
#     define PAWS_C__BEHEST
#     define DECLARATIONS
#   endif
#       include <stdbool.h>

/*#     include "Ancillary/Threading/Threading.c" */
/*#     include "Ancillary/Unit/Unit.c" */

#       include "Metadata/Metadata.c"

#       include "Nuketypes/label/label.c"
#       include "Nuketypes/execution/execution.c"

#       include "Core.h"
#       include "Nuketypes/Nuketypes.h"
#   if defined(PAWS_C__BEHEST)
#     undef DECLARATIONS
#   endif
# if defined(PAWS_C__BEHEST__EXTERNALIZE)
#   undef EXTERNALIZE
# endif


struct Paws {
  // Families ==========
  /// Ancillary families
/*struct E(Threading)    *Threading;*/
/*struct E(Unit)         *Unit;*/
  struct E(Metadata)     *Metadata;
  
  /// Fundamental nuketypes’ families
  struct E(Blob)         *Blob;
  struct E(Label)        *Label;
  struct E(Execution)    *Execution;
  
  /// Core nuclear extensions’ families
/*struct E(Number)       *Number;*/
} extern *Paws;


extern               void e(construct)(void);

extern bool   MAKE_EXTERNAL(constructed); // (see `void construct(void)` below.)



# endif //!defined(PAWS_DECLARATIONS)
# if !defined(PAWS_IMPLEMENTATION) && !defined(DECLARATIONS) /* ========================================= BODY */
#   define    PAWS_IMPLEMENTATION

# define DECLARATIONS
#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


static    void Paws__register_Paws(void);

                          struct Paws * // »
                                 Paws     = NULL;
void Paws__register_Paws(void) { Paws     = malloc(sizeof( struct Paws ));
  
  auto struct Paws // »
  data =
  /*.Threading    = NULL*/
  /*.Unit         = NULL*/
  { .Metadata     = NULL
    
  , .Blob         = NULL
  , .Label        = NULL
  , .Execution    = NULL
    
  /*.Number       = NULL*/ };
  
  memcpy(Paws, &data, sizeof( struct Paws ));
  
//Paws__register_Threading();
//Paws__register_Unit();
  Paws__register_Metadata();
  
  Paws__register_Blob();
  Paws__register_Label();
  Paws__register_Execution();
  
//Paws__register_Number();
}


void __constructor e(construct)(void) {
  if ( !MAKE_EXTERNAL(constructed) ) // »
    Paws__register_Paws();
  
  MAKE_EXTERNAL(constructed) = true; }

bool MAKE_EXTERNAL(constructed) = false;


# endif //!defined(PAWS_IMPLEMENTATION) && !defined(DECLARATIONS)
