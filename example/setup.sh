# -*- mode: shell; coding: utf-8 -*-

cd ../src/cpp                         && \
export LD_LIBRARY_PATH=$(pwd)         && \
cd ../python                          && \
export PYTHONPATH=$(pwd)              && \
cd ../../example/                     && \
export PYTHONPATH=$PYTHONPATH:$(pwd)

