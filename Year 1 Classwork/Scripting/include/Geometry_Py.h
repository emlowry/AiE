/******************************************************************************
 * File:               Geometry_Py.h
 * Author:             Elizabeth Lowry
 * Date Created:       April 1, 2014
 * Description:        Declares functions for a collision detection module.
 * Last Modified:      April 1, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#ifndef GEOMETRY__PY__H
#define GEOMETRY__PY__H

#include <Python.h>

#if defined ( _WIN32 )
#define __func__ __FUNCTION__
#endif

extern PyMethodDef Geometry_Functions[];

static PyObject* Geometry_SegmentCircleIntersect( PyObject *self, PyObject *args );
static PyObject* Geometry_SegmentSquareIntersect( PyObject *self, PyObject *args );
static PyObject* Geometry_SegmentsIntersect( PyObject *self, PyObject *args );
static PyObject* Geometry_PointInSquare( PyObject *self, PyObject *args );
static PyObject* Geometry_RayCircleDistance( PyObject *self, PyObject *args );
static PyObject* Geometry_RaySquareDistance( PyObject *self, PyObject *args );
static PyObject* Geometry_RaySegmentDistance( PyObject *self, PyObject *args );

#endif  // GEOMETRY__PY__H