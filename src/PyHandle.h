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


#ifndef PYENDPOINT_PYHANDLE_H
#define PYENDPOINT_PYHANDLE_H

#include <iostream>
#include <Python.h>

// Note: use only with functions wich returns new references. If
// function's return value is a borrowed reference, this will cause
// unexpected behaviour.

template<typename T>
class PyHandle {
public:
    PyHandle(T* p = NULL) {
	_ptr = p;
    }

    PyHandle(const PyHandle& other) {
	_ptr = other._ptr;

	if (_ptr) {
	    Py_INCREF(_ptr);
	}
    }

    ~PyHandle() {
	Py_XDECREF(_ptr);
    }

    PyHandle& operator=(const PyHandle& other) {
	if (_ptr != other._ptr) {
	    if (other._ptr) {
		Py_INCREF(other._ptr);

		T* ptr = this->_ptr;
		this->_ptr = other._ptr;
		Py_XDECREF(ptr);
	    }
	}
	return *this;
    }

    T* get() {
	return _ptr;
    }

    operator T*() const {
	return _ptr;
    }

    T* operator->() const {
	if (not _ptr) {
	    std::cout << __FILE__ << ":" << __LINE__
		      << ": ERROR, using NullHandle" << std::endl;
	    throw;
	}
	return _ptr;
    }

private:
    T* _ptr;
};

typedef PyHandle<PyObject> PyObjectPtr;

#endif // PYENDPOINT_PYHANDLE_H
