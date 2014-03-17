/******************************************************************************
 * File:               QuadFragment.glsl
 * Author:             Elizabeth Lowry
 * Date Created:       February 25, 2014
 * Description:        Fragment shader for a solid Quad.
 * Last Modified:      March 17, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#version 410

uniform vec4 u_v4Color;

void main()
{
    gl_FragColor = u_v4Color;
}
