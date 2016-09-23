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


#include <Ice/LocalException.h>

#include "Ice/ProtocolInstance.h"

#include "PyConnector.h"
#include "PyFunctions.h"
#include "PyConnectorsCallback.h"
#include "debug.h"


struct PyConnectorsCallbackObject {

    PyObject_HEAD
    IceInternal::EndpointI_connectorsPtr* cb;
    IceInternal::ProtocolInstancePtr* instance;
};

static void
PyConnectorsCallback_dealloc(PyConnectorsCallbackObject* self) {
    trace();

    delete self->cb;
    delete self->instance;
    PyObject_Del(self);
}

static PyObject*
PyConnectorsCallback_connectors(PyConnectorsCallbackObject* self, PyObject* args) {
    trace();

    PyObject* connList;
    if (not PyArg_ParseTuple(args, "O!", &PyList_Type, &connList)) {
	return NULL;
    }

    if (PyList_Size(connList) == 0) {
	PyErr_SetString(PyExc_ValueError,
			"need at least one connector (none received)");
	return NULL;
    }

    IceInternal::ConnectorPtr connector;
    PyObjectPtr pyConnector;
    std::vector< IceInternal::ConnectorPtr > retval;

    for (short i=0; i<PyList_Size(connList); i++) {

	pyConnector = PyObjectPtr::fromBorrowed(PyList_GetItem(connList, i));
	connector = new PyEndpoint::PyConnector(*self->instance, pyConnector);
	retval.push_back(connector);
    }

    (*self->cb)->connectors(retval);
    Py_RETURN_NONE;
}

static PyObject*
PyConnectorsCallback_exception(PyConnectorsCallbackObject* self, PyObject* args) {
    trace();

    Py_RETURN_NONE;
}

static PyMethodDef PyConnectorsCallbackMethods[] = {

    { "connectors", (PyCFunction)PyConnectorsCallback_connectors,
      METH_VARARGS, "internal function" },
    { "exception", (PyCFunction)PyConnectorsCallback_exception,
      METH_VARARGS, "internal function" },

    { NULL } /* sentinel */
};


PyTypeObject PyConnectorsCallbackType = {

    PyObject_HEAD_INIT(0)
    0,                                /* ob_size */
    "PyEndpoint.PyConnectorsCallback",  /* tp_name */
    sizeof(PyConnectorsCallbackObject), /* tp_basicsize */
    0,                                /* tp_itemsize */
    reinterpret_cast<destructor>(PyConnectorsCallback_dealloc), /* tp_dealloc */
    0,                                /* tp_print */
    0,                                /* tp_getattr */
    0,                                /* tp_setattr */
    0,                                /* tp_compare */
    0,                                /* tp_repr */
    0,                                /* tp_as_number */
    0,                                /* tp_as_sequence */
    0,                                /* tp_as_mapping */
    0,                                /* tp_hash */
    0,                                /* tp_call */
    0,                                /* tp_str */
    0,                                /* tp_getattro */
    0,                                /* tp_setattro */
    0,                                /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,               /* tp_flags */
    0,                                /* tp_doc */
    0,                                /* tp_traverse */
    0,                                /* tp_clear */
    0,                                /* tp_richcompare */
    0,                                /* tp_weaklistoffset */
    0,                                /* tp_iter */
    0,                                /* tp_iternext */
    PyConnectorsCallbackMethods         /* tp_methods */
};

void
PyEndpoint::PyConnectorsCallback_initModule() {
    trace();

    PyGILEnsurer pge;
    if (PyType_Ready(&PyConnectorsCallbackType) < 0) {
    	std::cerr << "ERROR: could not initialize PyConnectorsCallback type"
    		  << std::endl;
    	throw PyFunc::RuntimeError();
    }
}

PyObjectPtr
PyEndpoint::PyConnectorsCallback_new(const IceInternal::ProtocolInstancePtr& instance,
				     const IceInternal::EndpointI_connectorsPtr& cb) {
    trace();

    PyConnectorsCallbackObject* self = PyObject_New(PyConnectorsCallbackObject,
						    &PyConnectorsCallbackType);
    if (not self) {
        return 0;
    }

    self->instance = new IceInternal::ProtocolInstancePtr(instance);
    self->cb = new IceInternal::EndpointI_connectorsPtr(cb);
    return reinterpret_cast<PyObject*>(self);
}
