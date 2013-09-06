include ../Rules.make

CXXFLAGS += -I../include

OBJS=control/control.o formal/formal.o io/io.o  util/util.o time/time.o \
     extract/extract.o bddfca.o 

$(OUTPUT):	$(OBJS)
		$(CXX) -o $@ $(OBJS) $(LDFLAGS)

control/control.o:
	$(MAKE) -C control control.o

formal/formal.o:
	$(MAKE) -C formal formal.o

io/io.o:
	$(MAKE) -C io io.o

util/util.o:
	$(MAKE) -C util util.o

time/time.o:
	$(MAKE) -C time time.o

extract/extract.o:
	$(MAKE) -C extract extract.o

bddfca.o:

clean:
	$(MAKE) -C control clean
	$(MAKE) -C formal clean
	$(MAKE) -C io clean
	$(MAKE) -C extract clean
	$(MAKE) -C util clean
	$(MAKE) -C time clean
	$(RM) $(RMFLAGS) bddfca.o
	$(RM) $(RMFLAGS) $(OUTPUT)
