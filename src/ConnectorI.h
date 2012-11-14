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


#ifndef PYENDPOINT_CONNECTOR_I_H
#define PYENDPOINT_CONNECTOR_I_H

#include "Ice/ConnectorF.h"

namespace PyEndpoint {

class ConnectorI : public IceInternal::Connector {
public:

    virtual IceInternal::TransceiverPtr connect();

    virtual Ice::Short type() const;
    virtual std::string toString() const;

    virtual bool operator==(const IceInternal::Connector&) const;
    virtual bool operator!=(const IceInternal::Connector&) const;
    virtual bool operator<(const IceInternal::Connector&) const;

private:

    ConnectorI(const InstancePtr&, const std::string&, const struct sockaddr_storage&, Ice::Int, const std::string&);
    virtual ~ConnectorI();
    friend class EndpointI;

    const InstancePtr _instance;
}

}

#endif // PYENDPOINT_CONNECTOR_I_H
