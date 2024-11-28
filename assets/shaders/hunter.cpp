#pragma once

namespace rl { namespace shader {

    Shader hunter() { return LoadShaderFromMemory(
        nullptr, _SHADER_(
            precision mediump float;
            uniform   vec3 mos;

            void main(){

                vec2  pos    = vec2( gl_FragCoord.x, gl_FragCoord.y );
                vec2  mouse  = vec2( mos.x, mos.z - mos.y );
                float dis    = distance( pos, mouse )/200.0;

                if( dis<0.7 ){ dis = 0.0; }

                gl_FragColor = vec4( 0, 0, 0, dis );

            }

        )
    );}

}}