#pragma once
#include <nodepp/ws.h>

namespace rl { namespace websocket {

    ws_t              client; 
    event_t<string_t> onSend;
    event_t<except_t> onError;
    event_t<ws_t>     onConnect;
    event_t<string_t> onMessage;
    event_t<>         onDisconnect;

    void send( string_t message ){ onSend.emit( message ); }

    void connect( string_t url ){ try {
        client.close(); client = ws::connect( url );
        client.onConnect.once([=]( ws_t cli ){ onConnect.emit( cli );
            cli.onData([=]( string_t msg ){ onMessage.emit( msg ); });
            auto ids = onSend([=]( string_t msg ){ cli.write( msg ); });
            cli.onClose([=](){ onDisconnect.emit(); process::clear(ids); });
        }); client.onError.once([=]( except_t err ){ onError.emit( err ); });
    } catch( except_t err ) { onError.emit( err ); }}

} } 