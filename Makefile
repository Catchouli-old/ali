#
# Makefile to build ali (a library - apologies for the generic naming)
#

BINDIR	= bin

all: $(BINDIR)
	$(MAKE) -C Library
	cp Library/$(BINDIR)/* $(BINDIR)/

	$(MAKE) -C Tests
	cp Tests/$(BINDIR)/* $(BINDIR)/

clean:
	rm -rf $(BINDIR)
	$(MAKE) clean -C Library
	$(MAKE) clean -C Tests

$(BINDIR):
	mkdir -p $(BINDIR)
