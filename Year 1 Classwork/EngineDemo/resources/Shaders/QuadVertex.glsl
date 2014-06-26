/******************************************************************************
 * File:               QuadVertex.glsl
 * Author:             Elizabeth Lowry
 * Date Created:       February 25, 2014
 * Description:        Vertex shader for a solid Quad.
 * Last Modified:      June 26, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#version 410

uniform dmat4 u_dm4ModelViewProjection;

in vec2 i_v2Position;

void main()
{
    gl_Position = vec4( u_dm4ModelViewProjection * vec4( i_v2Position, 0.0, 1.0 ));
}
