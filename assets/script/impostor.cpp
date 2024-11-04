#pragma once
#include "../network/client.cpp"

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    void impostor( ptr_t<Item> self ) {

        struct NODE { 
            Texture img = LoadTexture( "./assets/images/pointer.png" );
            Vector3 pos = { 3, 3, 3 }; float angle = 0;
            Vector3 dir = { 3, 3, 3 }; ulong model = 0;
            Vector2 mos = { 0, -1.2 };
            array_t<Model> list;
            ptr_t<Camera3D> cam = new Camera3D();
        };  ptr_t<NODE> obj = new NODE();
    
    /*─······································································─*/

        obj->list.push( LoadModel( "./assets/models/characters/player8.obj" ) );
        obj->list.push( LoadModel( "./assets/models/characters/player7.obj" ) );
        obj->list.push( LoadModel( "./assets/models/characters/player6.obj" ) );
        obj->list.push( LoadModel( "./assets/models/characters/player5.obj" ) );
        obj->list.push( LoadModel( "./assets/models/characters/player4.obj" ) );
        obj->list.push( LoadModel( "./assets/models/characters/player3.obj" ) );
        obj->list.push( LoadModel( "./assets/models/characters/player2.obj" ) );
        obj->list.push( LoadModel( "./assets/models/characters/player1.obj" ) );
    
    /*─······································································─*/

        GlobalCam3D = obj->cam; memset( &obj->cam, 0, sizeof(*obj->cam) );
        obj->cam->up         = Vector3({ 0, 1, 0 });
        obj->cam->projection = CAMERA_PERSPECTIVE;
        obj->model           = rand() % 8;
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
        coStart; coDelay(80); auto mos = GetMousePosition();
            websocket::send( json::stringify( object_t({
                { "pos", array_t<float>({ obj->pos.x, obj->pos.y, obj->pos.z }) },
                { "ang", obj->angle }, { "mdl", obj->model }, { "type", 1u },
                { "mos", array_t<float>({ mos.x, mos.y }) }
            }) ));
        coStop
        }(); });
    
    /*─······································································─*/

        self->on3DDraw([=](){
            DrawModelEx( 
                obj->list[obj->model], 
                obj->pos,   { 0, 1, 0 }, 
                obj->angle, { 1, 1, 1 }, WHITE
            );
        });
    
    /*─······································································─*/

        self->onDraw([=](){ 
            DrawTextureEx( obj->img, GetMousePosition()-Vector2({ 18, 18 }), 0, 1, WHITE );
        });
    
    /*─······································································─*/

        self->onRemove([=](){
            forEach( x, obj->list )
            if( IsModelReady( x ) ){ UnloadModel( x ); }
            if( IsTextureReady( obj->img )  ){ UnloadTexture( obj->img );   }
        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/