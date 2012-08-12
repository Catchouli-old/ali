#
# Builds tests
#

BINDIR		= bin
OBJDIR		= obj

INCDIR		= -I../Library

CXX		= g++
CXXFLAGS	= $(INCDIR) -O2 -Wall -std=c++0x

LIBRARIES	= ../Library/bin/libali.a -lpthread

SRCS		= $(wildcard *.cpp)
OBJS		= $(patsubst %.cpp, $(OBJDIR)/%.obj, $(SRCS))

BIN		= tests

all: $(BINDIR) $(OBJDIR) $(BINDIR)/$(BIN)

clean:
	rm -rf $(BINDIR)
	rm -rf $(OBJDIR)

$(BINDIR)/$(BIN): $(OBJS)
	$(LINK.cpp) $(OBJS) $(LIBRARIES) -o $(BINDIR)/$(BIN)

$(OBJDIR)/%.obj: 
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)
