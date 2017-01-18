MKDIR := mkdir -p
RM := rm -f

BINDIR := bin
OBJDIR := obj

BIN := $(BINDIR)/astar
SRC := $(wildcard *.cpp)
OBJ := $(addprefix $(OBJDIR)/,$(patsubst %.cpp,%.o,$(SRC)))
CH := $(wildcard *.gch)
ifdef DEBUG
CXXFLAGS += -g -Og
else
CXXFLAGS += -O3
endif

.PHONY: all clean

$(BINDIR):
	$(MKDIR) $@

$(OBJDIR):
	$(MKDIR) $@

$(OBJDIR)/%.o: %.cpp $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN): $(OBJ) $(BINDIR)
	$(LD) $(LDFLAGS) $(OBJ) -o $@

all: $(BIN)

clean:
	$(RM) $(CH) $(OBJ) $(BIN)
