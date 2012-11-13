# -*- mode: makefile-gmake; coding: utf-8 -*-

all:
%:
	$(MAKE) -C src $@

test: all
	@export PYTHONPATH=$$(pwd)/test; \
	export LD_LIBRARY_PATH=$$(pwd)/src; \
	atheist test

