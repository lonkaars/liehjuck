BIN := pws-engine

SOURCE_DIR = src
TESTS_DIR  = tests
OBJ_DIR    = .o

SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
HEADERS := $(wildcard $(SOURCE_DIR)/*.h)
TESTS   := $(wildcard $(TESTS_DIR)/*.cpp)

OBJECTS      := $(patsubst %,$(OBJ_DIR)/%, $(patsubst %.cpp,%.o, $(SOURCES)))
TEST_OBJECTS := $(patsubst %,$(OBJ_DIR)/%, $(patsubst %.cpp,%.o, $(TESTS)))

$(shell mkdir -p $(dir $(OBJECTS)) >/dev/null)

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
LDFLAGS  :=

LDLIBS := -lxcb -lxcb-xtest -lxcb-xfixes -pthread 

COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDLIBS) -c -o $@
LINK.o     = $(LD) $(LDFLAGS) -o $@
PRECOMPILE =

all: $(BIN)

clean:
	$(RM) -r $(OBJ_DIR)/

distclean: clean
	$(RM) $(BIN) $(DISTOUTPUT)

install: $(BIN)
	sudo cp $(BIN) /bin/$(BIN)

uninstall:
	sudo rm /bin/$(BIN)

format:
	clang-format -i $(SRCS) $(HEADERS)

$(OBJ_DIR)/$(SOURCE_DIR)/%.o: $(SOURCES)
	$(COMPILE.cc) $(SOURCE_DIR)/$*.cpp

$(BIN): $(OBJECTS)
	$(LINK.o) $^ $(LDLIBS) 

docs:
	doxygen Doxyfile

check: $(BIN) docs
	echo gert

compile_commands: clean
	bear -- make
	rm compile_commands.commands.json

