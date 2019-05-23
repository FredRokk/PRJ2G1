SRCS=Map.cpp Gamerules.cpp gameRulesTest.cpp
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)
EXE=gamerulesTest
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

all: $(EXE)

%.d: %.cpp
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< > $@

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $<

$(EXE): $(OBJS) $(DEPS)
	$(CXX) -o $@ $(OBJS) -L$(LIBPATH) -lOSApi -lrt -lpthread

.PHONY: clean
clean:
	@echo "Cleaning up..."
	@rm -f $(OBJS) $(EXE) $(DEPS)

ifneq ($(MAKECMDGOALS),clean)

-include $(DEPS)

endif