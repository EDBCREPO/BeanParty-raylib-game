#pragma once
#include "../network/client.cpp"
#include "../shaders/hunter.cpp"

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    void hunter( ptr_t<Item> self ) {

        struct NODE {
            float distance= 15.0f;
            float   speed = 10.0f;
            Vector2 dir   = { 0.0f, -1.2f };
            Shader shader = shader::hunter();
            ptr_t<Camera3D> cam = new Camera3D();
            Texture img = GetAttr("Texture").as<array_t<Texture>>()[0];
        };  ptr_t<NODE> obj = new NODE();
    
    /*─······································································─*/

        GlobalCam3D = obj->cam; memset( &obj->cam, 0, sizeof(*obj->cam) );
        obj->cam->position   = Vector3({ 10, 10, 10 });
        obj->cam->up         = Vector3({ 0, 1, 0 });
        obj->cam->projection = CAMERA_PERSPECTIVE;
        obj->cam->fovy       = 75.0f;
        SetAttr( "Mode", "HUNTER" );
    
    /*─······································································─*/

        self->onLoop([=]( float delta ){

            if( IsKeyDown('A') ){ obj->dir.x -= 0.1 * delta * obj->speed; }
          elif( IsKeyDown('D') ){ obj->dir.x += 0.1 * delta * obj->speed; }
            
            if( IsKeyDown('W') ){ obj->dir.y += 0.1 * delta * obj->speed; }
          elif( IsKeyDown('S') ){ obj->dir.y -= 0.1 * delta * obj->speed; }

            obj->dir.y           = clamp( obj->dir.y, -1.2f, -0.4f );
            
            obj->cam->position.y = obj->distance* cos( obj->dir.y );
            obj->cam->position.x = obj->distance* sin( obj->dir.x ) * sin( obj->dir.y );
            obj->cam->position.z = obj->distance* cos( obj->dir.x ) * sin( obj->dir.y );

        });

        self->onLoop([=]( float delta ){ [=](){
            static string_t prev, msg;
        coStart; coDelay(100); auto mos = GetMousePosition();

            msg = json::stringify( object_t({
                { "pos", array_t<float>({ obj->cam->position.x, obj->cam->position.y, obj->cam->position.z }) },
                { "ang", array_t<float>({ obj->dir.x, obj->dir.y }) },
                { "mos", array_t<float>({ mos.x, mos.y }) },
                { "mdl", 1u }, { "type", 0u },
            }) );

            if( msg != prev ){ websocket::send( msg ); prev = msg; }
            
        coStop
        }(); });
    
    /*─······································································─*/

        self->onDraw([=](){ 
            DrawTextureEx( obj->img, GetMousePosition()-Vector2({ 18, 18 }), 0, 1, WHITE );
            BeginShaderMode( obj->shader ); Vector3 mos = { GetMouseX()*1.0f, GetMouseY()*1.0f, GetRenderHeight()*1.0f };
            SetShaderValue( obj->shader, GetShaderLocation( obj->shader, "mos" ), &mos, SHADER_UNIFORM_VEC3 );
            DrawRectangle( 0, 0, GetRenderWidth(), GetRenderHeight(), BLACK );
            EndShaderMode();
        });
    
    /*─······································································─*/

        self->onRemove([=](){ 
            if( IsShaderReady( obj->shader ) ){ UnloadShader( obj->shader ); }
        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/