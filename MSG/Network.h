#pragma once

#include <SFML\Network.hpp>
#include <string>
#include <queue>

#define NETWORK Network::getInstance()

#define HOST "localhost"
#define PORT 9046
#define SERVER_PORT 9045
#define MAX_BUFFER_SIZE 1024

class Network
{
public:
	static Network& getInstance();
	~Network();

	void Initialise();
	void sendUDPMessage(const std::string &msg);
	void recvUDPMessage();
	void sendRecvUDPMessage(const std::string &msg);

	void printQueue();

private:
	Network() {};
	void cleanup();

	Network(Network const&) = delete;
	void operator=(Network const&) = delete;

	sf::UdpSocket *socket_;
	std::queue<std::string> msg_queue_;
	static Network *instance_;
};