# if !defined(CORE_DECLARATIONS)
#   define    CORE_DECLARATIONS


# define MAKE_EXTERNAL(NAME) Paws__ ## NAME
# define MAKE_INTERNAL(NAME) NAME

# if defined(EXTERNALIZE)
#   define e(NAME) MAKE_EXTERNAL(NAME)
#   define E(NAME) MAKE_EXTERNAL(NAME)

#   define IF_EXTERNALIZED(CODE) CODE
#   define IF_INTERNALIZED(CODE) // fizzle
# else
#   define e(NAME) MAKE_INTERNAL(NAME)
#   define E(NAME) MAKE_INTERNAL(NAME)

#   define IF_EXTERNALIZED(CODE) // fizzle
#   define IF_INTERNALIZED(CODE) CODE
# endif


/* Yes, I’m a pedant. Get over it. */
typedef   unsigned char   e(byte);
typedef   void *          e(pointer);
typedef   char *          e(charray);

# if !defined(__has_attribute)
#   define has_no_has_attribute
#   define __has_attribute(x) 0
# endif

#   if __has_attribute(constructor)
#     define __constructor __attribute__((constructor))
#   else
#     define __constructor
#   endif

#   if __has_attribute(packed)
#     define __packed __attribute__((packed))
#   else
#     define __packed
#   endif

# if defined(has_no_has_attribute)
#   undef has_no_has_attribute
#   undef __has_attribute
# endif


# endif //!defined(CORE_DECLARATIONS)
