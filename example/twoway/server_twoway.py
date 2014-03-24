#!/usr/bin/python
# -*- mode: python; coding: utf-8 -*-

import sys
import Ice


class ObjectI(Ice.Object):
    def __init__(self):
        self.count = 0

    def ice_ids(self, current=None):
        self.count += 1

        print "  ### ice_ids() was called!"
        return ["Module::Interface{0}".format(self.count)]


class Server(Ice.Application):
    def run(self, args):
        ic = self.communicator()
        endps = "twowayEndp -p1 param1"

        oa = ic.createObjectAdapterWithEndpoints("adapter", endps)
        oa.activate()

        servant = ObjectI()
        oid = ic.stringToIdentity("ServerId")
        print "Proxy @ '{}'".format(oa.add(servant, oid))

        self.shutdownOnInterrupt()
        ic.waitForShutdown()


if __name__ == "__main__":
    Server().main(sys.argv, "config")
