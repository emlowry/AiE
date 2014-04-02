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
	{"SegmentSquareIntersect",  Geometry_SegmentSquareIntersect,    METH_VARARGS,   "Checks if a line segment and a square intersect"   },
	{"SegmentsIntersect",       Geometry_SegmentsIntersect,         METH_VARARGS,   "Checks if a pair of line segments intersect"       },
	{"PointInSquare",           Geometry_PointInSquare,             METH_VARARGS,   "Checks if a point is within a square"              },
	{NULL, NULL, 0, NULL}
};

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
