#include <SFML/Graphics.hpp>
#include <SFML\Network.hpp>
#include <Windows.h>
#include "WorldComponent.h"
#include <thread>

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
#include "GameManager.h"
#include "LobbyState.h"
#include "Network.h"
int main()
{
	/*NETWORK.Initialise();
	NETWORK.sendRecvUDPMessage("bluh");
	NETWORK.sendRecvUDPMessage("bluh2");
	NETWORK.sendRecvUDPMessage("bluher");

	NETWORK.printQueue();*/







	/*sf::UdpSocket *socket = new sf::UdpSocket();
	socket->bind(PORT);

	std::string msg = "hello";


	std::thread thread1(send_recv_msg, msg, socket);

	thread1.join();*/


	//socket.receive(buffer, sizeof(buffer), received, sIP, sPORT);
	
	//msg = std::string(buffer);

	//sf::Text message = sf::Text();
	//message.setString(msg);
	//message.setColor(sf::Color::Magenta);
	//message.setPosition(100, 100);
	//OutputDebugString(L"Reached this point");


	sf::RenderWindow window(sf::VideoMode(800, 600), "Mario Kart(ish)");
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
	
	//create world component instance and initialise
	/*WorldComponent world;
	if (!world.Initialise())
	{
		OutputDebugString(L"World failed to initialise");
		return 0;
	}*/


	std::shared_ptr<LobbyState> ls = std::make_shared<LobbyState>();
	std::shared_ptr<WorldComponent> wc = std::make_shared<WorldComponent>();
	NETWORK.Initialise();
	NETWORK.sendRecvUDPMessage("test");
	GAMEMANAGER.Initialise();
	GAMEMANAGER.addState("lobby", ls);
	GAMEMANAGER.addState("game", wc);
	GAMEMANAGER.setState("lobby");


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
				
		} 
		

		//world.Update();
		window.clear();
		GAMEMANAGER.Run(window);
		//window.draw(message);
		//world.Render(window);
		window.display();
	}

	delete &NETWORK;
	delete &GAMEMANAGER;
	return 0;
}