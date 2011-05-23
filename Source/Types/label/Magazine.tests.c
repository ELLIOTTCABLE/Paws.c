# include "Magazine.c"

# define DECLARATIONS
#   include "Cest.c/Source/Cest.c"
# undef  DECLARATIONS


CEST(Magazine, allocate) { auto struct magazine * // »
  a_magazine_pointer = Magazine->allocate();
  
  // This is an absolutely paltry test, but I don’t know what else I can do here. /=
  ASSERT_NOT_NULL( a_magazine_pointer );
  
  SUCCEED; }}

CEST(Magazine, initialize) { auto struct magazine * // »
  a_magazine_pointer = Magazine->allocate();
  
  Magazine->initialize(a_magazine_pointer);
//ASSERT_NULL( (*a_magazine_pointer).first );
//ASSERT_NULL( (*a_magazine_pointer).last );
//ASSERT_ZERO( (*a_magazine_pointer).length );
  
  SUCCEED; }}


CEST(Unique, allocate) { auto struct unique * // »
  a_unique_pointer = Unique->allocate();
  
  // This is an absolutely paltry test, but I don’t know what else I can do here. /=
  ASSERT_NOT_NULL( a_unique_pointer );
  
  SUCCEED; }}

CEST(Unique, initialize) { auto struct unique * // »
  a_unique_pointer = Unique->allocate();
  
  Unique->initialize(a_unique_pointer);
//ASSERT_NULL( (*a_unique_pointer).next );
//ASSERT_NULL( (*a_unique_pointer).previous );
  
  SUCCEED; }}
