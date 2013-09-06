include ../../Rules.make

CXXFLAGS += -I../../include

OBJS=FCA.o Args.o

control.o:	$(OBJS)
		$(LD) -r -o $@ $(OBJS)

FCA.o:

Args.o:

clean:
	$(RM) $(RMFLAGS) $(OBJS)
	$(RM) $(RMFLAGS) control.o
