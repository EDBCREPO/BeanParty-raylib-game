#pragma once

/*────────────────────────────────────────────────────────────────────────────*/

#include "../script/npc.cpp"
#include "../script/menu.cpp"
#include "../script/world.cpp"

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace scene {

    void scene_0( ptr_t<Scene> self ) {

        string_t message; if( GetAttr("Err").has_value() )
                 message = GetAttr("Err").as<string_t>();
                 RemoveAttr("Err");

        self->onDraw([=](){ if( !message.empty() ){
            DrawRectangle( 0, 0, GetRenderWidth(), GetRenderHeight()*5/100, RED );
            DrawText( message.get(), 10, 10, 13, WHITE );
        }});

        self->on3DDraw([=](){ ClearBackground({ 0, 49, 97, 255 }); });

        self->AppendItem( "npc",   game::npc   );
        self->AppendItem( "menu",  game::menu  );
        self->AppendItem( "world", game::world );

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/