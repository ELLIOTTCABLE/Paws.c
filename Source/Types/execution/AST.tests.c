# include "AST.c"

# define DECLARATIONS
#   include "Cest.c/Source/Cest.c"

#   include <stdlib.h>
# undef  DECLARATIONS


# define SOMETHING _make_something()//;

thing static _make_something(void) { auto struct thing // »
  something = { .pointer = NULL, .isa = NULL };
  
  return something; }

CEST(Node, allocate) { auto struct node * // »
  a_node_pointer = Node->allocate();
  
  // This is an absolutely paltry test, but I don’t know what else I can do here. /=
  ASSERT_NOT_NULL( a_node_pointer );
  
  SUCCEED; }}

CEST(Node, initialize_phrase) { auto struct node * // »
  a_node_pointer = Node->allocate();
  
  auto thing something = SOMETHING;
  Node->initialize_phrase(a_node_pointer, something);
  ASSERT_NULL ( (*a_node_pointer).next );
  ASSERT_EQUAL( (*a_node_pointer).isa, PHRASE );
  ASSERT_NOT  ( (*a_node_pointer).last );
  ASSERT_ZERO ( (*a_node_pointer).start );
  ASSERT_ZERO ( (*a_node_pointer).end );
  ASSERT_EQUAL(((*a_node_pointer).content.payload).pointer, something.pointer );
  
  SUCCEED; }}

CEST(Node, initialize_expression) { auto struct node * // »
  a_node_pointer = Node->allocate();
  
  Node->initialize_expression(a_node_pointer);
  ASSERT_NULL ( (*a_node_pointer).next );
  ASSERT_EQUAL( (*a_node_pointer).isa, EXPRESSION );
  ASSERT_NOT  ( (*a_node_pointer).last );
  ASSERT_ZERO ( (*a_node_pointer).start );
  ASSERT_ZERO ( (*a_node_pointer).end );
  ASSERT_NULL ( (*a_node_pointer).content.child );
  
  SUCCEED; }}

CEST(Node, initialize_scope) { auto struct node * // »
  a_node_pointer = Node->allocate();
  
  Node->initialize_scope(a_node_pointer);
  ASSERT_NULL ( (*a_node_pointer).next );
  ASSERT_EQUAL( (*a_node_pointer).isa, SCOPE );
  ASSERT_NOT  ( (*a_node_pointer).last );
  ASSERT_ZERO ( (*a_node_pointer).start );
  ASSERT_ZERO ( (*a_node_pointer).end );
  ASSERT_NULL ( (*a_node_pointer).content.child );
  
  SUCCEED; }}

CEST(Node, parent) { auto node result;
  auto node parent = Node->scope();
  auto node child  = Node->expression(); child ->next = parent; child ->last = true;
                result    = Node->parent(child);
  ASSERT_EQUAL( result, parent );
  
  auto node child1 = Node->expression(); 
  auto node child2 = Node->expression(); child1->next = child2;
  auto node child3 = Node->expression(); child2->next = child3;
                                         child3->next = parent; child3->last = true;
                result    = Node->parent(child1);
  ASSERT_EQUAL( result, parent );
  
  
  auto node childA = Node->expression(); 
  auto node childB = Node->expression(); childA->next = childB;
  auto node childC = Node->expression(); childB->next = childC;
                                         childC->next = NULL;   childC->last = true;
               result     = Node->parent(childA);
  ASSERT_NULL( result );
  
  SUCCEED; }}

CEST(Node, child) { auto node result;
  /* `EXPRESSION` as a child of a `SCOPE`: `(:SCOPE (:EXPRESSION))` */
  auto node scope       = Node->scope();
  auto node expression  = Node->expression(); expression->next = scope; expression->last = true;
                                              scope->content.child = expression;
                result  = Node->child(scope);
  ASSERT_EQUAL( result, expression );
  
  /* `EXPRESSION` as a child of an `EXPRESSION`: `(:EXPRESSION (:EXPRESSION))` */
  auto node parent_expression = Node->expression();
  auto node  child_expression = Node->expression();  child_expression->next = parent_expression;
                                                     child_expression->last = true;
                                                    parent_expression->content.child = child_expression;
                result = Node->child(parent_expression);
  ASSERT_EQUAL( result, child_expression );
  
  /* `EXPRESSION` with no child: `(:EXPRESSION)` */
  auto node another_expression = Node->expression();
               result          = Node->parent(another_expression);
  ASSERT_NULL( result );
  
  SOMEDAY;
  /* Erraneous `PHRASE` node: `(:PHRASE, <NULL>)` */
  //auto node phrase = Node->phrase(SOMETHING);
  //ASSERT_ERRANEOUS( Node->child(phrase) );
  
  SUCCEED; }}

CEST(Node, payload) { auto node phrase; auto thing result
, something = SOMETHING;
  phrase = Node->phrase(something);
  
  result = Node->payload(phrase);
  ASSERT_EQUAL( result.pointer, something.pointer );
  
  SOMEDAY;
  /* Erraneous `EXPRESSION` node: `(:EXPRESSION)` */
  //auto node expression = Node->expression();
  //ASSERT_ERRANEOUS( Node->payload(expression) );
  
  /* Erraneous `SCOPE` node: `(:SCOPE)` */
  //auto node scope = Node->scope();
  //ASSERT_ERRANEOUS( Node->payload(scope) );
  
  SUCCEED; }}

CEST(Node, affix) { auto node // »
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

CEST(Node, descend) { auto node // »
  scope         = Node->scope(),
  expression1   = Node->expression(),
  expression2   = Node->expression();
  
  ASSERT_NULL ( scope->content.child );
  ASSERT_NULL ( expression1->next );
  ASSERT_NOT  ( expression1->last );
  ASSERT_NOT  ( expression2->last );
  
  Node->descend(scope, expression1);
  ASSERT_EQUAL( scope->content.child, expression1 );
  ASSERT      ( expression1->last );
  
  Node->descend(scope, expression2);
  ASSERT_EQUAL( scope->content.child, expression1 );
  ASSERT_EQUAL( expression1->next, expression2 );
  ASSERT_NOT  ( expression1->last );
  ASSERT      ( expression2->last );
  
  SOMEDAY;
  // test for errors here
  
  SUCCEED; }}
