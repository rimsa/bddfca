WIN32=no
DEBUG=no
BDD=

ifeq ($(WIN32), yes)
  MAKE=mingw32-make
else
  MAKE=make
endif

CC=gcc
CFLAGS=-g -O2 -Wall -D_GNU_SOURCE

CXX=g++
CXXFLAGS=-g -O2 -Wall -D_GNU_SOURCE

LD=ld
LDFLAGS=

ifeq ($(BDD), BuDDy)
  CFLAGS+=-DBuDDy
  CXXFLAGS+=-DBuDDy
  LDFLAGS=-lbdd
else ifeq ($(BDD), CUDD)
  CFLAGS+=-DCUDD
  CXXFLAGS+=-DCUDD
  LDFLAGS=-L/usr/local/lib -lcudd -lepd -lmtr -lutil -lst -lm
else
  $(error BDD library is not set. Please choose between BuDDy and CUDD)
endif

RM=rm
RMFLAGS=-rf

CP=cp
CPFLAGS=

ifeq ($(WIN32), yes)
  OUTPUT=bddfca.exe
else
  OUTPUT=bddfca
endif

SRC=src/$(OUTPUT)
DEST=bin/$(OUTPUT)

ifeq ($(DEBUG), yes)
  CFLAGS += -DDEBUG
  CXXFLAGS += -DDEBUG
endif

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.cc.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
