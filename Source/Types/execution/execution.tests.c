# include "execution.c"

# define DECLARATIONS
#   include "Cest.c/Source/Cest.c"
# undef  DECLARATIONS


# define A_SCOPE _make_a_scope()//;

static node _make_a_scope(void) { auto node // »
  a_scope = Node->scope();
  
  return a_scope; }

CEST(Execution, allocate) { auto struct execution * // »
  an_execution_pointer = Execution->allocate();
  
  // This is an absolutely paltry test, but I don’t know what else I can do here. /=
  ASSERT_NOT_NULL( an_execution_pointer );
  
  SUCCEED; }}

CEST(Execution, initialize) {
  auto execution an_execution = Execution->allocate();
  auto node a_node = Node->scope();
  
  Execution->initialize(an_execution, a_node);
  ASSERT_NULL( an_execution->content->first );
  ASSERT_NULL( an_execution->content->last );
  ASSERT_ZERO( an_execution->content->length );
  
  ASSERT_EQUAL( an_execution->position, a_node );
  ASSERT_NULL ( an_execution->juxtaposees );
  
  SUCCEED; }}

CEST(execution, thing) {
  auto execution an_execution = Execution->create(A_SCOPE);
  
  ASSERT_EQUAL( Execution->thing(an_execution).pointer, an_execution );
  ASSERT_EQUAL( Execution->thing(an_execution).isa,     Execution->Execution );
  
  SUCCEED; }}

CEST(execution, advance) {
  
  /*  For the purposes of this set of tests, we’re going to use the following mini-AST:
   *      
   *      { () ( () ) }
   *      
   *  Since `execution->advance()` does not actually *preform* any juxtapositions, we needn’t be concerned with
   *  the Paws semantics of this code; simply how `execution->advance()` will progressively crawl through it.
   */
  auto node   root = Node->scope();
  auto node  first = Node->expression(); Node->descend(root, first);
  auto node second = Node->expression(); Node->descend(root, second);
  auto node    sub = Node->expression(); Node->descend(second, sub);
  
  //        ┌┐ 
  //      { () ( () ) }
  auto execution an_execution = Execution->create(first);
  
  ASSERT_EQUAL( an_execution->position, first );
  ASSERT_NULL ( an_execution->juxtaposees );
  
  // Advancing pristine execution
  Execution->advance(an_execution);
  //           ┌────┐
  //      { () ( () ) }
  ASSERT_EQUAL   ( an_execution->position, second );
  ASSERT_NOT_NULL( an_execution->juxtaposees );
  
  PEND;
  // Advancing liminal execution
  
  // Advancing liminal execution (into sub-expression)
  
  // Advancing liminal execution (out of sub-expression)
  
  // Complete execution
  
  SUCCEED; }}
