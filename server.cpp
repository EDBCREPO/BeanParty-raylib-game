#define MAX_FILENO 1048576

#include <nodepp/nodepp.h>
#include <nodepp/http.h>
#include <nodepp/timer.h>
#include <nodepp/ws.h>

using namespace nodepp;

#include "./assets/network/server.cpp"

void onMain(){

    auto server = http::server( rl::http_handler );
                    ws::server( server );

    rl::websocket_handler( server );

    server.listen( "0.0.0.0", 8000, [=]( ... ){
        console::log("-> http://localhost:8000");
    });

}