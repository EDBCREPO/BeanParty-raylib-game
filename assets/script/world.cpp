#pragma once

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    void world( ptr_t<Item> self ) {

        struct NODE {
            Model model     = GetAttr("Model").as<array_t<Model>>()[0];
        };  ptr_t<NODE> obj = new NODE();

        self->on3DDraw([=](){
            DrawModel( obj->model, { 0, -5, 0 }, 10, WHITE );
            DrawPlane( { 0, -1, 0 }, { 100, 100 }, BLUE );
        });

      //self->onRemove([=](){ });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/