include $(top_srcdir)/example/Makefile.inc

bindir=${exec_prefix}/odp/bin
bin_PROGRAMS = odp_reflector$(EXEEXT)
odp_reflector_LDFLAGS = $(AM_LDFLAGS) -static
odp_reflector_CFLAGS = $(AM_CFLAGS) -I${top_srcdir}/example

noinst_HEADERS = \
		  $(top_srcdir)/example/example_debug.h

dist_odp_reflector_SOURCES = odp_reflector.c
