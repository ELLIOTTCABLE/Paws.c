# if !defined(TYPE_DECLARATIONS)
#   define    TYPE_DECLARATIONS

# include "Core.h"


          struct e(fork);
typedef   struct e(fork) *                  e(fork);

          struct e(label);
typedef   struct e(label) *                 e(label);

          struct e(execution);
typedef   struct e(execution) *             e(execution);


          struct e(thing);
typedef   struct e(thing)                   e(thing);

          struct e(typeRepresentation);
typedef   struct e(typeRepresentation) *    e(typeRepresentation);


struct e(typeRepresentation) {
  e(pointer)                    family;
  e(byte)                       name[64]; };

struct e(thing) {
  e(pointer) const              pointer;
  e(typeRepresentation) const   isa; };


# endif //!defined(TYPE_DECLARATIONS)
