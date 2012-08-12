#
# Builds library
#

BINDIR		= bin
OBJDIR		= obj

CXX		= g++
CXXFLAGS	= -O2 -Wall -lpthread

SRCS		= $(wildcard *.cpp)
OBJS		= $(patsubst %.cpp, $(OBJDIR)/%.obj, $(SRCS))

BIN		= libali.a

all: $(BINDIR) $(OBJDIR) $(BINDIR)/$(BIN)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

$(BINDIR)/$(BIN): $(OBJS)
	ar rvs $(BINDIR)/$(BIN) $(OBJS)

$(OBJDIR)/%.obj: 
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

.PHONY: all clean
