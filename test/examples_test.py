# -*- mode: python; coding: utf-8 -*-

from hamcrest import contains_string
from prego import TestCase, Task, context as ctx


class TestDatagram(TestCase):
    def setUp(self):
        ctx.example = "example/datagram"
        self.env = {"LD_LIBRARY_PATH": "../../src/cpp",
                    "PYTHONPATH": "../../src/python:../../example/datagram"}

        gcc = Task("compile pyEndpoint plugin")
        gcc.command("make", timeout=20)

    def test(self):
        # run server
        server = Task("Run datagram server", detach=True)
        server.command("./server_datagram.py", cwd="$example", env=self.env)
        server.assert_that(server.lastcmd.stdout.content,
                           contains_string("ice_ping() was called"))

        # run client
        client = Task("Run datagram client")
        client.command("./client_datagram.py", cwd="$example", env=self.env)


class TestTwoway(TestCase):
    def setUp(self):
        ctx.example = "example/twoway"
        self.env = {"LD_LIBRARY_PATH": "../../src/cpp",
                    "PYTHONPATH": "../../src/python:../../example/twoway"}

        gcc = Task("compile pyEndpoint plugin")
        gcc.command("make", timeout=20)

    def test(self):
        # run server
        server = Task("Run twoway server", detach=True)
        server.command("./server_twoway.py", cwd="$example", env=self.env)
        server.assert_that(server.lastcmd.stdout.content,
                           contains_string("ice_ids() was called"))

        # run client
        client = Task("Run twoway client")
        client.command("./client_twoway.py", cwd="$example", env=self.env)
        client.assert_that(client.lastcmd.stdout.content,
                           contains_string("IDS: ['Module::Interface1']"))
