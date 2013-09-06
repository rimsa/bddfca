include ../../Rules.make

CXXFLAGS += -I../../include

OBJS=BurMeister.o OutputRelations.o OutputStats.o IOException.o

io.o:	$(OBJS)
	$(LD) -r -o $@ $(OBJS)

BurMeister.o:

OutputRelations.o:

OutputStats.o:

IOExcption.o:

clean:
	$(RM) $(RMFLAGS) $(OBJS)
	$(RM) $(RMFLAGS) io.o
