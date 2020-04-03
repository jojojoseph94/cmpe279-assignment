To build
--------
gcc -o client client.c
gcc -o server server.c

After build start server as root

sudo ./server

The server starts as root and attaches itself to port 80 then forks a child. The child drops the privilege and starts listening.
The parent waits for the child to complete.
