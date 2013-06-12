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


#ifndef PYENDPOINT_PYUTIL_H
#define PYENDPOINT_PYUTIL_H

#include <Python.h>


class PyGILEnsurer {
public:

    PyGILEnsurer() :
	acquired(false) {

	// FIXME: this implies that this thread does not know about
	// GIL, and thus it is NOT SAFE!
	if (PyGILState_GetThisThreadState() == 0) {
	    return;
	}

	// Current thread should have support for GIL API, otherwise
	// this will unsue a deadlock. Assure it.
	assert(PyGILState_GetThisThreadState() != 0);
	_gstate = PyGILState_Ensure();
	acquired = true;
    }

    ~PyGILEnsurer() {
	if (acquired)
	    PyGILState_Release(_gstate);
    }

private:
    PyGILState_STATE _gstate;
    bool acquired;
};

#endif // PYENDPOINT_PYUTIL_H
