include ../../Rules.make

CXXFLAGS += -I../../include

OBJS=Object.o HashTable.o

util.o:	$(OBJS)
	$(LD) -r -o $@ $(OBJS)

Object.o:

HashTable.o:

clean:
	$(RM) $(RMFLAGS) $(OBJS)
	$(RM) $(RMFLAGS) util.o
