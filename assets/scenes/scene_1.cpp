#pragma once

/*────────────────────────────────────────────────────────────────────────────*/

#include "../script/gest.cpp"
#include "../script/world.cpp"
#include "../script/impostor.cpp"

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace scene {

    void scene_1( ptr_t<Scene> self ) {

        self->AppendItem( "impostor", game::impostor );
        self->AppendItem( "world",    game::world    );
        self->AppendItem( "gest",     game::gest     );
    
    /*─······································································─*/

        self->on3DDraw([](){ ClearBackground({ 0, 49, 97, 255 }); });

        self->onDraw([](){
            DrawRectangle( 0, 0, GetRenderWidth(), GetRenderHeight()*5/100, BLUE );
            DrawText( "...Waiting Players... 1/5", 10, 10, 13, WHITE );
        });
    
    /*─······································································─*/

        websocket::connect( "http://localhost:8000" );

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/