#include <SFML\Network.hpp>
#include <Windows.h>
#include "WorldComponent.h"
#include <thread>
#include "GameManager.h"
#include "MainMenuState.h"
#include "Network.h"
#include "KeyboardHandler.h"

#define HOST "localhost"
#define PORT 9046
#define SERVER_PORT 9045
#define MAX_BUFFER_SIZE 1024

void send_msg(const std::string &msg, sf::UdpSocket *socket)
{
	char buffer[MAX_BUFFER_SIZE];

	memset(buffer, 0, sizeof(buffer));
	memcpy(buffer, msg.c_str(), msg.length());

	socket->send(buffer, msg.length(), HOST, SERVER_PORT);
}

void recv_msg(sf::UdpSocket *socket)
{
	char buffer[MAX_BUFFER_SIZE];

	memset(buffer, 0, sizeof(buffer));
	size_t received = 0;
	sf::IpAddress sIP;
	unsigned short sPort = SERVER_PORT;
	socket->receive(buffer, MAX_BUFFER_SIZE, received, sIP, sPort);

	//*recvd = std::string(buffer);
}

void send_recv_msg(const std::string &msg, sf::UdpSocket *socket)
{
	send_msg(msg, socket);
	recv_msg(socket);
}

int main()
{
	/*sf::UdpSocket *socket = new sf::UdpSocket();
	socket->bind(PORT);

	std::string msg = "hello";


	std::thread thread1(send_recv_msg, msg, socket);

	thread1.join();*/

	std::shared_ptr<MainMenuState> mm = std::make_shared<MainMenuState>();
	std::shared_ptr<WorldComponent> wc = std::make_shared<WorldComponent>();
	NETWORK.Initialise();
	NETWORK.sendTCPMessage("test");
	Sleep(500);
	NETWORK.sendTCPMessage("test2");
	Sleep(500);
	NETWORK.sendTCPMessage("test3");
	//NETWORK.sendRecvUDPMessage("test");
	GAMEMANAGER.Initialise(800, 600, "Drag Queen");
	GAMEMANAGER.addState("main", mm);
	GAMEMANAGER.addState("game", wc);
	GAMEMANAGER.setState("main");
	GAMEMANAGER.Run();

	delete &NETWORK;
	delete &GAMEMANAGER;
	delete &KEYBOARD;
	return 0;
}