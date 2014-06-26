/******************************************************************************
 * File:               SpriteVertex.glsl
 * Author:             Elizabeth Lowry
 * Date Created:       March 12, 2014
 * Description:        Vertex shader for a Sprite.
 * Last Modified:      June 26, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#version 410

uniform dmat4 u_dm4ModelViewProjection;
uniform dmat3 u_dm3TexTransform;

in vec2 i_v2Position;
in vec2 i_v2TexCoordinate;

out vec2 v_v2TexCoordinate;

void main()
{
    gl_Position = vec4( u_dm4ModelViewProjection * vec4( i_v2Position, 0.0, 1.0 ));
    dvec3 dv3TexCoordinate = u_dm3TexTransform * dvec3( i_v2TexCoordinate, 1.0 );
    v_v2TexCoordinate = vec2(dv3TexCoordinate.xy);
}
