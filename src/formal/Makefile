include ../../Rules.make

CXXFLAGS += -I../../include

OBJS=FormalContext.o FormalConcept.o concepts/concepts.o
FILES=FormalContext.o FormalConcept.o

formal.o:	$(OBJS)
		$(LD) -r -o $@ $(OBJS)

FormalContext.o:

FormalConcept.o:

concepts/concepts.o:
	$(MAKE) -C concepts concepts.o

clean:
	$(MAKE) -C concepts clean
	$(RM) $(RMFLAGS) $(FILES)
	$(RM) $(RMFLAGS) formal.o
