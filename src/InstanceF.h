/* -*- mode: c++; coding: utf-8 -*- */

#ifndef PYENDPOINT_INSTANCE_F_H
#define PYENDPOINT_INSTANCE_F_H

#include <IceUtil/Shared.h>
#include <Ice/Handle.h>


namespace PyEndpoint {

class Instance;

}

namespace IceInternal {

IceUtil::Shared* upCast(PyEndpoint::Instance*);

}

namespace PyEndpoint {

typedef IceInternal::Handle<Instance> InstancePtr;

}

#endif // PYENDPOINT_INSTANCE_F_H
