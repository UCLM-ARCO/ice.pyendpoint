/* -*- mode: c++; coding: utf-8 -*- */

//
// Copyright (c) 2012 Oscar Aceña. All rights reserved.
//
// This file is part of PyEndpoint
//
// PyEndpoint is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// PyEndpoint is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with PyEndpoint.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef PYENDPOINT_ENDPOINT_I_H
#define PYENDPOINT_ENDPOINT_I_H

#include <Ice/EndpointFactory.h>

#include "PyHandle.h"
#include "Ice/EndpointI.h"
#include "InstanceF.h"


namespace PyEndpoint {

class EndpointI : public IceInternal::EndpointI {
public:

    EndpointI(const InstancePtr&, PyObjectPtr);

    virtual void streamWrite(IceInternal::BasicStream*) const;
    virtual std::string toString() const;
    virtual Ice::EndpointInfoPtr getInfo() const;
    virtual Ice::Short type() const;
    virtual Ice::Int timeout() const;
    virtual IceInternal::EndpointIPtr timeout(Ice::Int) const;
    virtual IceInternal::EndpointIPtr connectionId(const ::std::string&) const;
    virtual bool compress() const;
    virtual IceInternal::EndpointIPtr compress(bool) const;
    virtual bool datagram() const;
    virtual bool secure() const;
    virtual IceInternal::TransceiverPtr transceiver(IceInternal::EndpointIPtr&) const;
    virtual std::vector<IceInternal::ConnectorPtr> connectors() const;
    virtual void connectors_async(const IceInternal::EndpointI_connectorsPtr&) const;
    virtual IceInternal::AcceptorPtr acceptor(IceInternal::EndpointIPtr&,
					      const std::string&) const;
    virtual std::vector<IceInternal::EndpointIPtr> expand() const;
    virtual bool equivalent(const IceInternal::EndpointIPtr&) const;

    virtual bool operator==(const Ice::LocalObject&) const;
    virtual bool operator<(const Ice::LocalObject&) const;

private:

    virtual ::Ice::Int hashInit() const;

    const InstancePtr _instance;
    PyObjectPtr _pyEndpoint;
};

class EndpointFactoryI : public IceInternal::EndpointFactory
{
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

    PyObjectPtr _pyFactory;
    InstancePtr _instance;
};

}

#endif // PYENDPOINT_ENDPOINT_I_H
