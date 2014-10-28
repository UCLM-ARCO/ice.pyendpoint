# -*- mode: makefile-gmake; coding: utf-8 -*-

all:
	$(MAKE) -C src $@

.PHONY: test
test:
	-prego -veo test/*_test.py

install:
	$(MAKE) -C src $@
	python setup.py install \
	--prefix=$(DESTDIR)/usr/ \
        --install-layout=deb

.PHONY: clean
clean:
	$(MAKE) -C src $@

