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


#include "BasicStream.h"
#include "PyFunctions.h"

#include "debug.h"


struct BasicStreamObject {

    PyObject_HEAD
    IceInternal::BasicStream* s;
};

extern PyTypeObject BasicStreamType;

void
BasicStream_initModule() {

    if(PyType_Ready(&BasicStreamType) < 0) {
 	std::cerr << "ERROR: could not initialize BasicStream type"
		  << std::endl;
	throw PyFunc::RuntimeError();
    }
}

PyObject*
BasicStream_new(IceInternal::BasicStream* s) {

    IDG std::cout << " - call to BasicStream_new()" << std::endl;

    BasicStreamObject* self = PyObject_New(BasicStreamObject,
					   &BasicStreamType);

    if(not self) {
	return 0;
    }

    self->s = s;
    return reinterpret_cast<PyObject*>(self);
}

static PyObject*
BasicStream_readInt(BasicStreamObject* self, PyObject* args) {
    Py_RETURN_NONE;
}

// static PyObject*
// ConnectorsCallback_connectors(ConnectorsCallbackObject* self, PyObject* args) {

//     IDG std::cout << " - call to ConnectorsCallback_connectors()" << std::endl;

//     PyObject* connList;
//     if (not PyArg_ParseTuple(args, "O!", &PyList_Type, &connList)) {
// 	return NULL;
//     }

//     if (PyList_Size(connList) == 0) {
// 	PyErr_SetString(PyExc_ValueError,
// 			"need at least one connector (none received)");
// 	return NULL;
//     }

//     IceInternal::ConnectorPtr connector;
//     PyObjectPtr pyConnector;
//     std::vector< IceInternal::ConnectorPtr > retval;

//     for (short i=0; i<PyList_Size(connList); i++) {

// 	pyConnector = PyObjectPtr::fromBorrowed(PyList_GetItem(connList, i));
// 	connector = new PyEndpoint::ConnectorI(*self->instance, pyConnector);
// 	retval.push_back(connector);
//     }

//     (*self->cb)->connectors(retval);
//     Py_RETURN_NONE;
// }

//  static PyObject*
// ConnectorsCallback_exception(ConnectorsCallbackObject* self, PyObject* args) {

//     IDG std::cout << " - call to ConnectorsCallback_exception()" << std::endl;

//     Py_RETURN_NONE;
// }

static PyMethodDef basicStreamMethods[] = {

    { "readInt", (PyCFunction)BasicStream_readInt,
      METH_VARARGS, "internal function" },
//     { "exception", (PyCFunction)ConnectorsCallback_exception,
//       METH_VARARGS, "internal function" },

    { NULL } /* sentinel */
};


PyTypeObject BasicStreamType = {

    PyObject_HEAD_INIT(0)
    0,                            /* ob_size */
    "PyEndpoint.BasicStream",     /* tp_name */
    sizeof(BasicStreamObject),    /* tp_basicsize */
    0,                            /* tp_itemsize */
    0,                            /* tp_dealloc */
    0,                            /* tp_print */
    0,                            /* tp_getattr */
    0,                            /* tp_setattr */
    0,                            /* tp_compare */
    0,                            /* tp_repr */
    0,                            /* tp_as_number */
    0,                            /* tp_as_sequence */
    0,                            /* tp_as_mapping */
    0,                            /* tp_hash */
    0,                            /* tp_call */
    0,                            /* tp_str */
    0,                            /* tp_getattro */
    0,                            /* tp_setattro */
    0,                            /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,           /* tp_flags */
    0,                            /* tp_doc */
    0,                            /* tp_traverse */
    0,                            /* tp_clear */
    0,                            /* tp_richcompare */
    0,                            /* tp_weaklistoffset */
    0,                            /* tp_iter */
    0,                            /* tp_iternext */
    basicStreamMethods            /* tp_methods */
};

