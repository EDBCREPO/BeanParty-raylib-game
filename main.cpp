#define MAX_FILENO 1048576

#include <nodepp/nodepp.h>
#include <nodepp/worker.h>
#include <nodepp/http.h>
#include <nodepp/ws.h>

using namespace nodepp;

#include "assets/script/game.cpp"
#include "assets/scenes/scene_2.cpp"
#include "assets/scenes/scene_1.cpp"
#include "assets/scenes/scene_0.cpp"

#include "./assets/network/server.cpp"

/*────────────────────────────────────────────────────────────────────────────*/

void onMain() {

    if( process::env::get("MODE") == "server" ){

        auto server = http::server( rl::http_handler );
                        ws::server( server );

        rl::websocket_handler( server );

        server.listen( "localhost", 8000, [=]( ... ){
            console::log("-> http://localhost:8000");
        });

    } else {

        rl::Init( 800, 600, 60, "Impostor Hunt" );

        rl::websocket::onError.once([](...){
            rl::SetAttr("Err","Couldn't connect to the Server");
            rl::AppendScene( rl::scene::scene_0 );
        });

        rl::websocket::onDisconnect.once([](){
            rl::SetAttr("Err","Disconnected From Server");
            rl::AppendScene( rl::scene::scene_0 );
        });

        rl::AppendScene( rl::scene::scene_0 );

        rl::onClose([](){
            console::log("Closed");
            rl::Close();
        });

    }

}

/*────────────────────────────────────────────────────────────────────────────*/