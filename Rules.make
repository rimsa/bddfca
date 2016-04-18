WIN32=no
DEBUG=no
BDD=

ifeq ($(WIN32), yes)
  MAKE=mingw32-make
else
  MAKE=make
endif

CC=gcc
CFLAGS=-Wall -D_GNU_SOURCE

CXX=g++
CXXFLAGS=-Wall -D_GNU_SOURCE

LD=ld
LDFLAGS=

ifeq ($(BDD), BuDDy)
  CFLAGS+=-DBuDDy
  CXXFLAGS+=-DBuDDy
  LDFLAGS=-lbdd
else ifeq ($(BDD), CUDD)
  CUDD_PATH=/opt/cudd-2.5.1
  CFLAGS+=-DCUDD -I$(CUDD_PATH)/include
  CXXFLAGS+=-DCUDD -I$(CUDD_PATH)/include
  LDFLAGS=-L$(CUDD_PATH)/lib -lcudd -lepd -lmtr -lutil -lst -lm
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
	CFLAGS += -g -ggdb -DDEBUG -O0
	CXXFLAGS += -g -ggdb -DDEBUG -O0
else
	CFLAGS += -O2
	CXXFLAGS += -O2
endif

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.cc.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
