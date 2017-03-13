#!/usr/bin/python3 -u
# -*- mode: python; coding: utf-8 -*-

import sys
import Ice


class ObjectI(Ice.Object):
    def ice_ping(self, current=None):
        print("  ### ice_ping() was called!")


class Server(Ice.Application):
    def run(self, args):
        ic = self.communicator()
        endps = "datagramEndp -p1 param1"

        oa = ic.createObjectAdapterWithEndpoints("adapter", endps)
        oa.activate()

        servant = ObjectI()
        oid = ic.stringToIdentity("ServerId")
        print("Proxy @ '{}'".format(oa.add(servant, oid)))
        sys.stdout.flush()

        self.shutdownOnInterrupt()
        ic.waitForShutdown()


if __name__ == "__main__":
    Server().main(sys.argv, "config")
