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

    IDG std::cout << " - call to BasicStream_new(" << s << ")" << std::endl;

    BasicStreamObject* self = PyObject_New(BasicStreamObject, &BasicStreamType);
    if(not self) {
	return 0;
    }

    self->s = s;
    return reinterpret_cast<PyObject*>(self);
}

static PyObject*
BasicStream_startReadEncaps(BasicStreamObject* self, PyObject* args) {

    IDG std::cout << " - call to BasicStream_startReadEncaps()" << std::endl;

    self->s->startReadEncaps();
    Py_RETURN_NONE;
}

static PyObject*
BasicStream_endReadEncaps(BasicStreamObject* self, PyObject* args) {

    IDG std::cout << " - call to BasicStream_endReadEncaps()" << std::endl;

    self->s->endReadEncaps();
    Py_RETURN_NONE;
}

static PyObject*
BasicStream_readString(BasicStreamObject* self, PyObject* args) {

    IDG std::cout << " - call to BasicStream_readString()" << std::endl;

    std::string retval;
    self->s->read(retval);
    return PyString_FromStringAndSize(retval.data(), retval.size());
}

static PyObject*
BasicStream_readBlob(BasicStreamObject* self, PyObject* args) {

    IDG std::cout << " - call to BasicStream_readBlob()" << std::endl;

    int size;
    if (not PyArg_ParseTuple(args, "i", &size)) {
     	return NULL;
    }

    const Ice::Byte* blob;
    self->s->readBlob(blob, size);
    return PyString_FromStringAndSize((const char*)blob, size);
}

static PyObject*
BasicStream_startWriteEncaps(BasicStreamObject* self, PyObject* args) {

    IDG std::cout << " - call to BasicStream_startWriteEncaps()" << std::endl;

    self->s->startWriteEncaps();
    Py_RETURN_NONE;
}

static PyObject*
BasicStream_endWriteEncaps(BasicStreamObject* self, PyObject* args) {

    IDG std::cout << " - call to BasicStream_endWriteEncaps()" << std::endl;

    self->s->endWriteEncaps();
    Py_RETURN_NONE;
}

static PyObject*
BasicStream_writeString(BasicStreamObject* self, PyObject* args) {

    IDG std::cout << " - call to BasicStream_writeString()" << std::endl;

    char* data;
    int size;
    if (not PyArg_ParseTuple(args, "s#", &data, &size)) {
     	return NULL;
    }

    IDG std::cout << "    -> string: " << std::string(data, size) << std::endl;

    self->s->write(std::string(data, size));
    Py_RETURN_NONE;
}

static PyObject*
BasicStream_writeByte(BasicStreamObject* self, PyObject* args) {

    IDG std::cout << " - call to BasicStream_writeByte()" << std::endl;

    Ice::Byte b;
    if (not PyArg_ParseTuple(args, "b", &b)) {
     	return NULL;
    }

    IDG std::cout << "    -> byte: " << (int)b << std::endl;

    self->s->write(b);
    Py_RETURN_NONE;
}

static PyObject*
BasicStream_writeBlob(BasicStreamObject* self, PyObject* args) {

    IDG std::cout << " - call to BasicStream_writeBlob()" << std::endl;

    Ice::Byte* data;
    int size;
    int count;
    if (not PyArg_ParseTuple(args, "s#i", &data, &size, &count)) {
     	return NULL;
    }

    if (count > size) {
    	std::cerr << "ValueError, need at least one endpoint from expand()"
		  << std::endl;
     	throw PyFunc::RuntimeError();
    }

    self->s->writeBlob(data, count);
    Py_RETURN_NONE;
}

static PyMethodDef basicStreamMethods[] = {

    { "startReadEncaps", (PyCFunction)BasicStream_startReadEncaps,
      METH_VARARGS, "prepare stream for reading" },
    { "endReadEncaps", (PyCFunction)BasicStream_endReadEncaps,
      METH_VARARGS, "notify end of stream reading" },
    { "readString", (PyCFunction)BasicStream_readString,
      METH_VARARGS, "read a string from stream" },
    { "readBlob", (PyCFunction)BasicStream_readBlob,
      METH_VARARGS, "read n bytes from stream" },

    { "startWriteEncaps", (PyCFunction)BasicStream_startWriteEncaps,
      METH_VARARGS, "prepare stream for writing" },
    { "endWriteEncaps", (PyCFunction)BasicStream_endWriteEncaps,
      METH_VARARGS, "notify end of stream writing" },
    { "writeString", (PyCFunction)BasicStream_writeString,
      METH_VARARGS, "write a string to stream" },
    { "writeByte", (PyCFunction)BasicStream_writeByte,
      METH_VARARGS, "write a byte to stream" },
    { "writeBlob", (PyCFunction)BasicStream_writeBlob,
      METH_VARARGS, "write b bytes to stream" },

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
