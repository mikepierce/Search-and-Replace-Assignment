
# Mike Pierce
# Makefile



EXE = executable
COMPILER = g++
CPPFLAGS = -g -std=c++11 -fdiagnostics-color -Wall -W -Werror -pedantic
LDFLAGS = -lrt
SOURCES = $(wildcard *.*pp)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.cpp=.o)
DENTFLAGS = -bli0 -brf -br -ts4 -nut -i4 -npsl -nsaf -nsai -nsaw -npcs -nsob



all: $(EXE)

$(EXE): $(OBJECTS) $(HEADERS)
	$(COMPILER) $(LDFLAGS) *.o -o $(EXE)

%.o: %.cpp
	$(COMPILER) $(CPPFLAGS) -c $< -o $@

.PHONY: run clean indent tarball sync

run: all
	./$(EXE)

clean:
	rm -f $(EXE)
	rm -f $(TARNAME)
	rm -f *.o
	rm -f *.h.gch

indent:
	indent $(DENTFLAGS) $(SOURCES)
	indent $(DENTFLAGS) $(HEADERS)


