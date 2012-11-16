#!/usr/bin/python
# -*- mode: python; coding: utf-8 -*-

import sys
import Ice


class Server(Ice.Application):
    def run(self, args):
        ic = self.communicator()
        endps = "example -p1 param1"

        oa = ic.createObjectAdapterWithEndpoints("adapter", endps)
        oa.activate()

        servant = Ice.Object()
        oid = ic.stringToIdentity("ServerId")
        print "Proxy @ '{}'".format(oa.add(servant, oid))

        ic.shutdownOnInterrupt()
        self.waitForShutdown()



if __name__ == "__main__":
    Server().main(sys.argv, "config")
