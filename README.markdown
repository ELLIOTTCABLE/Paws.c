`Paws.c` <img alt='Maintenance status: Unmaintained, of historical interest' src="https://img.shields.io/badge/maintained%3F-historical-lightgrey.svg?style=flat"><img src="http://elliottcable.s3.amazonaws.com/p/8x8.png"><a target="_blank" href="COPYING.markdown"><img alt='License: ISC' src="https://img.shields.io/badge/license-ISC-blue.svg?style=flat"></a><img src="http://elliottcable.s3.amazonaws.com/p/8x8.png"><a target="_blank" href="http://ell.io/IRC"><img alt='Chat: IRC on Freenode.net' src="https://img.shields.io/badge/chat-IRC-blue.svg"></a><img src="http://elliottcable.s3.amazonaws.com/p/8x8.png"><a target="_blank" href="http://twitter.com/ELLIOTTCABLE"><img alt='Follow my work on Twitter' src="https://img.shields.io/twitter/follow/ELLIOTTCABLE.svg?style=flat&label=followers&color=blue"></a>
========
Paws is [@elliottcable][]’s programming language. The design is almost two years old, but has gone through
[many iterations][Strata] and changes. There is no working implementation, though several separate codebases are
underway.

This project is my reference implementation. It’s going to be absolutely non-performant at the outset; it is
primarily intended to be an easy-to-peruse codebase that provides a *clean* API for embedding the interpreter
into other projects (statically linked.)

**If you’re interested in Paws, you should join the IRC channel.** There’s no coherent documentation on the
underlying paradigm online; we’ve tried several times to compile such, and had no luck. It’s quite difficult to
explain without an example interpreter to point people to, even on a one-on-basis; nearly impossible to do so
with no example implementation *and* in a generalized anybody-who-reads-this form. (Yes, we know this situation
sucks!)

We’re always available in [**#elliottcable**][irc] on the Freenode IRC network
([click here][webchat] to immediately open a temporary IRC client in your browser.)

  [@elliottcable]: http://twitter.com/elliottcable
  [strata]: https://github.com/Paws/Paws.c/wiki/Strata
  [irc]: irc://chat.freenode.net/#elliottcable
  [webchat]: http://webchat.freenode.net?channels=%23elliottcable

Spelunking
----------
This distribution includes a file that describes many points of interest within the codebase, and should help you
have an easier time exploring it.

If you’re the sort who learns best by reading code instead of docs, head over to the [SPELUNKING][] file!

  [SPELUNKING]: /elliottcable/Paws.c/blob/Master/SPELUNKING.markdown

Compiling
---------
Using the `C99` function below, you can use the following (compatible with `$CC` set to either `clang` or `gcc`,
right now):
    
    # Compiling library (TODO)
    #   (I’ll admit it. I have no idea how to compile a shared library, or even how to make Paws capable of being
    #    compiled as a shared library.)
    
    # Compiling executable (TODO)
    #C99 -ISource \
    #  Source/Metadata/LL.tests.c \
    #  Source/Metadata/Metadata.tests.c \
    #  Source/Nuketypes/execution/Script.c \
    #  Source/Nuketypes/execution/execution.c \
    #  Source/Nuketypes/label/Magazine.tests.c \
    #  Source/Nuketypes/label/label.tests.c \
    #Source/Executable/Paws.c.c && ./Paws.c.o
    
    # Compiling and running all tests
    C99   -IVendor -DCEST__NO_AUTO Vendor/Cest.c/Source/Cest.c   -ISource \
      Source/Metadata/LL.tests.c \
      Source/Metadata/Metadata.tests.c \
      Source/Nuketypes/execution/Script.tests.c \
      Source/Nuketypes/execution/execution.tests.c \
      Source/Nuketypes/label/Magazine.tests.c \
      Source/Nuketypes/label/label.tests.c \
    Source/Paws.tests.c && ./Paws.tests.o
    
    # Compiling and running all tests with gdb
    C99 -ggdb   -IVendor -DCEST__NO_AUTO Vendor/Cest.c/Source/Cest.c   -ISource \
      Source/Metadata/LL.tests.c \
      Source/Metadata/Metadata.tests.c \
      Source/Nuketypes/execution/Script.tests.c \
      Source/Nuketypes/execution/execution.tests.c \
      Source/Nuketypes/label/Magazine.tests.c \
      Source/Nuketypes/label/label.tests.c \
    Source/Paws.tests.c && gdb -q -batch -x =(echo -e "run\nquit") -se ./Paws.tests.o
    
### Makefile
This project will almost certainly never have a makefile. I love ISO C, and I love the CPP, so don’t
misunderstand me for simply being too pandered-to by modern toolsets to handle the complexity:

**GNU make sucks.**

Just to be clear, SCons sucks too. So do Rake, CMake, and Waf. They all suck, they’re all bloated and overly
verbose, and they all solve the wrong problem (at least for me. To each their own, and all that.)

When it becomes a big enough issue, I’ll probably write a custom buildtool for my C code. Something sleek and
small, with file watchers, SHA1 comparison, git integration, and in-file dependency declaration.

Until then…
    
    zsh; # I’m not very familiar with bash.
    C99() { eval local last="\$$#"; last=${last##*/}; $CC -std=c99 -pedantic-errors -Wall -O0 -o "${last%.*}.o" "$@" }
    
(-;

License
-------
This project is released for public usage under the terms of the very-permissive [ISC license][] (a
modern evolution of the MIT / BSD licenses); more information is available in [COPYING][].

   [ISC license]: <http://choosealicense.com/licenses/isc/> "Information about the ISC license"
   [COPYING]: <./COPYING.text>
