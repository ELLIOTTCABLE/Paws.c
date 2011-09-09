# if !defined(TYPE_DECLARATIONS)
#   define    TYPE_DECLARATIONS

# include "Core.h"


          struct e(blob);
typedef   struct e(blob)                    e(blob);

          struct e(metadata);
typedef   struct e(metadata)                e(metadata);

          struct e(representation);
typedef   struct e(representation) *        e(representation);


typedef   struct e(metadata) *              e(empty);

          struct e(label);
typedef   struct e(label) *                 e(label);

          struct e(execution);
typedef   struct e(execution) *             e(execution);


struct e(representation) {
  e(pointer)                    family;
  e(byte)                       name[64]; };

struct e(blob) {
  e(pointer) const              pointer;
  e(representation) const       isa; };


# endif //!defined(TYPE_DECLARATIONS)
