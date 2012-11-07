/* -*- mode: c++; coding: utf-8 -*- */

#ifndef PYENDPOINT_INSTANCE_H
#define PYENDPOINT_INSTANCE_H

#include <Ice/Communicator.h>
#include <Ice/ProtocolPluginFacadeF.h>
#include <IceUtil/Shared.h>

#include "InstanceF.h"


namespace PyEndpoint {

class Instance : public IceUtil::Shared {
public:

    Instance(const Ice::CommunicatorPtr&);

    void initialize();
    void destroy();

private:

    IceInternal::ProtocolPluginFacadePtr _facade;
};

}

#endif // PYENDPOINT_INSTANCE_H
