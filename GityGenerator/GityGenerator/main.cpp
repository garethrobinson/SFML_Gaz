#include <Windows.h>
#include <tchar.h>
#include <SFML\Graphics.hpp>

#include "Level.h"
#include "Input.h"

int WinMain( HINSTANCE hInstance,
	 HINSTANCE hPrevInstance,
	 LPSTR     lpCmdLine,
	 int       nCmdShow) {


	sf::RenderWindow window(sf::VideoMode(256, 240), "SFML works!");
	window.setSize(sf::Vector2u(512, 480));
	Input input;
	Level level(&window, &input);

	//Delta time calculation
	sf::Clock clock;
	float deltaTime;
	sf::Text fpsText;
	sf::Font txtFont;

	if (!txtFont.loadFromFile("Images/ALGER.ttf")) {
		std::cout << "Error loading font\n";
	}
	fpsText.setFont(txtFont);
	fpsText.setCharacterSize(16);
	fpsText.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		//Reset the clock
		deltaTime = clock.restart().asSeconds();
		fpsText.setString(std::to_string(1.0f / deltaTime));
		//Reset the Input and log the last tick's input
		input.Update();

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
						window.close();
					else
						input.SetKeyDown(event.key.code);
					break;
				case sf::Event::KeyReleased:
						input.SetKeyUp(event.key.code);
					break;
				case sf::Event::MouseMoved:
					input.SetMousePosition(event.mouseMove.x, event.mouseMove.y);
					break;
				case sf::Event::MouseButtonPressed:
					input.SetMouseButtonDown(event.mouseButton.button);
					break;
				case sf::Event::MouseButtonReleased:
					input.SetMouseButtonUp(event.mouseButton.button);
					break;
			}
		}
		
		level.HandleInput();
		level.Update(deltaTime);

		window.clear(sf::Color::Black);
		level.Render();
		window.draw(fpsText);
		window.display();
	}

	return 0;
}