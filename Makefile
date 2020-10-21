BIN := pws-engine
SRCS := \
	src/main.cpp \
	src/import.cpp \
	src/scene.cpp \
	src/win.cpp \
	src/draw.cpp \
	src/argparse.cpp \
	src/calc.cpp

HEADERS := \
	src/scene.h \
	src/argparse.h \
	src/import.h \
	src/win.h \
	src/calc.h \
	src/jdscn_types.h \
	src/draw.h

OBJDIR := .o
DEPDIR := .d

OBJS := $(patsubst %,$(OBJDIR)/%.o,$(basename $(SRCS)))
DEPS := $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))

# make directories
$(shell mkdir -p $(dir $(OBJS)) >/dev/null)
$(shell mkdir -p $(dir $(DEPS)) >/dev/null)

CXX=g++
CC=gcc
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

CXXFLAGS := -std=c++17 -fPIC
LDFLAGS :=

LDLIBS := -lX11 -pthread 

DEPFLAGS = -MT $@ -MD -MP -MF $(DEPDIR)/$*.Td

COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) -c -o $@
LINK.o = $(LD) $(LDFLAGS) -o $@
PRECOMPILE =
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

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

docs:
	doxygen Doxyfile

#$(OBJDIR)/%.o: %.c
#$(OBJDIR)/%.o: %.c $(DEPDIR)/%.d
#	$(PRECOMPILE)
#	$(COMPILE.c) $<
#	$(POSTCOMPILE)

$(OBJDIR)/%.o: %.cpp
$(OBJDIR)/%.o: %.cpp $(DEPDIR)/%.d
	$(PRECOMPILE)
	$(COMPILE.cc) $<
	$(POSTCOMPILE)

$(OBJDIR)/%.o: %.cc
$(OBJDIR)/%.o: %.cc $(DEPDIR)/%.d
	$(PRECOMPILE)
	$(COMPILE.cc) $<
	$(POSTCOMPILE)

$(OBJDIR)/%.o: %.cxx
$(OBJDIR)/%.o: %.cxx $(DEPDIR)/%.d
	$(PRECOMPILE)
	$(COMPILE.cc) $<
	$(POSTCOMPILE)

.PRECIOUS: $(DEPDIR)/%.d
$(DEPDIR)/%.d: ;

-include $(DEPS)

