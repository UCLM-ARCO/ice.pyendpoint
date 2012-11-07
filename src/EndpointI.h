/* -*- mode: c++; coding: utf-8 -*- */

#ifndef PYENDPOINT_ENDPOINT_I_H
#define PYENDPOINT_ENDPOINT_I_H

#include <Ice/EndpointFactory.h>
#include "InstanceF.h"

namespace PyEndpoint {

class EndpointFactoryI : public IceInternal::EndpointFactory {
public:

    virtual ~EndpointFactoryI();

    virtual Ice::Short type() const;
    virtual std::string protocol() const;
    virtual IceInternal::EndpointIPtr create(const std::string&, bool) const;
    virtual IceInternal::EndpointIPtr read(IceInternal::BasicStream*) const;
    virtual void destroy();

private:

    EndpointFactoryI(const InstancePtr&);
    friend class Instance;

    InstancePtr _instance;
};

}

#endif // PYENDPOINT_ENDPOINT_I_H

