/* -*- mode: c++; coding: utf-8 -*- */

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

#ifndef _PYCONNECTOR_H_
#define _PYCONNECTOR_H_

#include "Ice/Connector.h"
#include "Ice/ProtocolInstanceF.h"

#include "PyHandle.h"


namespace PyEndpoint {

class PyConnector: public IceInternal::Connector {
public:

    virtual IceInternal::TransceiverPtr connect();

    virtual Ice::Short type() const;
    virtual std::string toString() const;

    virtual bool operator==(const IceInternal::Connector&) const;
    virtual bool operator!=(const IceInternal::Connector&) const;
    virtual bool operator<(const IceInternal::Connector&) const;

    PyConnector(const IceInternal::ProtocolInstancePtr&, PyObjectPtr&);
    virtual ~PyConnector() {};

private:

    const IceInternal::ProtocolInstancePtr _instance;
    const PyObjectPtr _pyConnector;
};

}

#endif /* _PYCONNECTOR_H_ */
