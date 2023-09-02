# amadeusRPC
A Concurrent Asynchronous RPC Framework Written by C++ 11 &amp; Linux.


## 1. Overview
amadeusRPC is a multi-threaded asynchronous RPC framework based on C++11, which aims to be efficient and simple while maintaining high performance.

amadeusRPC is also based on the Master-Slave Reactor architecture, and the bottom layer uses epoll to realize IO multiplexing. The application layer uses protobuf to customize the rpc communication protocol, and will also support the simple HTTP protocol. A multi-threaded asynchronous RPC framework based on C++11.
