#pragma once
#include "../network/client.cpp"

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    void impostor( ptr_t<Item> self ) {

        struct NODE { 
            Texture img = GetAttr("Texture").as<array_t<Texture>>()[1];
            Vector3 pos = { 3, 3, 3 }; float angle = 0;
            Vector3 dir = { 3, 3, 3 }; ulong model = 0;
            Vector2 mos = { 0, -1.2 };
            ptr_t<Camera3D> cam = new Camera3D();
        };  ptr_t<NODE> obj = new NODE();
    
    /*─······································································─*/

        GlobalCam3D = obj->cam; memset( &obj->cam, 0, sizeof(*obj->cam) );
        obj->cam->up         = Vector3({ 0, 1, 0 });
        obj->cam->projection = CAMERA_PERSPECTIVE;
        obj->model           = rand_range( 1, 8 );
        obj->cam->fovy       = 75.0f;

        SetAttr( "Mode", "IMPOSTOR" );
    
    /*─······································································─*/

        self->onLoop([=]( float delta ){
            static float elapsed = 0; elapsed += delta * 5;

            if( IsKeyDown( 'A' ) ){ 
                obj->angle += delta * 150.f; 
            } elif( IsKeyDown( 'D' ) ) {
                obj->angle -= delta * 150.f;
            }

            if( IsKeyDown( 'W' ) ){ 
                obj->pos.x += sin( obj->angle * DEG2RAD ) * delta;
                obj->pos.z += cos( obj->angle * DEG2RAD ) * delta;
            } elif( IsKeyDown( 'S' ) ) { 
                obj->pos.x -= sin( obj->angle * DEG2RAD ) * delta;
                obj->pos.z -= cos( obj->angle * DEG2RAD ) * delta;
            }

            if( IsMouseButtonDown(0) ){
                auto mos = GetMouseDelta();
                obj->mos.x -= delta * 0.7 * mos.x;
                obj->mos.y += delta * 0.7 * mos.y;
                obj->mos.y  = clamp( obj->mos.y, -1.2f, -0.4f );
            }

            obj->pos.y         = .1+abs( .3*sin( elapsed ) );
            obj->cam->target   = obj->pos * Vector3({ 1, 0, 1 });
            obj->cam->position = obj->pos * Vector3({ 1, 0, 1 });

            obj->cam->position.x += 5 * sin( obj->mos.x ) * sin( obj->mos.y );
            obj->cam->position.z += 5 * cos( obj->mos.x ) * sin( obj->mos.y ); 
            obj->cam->position.y += 5 * cos( obj->mos.y );

            obj->pos.x = clamp( obj->pos.x, -8.0f, 8.0f );
            obj->pos.z = clamp( obj->pos.z, -8.0f, 8.0f ); //console::log( obj->pos.x, obj->pos.z );

        });

        self->onLoop([=]( float delta ){ [=](){
            static string_t prev, msg;
        coStart; coDelay(100); auto mos = GetMousePosition();

            msg = json::stringify( object_t({
                { "mos", array_t<float>({ obj->cam->position.x, obj->cam->position.y, obj->cam->position.z }) },
                { "ang", obj->angle }, { "mdl", obj->model }, { "type", 1u },
                { "pos", array_t<float>({ obj->pos.x, obj->pos.z }) }
            }) );

            if( msg != prev ){ websocket::send( msg ); prev = msg; }

        coStop
        }(); });

    /*─······································································─*/

        self->on3DDraw([=](){
            DrawModelEx( 
                GetAttr("Model").as<array_t<Model>>()[obj->model],
                obj->pos,   { 0, 1, 0 }, 
                obj->angle, { 1, 1, 1 }, WHITE
            );
        });
    
    /*─······································································─*/

        self->onDraw([=](){ 
            DrawTextureEx( obj->img, GetMousePosition()-Vector2({ 18, 18 }), 0, 1, WHITE );
        });
    
    /*─······································································─*/

      //self->onRemove([=](){ });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/