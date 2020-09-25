BIN := pws-engine
SRCS := \
	src/main.cpp \
	src/import.cpp \
	src/scene.cpp \
	src/win.cpp \
	src/argparse.cpp \
#	lib/gfx/gfx.c
HEADERS := \
	src/scene.h \
	src/argparse.h \
	src/import.h \
	src/win.h \
#	lib/gfx/gfx.h

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

CXXFLAGS := -std=c++17
LDFLAGS :=

LDLIBS := -lX11

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

