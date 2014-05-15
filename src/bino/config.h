/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Define to 1 if translation of program messages to the user's native
   language is requested. */
#define ENABLE_NLS 1

/* Define to 1 if you have the <AL/al.h> header file. */
#define HAVE_AL_AL_H 1

/* Define to 1 if you have the `backtrace' function. */
#define HAVE_BACKTRACE 1

/* Define to 1 if you have the MacOS X function CFLocaleCopyCurrent in the
   CoreFoundation framework. */
/* #undef HAVE_CFLOCALECOPYCURRENT */

/* Define to 1 if you have the MacOS X function CFPreferencesCopyAppValue in
   the CoreFoundation framework. */
/* #undef HAVE_CFPREFERENCESCOPYAPPVALUE */

/* Define to 1 if you have the `clock_gettime' function. */
#define HAVE_CLOCK_GETTIME 1

/* Define if the GNU dcgettext() function is already present or preinstalled.
   */
#define HAVE_DCGETTEXT 1

/* Define to 1 if you have the declaration of `optreset', and to 0 if you
   don't. */
#define HAVE_DECL_OPTRESET 0

/* Define if the GNU gettext() function is already present or preinstalled. */
#define HAVE_GETTEXT 1

/* Define if you have the iconv() function and it works. */
#define HAVE_ICONV 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Have Equalizer? */
#define HAVE_LIBEQUALIZER 0

/* Have liblircclient? */
#define HAVE_LIBLIRCCLIENT 0

/* Have NVIDIA libXNVCtrl for Quadro SDI output? */
#define HAVE_LIBXNVCTRL 0

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `nl_langinfo' function. */
#define HAVE_NL_LANGINFO 1

/* Define to 1 if you have the <NVCtrlLib.h> header file. */
/* #undef HAVE_NVCTRLLIB_H */

/* Define to 1 if you have the <NVCtrl.h> header file. */
/* #undef HAVE_NVCTRL_H */

/* Define to 1 if you have the `sigaction' function. */
#define HAVE_SIGACTION 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `sysconf' function. */
#define HAVE_SYSCONF 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `vasprintf' function. */
#define HAVE_VASPRINTF 1

/* Define to 1 if you have the `wcswidth' function. */
#define HAVE_WCSWIDTH 1

/* Whether we are running on X11 */
#define HAVE_X11 1
#define GLEW_MX 1

/* Define as const if the declaration of iconv() needs const. */
#define ICONV_CONST 

/* libass version */
#define LIBASS_PKGCONFIG_VERSION "0.10.1"

/* liblircclient version */
#define LIBLIRCCLIENT_PKGCONFIG_VERSION ""

/* Define to 1 to disable assertions and other debugging checks. */
#define NDEBUG 1

/* Name of package */
#define PACKAGE "bino"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "bino-list@nongnu.org"

/* Define to the full name of this package. */
#define PACKAGE_NAME "Bino"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "Bino 1.5.0"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "bino"

/* Define to the home page for this package. */
#define PACKAGE_URL "http://bino3d.org/"

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.5.0"

/* Platform triplet */
#define PLATFORM "x86_64-unknown-linux-gnu"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Version number of package */
#define VERSION "1.5.0"

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Enable large inode numbers on Mac OS X 10.5.  */
#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */
