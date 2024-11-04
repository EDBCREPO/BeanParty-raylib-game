#pragma once

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    void menu( ptr_t<Item> self ) {

        struct state {
            function_t<void> callback;
            Rectangle origin;
            string_t text;
            bool state;
            int size;
        };

        struct NODE {
            queue_t<state> list;
            float distance= 20.0f;
            float   speed =  3.0f;
            Vector2 dir   = { 0.0f, -1.2f };
            ptr_t<Camera3D> cam = new Camera3D();
            Texture img = LoadTexture( "assets/images/pointer.png" );
        };  ptr_t<NODE> obj = new NODE(); DisableCursor();
    
    /*─······································································─*/

        GlobalCam3D = obj->cam; memset( &obj->cam, 0, sizeof(*obj->cam) );
        obj->cam->position   = Vector3({ 10, 10, 10 });
        obj->cam->up         = Vector3({ 0, 1, 0 });
        obj->cam->projection = CAMERA_PERSPECTIVE;
        obj->cam->fovy       = 75.0f;

        obj->list.push({
            .callback = [=](){ AppendScene( scene::scene_1 ); },
            .origin   = { 100, 300, 190, 50 },
            .text     = "Connect",
            .size     = 48
        });

        obj->list.push({
            .callback = [=](){ OpenURL("https://github.com/NodeppOficial/nodepp/"); },
            .origin   = { 100, 370, 190, 50 },
            .text     = "Github",
            .size     = 48
        });
    
    /*─······································································─*/

        self->onLoop([=]( float delta ){

            obj->dir.x += 0.1 * delta * obj->speed;

            auto x=obj->list.first(); while( x!=nullptr ){
            if( CheckCollisionPointRec( GetMousePosition(), x->data.origin ) ){
            if( IsMouseButtonPressed(0) ){ x->data.callback(); }
                x->data.state = 1; 
            } else {
                x->data.state = 0;
            }   x = x->next;  }

            obj->cam->position.y = obj->distance* cos( obj->dir.y );
            obj->cam->position.x = obj->distance* sin( obj->dir.x ) * sin( obj->dir.y );
            obj->cam->position.z = obj->distance* cos( obj->dir.x ) * sin( obj->dir.y );

        });
    
    /*─······································································─*/

        self->onDraw([=](){
            DrawText( "Impostor Hunt", 100, 100, 72, WHITE );
            auto x=obj->list.first(); while( x!=nullptr ){
              //DrawRectangleRec( x->data.origin, BLACK );
                DrawText( 
                    x->data.text.get(), x->data.origin.x, 
                    x->data.origin.y, x->data.size, 
                    x->data.state? BLACK: WHITE
                );  x = x->next;
            }
        });
    
    /*─······································································─*/

        self->onDraw([=](){
            DrawTextureEx( obj->img, GetMousePosition()-Vector2({ 18, 18 }), 0, 1, WHITE );
        });

        self->onRemove([=](){ 
            if( IsTextureReady( obj->img ) ){ UnloadTexture( obj->img ); }
        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/