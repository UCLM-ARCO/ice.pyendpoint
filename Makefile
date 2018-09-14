# -*- mode: makefile-gmake; coding: utf-8 -*-

all:
	$(MAKE) -C src $@

.PHONY: test
tests:
	-prego -veo test/*_test.py

install: clean
	$(MAKE) -C src $@
	find -name "__pycache__" -delete
	python3 setup.py install \
	--prefix=$(DESTDIR)/usr/ \
        --install-layout=deb

.PHONY: clean
clean:
	$(MAKE) -C src $@
	$(RM) -rf build/
	find -name "*.pyc" -delete
	find -name "__pycache__" -delete
