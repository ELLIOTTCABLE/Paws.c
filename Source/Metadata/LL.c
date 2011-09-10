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
  e(blob)       blob;
  e(element)    next;
  e(element)    previous; };
struct e(ll) {
  e(element)    first;
  e(element)    last;
  e(ll_size)    length; };


struct E(Element) {
  // Functions ==============
  /// `Element` family functions
  e(element)                    (*create)             ( e(blob) content );
    struct e(element) *         (*allocate)(void);
  e(element)                    (*initialize)         ( struct e(element)* it, e(blob) content );
  
  /// `struct element` instance functions
                           void (*prefix)             ( e(element) this, e(element) it );
                           void (*affix)              ( e(element) this, e(element) it );
} IF_INTERNALIZED(extern *Element);

struct E(LL) {
  // Functions ==============
  /// `LL` family functions
  e(ll)                   (*create)(void);
    struct e(ll) *        (*allocate)(void);
  e(ll)                   (*initialize)         ( struct e(ll)* it );
  
  /// `struct ll` instance functions
                     void (*anterior_insert)    ( e(ll) this, e(element) it, e(ll_size) idx );
                     void (*posterior_insert)   ( e(ll) this, e(element) it, e(ll_size) idx );
                     void (*prefix)             ( e(ll) this, e(element) it );
                     void (*affix)              ( e(ll) this, e(element) it );
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


static element                  Element__create            (blob content);
static struct element *         Element__allocate(void);
static element                  Element__initialize        (struct element* it, blob content);

static                     void element__prefix            (element this,         element it);
static                     void element__affix             (element this,         element it);


     IF_EXTERNALIZED(static) struct Element * // »
                                    Element   = NULL;
void Paws__register_Element(void) { Element   = malloc(sizeof( struct Element ));
  
  auto struct Element _ = // »
  { .create       = Element__create
  , .allocate     = Element__allocate
  , .initialize   = Element__initialize
    
  , .prefix       = element__prefix
  , .affix        = element__affix };
  
  memcpy(Element, &_, sizeof( struct Element )); }


static ll                 LL__create(void);
static struct ll *        LL__allocate(void);
static ll                 LL__initialize         (struct ll* it);

static               void ll__anterior_insert    (ll this, element it, ll_size idx);
static               void ll__posterior_insert   (ll this, element it, ll_size idx);
static               void ll__prefix             (ll this, element it);
static               void ll__affix              (ll this, element it);
static element            ll__at                 (ll this,                ll_size idx);

IF_EXTERNALIZED(static) struct LL * // »
                               LL   = NULL;
void Paws__register_LL(void) { LL   = malloc(sizeof( struct LL ));
  
  auto struct LL _ = // »
  { .create             = LL__create
  , .allocate           = LL__allocate
  , .initialize         = LL__initialize
    
  , .anterior_insert    = ll__anterior_insert
  , .posterior_insert   = ll__posterior_insert
  , .prefix             = ll__prefix
  , .affix              = ll__affix
  , .at                 = ll__at };
  
  memcpy(LL, &_, sizeof( struct LL )); }


element Element__create(blob content) {
  return Element->initialize(Element->allocate(), content); }

struct element * Element__allocate(void) {
  return malloc(sizeof( struct element )); }

element Element__initialize(struct element* it, blob content) {
  it->next     = NULL;
  it->previous = NULL;
  memcpy(&it->blob, &content, sizeof( struct blob ));
  
  return it; }

void element__prefix(element this, element it) {
  if (this->previous != NULL) {
    if (it->previous == NULL)     element__prefix(it, this->previous);
                         else {   this->previous->next = NULL;
        if (it->next != NULL)       it->next->previous = NULL; } }
  
  it->next       = this;
  this->previous = it; }

void element__affix(element this, element it) {
  if (this->next != NULL) {
    if (it->next == NULL)         element__affix(it, this->next);
                     else {       this->next->previous = NULL;
      if (it->previous != NULL)     it->previous->next = NULL; } }
  
  it->previous = this;
  this->next   = it; }


ll LL__create(void) {
  return LL->initialize(LL->allocate()); }

struct ll* LL__allocate(void) {
  return malloc(sizeof( struct ll )); }

ll LL__initialize(struct ll* it) {
  it->first  = NULL;
  it->last   = NULL;
  it->length = 0;
  
  return it; }

void ll__anterior_insert(ll this, element it, ll_size idx) {
  if (idx == 0)
    /* TODO: Error condition, cannot anterior-insert at first position */;
  else {
    Element->affix(LL->at(this, idx - 1), it);
    this->length++; } }

void ll__posterior_insert(ll this, element it, ll_size idx) {
  if (idx == this->length)
    /* TODO: Error condition, cannot posterior-insert at last position */;
  else {
    Element->prefix(LL->at(this, idx), it);
    this->length++; } }

void ll__prefix(ll this, element it) {
  if (this->length < 1)
    this->last = it;
  else
    Element->prefix(this->first, it);
  this->first = it;
  this->length++; }

void ll__affix(ll this, element it) {
  if (this->length < 1)
    this->first = it;
  else
    Element->affix(this->last, it);
  this->last = it;
  this->length++; }

element ll__at(ll this, ll_size idx) { auto element it; ll_size i;
  
  if (idx >= this->length) return NULL;
  
  if (idx <= this->length / 2) {
    it = this->first;
    for (i = 0; i < idx; ++i)
      it = it->next;
  } else {
    it = this->last;
    for (i = this->length - 1; i > idx; --i)
      it = it->next;
  }
  
  return it; }


# endif //!defined(LL_IMPLEMENTATION) && !defined(DECLARATIONS)
