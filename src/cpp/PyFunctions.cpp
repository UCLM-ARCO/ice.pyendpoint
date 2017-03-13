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

#include <Python.h>
#include "PyFunctions.h"
#include "PyUtils.h"


PyObjectPtr
PyFunc::importModule(std::string name) {
    PyGILEnsurer e;

    // this returns a new reference
    PyObjectPtr nameObj = PyUnicode_FromString(name.c_str());

    // this returns a new reference
    PyObjectPtr moduleObj = PyImport_Import(nameObj);

    if (not moduleObj) {
	PyErr_Print();
	throw RuntimeError();
    }

    return moduleObj;
}

PyObjectPtr
PyFunc::getClass(PyObjectPtr module, std::string name) {
    PyGILEnsurer e;

    // this returns a new reference
    PyObjectPtr classObj = PyObject_GetAttrString(module, name.c_str());

    if (not classObj) {
    	PyErr_Print();
    	throw RuntimeError();
    }

    if (not PyType_Check(classObj)) {
    	std::cerr << name << " is not a class or a valid type" << std::endl;
    	throw RuntimeError();
    }

    return classObj;
}

PyObjectPtr
PyFunc::getMethod(PyObjectPtr classObj, std::string name) {
    PyGILEnsurer e;

    if (not PyObject_HasAttrString(classObj, name.c_str())) {
	std::cerr << "object has not attribute '" << name << "'" << std::endl;
    	throw RuntimeError();
    }

    // this returns a new reference
    PyObjectPtr method = PyObject_GetAttrString(classObj, name.c_str());

    if (not PyCallable_Check(method)) {
    	std::cerr << name << " is not a valid method (is not callable)"
		  << std::endl;
    	throw RuntimeError();
    }

    return method;
}

PyObjectPtr
PyFunc::newInstance(PyObjectPtr cls) {
    return newInstance(cls, NULL);
}

PyObjectPtr
PyFunc::newInstance(PyObjectPtr cls, PyObjectPtr args) {
    PyGILEnsurer e;

    if (not PyCallable_Check(cls)) {
	std::cerr << "Object is not callable!" << std::endl;
	throw RuntimeError();
    }

    // this returns a new reference
    PyObjectPtr instance = PyObject_CallObject(cls, args);

    if (not instance) {
    	PyErr_Print();
    	throw RuntimeError();
    }

    return instance;
}

PyObjectPtr
PyFunc::callMethod(PyObjectPtr object, std::string name) {
    return callMethod(object, name, NULL);
}

PyObjectPtr
PyFunc::callMethod(PyObjectPtr object, std::string name, PyObjectPtr args) {
    PyGILEnsurer e;

    PyObjectPtr method = getMethod(object, name);

    // this returns a new reference
    PyObjectPtr result = PyObject_CallObject(method, args);

    if (not result) {
      	PyErr_Print();
	throw PyFunc::RuntimeError();
    }

    return result;
}

PyObjectPtr
PyFunc::getAttr(PyObjectPtr object, std::string name) {
    PyGILEnsurer e;

    assert(object);

    // this returns a new reference
    PyObjectPtr result = PyObject_GetAttrString(object, name.c_str());

    if (not result) {
      	PyErr_Print();
	throw PyFunc::RuntimeError();
    }

    return result;
}

bool
PyFunc::getAsBool(PyObjectPtr value) {
    return getAsInteger(value);
}

int
PyFunc::getAsInteger(PyObjectPtr value) {
    PyGILEnsurer e;

    int retval = PyLong_AsLong(value);
    if (PyErr_Occurred()) {
     	PyErr_Print();
    	throw PyFunc::RuntimeError();
    }

    return retval;
}

std::string
PyFunc::getAsString(PyObjectPtr value) {
    PyGILEnsurer e;

    Py_ssize_t length = 0;
    char* buffer;
    PyBytes_AsStringAndSize(value, &buffer, &length);

    if (PyErr_Occurred()) {
     	PyErr_Print();
    	throw PyFunc::RuntimeError();
    }

    std::string retval(buffer, length);
    return retval;
}
