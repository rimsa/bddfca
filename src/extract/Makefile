include ../../Rules.make

CXXFLAGS += -I../../include

OBJS=ExtractRelations.o Relation.o

extract.o:	$(OBJS)
		$(LD) -r -o $@ $(OBJS)

ExtractRelatins.o:

Relation.o:

clean:
	$(RM) $(RMFLAGS) $(OBJS)
	$(RM) $(RMFLAGS) extract.o
