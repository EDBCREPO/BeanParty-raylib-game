#pragma once

namespace rl { namespace shader {

    Shader water() { return LoadShaderFromMemory(
        nullptr, R"(
            #version 330

            uniform sampler2D texture0;
            in  vec2 fragTexCoord;
            out vec4 color;

            void main(){
                color = texture( texture0, fragTexCoord*vec2(100.) );
            }

        )"
    );}

}}