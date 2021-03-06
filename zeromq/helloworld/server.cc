#include <unistd.h>
#include <iostream>
#include <string>
#include <zmq.hpp>

int main() {
  // Prepare our context and socket
  zmq::context_t context(1);
  zmq::socket_t socket(context, ZMQ_REP);
  socket.bind("tcp://*:5555");

  zmq::message_t request;
  socket.recv(&request);
  std::cout << "Received request" << std::endl;

  std::cout << "Sending reply " << std::endl;
  zmq::message_t reply(6);
  memcpy(reply.data(), "Reply", 6);
  socket.send(reply);

  return 0;
}
