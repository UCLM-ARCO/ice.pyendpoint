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

#include <Ice/Connector.h>

#include "PyHandle.h"
#include "InstanceF.h"


namespace PyEndpoint {

class ConnectorI: public IceInternal::Connector {
public:

    ConnectorI(PyEndpoint::InstancePtr&, PyObjectPtr&);
    virtual ~ConnectorI();

    virtual IceInternal::TransceiverPtr connect();

    virtual Ice::Short type() const;
    virtual std::string toString() const;

    virtual bool operator==(const IceInternal::Connector&) const;
    virtual bool operator!=(const IceInternal::Connector&) const;
    virtual bool operator<(const IceInternal::Connector&) const;

private:

    PyEndpoint::InstancePtr _instance;
    PyObjectPtr _pyConnector;
};

}

#endif
