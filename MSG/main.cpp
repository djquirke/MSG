#include <SFML/Graphics.hpp>
#include "WorldComponent.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Mario Kart(ish)");
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
	
	//create world component instance and initialise
	WorldComponent world;
	world.Initialise();


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

		world.Update();
		window.clear();
		world.Render(window);
		window.display();

		/*window.clear();
		window.draw(shape);
		window.display();*/
	}

	return 0;
}