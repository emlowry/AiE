/******************************************************************************
 * File:               Geometry_Py.cpp
 * Author:             Elizabeth Lowry
 * Date Created:       April 1, 2014
 * Description:        Declares functions for a collision detection module.
 * Last Modified:      April 1, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

#include "Geometry_Py.h"
#include "Geometry.h"
#include "AIE_Py.h"
#include <Python.h>

PyMethodDef Geometry_Functions[] = 
{
	{"SegmentCircleIntersect",  Geometry_SegmentCircleIntersect,    METH_VARARGS,   "Checks if a line segment and a circle intersect"   },
	{"SegmentSquareIntersect",  Geometry_SegmentSquareIntersect,    METH_VARARGS,   "Checks if a line segment and a square intersect"   },
	{"SegmentsIntersect",       Geometry_SegmentsIntersect,         METH_VARARGS,   "Checks if a pair of line segments intersect"       },
	{"PointInSquare",           Geometry_PointInSquare,             METH_VARARGS,   "Checks if a point is within a square"              },
	{"RayCircleDistance",       Geometry_RayCircleDistance,         METH_VARARGS,   "Returns distance along a ray to a circle"          },
	{"RaySquareDistance",       Geometry_RaySquareDistance,         METH_VARARGS,   "Returns distance along a ray to a square"          },
	{"RaySegmentDistance",      Geometry_RaySegmentDistance,        METH_VARARGS,   "Returns distance along a ray to a line segment"    },
	{NULL, NULL, 0, NULL}
};

PyObject* Geometry_SegmentCircleIntersect( PyObject *self, PyObject *args )
{
    LineSegment oSegment;
    Circle oCircle;
    if ( !PyArg_ParseTuple( args, "fffffff",
                            &oSegment.point1.x, &oSegment.point1.y,
                            &oSegment.point2.x, &oSegment.point2.y,
                            &oCircle.location.x, &oCircle.location.y,
                            &oCircle.radius ) )
    {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
    }
    if( SegmentCircleIntersect( oSegment, oCircle ) )
    {
        Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
}

PyObject* Geometry_SegmentSquareIntersect( PyObject *self, PyObject *args )
{
    LineSegment oSegment;
    Square oSquare;
    if ( !PyArg_ParseTuple( args, "ffffffff",
                            &oSegment.point1.x, &oSegment.point1.y,
                            &oSegment.point2.x, &oSegment.point2.y,
                            &oSquare.corner1.x, &oSquare.corner1.y,
                            &oSquare.corner2.x, &oSquare.corner2.y ) )
    {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
    }
    if( SegmentSquareIntersect( oSegment, oSquare ) )
    {
        Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
}

PyObject* Geometry_SegmentsIntersect( PyObject *self, PyObject *args )
{
    LineSegment oSegment1, oSegment2;
    if ( !PyArg_ParseTuple( args, "ffffffff",
                            &oSegment1.point1.x, &oSegment1.point1.y,
                            &oSegment1.point2.x, &oSegment1.point2.y,
                            &oSegment2.point1.x, &oSegment2.point1.y,
                            &oSegment2.point2.x, &oSegment2.point2.y ) )
    {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
    }
    if( SegmentsIntersect( oSegment1, oSegment2 ) )
    {
        Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
}

PyObject* Geometry_PointInSquare( PyObject *self, PyObject *args )
{
    Point oPoint;
    Square oSquare;
    if ( !PyArg_ParseTuple( args, "ffffff", &oPoint.x, &oPoint.y,
                            &oSquare.corner1.x, &oSquare.corner1.y,
                            &oSquare.corner2.x, &oSquare.corner2.y ) )
    {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
    }
    if( PointInSquare( oPoint, oSquare ) )
    {
        Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
}

PyObject* Geometry_RayCircleDistance( PyObject *self, PyObject *args )
{
    Ray oRay;
    Circle oCircle;
    if ( !PyArg_ParseTuple( args, "fffffff",
                            &oRay.location.x, &oRay.location.y,
                            &oRay.direction.x, &oRay.direction.y,
                            &oCircle.location.x, &oCircle.location.y,
                            &oCircle.radius ) )
    {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
    }
	return Py_BuildValue("f", RayCircleDistance( oRay, oCircle ) );
}

PyObject* Geometry_RaySquareDistance( PyObject *self, PyObject *args )
{
    Ray oRay;
    Square oSquare;
    if ( !PyArg_ParseTuple( args, "ffffffff",
                            &oRay.location.x, &oRay.location.y,
                            &oRay.direction.x, &oRay.direction.y,
                            &oSquare.corner1.x, &oSquare.corner1.y,
                            &oSquare.corner2.x, &oSquare.corner2.y ) )
    {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
    }
	return Py_BuildValue("f", RaySquareDistance( oRay, oSquare ) );
}

PyObject* Geometry_RaySegmentDistance( PyObject *self, PyObject *args )
{
    Ray oRay;
    LineSegment oSegment;
    if ( !PyArg_ParseTuple( args, "ffffffff",
                            &oRay.location.x, &oRay.location.y,
                            &oRay.direction.x, &oRay.direction.y,
                            &oSegment.point1.x, &oSegment.point1.y,
                            &oSegment.point2.x, &oSegment.point2.y ) )
    {
		ParsePyTupleError( __func__, __LINE__ );
		return nullptr;
    }
	return Py_BuildValue("f", RaySegmentDistance( oRay, oSegment ) );
}
