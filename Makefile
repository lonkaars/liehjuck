BIN := pws-engine

SOURCES := $(wildcard src/*.cpp)
HEADERS := $(wildcard src/*.h)
TESTS := $(wildcard tests/*.cpp)

OBJDIR := .o/

# OBJS := $(patsubst %,$(OBJDIR)/%.o,$(basename $(SRCS)))
OBJECTS := $(patsubst %,$(OBJDIR)%, $(patsubst %.cpp,%.o, $(SOURCES)))
TEST_OBJECTS := $(patsubst %,$(OBJDIR)%, $(patsubst %.cpp,%.o, $(TESTS)))

$(shell mkdir -p $(dir $(OBJS)) >/dev/null)

CXX=g++
LD=g++

# Optionele 3rdparty headers.
# 
# Als er geen distro-packages zijn, of ze zijn verouderd, dan kan
# de headers in 3rdparty/<subdir> geplaatst worden.
#
_3p=$(shell test -d 3rdparty && echo 3rdparty)
ifeq (3rdparty,$(_3p))
	CPPFLAGS += -I$(_3p)
endif

CXXFLAGS := -std=c++17
LDFLAGS :=

LDLIBS := -lxcb -lxcb-xtest -lxcb-xfixes -pthread 

COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@
LINK.o = $(LD) $(LDFLAGS) -o $@
PRECOMPILE =

all: $(BIN)

.PHONY: clean
clean:
	$(RM) -r $(OBJDIR) $(DEPDIR)

.PHONY: distclean
distclean: clean
	$(RM) $(BIN) $(DISTOUTPUT)

.PHONY: install
install: $(BIN)
	sudo cp $(BIN) /bin/$(BIN)

.PHONY: uninstall
uninstall:
	sudo rm /bin/$(BIN)

format:
	clang-format -i $(SRCS) $(HEADERS)

$(BIN): $(OBJS)
	$(LINK.o) $^ $(LDLIBS) 

# test: $(TEST_OBJS)
# 	$(LINK.o) $^ $(LDLIBS) 

docs:
	doxygen Doxyfile

check: $(BIN) docs
	echo gert

compile_commands: clean
	bear -- make
	rm compile_commands.commands.json

# $(OBJDIR)/%.o: %.cpp
$(OBJDIR)/%.o: $(SOURCES)
	$(PRECOMPILE)
	$(COMPILE.cc) $<
	$(POSTCOMPILE)
#

$(OBJDIR)/src/%o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(LDLIBS) -c $< -o .o/$@

