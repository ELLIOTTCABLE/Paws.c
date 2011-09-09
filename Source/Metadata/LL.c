# if !defined(LL_DECLARATIONS)
#   define    LL_DECLARATIONS

# if !defined(DECLARATIONS)
#   define LL_C__BEHEST
#   define DECLARATIONS
# endif
#     include "Core.h"
#     include "Nuketypes/Nuketypes.h"

#     include <limits.h>
# if defined(LL_C__BEHEST)
#   undef DECLARATIONS
# endif


          struct e(element);
          struct e(ll);
typedef   struct e(element) *       e(element);
typedef   struct e(ll) *            e(ll);

typedef   unsigned long long int    e(ll_size);

struct e(element) {
  e(thing)      thing;
  e(element)    next;
  e(element)    previous; };
struct e(ll) {
  e(element)    first;
  e(element)    last;
  e(ll_size)    length; };


struct E(Element) {
  // Functions ==============
  /// `Element` family functions
  e(element)                    (*create)             ( e(thing) thing );
    struct e(element) *         (*allocate)(void);
  e(element)                    (*initialize)         ( struct e(element)* this, e(thing) thing );
  
  /// `struct element` instance functions
                           void (*prefix)             ( e(element) this, e(element) other );
                           void (*affix)              ( e(element) this, e(element) other );
} IF_INTERNALIZED(extern *Element);

struct E(LL) {
  // Functions ==============
  /// `LL` family functions
  e(ll)                   (*create)(void);
    struct e(ll) *        (*allocate)(void);
  e(ll)                   (*initialize)         ( struct e(ll)* this );
  
  /// `struct ll` instance functions
                     void (*anterior_insert)    ( e(ll) this, e(element) child, e(ll_size) idx );
                     void (*posterior_insert)   ( e(ll) this, e(element) child, e(ll_size) idx );
                     void (*prefix)             ( e(ll) this, e(element) child );
                     void (*affix)              ( e(ll) this, e(element) child );
  e(element)              (*at)                 ( e(ll) this,                   e(ll_size) idx );
} IF_INTERNALIZED(extern *LL);

extern    void MAKE_EXTERNAL(register_Element)(void);
extern    void MAKE_EXTERNAL(register_LL)(void);



# endif //!defined(LL_DECLARATIONS)
# if !defined(LL_IMPLEMENTATION) && !defined(DECLARATIONS) /* =========================================== BODY */
#   define    LL_IMPLEMENTATION

# define DECLARATIONS
#   include <stdlib.h>
#   include <string.h>
# undef  DECLARATIONS


static element                  Element__create            (thing thing);
static struct element *         Element__allocate(void);
static element                  Element__initialize        (struct element* this, thing thing);

static                     void element__prefix            (element this,         element other);
static                     void element__affix             (element this,         element other);


     IF_EXTERNALIZED(static) struct Element * // »
                                    Element   = NULL;
void Paws__register_Element(void) { Element   = malloc(sizeof( struct Element ));
  
  auto struct Element // »
  data = {
    .create       = Element__create,
    .allocate     = Element__allocate,
    .initialize   = Element__initialize,
    
    .prefix       = element__prefix,
    .affix        = element__affix };
  
  memcpy(Element, &data, sizeof( struct Element )); }


static ll                 LL__create(void);
static struct ll *        LL__allocate(void);
static ll                 LL__initialize         (struct ll* this);

static               void ll__anterior_insert    (ll this, element child, ll_size idx);
static               void ll__posterior_insert   (ll this, element child, ll_size idx);
static               void ll__prefix             (ll this, element child);
static               void ll__affix              (ll this, element child);
static element            ll__at                 (ll this,                ll_size idx);

IF_EXTERNALIZED(static) struct LL * // »
                               LL   = NULL;
void Paws__register_LL(void) { LL   = malloc(sizeof( struct LL ));
  
  auto struct LL // »
  data = {
    .create             = LL__create,
    .allocate           = LL__allocate,
    .initialize         = LL__initialize,
    
    .anterior_insert    = ll__anterior_insert,
    .posterior_insert   = ll__posterior_insert,
    .prefix             = ll__prefix,
    .affix              = ll__affix,
    .at                 = ll__at };
  
  memcpy(LL, &data, sizeof( struct LL )); }


element Element__create(thing target) {
  return Element->initialize(Element->allocate(), target); }

struct element * Element__allocate(void) {
  return malloc(sizeof( struct element )); }

element Element__initialize(struct element* this, thing target) {
  this->next     = NULL;
  this->previous = NULL;
  memcpy(&this->thing, &target, sizeof( struct thing ));
  /* LEAK: Well, what exactly can we do? It’s not like we have a GC yet… */
  
  return this; }

void element__prefix(element this, element other) {
  if (this->previous != NULL) {
    if (other->previous == NULL)
      element__prefix(other, this->previous);
    else {
      this->previous->next = NULL;
      if (other->next != NULL)
        other->next->previous = NULL; } }
  
  other->next     = this;
  this->previous  = other; }

void element__affix(element this, element other) {
  if (this->next != NULL) {
    if (other->next == NULL)
      element__affix(other, this->next);
    else {
      this->next->previous = NULL;
      if (other->previous != NULL)
        other->previous->next = NULL; } }
  
  other->previous = this;
  this->next      = other; }


ll LL__create(void) {
  return LL->initialize(LL->allocate()); }

struct ll * LL__allocate(void) {
  return malloc(sizeof( struct ll )); }

ll LL__initialize(struct ll* this) {
  this->first  = NULL;
  this->last   = NULL;
  this->length = 0;
  
  return this; }

void ll__anterior_insert(ll this, element child, ll_size idx) {
  if (idx == 0)
    /* TODO: Error condition, cannot anterior-insert at first position */;
  else {
    Element->affix(LL->at(this, idx - 1), child);
    this->length++; } }

void ll__posterior_insert(ll this, element child, ll_size idx) {
  if (idx == this->length)
    /* TODO: Error condition, cannot posterior-insert at last position */;
  else {
    Element->prefix(LL->at(this, idx), child);
    this->length++; } }

void ll__prefix(ll this, element child) {
  if (this->length < 1)
    this->last = child;
  else
    Element->prefix( this->first, child );
  this->first = child;
  this->length++; }

void ll__affix(ll this, element child) {
  if (this->length < 1)
    this->first = child;
  else
    Element->affix( this->last, child );
  this->last = child;
  this->length++; }

element ll__at(ll this, ll_size idx) { auto element result; ll_size i;
  
  if (idx >= this->length) return NULL;
  
  if (idx <= this->length / 2) {
    result = this->first;
    for (i = 0; i < idx; ++i)
      result = result->next;
  } else {
    result = this->last;
    for (i = this->length - 1; i > idx; --i)
      result = result->next;
  }
  
  return result; }


# endif //!defined(LL_IMPLEMENTATION) && !defined(DECLARATIONS)
