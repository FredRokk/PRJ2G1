SRCS=test.cpp Classes.cpp
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)
EXE=test
BASEPATH=../..
# Determine whether this is a debug build or not
ifeq (${TARGET},target)
CXX=arm-rpizw-g++
TARGETPATH=$(BASEPATH)/lib/target
else
CXX=g++
TARGETPATH=$(BASEPATH)/lib/host
endif

ifdef DEBUG
CFLAGS= -ggdb -O0
LIBPATH=$(TARGETPATH)/debug
else
CFLAGS=-O2
LIBPATH=$(TARGETPATH)/release
endif
# Setup the CFLAGS to ensure that the relevant warnings, includes and defines.
CFLAGS+= -Wall -D_REENTRANT -DOS_LINUX -I$(BASEPATH)/inc

# Note how the flags are part of the compilation of .cpp file(s).
%.o: %.cpp
	$(CXX) -c $(CFLAGS) $(SRCS)
# Then again, note how the flags are NOT part of the linking process
$(EXE): $(OBJS)
	$(CXX) -o $@ $^ -L$(LIBPATH) -lOSApi -lrt -lpthread

all: $(EXE)

clean:
	rm -f $(OBJS) $(EXE)