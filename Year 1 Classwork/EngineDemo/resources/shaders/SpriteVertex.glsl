/******************************************************************************
 * File:               SpriteVertex.glsl
 * Author:             Elizabeth Lowry
 * Date Created:       March 12, 2014
 * Description:        Vertex shader for a Sprite.
 * Last Modified:      March 12, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

# version 150

uniform dmat3 u_dm3TexTransform;

in vec2 i_v2Position;
in vec2 i_v2TexCoordinate;

out dvec2 v_dv2TexCoordinate;

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * vec4( i_v2Position, 0.0, 1.0 );
    vec3 dv3TexCoordinate = u_dm3TexTransform * dvec3( i_dv2TexCoordinate, 1.0 );
    v_dv2TextureCoordinate = dv3TexCoordinate.xy;
}