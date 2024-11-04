ulimit -Sn 1048576 ; VAL=$( ulimit -Sn ) ; echo -e "MAX_FILENO: $VAL" 

time g++ -o main main.cpp -I./include -L./lib -lraylib -lssl -lcrypto

./main & ./main ?MODE=server