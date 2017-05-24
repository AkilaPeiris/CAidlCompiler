SUFFIXES = .c .h .y .l

ACLOCAL_AMFLAGS = -I

AM_YFLAGS = -d

bin_PROGRAMS = CAIDL

CAIDL_SOURCES = parser.y lexer.l Compiler.c ASTGeneration.c SemanticAnalysis.c CodeGeneration.c ParcelUtilities.c HashTable.c
CAIDL_LDFLAGS = 
CAIDL_LDADD =

BUILT_SOURCES = parser.h

EXTRA_DIST = Makefile.dist configure.ac

CLEANFILES = *~

MAINTAINERCLEANFILES = aclocal.m4 config.guess config.sub configure install-sh ltmain.sh Makefile.in missing mkinstalldirs stamp-h.in libtool config.cache config.h config.h.in acinclude.m4 depcomp ylwrap

