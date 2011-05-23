# include "label.c"

# define DECLARATIONS
#   include "Cest.c/Source/Cest.c"
# undef  DECLARATIONS


CEST(Label, allocate) { auto struct label * // »
  a_label_struct = Label->allocate();
  
  // This is an absolutely paltry test, but I don’t know what else I can do here. /=
  ASSERT_NOT_NULL( a_label_struct );
  
  SUCCEED; }}

CEST(Label, initialize) { auto label // »
  a_label = Label->allocate();
  
  Label->initialize(a_label);
  ASSERT_NULL( a_label->content->first );
  ASSERT_NULL( a_label->content->last );
  ASSERT_ZERO( a_label->content->length );
  
  SUCCEED; }}

CEST(label, thing) { auto label // »
  a_label = Label->create();
  
  ASSERT_EQUAL( Label->thing(a_label).pointer, a_label );
  ASSERT_EQUAL( Label->thing(a_label).isa,     Label->Label );
  
  SUCCEED; }}
