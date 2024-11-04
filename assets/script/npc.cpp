#pragma once

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    void npc( ptr_t<Item> self ) {

        struct item {
            Model* model;
            Vector3 pos;
            Vector3 tar;
            float angle;
            bool  state;
            float salt;
        };

        struct NODE {
            queue_t<item>  list;
            array_t<Model> model;
        };  ptr_t<NODE> obj = new NODE();
    
    /*─······································································─*/

        obj->model.push( LoadModel( "./assets/models/characters/player8.obj" ) );
        obj->model.push( LoadModel( "./assets/models/characters/player7.obj" ) );
        obj->model.push( LoadModel( "./assets/models/characters/player6.obj" ) );
        obj->model.push( LoadModel( "./assets/models/characters/player5.obj" ) );
        obj->model.push( LoadModel( "./assets/models/characters/player4.obj" ) );
        obj->model.push( LoadModel( "./assets/models/characters/player3.obj" ) );
        obj->model.push( LoadModel( "./assets/models/characters/player2.obj" ) );
        obj->model.push( LoadModel( "./assets/models/characters/player1.obj" ) );
    
    /*─······································································─*/

        for( auto x=10; x--; ){
            item data; memset( &data, 0, sizeof(item) );
                 data.pos   = Vector3({ rand_range(0,15)-7.0f, 0, rand_range(0,15)-7.0f });
                 data.tar   = Vector3({ rand_range(0,15)-7.0f, 0, rand_range(0,15)-7.0f });
                 data.state = true; // rand_range( 0, 2 )==0;
                 data.model = &obj->model[ rand()%8 ];
                 data.angle = rand_range( 0, 360 );
                 data.salt  = rand_range( 0, 2 )-1;
            obj->list.push( data );
        }
    
    /*─······································································─*/

        self->onLoop([=]( float delta ){ [=](){
        coStart; coDelay( 60000 );

            do {
            auto x = obj->list.first(); while( x!=nullptr ){
                x->data.tar.x = rand_range( 0, 15 ) - 7;
                x->data.tar.z = rand_range( 0, 15 ) - 7;
                x = x->next;
            } } while(0);

        coStop
        }(); });
    
    /*─······································································─*/

        self->onLoop([=]( float delta ){
            static float elapsed = 0; elapsed += delta * 5;

            auto x = obj->list.first(); while( x!=nullptr ){
            auto targetAngle = Vector2LineAngle(
                    { x->data.pos.x, x->data.pos.z },
                    { x->data.tar.x, x->data.tar.z }
                ) * RAD2DEG + 90;

                x->data.pos.x = clamp( x->data.pos.x, -8.0f, 8.0f );
                x->data.pos.z = clamp( x->data.pos.z, -8.0f, 8.0f );
                x->data.pos.y = .1+abs( .3*sin( elapsed ) );

            if( abs( x->data.angle-targetAngle ) > 10 && x->data.angle != targetAngle ){ 
                     x->data.angle-= ( x->data.angle-targetAngle ) * delta;
                if ( x->data.state ) { goto DONE; }
            } else { x->data.angle = targetAngle; }

            if( Vector3Distance( x->data.pos, x->data.tar )<1 ){
                x->data.tar.x = rand_range( 0, 15 ) - 7;
                x->data.tar.z = rand_range( 0, 15 ) - 7;
            }

                x->data.pos.x += sin( x->data.angle * DEG2RAD ) * delta;
                x->data.pos.z += cos( x->data.angle * DEG2RAD ) * delta;
                DONE:; x = x->next;

            }

        });
    
    /*─······································································─*/

        self->on3DDraw([=](){
            auto x = obj->list.first(); while( x!=nullptr ){
              //DrawCube( x->data.tar, 1, 1, 1, RED );
                DrawModelEx( 
                   *x->data.model, x->data.pos, { 0, 1, 0 }, 
                    x->data.angle, { 1, 1, 1 }, WHITE
                );  x = x->next;
            }
        });
    
    /*─······································································─*/

        self->onRemove([=](){
            forEach( x, obj->model )
            if( IsModelReady( x ) ){ UnloadModel( x ); }
        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/