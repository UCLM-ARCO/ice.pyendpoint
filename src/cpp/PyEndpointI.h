// -*- mode: c++; coding: utf-8 -*-

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


namespace PyEndpoint {

class PyEndpointFactory : public IceInternal::EndpointFactory {
public:

    PyEndpointFactory(const Ice::CommunicatorPtr& ic) ;
    virtual ~PyEndpointFactory();

    virtual Ice::Short type() const;
    virtual std::string protocol() const;
    virtual IceInternal::EndpointIPtr create(std::vector<std::string>&, bool) const;
    virtual IceInternal::EndpointIPtr read(IceInternal::BasicStream*) const;
    virtual void destroy();

    virtual IceInternal::EndpointFactoryPtr clone(const IceInternal::ProtocolInstancePtr&) const;

private:

    IceInternal::ProtocolInstancePtr _instance;
};

}

#endif /* _PYENDPOINTI_H_ */
