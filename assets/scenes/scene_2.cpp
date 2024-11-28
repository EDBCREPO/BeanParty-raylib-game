#pragma once

/*────────────────────────────────────────────────────────────────────────────*/

#include "../script/npc.cpp"
#include "../script/world.cpp"
#include "../script/hunter.cpp"
#include "../script/impostor.cpp"

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace scene {

    void scene_2( ptr_t<Scene> self ) {

        self->AppendItem( "hunter",   game::hunter   );
      //self->AppendItem( "impostor", game::impostor );
        self->AppendItem( "world",    game::world    );
        self->AppendItem( "npc",      game::npc      );

        self->on3DDraw([](){
            ClearBackground({ 0, 49, 97, 255 });
            DrawText( GetAttr("Mode").as<string_t>().get(), 10, 10, 13, RED );
        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/