CC = gcc
CFLAGS = -std=c++11 -g3
EXE = cs426_graph_server

# space-separated list of header files
HDRS = mongoose.h headers.h

# space-separated list of source files
SRCS = mongoose.c hashtable.c checkpoint.c server.c test.cpp

# automatically generated list of object files
OBJS = $(SRCS:.c=.o)

# default target
$(EXE): $(OBJS) $(HDRS)
	$(CXX) $(CFLAGS) -o $@ $(OBJS)

# dependencies
$(OBJS): $(HDRS)

# housekeeping
clean:
	rm -f core $(EXE) *.o
