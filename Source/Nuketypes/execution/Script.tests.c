# include "Script.c"

# define DECLARATIONS
#   include "Cest.c/Source/Cest.c"

#   include <stdlib.h>
# undef  DECLARATIONS


# define SOME_BLOB _make_some_blob()//;
static blob        _make_some_blob(void) { return (blob){ NULL, NULL }; }

CEST(Node, allocate) { auto struct node * // »
  a_node_pointer = Node->allocate();
  
  // This is an absolutely paltry test, but I don’t know what else I can do here. /=
  ASSERT_NOT_NULL( a_node_pointer );
  
  SUCCEED; }}

CEST(Node, initialize_terminal) { auto struct node * // »
  a_terminal_pointer = Node->allocate();
  
  auto blob some_blob = SOME_BLOB;
  Node->initialize_terminal(a_terminal_pointer, some_blob);
  ASSERT_NULL ( (*a_terminal_pointer).next );
  ASSERT_EQUAL( (*a_terminal_pointer).isa, TERMINAL );
  ASSERT_NOT  ( (*a_terminal_pointer).last );
  ASSERT_EQUAL(((*a_terminal_pointer).content.blob).pointer, some_blob.pointer );
  
  SUCCEED; }}

CEST(Node, initialize_expression) { auto struct node * // »
  an_expression_pointer = Node->allocate();
  
  Node->initialize_expression(an_expression_pointer);
  ASSERT_NULL ( (*an_expression_pointer).next );
  ASSERT_EQUAL( (*an_expression_pointer).isa, EXPRESSION );
  ASSERT_NOT  ( (*an_expression_pointer).last );
  ASSERT_NULL ( (*an_expression_pointer).content.child );
  
  SUCCEED; }}

CEST(node, parent) { auto node result;
  auto expression parent = Node->expression();
  auto expression child  = Node->expression(); child ->next = parent; child ->last = true;
                result          = Node->parent(child);
  ASSERT_EQUAL( result, parent );
  
  auto expression child1 = Node->expression(); 
  auto expression child2 = Node->expression(); child1->next = child2;
  auto expression child3 = Node->expression(); child2->next = child3;
                                               child3->next = parent; child3->last = true;
                result          = Node->parent(child1);
  ASSERT_EQUAL( result, parent );
  
  
  auto expression childA = Node->expression(); 
  auto expression childB = Node->expression(); childA->next = childB;
  auto expression childC = Node->expression(); childB->next = childC;
                                               childC->next = NULL;   childC->last = true;
               result           = Node->parent(childA);
  ASSERT_NULL( result );
  
  SUCCEED; }}

CEST(node, affix) { auto expression // »
  expression1   = Node->expression(),
  expression2   = Node->expression(),
  expression3   = Node->expression(),
  expressionA   = Node->expression(),
  expressionB   = Node->expression(),
  expressionC   = Node->expression(),
  expressionX   = Node->expression(),
  expressionY   = Node->expression();
  
  /* A basic single affix */
  /* > node1 [***]
   * 
   *         node3 [***]
   * > node1 ←┘    [***]
   * 
   * > node1 node3 [***]
   */
  Node->affix(expression1, expression3);
  ASSERT_EQUAL( expression1->next, expression3 ); ASSERT_NOT( expression1->last );
  ASSERT_NULL ( expression3->next );              ASSERT_NOT( expression3->last );
  
  
  /* A single affix that pushes old nodes */
  /* > node1 node3 [***]
   * 
   *         node2 [***]
   * > node1 ←┘    node3 [***]
   * 
   * > node1 node2 node3 [***]
   */
  Node->affix(expression1, expression2);
  ASSERT_EQUAL( expression1->next, expression2 ); ASSERT_NOT( expression1->last );
  ASSERT_EQUAL( expression2->next, expression3 ); ASSERT_NOT( expression2->last );
  ASSERT_NULL ( expression3->next );              ASSERT_NOT( expression3->last );
  
  
  Node->affix(expressionA, expressionB);
  Node->affix(expressionB, expressionC);
  
  /* A splicing-affix that pushes old nodes */
  /* > node1 node2 node3 [***]
   * 
   *       > nodeA nodeB nodeC [***]
   * > node1 node2 ←┘          node3 [***]
   * 
   * > node1 node2 nodeB nodeC node3 [***]
   *   nodeA [***]
   */
  Node->affix(expression2, expressionB);
  ASSERT_EQUAL( expression1->next, expression2 ); ASSERT_NOT( expression1->last );
  ASSERT_EQUAL( expression2->next, expressionB ); ASSERT_NOT( expression2->last );
  ASSERT_EQUAL( expressionB->next, expressionC ); ASSERT_NOT( expressionB->last );
  ASSERT_EQUAL( expressionC->next, expression3 ); ASSERT_NOT( expressionC->last );
  ASSERT_NULL ( expression3->next );              ASSERT_NOT( expression3->last );
  
  
  /* A single affix that pushes old nodes and advances `last` */
  /* > node1 node2 nodeB nodeC.
   * 
   *                           nodeY [***]
   * > node1 node2 nodeB nodeC. ←┘
   * 
   * > node1 node2 nodeB nodeC nodeY.
   */
  expressionC->last = true; // Above, was testing last-agnosticness. Below, testing last-handling.
  Node->affix(expressionC, expressionY);
  ASSERT_EQUAL( expression1->next, expression2 ); ASSERT_NOT( expression1->last );
  ASSERT_EQUAL( expression2->next, expressionB ); ASSERT_NOT( expression2->last );
  ASSERT_EQUAL( expressionB->next, expressionC ); ASSERT_NOT( expressionB->last );
  ASSERT_EQUAL( expressionC->next, expressionY ); ASSERT_NOT( expressionC->last );
  ASSERT_NULL ( expressionY->next );              ASSERT    ( expressionY->last );
  
  /* A single affix that pushes old nodes and doesn’t affect `last` */
  /* > node1 node2 nodeB nodeC nodeY.
   * 
   *                           nodeX [***]
   * > node1 node2 nodeB nodeC ←┘    nodeY.
   * 
   * > node1 node2 nodeB nodeC nodeX nodeY.
   */
  Node->affix(expressionC, expressionX);
  ASSERT_EQUAL( expression1->next, expression2 ); ASSERT_NOT( expression1->last );
  ASSERT_EQUAL( expression2->next, expressionB ); ASSERT_NOT( expression2->last );
  ASSERT_EQUAL( expressionB->next, expressionC ); ASSERT_NOT( expressionB->last );
  ASSERT_EQUAL( expressionC->next, expressionX ); ASSERT_NOT( expressionC->last );
  ASSERT_EQUAL( expressionX->next, expressionY ); ASSERT_NOT( expressionX->last );
  ASSERT_NULL ( expressionY->next );              ASSERT    ( expressionY->last );
  
  SOMEDAY;
  // test for errors here
  
  SUCCEED; }}

CEST(node, descend) { auto expression // »
  parent    = Node->expression(),
  child1    = Node->expression(),
  child2    = Node->expression();
  
  ASSERT_NULL ( parent->content.child );
  ASSERT_NULL ( child1->next );
  ASSERT_NOT  ( child1->last );
  ASSERT_NOT  ( child2->last );
  
  Node->descend(parent, child1);
  ASSERT_EQUAL( parent->content.child, child1 );
  ASSERT      ( child1->last );
  
  Node->descend(parent, child2);
  ASSERT_EQUAL( parent->content.child, child1 );
  ASSERT_EQUAL( child1->next, child2 );
  ASSERT_NOT  ( child1->last );
  ASSERT      ( child2->last );
  
  SOMEDAY;
  // test for errors here
  
  SUCCEED; }}
