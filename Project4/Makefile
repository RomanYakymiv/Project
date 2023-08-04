CC := g++
SRCDIR := .
BUILDDIR := build
LIBDIR := C:\Users\roman\source\repos\Proj\StaticLibV2
TARGET := my_programV2
LIBRARY := C:\Users\roman\source\repos\Proj\StaticLibV2\staticLib_2.a

SRCEXT := cpp
SOURCES := $(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%.$(SRCEXT),$(BUILDDIR)/%.o,$(SOURCES))

CFLAGS := -std=c++20 -Wall -I$(LIBDIR)
LFLAGS := -L$(LIBDIR)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	$(CC) $^ -o $(TARGET) $(LFLAGS) $(LIBRARY)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " Compiling $<..."
	$(CC) $(CFLAGS) -c -o $@ $<

