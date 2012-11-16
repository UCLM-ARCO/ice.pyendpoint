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

#include <Python.h>
#include <iostream>
#include "PyUtils.h"

#include "debug.h"


// Note: use only with functions wich returns new references. If
// function's return value is a borrowed reference, this will cause
// unexpected behaviour.

template<typename T>
class PyHandle {
public:
    PyHandle(T* p = NULL) {
	IXDG std::cout << "PyHandle::PyHandle(T* p = " << p << ")"
		       << " [" << (p ? p->ob_refcnt : -1) << "]"
		       << std::endl;

	_ptr = p;
    }

    PyHandle(const PyHandle& other) {
	IXDG  std::cout << "PyHandle::PyHandle(PyHandle& other = (_ptr) "
			<< other._ptr << ") [" << (other._ptr ? other._ptr->ob_refcnt : -1)
			<< "]" << std::endl;

	PyGILEnsurer e;
	if (other._ptr && other._ptr->ob_refcnt < 1) {
	    std::cerr << "PyHandle ERROR: BadPointer (" << other._ptr
		      << "), this python object may be already destroyed!!" << std::endl;
	    throw;
	}

	_ptr = other._ptr;

	if (_ptr) {
	    Py_INCREF(_ptr);
	}
    }

    ~PyHandle() {
	IXDG std::cout << "PyHandle::~PyHandle() (_ptr) = " << _ptr
		       << " [" << (_ptr ? _ptr->ob_refcnt : -1) << "]"
		       << std::endl;

	PyGILEnsurer e;
	Py_XDECREF(_ptr);
    }

    static T* fromBorrowed(T* p) {

	PyGILEnsurer e;

	Py_INCREF(p);
	return p;
    }

    PyHandle& operator=(const PyHandle& other) {
	IXDG std::cout << "PyHandle::operator=(PyHandle& other)"
		       << other._ptr << ") [" << (other._ptr ? other._ptr->ob_refcnt : -1)
		       << "]" << std::endl;

	PyGILEnsurer e;

	if (_ptr != other._ptr) {
	    if (other._ptr) {
		Py_INCREF(other._ptr);
		Py_XDECREF(this->_ptr);
		this->_ptr = other._ptr;
	    }
	}
	return *this;
    }

    T* get() const {
	return _ptr;
    }

    operator T*() const {
	return _ptr;
    }

    T* operator->() const {
	if (not _ptr) {
	    std::cerr << "NullHandleException: trying to use null pointer" << std::endl;
	    throw;
	}
	return _ptr;
    }

private:
    T* _ptr;
};

typedef PyHandle<PyObject> PyObjectPtr;

#endif // PYENDPOINT_PYHANDLE_H
