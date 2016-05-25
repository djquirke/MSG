#include "Network.h"
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
	sendTCPMessage("quit:");
	if (socket_ != NULL)
	{
		socket_->unbind();
		socket_->~UdpSocket();
	}
	run_ = false;

	tcp_recv_thread_.join();
	tcp_socket_.disconnect();
}

void Network::Initialise()
{
	msg_queue_ = std::queue<std::string>();
	socket_ = new sf::UdpSocket();
	socket_->bind(PORT);
	sendRecvUDPMessage("testing udp");

	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	
	tcp_socket_.connect(ip, SERVER_PORT, sf::milliseconds(2000));

	//start threads
	run_ = true;
	tcp_recv_thread_ = std::thread(&Network::recvTCPMessage, this);

}

void Network::sendUDPMessage(std::string msg)
{
	msg += "\n";

	char buffer[MAX_BUFFER_SIZE];

	memset(buffer, 0, sizeof(buffer));
	memcpy(buffer, msg.c_str(), msg.length());
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
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

void Network::sendRecvUDPMessage(std::string msg)
{
	sendUDPMessage(msg);
	recvUDPMessage();
}

void Network::sendTCPMessage(std::string msg)
{
	msg += "\n";
	char buffer[MAX_BUFFER_SIZE];

	memset(buffer, 0, sizeof(buffer));
	memcpy(buffer, msg.c_str(), msg.length());

	tcp_socket_.send(buffer, msg.length() + 1);
}

void Network::recvTCPMessage()
{
	while (run_)
	{
		char buffer[MAX_BUFFER_SIZE];

		memset(buffer, 0, sizeof(buffer));
		size_t received = 0;
		sf::IpAddress sIP;
		unsigned short sPort = SERVER_PORT;

		tcp_socket_.receive(buffer, MAX_BUFFER_SIZE, received);

		if (std::string(buffer) != "")
			msg_queue_.push(std::string(buffer));
	}
}

void Network::sendRecvTCPMessage(std::string msg)
{
	sendTCPMessage(msg);
	recvTCPMessage();
}


void Network::printQueue()
{
	while (!msg_queue_.empty())
	{
		std::wstring stemp = std::wstring(msg_queue_.front().begin(), msg_queue_.front().end());
		OutputDebugStringW(stemp.c_str());
		msg_queue_.pop();

	}
}