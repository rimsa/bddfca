include ../../../Rules.make

CXXFLAGS += -I../../../include

OBJS=Concept.o ConceptsKeeper.o ConceptsList.o ConceptsHash.o

concepts.o:	$(OBJS)
		$(LD) -r -o $@ $(OBJS)
Concept.o:

ConceptsKeeper.o:

ConceptsList.o:

ConceptsHash.o:

clean:
	$(RM) $(RMFLAGS) $(OBJS)
	$(RM) $(RMFLAGS) concepts.o
