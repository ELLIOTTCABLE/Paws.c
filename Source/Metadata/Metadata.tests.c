# include "Metadata.c"

# define DECLARATIONS
#   include "Cest.c/Source/Cest.c"
# undef  DECLARATIONS


CEST(Blob, allocate) { auto struct metadata * // »
  an_empty_struct = Blob->allocate();
  
  // This is an absolutely paltry test, but I don’t know what else I can do here. /=
  ASSERT_NOT_NULL( an_empty_struct );
  
  SUCCEED; }}

CEST(Metadata, initialize) { auto struct metadata * // »
  an_empty_struct = Blob->allocate();
  
  Metadata->initialize(an_empty_struct);
  ASSERT_NULL( an_empty_struct->metadata->first );
  ASSERT_NULL( an_empty_struct->metadata->last );
  ASSERT_ZERO( an_empty_struct->metadata->length );
  
  SUCCEED; }}

CEST(blob, as_blob) { auto empty // »
  an_empty = Blob->empty();
  
  ASSERT_EQUAL( Blob->as_blob(an_empty).pointer, an_empty );
  ASSERT_NULL ( Blob->as_blob(an_empty).isa );
  
  SUCCEED; }}

CEST(metadata, insert) {
  auto empty an_empty = Blob->empty();
  auto blob blob1 = Blob->as_blob(Blob->empty());
  auto blob blob2 = Blob->as_blob(Blob->empty());
  auto blob blob3 = Blob->as_blob(Blob->empty());
  auto blob blob4 = Blob->as_blob(Blob->empty());
  
  /* Insert into empty list */
  Metadata->insert(an_empty, blob2, 0);
  ASSERT_EQUAL( Metadata->at(an_empty, 0).pointer, blob2.pointer );
  ASSERT_EQUAL( an_empty->metadata->length, 1 );
  
  /* Insert onto the front of fork */
  Metadata->insert(an_empty, blob1, 0);
  ASSERT_EQUAL( Metadata->at(an_empty, 0).pointer, blob1.pointer );
  ASSERT_EQUAL( an_empty->metadata->length, 2 );
  
  /* Insert onto the end of fork */
  Metadata->insert(an_empty, blob4, 2);
  ASSERT_EQUAL( Metadata->at(an_empty, 2).pointer, blob4.pointer );
  ASSERT_EQUAL( an_empty->metadata->length, 3 );
  
  /* Insert into fork */
  Metadata->insert(an_empty, blob3, 2);
  ASSERT_EQUAL( Metadata->at(an_empty, 2).pointer, blob3.pointer );
  ASSERT_EQUAL( an_empty->metadata->length, 4 );
  
  SUCCEED; }}

CEST(metadata, prefix) {
  auto empty an_empty = Blob->empty();
  auto blob blob1 = Blob->as_blob(Blob->empty());
  auto blob blob2 = Blob->as_blob(Blob->empty());
  auto blob blob3 = Blob->as_blob(Blob->empty());
  
  Metadata->prefix(an_empty, blob3);
  ASSERT_EQUAL( Metadata->at(an_empty, 0).pointer, blob3.pointer );
  ASSERT_EQUAL( an_empty->metadata->length, 1 );
  
  Metadata->prefix(an_empty, blob2);
  ASSERT_EQUAL( Metadata->at(an_empty, 0).pointer, blob2.pointer );
  ASSERT_EQUAL( an_empty->metadata->length, 2 );
  
  Metadata->prefix(an_empty, blob1);
  ASSERT_EQUAL( Metadata->at(an_empty, 0).pointer, blob1.pointer );
  ASSERT_EQUAL( an_empty->metadata->length, 3 );
  
  SUCCEED; }}

CEST(metadata, affix) {
  auto empty a_empty = Blob->empty();
  auto blob blob1 = Blob->as_blob(Blob->empty());
  auto blob blob2 = Blob->as_blob(Blob->empty());
  auto blob blob3 = Blob->as_blob(Blob->empty());
  
  Metadata->affix(a_empty, blob1);
  ASSERT_EQUAL( Metadata->at(a_empty, 0).pointer, blob1.pointer );
  ASSERT_EQUAL( a_empty->metadata->length, 1 );
  
  Metadata->affix(a_empty, blob2);
  ASSERT_EQUAL( Metadata->at(a_empty, 1).pointer, blob2.pointer );
  ASSERT_EQUAL( a_empty->metadata->length, 2 );
  
  Metadata->affix(a_empty, blob3);
  ASSERT_EQUAL( Metadata->at(a_empty, 2).pointer, blob3.pointer );
  ASSERT_EQUAL( a_empty->metadata->length, 3 );
  
  SUCCEED; }}

CEST(metadata, at) {
  auto empty a_empty = Blob->empty();
  
  /* Empty `empty`s */
  ASSERT_NULL( Metadata->at(a_empty, 5).pointer );
  ASSERT_NULL( Metadata->at(a_empty, 4).pointer );
  ASSERT_NULL( Metadata->at(a_empty, 1).pointer );
  ASSERT_NULL( Metadata->at(a_empty, 0).pointer );
  
  auto blob blob1 = Blob->as_blob(Blob->empty()); Metadata->affix(a_empty, blob1);
  auto blob blob2 = Blob->as_blob(Blob->empty()); Metadata->affix(a_empty, blob2);
  auto blob blob3 = Blob->as_blob(Blob->empty()); Metadata->affix(a_empty, blob3);
  
  /* Positive indicies */
  ASSERT_EQUAL( Metadata->at(a_empty, 0).pointer, blob1.pointer );
  ASSERT_EQUAL( Metadata->at(a_empty, 1).pointer, blob2.pointer );
  ASSERT_EQUAL( Metadata->at(a_empty, 2).pointer, blob3.pointer );
  
  /* OOB indicies */
  ASSERT_NULL( Metadata->at(a_empty, 5).pointer );
  ASSERT_NULL( Metadata->at(a_empty, 4).pointer );
  
  SUCCEED; }}
