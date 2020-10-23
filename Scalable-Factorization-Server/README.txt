# Miscellaneous
This task is to write a factorization server factorizationd that reads factorization requests from
remote clients and returns factorization results to them.
In order to make the server scalable, it offloads all the processing to separate processes. In particular,
when the factorization server starts up, it creates a number of worker processes. Each
worker process is running the multi-threaded factorize program developed in the previous problem.
When factorization requests are received from clients, they are handed over to the worker
processes and the results produced by worker processes are passed back to the clients (pipes are
used to exchange data with the worker processes). In addition, the server keeps track how many
factorization requests have been processed by a specific process. Once a configurable threshold
has been crossed by a worker process, the worker process will be stopped and a new one created
(this is sometimes called rejuvenation).
Detailed requirements:
  The server must listen on a specific port on the IPv4 any address and the IPv6 any address.
  The server must be event-driven, i.e., it must use a select()-loop to determine which file
descriptor needs attention.
  The -p command line option controls the number of worker processes and the -t command
line option controls the number of threads in a worker process. The -m command line option
defines the maximum number of factorizations a worker process can do before it is retired
and replaced by a new worker process.
  While the protocol exposed to clients may be the same as the protocol used to communicate
with the worker processes, a server cannot assume that clients generate unique tags.
  The program must follow the programming requirements stated on the course web page.
In particular, it needs to handle all runtime error situations in an appropriate manner. In
particular, runtime error and warning messages should use the syslog mechanism
