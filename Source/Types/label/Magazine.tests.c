# include "Magazine.c"

# define DECLARATIONS
#   include "Cest.c/Source/Cest.c"
#   include <stdio.h>
# undef  DECLARATIONS


CEST(Unique, allocate) { auto struct unique * // »
  a_unique_pointer = Unique->allocate();
  
  // This is an absolutely paltry test, but I don’t know what else I can do here. /=
  ASSERT_NOT_NULL( a_unique_pointer );
  
  SUCCEED; }}

CEST(Unique, initialize) { auto struct unique * // »
  a_unique_pointer = Unique->allocate();
  
  Unique->initialize(a_unique_pointer, "foo", 4);
  ASSERT_STREQUAL( (*a_unique_pointer).content, "foo" );
  ASSERT_EQUAL   ( (*a_unique_pointer).bytes, 4 );
  
  SUCCEED; }}

CEST(unique, of) { auto unique result, unique4, unique5;
  auto unique unique1 = Unique->create("widget", 7);
  auto unique unique2 = Unique->create("qux", 4);  unique1->overflow = unique2;
  auto unique unique3 = Unique->create("quux", 5); unique2->overflow = unique3;
  
  // `this` matches
  result = Unique->of(unique1, "widget", 7);
  ASSERT_EQUAL( result, unique1 );
  
  // Element in list matches
  result = Unique->of(unique1, "quux", 5);
  ASSERT_EQUAL( result, unique3 );
  
  // No content match, but a length match
  unique4 = Unique->of(unique1, "foobar", 7);
  ASSERT_NOT_EQUAL( unique4, unique1 );
  ASSERT_NOT_EQUAL( unique4, unique2 );
  ASSERT_NOT_EQUAL( unique4, unique3 );
  ASSERT_EQUAL    ( unique4, unique3->overflow );
  ASSERT_STREQUAL ( unique4->content, "foobar" );
  ASSERT_EQUAL    ( unique4->bytes, 7 );
  
  // No content match, no length match
  unique5 = Unique->of(unique1, "abcde", 6);
  ASSERT_NOT_EQUAL( unique5, unique1 );
  ASSERT_NOT_EQUAL( unique5, unique2 );
  ASSERT_NOT_EQUAL( unique5, unique3 );
  ASSERT_NOT_EQUAL( unique5, unique4 );
  ASSERT_EQUAL    ( unique5, unique4->overflow );
  ASSERT_STREQUAL ( unique5->content, "abcde" );
  ASSERT_EQUAL    ( unique5->bytes, 6 );
  
  SUCCEED; }}


CEST(Magazine, allocate) { auto struct magazine * // »
  a_magazine_pointer = Magazine->allocate();
  
  // This is an absolutely paltry test, but I don’t know what else I can do here. /=
  ASSERT_NOT_NULL( a_magazine_pointer );
  
  SUCCEED; }}

CEST(Magazine, initialize) { auto struct magazine * // »
  a_magazine_pointer = Magazine->allocate();
  
  Magazine->initialize(a_magazine_pointer, 16);
  ASSERT_NOT_NULL( (*a_magazine_pointer).uniques );
  ASSERT_EQUAL   ( (*a_magazine_pointer).bits, 4 );
  
  SUCCEED; }}

CEST(magazine, of) { auto unique unique1, unique2, unique3, result1, result2, result3; auto magazine // »
  the_magazine = Magazine->create(64);
  
  unique1 = Magazine->of(the_magazine, "foo", 4);
  ASSERT_NOT_NULL ( unique1 );
  ASSERT_STREQUAL ( unique1->content, "foo" );
  ASSERT_EQUAL    ( unique1->bytes, 4 );
  
  unique2 = Magazine->of(the_magazine, "bar", 4);
  ASSERT_NOT_NULL ( unique2 );
  ASSERT_STREQUAL ( unique2->content, "bar" );
  ASSERT_EQUAL    ( unique2->bytes, 4 );
  
  unique3 = Magazine->of(the_magazine, "widget", 7);
  ASSERT_NOT_NULL ( unique3 );
  ASSERT_STREQUAL ( unique3->content, "widget" );
  ASSERT_EQUAL    ( unique3->bytes, 7 );
  
  result1 = Magazine->of(the_magazine, "foo", 4);
  ASSERT_EQUAL( unique1, result1 );
  
  result2 = Magazine->of(the_magazine, "bar", 4);
  ASSERT_EQUAL( unique2, result2 );
  
  result3 = Magazine->of(the_magazine, "widget", 7);
  ASSERT_EQUAL( unique3, result3 );
  
  // TODO: Add `SANITY()` checks for, well, everything.
  SUCCEED; }}

CEST(magazine, _hash) { auto magazine_length a_hash;
  
  a_hash = _magazine__hash(Magazine->create(1<<3), "foobar", 7);
  ASSERT( a_hash <= 1 << 3);
  //printf("2³: 0x%X, ", a_hash);
  
  a_hash = _magazine__hash(Magazine->create(1<<9), "foobar", 7);
  ASSERT( a_hash <= 1 << 9);
  //printf("2⁹: 0x%X, ", a_hash);
  
  a_hash = _magazine__hash(Magazine->create(1<<15), "foobar", 7);
  ASSERT( a_hash <= 1 << 15);
  //printf("2¹⁵: 0x%X",  a_hash);
  
  // TODO: Add `SANITY()` checks for hash equality and zero-ness.
  SUCCEED; }}
