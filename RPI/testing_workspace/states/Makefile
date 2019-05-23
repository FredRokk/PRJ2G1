SRCS=GameThreadFunctor.cpp State.cpp Idle.cpp MapSelect.cpp Practice.cpp Versus.cpp Results.cpp PlayerOneHighscore.cpp PlayerTwoHighscore.cpp test.cpp
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)
EXE=test
BASEPATH=..
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

%.d: %.cpp
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< > $@

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $<

$(EXE): $(OBJS) $(DEPS)
	$(CXX) -o $@ $(OBJS) -L$(LIBPATH) -lOSApi -lrt -lpthread

all: $(EXE)

clean:
	rm -f $(OBJS) $(EXE) $(DEPS)