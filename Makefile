BIN := liehjuck

SOURCE_DIR = src
TESTS_DIR  = tests
OBJ_DIR    = .o

SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
HEADERS := $(wildcard $(SOURCE_DIR)/*.h)
TESTS   := $(wildcard $(TESTS_DIR)/*.cpp)

OBJECTS      := $(patsubst %,$(OBJ_DIR)/%, $(patsubst %.cpp,%.o, $(SOURCES)))
TEST_OBJECTS := $(patsubst %,$(OBJ_DIR)/%, $(patsubst %.cpp,%.o, $(TESTS)))

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

LDLIBS := -lxcb -lxcb-xtest -lxcb-xfixes -pthread -lxcb-image

COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDLIBS) -c -o $@
LINK.o     = $(LD) $(LDFLAGS) -o $@

all: $(BIN)

clean:
	$(RM) -r $(OBJ_DIR)/

distclean: clean
	$(RM) $(BIN)
	$(RM) $(BIN)-test
	$(RM) -r doc/
	$(RM) compile_commands.json

install: $(BIN)
	sudo cp $(BIN) /bin/$(BIN)

uninstall:
	sudo rm /bin/$(BIN)

format:
	clang-format -i $(SRCS) $(HEADERS) $(TESTS)

obj_dirs:
	mkdir -p $(dir $(TEST_OBJECTS)) $(dir $(OBJECTS))

# Compiling files in src/ to .o/
$(OBJ_DIR)/$(SOURCE_DIR)/%.o: obj_dirs $(SOURCES)
	$(COMPILE.cc) $(SOURCE_DIR)/$*.cpp

# Linking all files in .o/ to pws-engine binary
$(BIN): $(OBJECTS)
	$(LINK.o) $^ $(LDLIBS) 

docs:
	doxygen Doxyfile

# Unit test binary and linker
$(OBJ_DIR)/$(TESTS_DIR)/%.o: obj_dirs $(TESTS)
	$(COMPILE.cc) $(TESTS_DIR)/$*.cpp
$(BIN)-test: $(OBJECTS) $(TESTS)
	$(LINK.o) $^ $(LDLIBS) 

check: CXXFLAGS += -D UNIT_TEST_BINARY
check: LDLIBS += -lgtest
check: $(OBJECTS) $(TEST_OBJECTS) $(BIN)-test
	./$(BIN)-test --gtest_color=no

compile_commands: clean
	bear -- make

