# 426-Lab3
This assignment was worked on by Alexis Saiontz and Stylianos Rousoglou.

IMPORTANT:
On each VM, execute "export CHAIN_NUM=n", where n is the VM's position in the chain. So 1 for the head, 2 for the middle, 3 for the tail.

# Assignment 3: Replicating the Graph Store #

----

## Introduction ##

In this lab, we'll replicate the graph store you built in Lab 1 and Lab 2. 
We'll use a simple hybrid of the chain replication and primary backup protocols. 
Clients will send each update to the primary replica, which will forward the update to a backup replica, 
which in turn will forward the update to the next replica in the chain, and so on. 
Acknowledgments will travel up the chain back to the primary, which will respond to the client.

Reads are satisfied at the tail of the chain. 
We will also support reads from the middle of the chain. 
Each replica only applies the update to its own state (and sends back an ack to its predecessor in the chain) 
when it receives the acknowledgment from its successor.

For this lab, you can choose to either build above the non-durable Lab 1 version or 
the durable Lab 2 version of your code. 
We will not require durability for this lab, so it may be simpler to start from your Lab 1 version.

This lab also need to run on Google Cloud. You need to create two more VM to form a 3-server chain. 

## API Changes ##

The API is identical to lab 2, with one exception: 
the mutator methods should return error code 500 if there's a problem with replication 
(e.g. if a node in the chain is unreachable and the RPC fails).

## Inter-node communication ##

You can use any RPC library for inter-node communication. We suggest you use Apache Thrift.
