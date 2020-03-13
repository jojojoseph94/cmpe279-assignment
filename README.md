# cmpe279-assignment1
In assigment 1, you will extend the server code to use privilege separation. You should accomplish this by 
splitting up the code into two logical parts – the part that sets up the socket and a separate part that 
processes the data from the client. Once you locate this split, you should fork and have the child process 
setuid() to drop its privileges to an unprivileged user (maybe the “nobody” user, or a user you create). The 
server should wait for the child to exit and the child should process the connection from the client.
Submission process – Commit the code to a github repo containing a directory ‘assignment1’ at the root of 
the repo. Place all assignment 1 code/Makefiles/etc in that directory and commit to your repo (and push 
changes). Make sure you invite me (‘mlarkin2015’) to your repo or make it public.
Grading – I will inspect the code to make sure the privilege separation is done properly and assign points 
accordingly. I might test your server code with my client.
