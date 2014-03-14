/******************************************************************************
 * File:               SpriteVertex.glsl
 * Author:             Elizabeth Lowry
 * Date Created:       March 12, 2014
 * Description:        Vertex shader for a Sprite.
 * Last Modified:      March 13, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

# version 150

//uniform dmat3 u_dm3TexTransform;

in vec2 i_v2Position;
in vec2 i_v2TexCoordinate;

//out dvec2 v_dv2TexCoordinate;
out vec2 v_v2TexCoordinate;

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * vec4( i_v2Position, 0.0, 1.0 );
    //dvec3 dv3TexCoordinate = u_dm3TexTransform * dvec3( i_v2TexCoordinate, 1.0 );
    //v_dv2TexCoordinate = dv3TexCoordinate.xy;
    v_v2TexCoordinate = i_v2TexCoordinate;
}