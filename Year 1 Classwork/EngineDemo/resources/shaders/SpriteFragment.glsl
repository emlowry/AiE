/******************************************************************************
 * File:               SpriteFragment.glsl
 * Author:             Elizabeth Lowry
 * Date Created:       March 12, 2014
 * Description:        Fragment shader for a Sprite.
 * Last Modified:      March 12, 2014
 * Last Modification:  Creation.
 ******************************************************************************/

# version 150

uniform vec4 u_v4Color;
uniform sampler2D u_t2dTexture;
uniform dvec2 u_dv2OffsetUV;
uniform dvec2 u_dv2SizeUV;
uniform bool u_bClampX;
uniform bool u_bClampY;

in dvec2 v_dv2TexCoordinate;

float ScaleUV( in double a_fValue, in double a_fOffset,
               in double a_fSize, in bool a_bClamp )
{
    if( a_bClamp )
    {
        if( a_dValue < 0.0 )
        {
            return a_dOffset;
        }
        if( a_dValue > 1.0 )
        {
            return a_dOffset + a_dSize;
        }
        return a_dValue * a_dSize;
    }

    int iSteps = a_dValue;
    double dPosition = a_dValue - iSteps;
    return ( ( a_dOffset + a_dSize ) * iSteps ) + ( a_dSize * fPosition );
}

void main()
{
    dvec2 dv2TexCoordinateUV =
        dvec2( ScaleUV( v_dv2TexCoordinate.x, u_dv2OffsetUV.x,
                        u_dv2SizeUV.x, u_bClampX ),
               ScaleUV( v_dv2TexCoordinate.y, u_dv2OffsetUV.y,
                        u_dv2SizeUV.y, u_bClampY ) );
    dvec2 dv2TexColor = texture( u_t2dTexture, dv2TexCoordinateUV );
    gl_FragColor = dv2TexColor * u_v4Color;
}