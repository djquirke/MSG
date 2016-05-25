#pragma once

#include <SFML\Network.hpp>
#include <string>
#include <queue>
#include <thread>

#define NETWORK Network::getInstance()

#define HOST "255.255.255.255"
#define PORT 9046
#define SERVER_PORT 9045
#define MAX_BUFFER_SIZE 1024

class Network
{
public:
	static Network& getInstance();
	~Network();

	void Initialise();
	void sendUDPMessage(std::string msg);
	void recvUDPMessage();
	void sendRecvUDPMessage(std::string msg);

	void sendTCPMessage(std::string msg);
	void recvTCPMessage();
	void sendRecvTCPMessage(std::string msg);

	void printQueue();

private:
	Network() {};
	void cleanup();

	Network(Network const&) = delete;
	void operator=(Network const&) = delete;

	sf::UdpSocket *socket_;
	sf::TcpSocket tcp_socket_;
	std::queue<std::string> msg_queue_;
	
	std::thread tcp_recv_thread_;
	bool run_ = false;
	
	static Network *instance_;

};