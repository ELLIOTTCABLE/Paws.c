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
  ASSERT_EQUAL(((*a_terminal_pointer)._.blob).pointer, some_blob.pointer );
  
  SUCCEED; }}

CEST(Node, initialize_expression) { auto struct node * // »
  an_expression_pointer = Node->allocate();
  
  Node->initialize_expression(an_expression_pointer);
  ASSERT_NULL ( (*an_expression_pointer).next );
  ASSERT_EQUAL( (*an_expression_pointer).isa, EXPRESSION );
  ASSERT_NOT  ( (*an_expression_pointer).last );
  ASSERT_NULL ( (*an_expression_pointer)._.skip );
  
  SUCCEED; }}

CEST(node, affix) { auto node // »
  terminal1     = Node->terminal(SOME_BLOB),
  expression2   = Node->expression(),
  terminal3     = Node->terminal(SOME_BLOB),
  expressionA   = Node->expression(),
  terminalB     = Node->terminal(SOME_BLOB),
  expressionC   = Node->expression(),
  terminalX     = Node->terminal(SOME_BLOB),
  expressionY   = Node->expression();
  
  /* A basic single affix */
  /* > terminal1 [***]
   * 
   *             terminal3 [***]
   * > terminal1 ←┘        [***]
   * 
   * > terminal1 terminal3 [***]
   */
  Node->affix(terminal1, terminal3);
  ASSERT_EQUAL( terminal1->next, terminal3 ); ASSERT_NOT( terminal1->last );
  ASSERT_NULL ( terminal3->next );            ASSERT_NOT( terminal3->last );
  
  
  /* A single affix that pushes old nodes */
  /* > terminal1 terminal3 [***]
   * 
   *             expression2 [***]
   * > terminal1 ←┘          terminal3 [***]
   * 
   * > terminal1 expression2 terminal3 [***]
   */
  Node->affix(terminal1, expression2);
  ASSERT_EQUAL( terminal1->next,     expression2 ); ASSERT_NOT( terminal1->last   );
  ASSERT_EQUAL( expression2->_.skip, terminal3   ); ASSERT_NOT( expression2->last );
  ASSERT_NULL ( terminal3->next );                  ASSERT_NOT( terminal3->last   );
  
  
  Node->affix(expressionA, terminalB);
  Node->affix(terminalB, expressionC);
  
  /* A splicing-affix that pushes old nodes */
  /* > terminal1 expression2 terminal3 [***]
   * 
   *           > expressionA terminalB expressionC [***]
   * > terminal1 expression2 ←┘                    terminal3 [***]
   * 
   * > terminal1 expression2 terminalB expressionC terminal3 [***]
   *   expressionA [***]
   */
  Node->affix(expression2, terminalB);
  ASSERT_EQUAL( terminal1->next,     expression2 ); ASSERT_NOT( terminal1->last   );
  ASSERT_EQUAL( expression2->_.skip, terminalB   ); ASSERT_NOT( expression2->last );
  ASSERT_EQUAL( terminalB->next,     expressionC ); ASSERT_NOT( terminalB->last   );
  ASSERT_EQUAL( expressionC->_.skip, terminal3   ); ASSERT_NOT( expressionC->last );
  ASSERT_NULL ( terminal3->next );                  ASSERT_NOT( terminal3->last   );
  
  
  /* A single affix that pushes old nodes and advances `last` */
  /* > terminal1 expression2 terminalB expressionC.
   * 
   *                                               expressionY [***]
   * > terminal1 expression2 terminalB expressionC ←┘         .
   * 
   * > terminal1 expression2 terminalB expressionC expressionY.
   */
  expressionC->last = true; // Above, was testing last-agnosticness. Below, testing last-handling.
  Node->affix(expressionC, expressionY);
  ASSERT_EQUAL( terminal1->next,     expression2 ); ASSERT_NOT( terminal1->last   );
  ASSERT_EQUAL( expression2->_.skip, terminalB   ); ASSERT_NOT( expression2->last );
  ASSERT_EQUAL( terminalB->next,     expressionC ); ASSERT_NOT( terminalB->last   );
  ASSERT_EQUAL( expressionC->_.skip, expressionY ); ASSERT_NOT( expressionC->last );
  ASSERT_NULL ( expressionY->next );                ASSERT    ( expressionY->last );
  
  /* A single affix that pushes old nodes and doesn’t affect `last` */
  /* > terminal1 expression2 terminalB expressionC expressionY.
   * 
   *                                               terminalX [***]
   * > terminal1 expression2 terminalB expressionC ←┘        expressionY.
   * 
   * > terminal1 expression2 terminalB expressionC terminalX expressionY.
   */
  Node->affix(expressionC, terminalX);
  ASSERT_EQUAL( terminal1->next,     expression2 ); ASSERT_NOT( terminal1->last   );
  ASSERT_EQUAL( expression2->_.skip, terminalB   ); ASSERT_NOT( expression2->last );
  ASSERT_EQUAL( terminalB->next,     expressionC ); ASSERT_NOT( terminalB->last   );
  ASSERT_EQUAL( expressionC->_.skip, terminalX   ); ASSERT_NOT( expressionC->last );
  ASSERT_EQUAL( terminalX->next,     expressionY ); ASSERT_NOT( terminalX->last   );
  ASSERT_NULL ( expressionY->next );                ASSERT    ( expressionY->last );
  
  SUCCEED; }}

CEST(node, descend) { auto node // »
  parent      = Node->expression(),
  expression1 = Node->expression(),
  terminal2   = Node->terminal(SOME_BLOB);
  
  ASSERT_NULL ( parent->next );
  ASSERT_NULL ( expression1->_.skip );
  ASSERT_NOT  ( expression1->last );
  ASSERT_NOT  ( terminal2->last );
  
  Node->descend(parent, expression1);
  ASSERT_EQUAL( parent->next, expression1 );
  ASSERT      ( expression1->last );
  
  Node->descend(parent, terminal2);
  ASSERT_EQUAL( parent->next, expression1 );
  ASSERT_EQUAL( expression1->_.skip, terminal2 );
  ASSERT_NOT  ( expression1->last );
  ASSERT      ( terminal2->last );
  
  SUCCEED; }}
