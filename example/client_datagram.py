#!/usr/bin/python
# -*- mode: python; coding: utf-8 -*-

import sys
import Ice


class Client(Ice.Application):
    def run(self, args):
        ic = self.communicator()
        proxy = ic.stringToProxy("ObjectId -d:example -h 127.0.0.1 -p 9999")
        proxy.ice_ping()


if __name__ == "__main__":
    Client().main(sys.argv, "config")
