# include "label.c"

# define DECLARATIONS
#   include "Cest.c/Source/Cest.c"
# undef  DECLARATIONS


CEST(Label, allocate) { auto struct label * // »
  a_label_struct = Label->allocate();
  
  // This is an absolutely paltry test, but I don’t know what else I can do here. /=
  ASSERT_NOT_NULL( a_label_struct );
  
  SUCCEED; }}

CEST(Label, initialize) { auto label a_label, another_label; auto magazine // »
  the_magazine = Magazine->create(1 << 4);
  a_label = Label->allocate();
  
  Label->initialize(a_label, the_magazine, "some content");
  ASSERT_NULL    ( a_label->content->first );
  ASSERT_NULL    ( a_label->content->last );
  ASSERT_ZERO    ( a_label->content->length );
  ASSERT_STREQUAL( Label->characters(a_label), "some content" );
  
  another_label = Label->allocate();
  
  Label->initialize(another_label, the_magazine, "some content");
  ASSERT_NOT_EQUAL( a_label,             another_label );
  ASSERT_EQUAL    ( a_label->characters, another_label->characters );
  
  SUCCEED; }}

CEST(label, thing) { auto label a_label; auto magazine // »
  the_magazine = Magazine->create(1 << 4);
  a_label = Label->create(the_magazine, "some content");
  
  ASSERT_EQUAL( Label->thing(a_label).pointer, a_label );
  ASSERT_EQUAL( Label->thing(a_label).isa,     Label->Label );
  
  SUCCEED; }}

CEST(label, equal) { auto label a_label, another_label, a_different_label; auto magazine // »
  the_magazine = Magazine->create(1 << 4);
  
  a_label =           Label->create(the_magazine, "some content");
  another_label =     Label->create(the_magazine, "some content");
  ASSERT_NOT_EQUAL( a_label, another_label );
  ASSERT          ( Label->equal(a_label, another_label) );
  
  a_different_label = Label->create(the_magazine, "different content");
  ASSERT_NOT_EQUAL( a_label, a_different_label );
  ASSERT_NOT      ( Label->equal(a_label, a_different_label) );
  
  SUCCEED; }}
