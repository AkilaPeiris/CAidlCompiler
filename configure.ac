#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([AIDLCompiler], [1.0], [akila.peiris@hotmail.com])
AM_INIT_AUTOMAKE(AIDLCompiler, 1.0)
AC_CONFIG_SRCDIR([src/HashTable.h])

# Checks for libraries.

# Checks for header files.
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([fcntl.h inttypes.h libintl.h malloc.h stddef.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_YACC
AC_PROG_LEX

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset strdup])

AC_OUTPUT(Makefile src/Makefile)
