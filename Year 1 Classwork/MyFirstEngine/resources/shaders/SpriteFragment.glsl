/******************************************************************************
 * File:               SpriteFragment.glsl
 * Author:             Elizabeth Lowry
 * Date Created:       March 12, 2014
 * Description:        Fragment shader for a Sprite.
 * Last Modified:      June 26, 2014
 * Last Modification:  Debugging.
 ******************************************************************************/

#version 410

uniform vec4 u_v4Color;
uniform sampler2D u_t2dTexture;
uniform dvec2 u_dv2OffsetUV;
uniform dvec2 u_dv2SizeUV;
uniform bool u_bClampX;
uniform bool u_bClampY;

in vec2 v_v2TexCoordinate;

float ScaleUV( in float a_fValue, in double a_dOffset,
               in double a_dSize, in bool a_bClamp )
{
    if( a_bClamp )
    {
        if( a_fValue < 0.0 )
        {
            return float( a_dOffset );
        }
        if( a_fValue > 1.0 )
        {
            return float( a_dOffset + a_dSize );
        }
        return float( a_dOffset + ( a_fValue * a_dSize ) );
    }

    int iSteps = int( a_fValue );
    double dPosition = a_fValue - double( iSteps );
    return float( double( iSteps ) + a_dOffset + ( a_dSize * dPosition ) );
}

void main()
{
    vec2 v2TexCoordinateUV =
        vec2( ScaleUV( v_v2TexCoordinate.x, u_dv2OffsetUV.x,
                       u_dv2SizeUV.x, u_bClampX ),
              ScaleUV( v_v2TexCoordinate.y, u_dv2OffsetUV.y,
                       u_dv2SizeUV.y, u_bClampY ) );
    gl_FragColor = texture( u_t2dTexture, v2TexCoordinateUV ) * u_v4Color;
}
