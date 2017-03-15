#!/usr/bin/env python3
# -*- mode: python; coding: utf-8 -*-

from distutils.core import setup

def get_version():
    with open('debian/changelog', errors='ignore') as chlog:
        line = chlog.readline()
        return line.split()[1][1:-1]

setup(name         = 'Ice-PyEndpoint',
      version      = get_version(),
      description  = 'ZeroC-ICE plugin for Python endpoints',
      author       = 'Oscar Aceña',
      author_email = 'oscaracena@gmail.com',
      url          = 'https://bitbucket.org/arco_group/ice-pyendpoint',

      package_dir  = {'': 'src/python'},
      py_modules   = ['pyendpoint'],
     )
