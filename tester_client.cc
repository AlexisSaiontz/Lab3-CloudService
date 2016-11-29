#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>
#include <stdint.h>

#include "test.grpc.pb.h"
#include "headers.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using mutate::Node;
using mutate::Edge;
using mutate::Code;
using mutate::Mutator;

class MutatorClient {
 public:
  MutatorClient(std::shared_ptr<Channel> channel)
      : stub_(Mutator::NewStub(channel)) {}

  int add_node(const uint64_t id) {
    Node toAdd;
    toAdd.set_id(id);

    Code code;

    ClientContext context;
    // The actual RPC.
    Status status = stub_->add_node(&context, toAdd, &code);

    // Act upon its status.
    if (status.ok()) {
      std::cout << "Code returned: " << code.code() << std::endl;
      return code.code();
    } else {
      std::cout <<  "RPC failed" << std::endl;
      return 500;
    }
  }

 private:
  std::unique_ptr<Mutator::Stub> stub_;

};

int send_to_next() {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  MutatorClient mutator(grpc::CreateChannel(
      "localhost:8080", grpc::InsecureChannelCredentials()));
  //:w:Node node;
  //node.set_id(9);
  int add_node_code = mutator.add_node(9);
  std::cout << "Client received status code: " << add_node_code << std::endl;
  return 0;
}
