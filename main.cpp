#define MAX_FILENO 1048576

#include <nodepp/nodepp.h>
#include <nodepp/worker.h>
#include <nodepp/ws.h>

using namespace nodepp;

#include "assets/script/game.cpp"
#include "assets/scenes/scene_2.cpp"
#include "assets/scenes/scene_1.cpp"
#include "assets/scenes/scene_0.cpp"

/*────────────────────────────────────────────────────────────────────────────*/

void onMain() {

    rl::Init( 800, 600, 60, "Impostor Hunt" ); rl::AppendScene( rl::scene::scene_0 );
    
    /*─······································································─*/

    rl::SetAttr( "Scene_0", function_t<void>([=](){ rl::AppendScene( rl::scene::scene_0 ); }) );
    rl::SetAttr( "Scene_1", function_t<void>([=](){ rl::AppendScene( rl::scene::scene_1 ); }) );
    rl::SetAttr( "Scene_2", function_t<void>([=](){ rl::AppendScene( rl::scene::scene_2 ); }) );

    rl::SetAttr( "Model", array_t<rl::Model>({
        rl::LoadModel( "./assets/models/environment/floor.obj"  ),
        rl::LoadModel( "./assets/models/characters/player8.obj" ),
        rl::LoadModel( "./assets/models/characters/player7.obj" ),
        rl::LoadModel( "./assets/models/characters/player6.obj" ),
        rl::LoadModel( "./assets/models/characters/player5.obj" ),
        rl::LoadModel( "./assets/models/characters/player4.obj" ),
        rl::LoadModel( "./assets/models/characters/player3.obj" ),
        rl::LoadModel( "./assets/models/characters/player2.obj" ),
        rl::LoadModel( "./assets/models/characters/player1.obj" ),
    }) );
    
    rl::SetAttr( "Texture", array_t<rl::Texture>({
        rl::LoadTexture( "assets/images/target.png" ),
        rl::LoadTexture( "./assets/images/pointer.png" ),
    }) );
    
    /*─······································································─*/

    rl::websocket::onError([]( except_t err ){
        rl::SetAttr("Err","Couldn't connect to the Server");
        rl::AppendScene( rl::scene::scene_0 );
    });

    rl::websocket::onDisconnect([](){
        rl::SetAttr("Err","Disconnected From Server");
        rl::AppendScene( rl::scene::scene_0 );
    });
        
    /*─······································································─*/

    rl::onClose([](){
        forEach( x, rl::GetAttr("Model").as<array_t<rl::Model>>() ){ 
            if( rl::IsModelReady(x) ){ rl::UnloadModel(x); }
        }
        forEach( x, rl::GetAttr("Texture").as<array_t<rl::Texture>>() ){ 
            if( rl::IsTextureReady(x) ){ rl::UnloadTexture(x); }
        }   console::log("Closed"); rl::Close();
    });

}

/*────────────────────────────────────────────────────────────────────────────*/