#include "Network.h"
#include <thread>
#include <Windows.h>

Network* Network::instance_ = NULL;

Network& Network::getInstance()
{
	if (instance_ == NULL)
		instance_ = new Network();

	return *instance_;
}

Network::~Network()
{
	cleanup();
}

void Network::cleanup()
{
	socket_->unbind();
	socket_->~UdpSocket();
}

void Network::Initialise()
{
	socket_ = new sf::UdpSocket();
	socket_->bind(PORT);

	msg_queue_ = std::queue<std::string>();

	//start threads
}

void Network::sendUDPMessage(const std::string &msg)
{
	char buffer[MAX_BUFFER_SIZE];

	memset(buffer, 0, sizeof(buffer));
	memcpy(buffer, msg.c_str(), msg.length());

	socket_->send(buffer, msg.length(), HOST, SERVER_PORT);
}

void Network::recvUDPMessage()
{
	char buffer[MAX_BUFFER_SIZE];

	memset(buffer, 0, sizeof(buffer));
	size_t received = 0;
	sf::IpAddress sIP;
	unsigned short sPort = SERVER_PORT;
	socket_->receive(buffer, MAX_BUFFER_SIZE, received, sIP, sPort);

	msg_queue_.push(std::string(buffer));
}

void Network::sendRecvUDPMessage(const std::string &msg)
{
	sendUDPMessage(msg);
	recvUDPMessage();
}


void Network::printQueue()
{
	while (!msg_queue_.empty())
	{
		std::wstring stemp = std::wstring(msg_queue_.front().begin(), msg_queue_.front().end());// +std::wstring("\n");
		OutputDebugStringW(stemp.c_str());
		msg_queue_.pop();

	}
}