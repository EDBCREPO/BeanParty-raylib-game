# time g++ -o main main.cpp -I./include -L./lib -lraylib -lssl -lcrypto ; ./main ; exit
if [ ! -f "www" ] ; then
    mkdir www
fi

em++ -o www/index.html main.cpp                          \
     -I./include -L./lib -lraylib -lwebsocket.js         \
     -s WEBSOCKET_SUBPROTOCOL=1 -s WEBSOCKET_URL=1       \
     -s ASYNCIFY=1 -s FETCH=1 -s WASM=1                  \
     -s USE_GLFW=3 -s USE_PTHREADS=1                     \
     -s ERROR_ON_UNDEFINED_SYMBOLS=0                     \
     --embed-file ./assets/models/characters/player8.obj \
     --embed-file ./assets/models/characters/player8.mtl \
     --embed-file ./assets/models/characters/player7.obj \
     --embed-file ./assets/models/characters/player7.mtl \
     --embed-file ./assets/models/characters/player6.obj \
     --embed-file ./assets/models/characters/player6.mtl \
     --embed-file ./assets/models/characters/player5.obj \
     --embed-file ./assets/models/characters/player5.mtl \
     --embed-file ./assets/models/characters/player4.obj \
     --embed-file ./assets/models/characters/player4.mtl \
     --embed-file ./assets/models/characters/player3.obj \
     --embed-file ./assets/models/characters/player3.mtl \
     --embed-file ./assets/models/characters/player2.obj \
     --embed-file ./assets/models/characters/player2.mtl \
     --embed-file ./assets/models/characters/player1.obj \
     --embed-file ./assets/models/characters/player1.mtl \
     --embed-file ./assets/models/environment/floor.obj \
     --embed-file ./assets/models/environment/floor.mtl \
     --embed-file ./assets/images/target.png \
     --embed-file assets/images/colormap.png \
     --embed-file assets/images/pointer.png  \

#g++ -o server server.cpp -lssl -lcrypto ; ./server
./server