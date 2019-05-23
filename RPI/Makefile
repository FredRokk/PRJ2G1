#Set default target if none is defined
ifndef TARGET
	TARGET=host
endif

# Determine whether this is a debug build or not
ifeq (${TARGET},target)
CXX=arm-rpizw-g++
TARGETPATH=$(BASEPATH)/lib/target
else
CXX=g++
TARGETPATH=$(BASEPATH)/lib/host
endif

ifdef DEBUG
CXXFLAGS= -ggdb -O0
DEST_DIR=bin/$(TARGET)/debug
LIBPATH=$(TARGETPATH)/debug
MODE=debug
else
CXXFLAGS=-O2
DEST_DIR=bin/$(TARGET)/release
LIBPATH=$(TARGETPATH)/release
MODE=release
endif
OBJ_DEST_DIR=build/$(DEST_DIR)

BASEPATH=.
INCPATH=$(BASEPATH)/inc
SRCPATH=src
THREADFUNCTORS=$(addprefix $(SRCSPATH)/threadfunctors/, GameThreadFunctor.cpp)
STATES=$(addprefix $(SRCSPATH)/states/, State.cpp Idle.cpp MapSelect.cpp Practice.cpp Versus.cpp Results.cpp PlayerOneHighscore.cpp PlayerTwoHighscore.cpp)
GAMESPECIFICS=$(addprefix $(SRCSPATH)/gameSpecifics/, Map.cpp Gamerules.cpp)
MAIN=test.cpp
SRC=$(THREADFUNCTORS) $(STATES) $(GAMESPECIFICS) $(MAIN) 
OBJS=$(addprefix $(OBJ_DEST_DIR)/,$(notdir $(SRC:.cpp=.o)))
DEPS=$(addprefix $(OBJ_DEST_DIR)/,$(notdir $(SRC:.cpp=.d)))
EXE=$(DEST_DIR)/test

# Setup the CFLAGS to ensure that the relevant warnings, includes and defines.
CXXFLAGS+= -Wall -D_REENTRANT -DOS_LINUX -I$(INCPATH)

VPATH=src src/threadFunctors src/states src/gameSpecifics

all: info $(EXE)

.PHONY: info
info:
	@echo "Compiling for '$(TARGET)' in '$(MODE)' mode..."

$(OBJ_DEST_DIR)/%.o: %.cpp
	@echo "Compiling for $<"
	@mkdir -p $(OBJ_DEST_DIR)
	@$(CXX) -c $< -o $@ $(CXXFLAGS)

$(OBJ_DEST_DIR)/%.d: %.cpp
	@echo "Generating dependency for $<"
	@mkdir -p $(OBJ_DEST_DIR)
	@$(CXX) -MT$(OBJ_DEST_DIR)/$(@:.d=.o) -MM $(CXXFLAGS) $^ > $@

$(DEST_DIR):
	@mkdir -p $(DEST_DIR)

$(OBJ_DEST_DIR):
	@mkdir -p $(OBJ_DEST_DIR)

$(EXE): $(DEST_DIR) $(OBJ_DEST_DIR) $(DEPS) $(OBJS)
	@echo "Linking $<"
	@$(CXX) -o $@ $(OBJS) -L$(LIBPATH) -lOSApi -lrt -lpthread

.PHONY: nuke
nuke:
	@echo "Nuking folders bin/ and build/ out of existence"
	@rm -rf bin/ build/

.PHONY: clean
clean:
	@echo "Cleaning up..."
	@rm -f $(OBJS) $(EXE) $(DEPS)

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),nuke)

-include $(DEPS)

endif
endif