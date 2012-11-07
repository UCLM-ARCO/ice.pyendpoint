#!/usr/bin/python
# -*- mode: python; coding: utf-8 -*-

import sys
import Ice


class Client(Ice.Application):
    def run(self, args):
        pass


if __name__ == "__main__":
    Client().main(sys.argv, "config")
