/******************************************************************************
 * File:               QuadVertex.glsl
 * Author:             Elizabeth Lowry
 * Date Created:       February 25, 2014
 * Description:        Vertex shader for a solid Quad.
 * Last Modified:      February 25, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

# version 150

in vec2 i_v2Position;

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * vec4( i_v2Position, 0.0, 1.0 );
}