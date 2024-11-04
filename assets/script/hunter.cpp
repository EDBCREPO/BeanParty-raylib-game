#pragma once
#include "../network/client.cpp"

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    void hunter( ptr_t<Item> self ) {

        struct NODE {
            float distance= 20.0f;
            float   speed = 10.0f;
            Vector2 dir   = { 0.0f, -1.2f };
            ptr_t<Camera3D> cam = new Camera3D();
            Texture img = LoadTexture( "assets/images/target.png" );
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
        coStart; coDelay(80); auto mos = GetMousePosition();
            websocket::send( json::stringify( object_t({
                { "ang", array_t<float>({ obj->dir.x, obj->dir.y }) },
                { "mos", array_t<float>({ mos.x, mos.y }) },
                { "mdl", 1u }, { "type", 0u },
                { "pos", array_t<float>({
                    obj->cam->position.x,
                    obj->cam->position.y,
                    obj->cam->position.z 
                }) }
            }) ));
        coStop
        }(); });
    
    /*─······································································─*/

        self->onDraw([=](){ 
            DrawTextureEx( obj->img, GetMousePosition()-Vector2({ 18, 18 }), 0, 1, WHITE );
        });
    
    /*─······································································─*/

        self->onRemove([=](){ 
            if( IsTextureReady( obj->img ) ){ UnloadTexture( obj->img ); }
        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/