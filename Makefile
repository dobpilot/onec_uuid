MODULE_big = onec_uuid
OBJS = onec_uuid.o	
DATA = onec_uuid--1.0.sql 
DOCS = README.onec_uuid
REGRESS = onec_uuid
EXTENSION=onec_uuid


ifdef USE_PGXS
PGXS := $(shell pg_config --pgxs)
include $(PGXS)
else
subdir = contrib/onec_uuid
top_builddir = ../..
#include $(top_builddir)/src/Makefile.global
#include $(top_srcdir)/contrib/contrib-global.mk
endif
