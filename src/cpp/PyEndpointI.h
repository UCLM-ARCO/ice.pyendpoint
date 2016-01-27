// -*- mode: c++; coding: utf-8; truncate-lines: true -*-

//
// Copyright (c) 2012-2016 Oscar Aceña. All rights reserved.
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

#ifndef _PYENDPOINTI_H_
#define _PYENDPOINTI_H_

#include <Ice/Communicator.h>
#include <Ice/EndpointFactory.h>

#include "Ice/EndpointI.h"

#include "PyEndpointF.h"


namespace PyEndpoint {

class PyEndpointI : public IceInternal::EndpointI {
public:

    PyEndpointI(const IceInternal::ProtocolInstancePtr&, PyObjectPtr);
    virtual ~PyEndpointI() {};

    virtual Ice::EndpointInfoPtr getInfo() const;
    virtual void streamWrite(IceInternal::BasicStream*) const;

    virtual Ice::Short type() const;
    virtual const std::string& protocol() const;
    virtual Ice::Int timeout() const;
    virtual IceInternal::EndpointIPtr timeout(Ice::Int) const;
    virtual bool compress() const;
    virtual IceInternal::EndpointIPtr compress(bool) const;
    virtual bool datagram() const;
    virtual bool secure() const;

    PyEndpointIPtr endpoint(const PyAcceptorPtr&) const;

    virtual const std::string& connectionId() const;
    virtual IceInternal::EndpointIPtr connectionId(const std::string&) const;

    virtual IceInternal::TransceiverPtr transceiver() const;
    virtual IceInternal::AcceptorPtr acceptor(const std::string&) const;
    virtual std::vector<IceInternal::EndpointIPtr> expand() const;
    virtual bool equivalent(const IceInternal::EndpointIPtr&) const;
    virtual Ice::Int hash() const;
    virtual std::string options() const;

    virtual void connectors_async(Ice::EndpointSelectionType,
				  const IceInternal::EndpointI_connectorsPtr&) const;

    virtual bool operator==(const Ice::LocalObject&) const;
    virtual bool operator<(const Ice::LocalObject&) const;

    virtual void initWithOptions(std::vector<std::string>&, bool);
    virtual void initWithOptions(std::vector<std::string>&);

private:

    IceInternal::ProtocolInstancePtr _instance;
    PyObjectPtr _pyEndpoint;

    std::string _protocol; // needed by method protocol(), it returns a reference
    std::string _connectionId; // needed by method connectionId(), it returns a reference
};

class PyEndpointFactory : public IceInternal::EndpointFactory {
public:

    PyEndpointFactory(const std::string& name, const Ice::CommunicatorPtr& ic) ;
    virtual ~PyEndpointFactory();

    virtual Ice::Short type() const;
    virtual std::string protocol() const;
    virtual IceInternal::EndpointIPtr create(std::vector<std::string>&, bool) const;
    virtual IceInternal::EndpointIPtr read(IceInternal::BasicStream*) const;
    virtual void destroy();

    virtual IceInternal::EndpointFactoryPtr clone(const IceInternal::ProtocolInstancePtr&) const;

private:

    IceInternal::ProtocolInstancePtr _instance;
    PyObjectPtr _pyFactory;
};

}

#endif /* _PYENDPOINTI_H_ */
