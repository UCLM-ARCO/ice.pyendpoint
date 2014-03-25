# -*- mode: shell; coding: utf-8 -*-

BASE=$(cd ../.. && pwd)

export LD_LIBRARY_PATH=$BASE/src/cpp
export PYTHONPATH=$BASE/src/python:$(pwd)
