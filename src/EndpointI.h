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

#include <Ice/EndpointI.h>
#include <Ice/EndpointFactory.h>

#include "PyHandle.h"
#include "InstanceF.h"


namespace PyEndpoint {

class EndpointI : public IceInternal::EndpointI {
public:

//     XbowEndpointI(const IceXbow::InstancePtr&, const std::string&, Ice::Int, const std::string&, Ice::Int,
// 		 Ice::Byte, Ice::Byte, Ice::Byte, Ice::Byte, bool, const std::string&, bool);
//     XbowEndpointI(const IceXbow::InstancePtr&, const std::string&, bool);
//     XbowEndpointI(const IceXbow::InstancePtr&, BasicStream*);

//     virtual void streamWrite(BasicStream*) const;
//     virtual std::string toString() const;
//     virtual Ice::Short type() const;
//     virtual Ice::Int timeout() const;
//     virtual EndpointIPtr timeout(Ice::Int) const;
//     virtual EndpointIPtr connectionId(const ::std::string&) const;
//     virtual bool compress() const;
//     virtual EndpointIPtr compress(bool) const;
//     virtual bool datagram() const;
//     virtual bool secure() const;
//     virtual bool unknown() const;
//     virtual TransceiverPtr transceiver(EndpointIPtr&) const;
//     virtual std::vector<ConnectorPtr> connectors() const;
//     virtual void connectors_async(const EndpointI_connectorsPtr&) const;
//     virtual AcceptorPtr acceptor(EndpointIPtr&, const std::string&) const;
//     virtual std::vector<EndpointIPtr> expand() const;
//     virtual bool equivalent(const EndpointIPtr&) const;

//     virtual bool operator==(const EndpointI&) const;
//     virtual bool operator!=(const EndpointI&) const;
//     virtual bool operator<(const EndpointI&) const;

// private:

//     virtual std::vector<ConnectorPtr> connectors(const std::vector<struct sockaddr_storage>&) const;

//     //
//     // All members are const, because endpoints are immutable.
//     //
//     const IceXbow::InstancePtr _instance;
//     const std::string _host;
//     const Ice::Int _port;
//     const std::string _mcastInterface;
//     const Ice::Int _mcastTtl;
//     const Ice::Byte _protocolMajor;
//     const Ice::Byte _protocolMinor;
//     const Ice::Byte _encodingMajor;
//     const Ice::Byte _encodingMinor;
//     const bool _connect;
//     const std::string _connectionId;
//     const bool _compress;

//     // Remove this
//     Ice::LoggerPtr _logger;
};

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
    PyObjectPtr _pyFactory;
    InstancePtr _instance;
};

}

#endif // PYENDPOINT_ENDPOINT_I_H

