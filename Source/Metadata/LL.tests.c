# include "LL.c"

# define DECLARATIONS
#   include "Cest.c/Source/Cest.c"
#   include <string.h>
# undef  DECLARATIONS


# define SOME_BLOB _make_some_blob()//;
static blob        _make_some_blob(void) { return (blob){ NULL, NULL }; }

CEST(LL, allocate) { auto struct ll * // »
  a_ll_pointer = LL->allocate();
  
  // This is an absolutely paltry test, but I don’t know what else I can do here. /=
  ASSERT_NOT_NULL( a_ll_pointer );
  
  SUCCEED; }}

CEST(LL, initialize) { auto struct ll * // »
  a_ll_pointer = LL->allocate();
  
  LL->initialize(a_ll_pointer);
  ASSERT_NULL( (*a_ll_pointer).first );
  ASSERT_NULL( (*a_ll_pointer).last );
  ASSERT_ZERO( (*a_ll_pointer).length );
  
  SUCCEED; }}

CEST(ll, anterior_insert) { auto ll a_ll; auto element element1, element2, element3, elementA;
  a_ll = LL->create();
  element1 = Element->create(SOME_BLOB); LL->affix(a_ll, element1);
  element2 = Element->create(SOME_BLOB); LL->affix(a_ll, element2);
  element3 = Element->create(SOME_BLOB); LL->affix(a_ll, element3);
  elementA = Element->create(SOME_BLOB);
  
  /* TODO: Error condition */
  LL->anterior_insert(a_ll, elementA, 0);
  ASSERT_EQUAL( LL->at(a_ll, 0), element1 );
  
  LL->anterior_insert(a_ll, elementA, 1);
  ASSERT_EQUAL( LL->at(a_ll, 0), element1 );
  ASSERT_EQUAL( LL->at(a_ll, 1), elementA );
  ASSERT_EQUAL( LL->at(a_ll, 2), element2 );
  
  SUCCEED; }}

CEST(ll, posterior_insert) { auto ll a_ll; auto element element1, element2, element3, elementA;
  a_ll = LL->create();
  element1 = Element->create(SOME_BLOB); LL->affix(a_ll, element1);
  element2 = Element->create(SOME_BLOB); LL->affix(a_ll, element2);
  element3 = Element->create(SOME_BLOB); LL->affix(a_ll, element3);
  elementA = Element->create(SOME_BLOB);
  
  /* TODO: Error condition */
  LL->posterior_insert(a_ll, elementA, a_ll->length);
  ASSERT_EQUAL( LL->at(a_ll, 0), element1 );
  
  LL->posterior_insert(a_ll, elementA, 1);
  ASSERT_EQUAL( LL->at(a_ll, 0), element1 );
  ASSERT_EQUAL( LL->at(a_ll, 1), elementA );
  ASSERT_EQUAL( LL->at(a_ll, 2), element2 );
  
  SUCCEED; }}

CEST(ll, prefix) { auto ll a_ll; auto element element1, element2, element3;
  a_ll = LL->create();
  element1 = Element->create(SOME_BLOB);
  element2 = Element->create(SOME_BLOB);
  element3 = Element->create(SOME_BLOB);
  
  LL->prefix(a_ll, element3);
  ASSERT_EQUAL( a_ll->length, 1 );
  ASSERT_EQUAL( a_ll->first,  element3 );
  ASSERT_EQUAL( a_ll->last,   element3 );
  
  LL->prefix(a_ll, element2);
  ASSERT_EQUAL( a_ll->length, 2 );
  ASSERT_EQUAL( a_ll->first,  element2 );
  ASSERT_EQUAL( a_ll->last,   element3 );
  
  LL->prefix(a_ll, element1);
  ASSERT_EQUAL( a_ll->length, 3 );
  ASSERT_EQUAL( a_ll->first,  element1 );
  ASSERT_EQUAL( a_ll->last,   element3 );
  
  SUCCEED; }}

CEST(ll, affix) { auto ll a_ll; auto element element1, element2, element3;
  a_ll = LL->create();
  element1 = Element->create(SOME_BLOB);
  element2 = Element->create(SOME_BLOB);
  element3 = Element->create(SOME_BLOB);
  
  LL->affix(a_ll, element1);
  ASSERT_EQUAL( a_ll->length, 1 );
  ASSERT_EQUAL( a_ll->first,  element1 );
  ASSERT_EQUAL( a_ll->last,   element1 );
  
  LL->affix(a_ll, element2);
  ASSERT_EQUAL( a_ll->length, 2 );
  ASSERT_EQUAL( a_ll->first,  element1 );
  ASSERT_EQUAL( a_ll->last,   element2 );
  
  LL->affix(a_ll, element3);
  ASSERT_EQUAL( a_ll->length, 3 );
  ASSERT_EQUAL( a_ll->first,  element1 );
  ASSERT_EQUAL( a_ll->last,   element3 );
  
  SUCCEED; }}

CEST(ll, at) { auto ll a_ll; auto element element1, element2, element3;
  a_ll = LL->create();
  
  /* Empty `ll`s */
  ASSERT_NULL( LL->at(a_ll, 5) );
  ASSERT_NULL( LL->at(a_ll, 1) );
  ASSERT_NULL( LL->at(a_ll, 0) );
  
  element1 = Element->create(SOME_BLOB); LL->affix(a_ll, element1);
  element2 = Element->create(SOME_BLOB); LL->affix(a_ll, element2);
  element3 = Element->create(SOME_BLOB); LL->affix(a_ll, element3);
  
  /* Positive indicies */
  ASSERT_EQUAL( LL->at(a_ll, 0), element1 );
  ASSERT_EQUAL( LL->at(a_ll, 1), element2 );
  ASSERT_EQUAL( LL->at(a_ll, 2), element3 );
  
  /* OOB indicies */
  ASSERT_NULL( LL->at(a_ll, 5) );
  ASSERT_NULL( LL->at(a_ll, 4) );
  
  SUCCEED; }}


CEST(Element, allocate) { auto struct element * // »
  an_element_pointer = Element->allocate();
  
  // This is an absolutely paltry test, but I don’t know what else I can do here. /=
  ASSERT_NOT_NULL( an_element_pointer );
  
  SUCCEED; }}

CEST(Element, initialize) { auto struct element * // »
  an_element_pointer = Element->allocate();
  
  Element->initialize(an_element_pointer, SOME_BLOB);
  ASSERT_NULL( (*an_element_pointer).next );
  ASSERT_NULL( (*an_element_pointer).previous );
  
  SUCCEED; }}

CEST(element, prefix) { auto element // »
  element1 = Element->create(SOME_BLOB),
  element2 = Element->create(SOME_BLOB),
  element3 = Element->create(SOME_BLOB),
  elementA = Element->create(SOME_BLOB),
  elementB = Element->create(SOME_BLOB),
  elementC = Element->create(SOME_BLOB);
  
  
  /* A basic single prefix */
  /* > [***] node3
   * 
   *         node1
   * > [***]    └→ node3
   * 
   * > [***] node1 node3
   */
  Element->prefix(element3, element1);
  ASSERT_NULL ( element1->previous );           ASSERT_EQUAL( element1->next, element3 );
  ASSERT_EQUAL( element3->previous, element1 ); ASSERT_NULL ( element3->next );
  
  
  /* A single prefix that pushes old nodes */
  /* > [***] node1 node3
   * 
   *               node2
   * > [***] node1    └→ node3
   * 
   * > [***] node1 node2 node3
   */
  Element->prefix(element3, element2);
  ASSERT_NULL ( element1->previous );           ASSERT_EQUAL( element1->next, element2 );
  ASSERT_EQUAL( element2->previous, element1 ); ASSERT_EQUAL( element2->next, element3 );
  ASSERT_EQUAL( element3->previous, element2 ); ASSERT_NULL ( element3->next );
  
  
  Element->affix(elementA, elementB);
  Element->affix(elementB, elementC);
  
  /* A splicing-prefix that pushes old nodes */
  /* > [***] node1 node2 node3
   * 
   * > [***] nodeA nodeB nodeC
   * > [***] node1    └→ node2 node3
   * 
   *   [***] node1   …   [***] nodeC
   * > [***] nodeA nodeB node2 node3
   */
  Element->prefix(element2, elementB);
  ASSERT_NULL ( elementA->previous );           ASSERT_EQUAL( elementA->next, elementB );
  ASSERT_EQUAL( elementB->previous, elementA ); ASSERT_EQUAL( elementB->next, element2 );
  ASSERT_EQUAL( element2->previous, elementB ); ASSERT_EQUAL( element2->next, element3 );
  ASSERT_EQUAL( element3->previous, element2 ); ASSERT_NULL ( element3->next );
  
  ASSERT_NOT_EQUAL( elementC->previous, elementB );
  ASSERT_NOT_EQUAL( element1->next,     element2 );
  
  
  SUCCEED; }}

CEST(element, affix) { auto element // »
  element1 = Element->create(SOME_BLOB),
  element2 = Element->create(SOME_BLOB),
  element3 = Element->create(SOME_BLOB),
  elementA = Element->create(SOME_BLOB),
  elementB = Element->create(SOME_BLOB),
  elementC = Element->create(SOME_BLOB);
  
  
  /* A basic single affix */
  /* > node1 [***]
   * 
   *         node3
   * > node1 ←┘    [***]
   * 
   * > node1 node3 [***]
   */
  Element->affix(element1, element3);
  ASSERT_NULL ( element1->previous );           ASSERT_EQUAL( element1->next, element3 );
  ASSERT_EQUAL( element3->previous, element1 ); ASSERT_NULL ( element3->next );
  
  
  /* A single affix that pushes old nodes */
  /* > node1 node3 [***]
   * 
   *         node2
   * > node1 ←┘    node3 [***]
   * 
   * > node1 node2 node3 [***]
   */
  Element->affix(element1, element2);
  ASSERT_NULL ( element1->previous );           ASSERT_EQUAL( element1->next, element2 );
  ASSERT_EQUAL( element2->previous, element1 ); ASSERT_EQUAL( element2->next, element3 );
  ASSERT_EQUAL( element3->previous, element2 ); ASSERT_NULL ( element3->next );
  
  
  Element->affix(elementA, elementB);
  Element->affix(elementB, elementC);
  
  /* A splicing-affix that pushes old nodes */
  /* > node1 node2 node3 [***]
   * 
   *       > nodeA nodeB nodeC [***]
   * > node1 node2 ←┘          node3 [***]
   * 
   * > node1 node2 nodeB nodeC [***]
   *   nodeA [***]   …   node3 [***]
   */
  Element->affix(element2, elementB);
  ASSERT_NULL ( element1->previous );           ASSERT_EQUAL( element1->next, element2 );
  ASSERT_EQUAL( element2->previous, element1 ); ASSERT_EQUAL( element2->next, elementB );
  ASSERT_EQUAL( elementB->previous, element2 ); ASSERT_EQUAL( elementB->next, elementC );
  ASSERT_EQUAL( elementC->previous, elementB ); ASSERT_NULL ( elementC->next );
  
  ASSERT_NOT_EQUAL( element3->previous, element2 );
  ASSERT_NOT_EQUAL( elementA->next,     elementB );
  
  
  SUCCEED; }}
