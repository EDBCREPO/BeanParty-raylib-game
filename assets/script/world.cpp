#pragma once
#include "../shaders/water.cpp"

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    void world( ptr_t<Item> self ) {

        struct NODE {
            Model model   = LoadModel("./assets/models/environment/floor.obj");
            Texture img   = LoadTexture("./assets/images/colormap.png");
            Shader shader = shader::water(); 
        };  ptr_t<NODE> obj = new NODE();

        self->on3DDraw([=](){
            DrawModel( obj->model, { 0, -5, 0 }, 10, WHITE );
            DrawPlane( { 0, -1, 0 }, { 100, 100 }, BLUE );
        });

        self->onRemove([=](){
            if( IsTextureReady( obj->img )   ){ UnloadTexture( obj->img ); }
            if( IsModelReady( obj->model )   ){ UnloadModel( obj->model ); }
            if( IsShaderReady( obj->shader ) ){ UnloadShader( obj->shader ); }
        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/