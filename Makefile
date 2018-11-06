# Makefile for building Graphics demo on command line
FILES 	= $(wildcard src/*.cpp) $(wildcard lib/*.cpp)
OBJS	= $(FILES:.cpp=.o)
TFILES	= $(wildcard tests/*.cpp)
TOBJS	= $(TFILES:.cpp=.o)
TARGET 	= demo
TSTTGT	= testapp
CFLAGS	= -std=c++11 -Iinclude

ifeq ($(OS), Windows_NT)
	EXT = .exe
	PREFIX =
	RM	= del
	CFLAGS = -I\tools\freeglut\include
	LFLAGS = -L\tools\freeglut\lib\x64
	LFLAGS += -lfreeglut -lglu32 -lopengl32 -Wl,--subsystem,windows
	CXX = g++
	DOBJS = $(subst /,\,$(OBJS)) $(subst /,\,$(TOBJS))
else
	EXT =
	RM 	= rm -f
	PREFIX = ./
	CXX = g++
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
	    CFLAGS += -I/usr/include
		LFLAGS = -lGL -lGLU -lglut
	endif
	ifeq ($(UNAME_S), Darwin)
		CFLAGS += -I/usr/local/include
		CFLAGS += -Wno-deprecated-declarations
		LFLAGS = -framework OpenGL -framework GLUT
	endif
	DOBJS = $(OBJS) $(TOBJS)
endif

.PHONY: all
all:	$(TARGET)$(EXT)

$(TARGET)$(EXT):	$(OBJS)
	g++ -o $@ $^ $(LFLAGS)

$(TSTTGT)$(EXT):	$(TOBJS)
	g++ -o $@ $^

%.o:	%.cpp
	g++ -c $< -o $@ $(CFLAGS)

.PHONY: run
run:	$(TARGET)$(EXT)
		$(PREFIX)$<

.PHONY: test
test:	$(TSTTGT)$(EXT)
		$(PREFIX)$<
.PHONY: clean
clean:
	$(RM) $(TARGET)$(EXT) $(TSTTGT)$(EXT) $(DOBJS)

