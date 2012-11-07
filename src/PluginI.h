// -*- mode: c++; coding: utf-8 -*-

#ifndef PLUGIN_H
#define PLUGIN_H

#include <Ice/Ice.h>
#include "InstanceF.h"

namespace PyEndpoint {

class PluginI : public Ice::Plugin {
public:

    PluginI(const Ice::CommunicatorPtr&);

    void initialize();
    void destroy();

private:
    InstancePtr _instance;
};

}

#endif // PLUGIN_H
