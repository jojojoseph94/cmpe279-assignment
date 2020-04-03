To build
--------
gcc -o client client.c
gcc -o server server.c

After build start server as root

sudo ./server

The server starts as root and forks a child. Child drops its previlege and execs server executable again with lower previlege passing the socket file descriptor as an argument. The child then listens to connections at lower previlege.
The parent waits for the child to complete.
