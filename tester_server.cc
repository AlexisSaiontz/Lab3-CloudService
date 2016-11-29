#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <grpc++/grpc++.h>

#include "test.grpc.pb.h"
#include "headers.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using mutate::Node;
using mutate::Edge;
using mutate::Code;
using mutate::Mutator;

// define the service class.
class TesterService final : public Mutator::Service {
  
  Status add_node(ServerContext* context, const Node* node,
                  Code* reply) override {
    // Call add_node, set *reply accordingly
    printf("Received: Add node %d\n", (int) node->id());
    reply->set_code(300);
    return Status::OK;
  }

  Status remove_node(ServerContext* context, const Node* node,
		     Code* reply) override {
    printf("Received: Remove node %d\n", (int) node->id());
    reply->set_code(300);
    return Status::OK;

  }

  Status add_edge(ServerContext* context, const Edge* edge,
                  Code* reply) override {
    printf("Received: Add edge %d - %d\n", (int) edge->id_a(), (int) edge->id_b());
    reply->set_code(300);
    return Status::OK;
  }

  Status remove_edge(ServerContext* context, const Edge* edge,
                  Code* reply) override {
    printf("Received: Remove edge %d - %d\n", (int) edge->id_a(), (int) edge->id_b()); 
    reply->set_code(300);
    return Status::OK;
  }
};

int serve_previous() {

  std::string address = "0.0.0.0:8080";
  TesterService service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << address << std::endl;
  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();

  return 0;
}
