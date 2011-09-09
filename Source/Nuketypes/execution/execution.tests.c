# include "execution.c"

# define DECLARATIONS
#   include "Cest.c/Source/Cest.c"
# undef  DECLARATIONS


# define SOME_EXPRESSION _make_an_expression()//;

static node _make_an_expression(void) { auto expression // »
  an_expression = Node->expression();
  
  return an_expression; }

CEST(Execution, allocate) { auto struct execution * // »
  an_execution_pointer = Execution->allocate();
  
  // This is an absolutely paltry test, but I don’t know what else I can do here. /=
  ASSERT_NOT_NULL( an_execution_pointer );
  
  SUCCEED; }}

CEST(Execution, initialize) {
  auto execution an_execution = Execution->allocate();
  auto expression an_expression = Node->expression();
  
  Execution->initialize(an_execution, an_expression);
  ASSERT_NULL( an_execution->metadata->first );
  ASSERT_NULL( an_execution->metadata->last );
  ASSERT_ZERO( an_execution->metadata->length );
  
  ASSERT_EQUAL( an_execution->position, an_expression );
  ASSERT_NULL ( an_execution->juxtaposees );
  
  SUCCEED; }}

CEST(execution, as_blob) {
  auto execution an_execution = Execution->create(SOME_EXPRESSION);
  
  ASSERT_EQUAL( Execution->as_blob(an_execution).pointer, an_execution );
  ASSERT_EQUAL( Execution->as_blob(an_execution).isa,     (representation)Execution );
  
  SUCCEED; }}

CEST(execution, advance) {
  
  /*  For the purposes of this set of tests, we’re going to use the following mini-AST:
   *      
   *      { () ( () ) }
   *      
   *  Since `execution->advance()` does not actually *preform* any juxtapositions, we needn’t be concerned with
   *  the Paws semantics of this code; simply how `execution->advance()` will progressively crawl through it.
   */
  auto expression   root = Node->expression();
  auto expression  first = Node->expression(); Node->descend(root, first);
  auto expression second = Node->expression(); Node->descend(root, second);
  auto expression    sub = Node->expression(); Node->descend(second, sub);
  
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
