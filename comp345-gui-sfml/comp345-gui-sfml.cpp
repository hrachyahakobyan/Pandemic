// comp345-gui-sfml.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define VIEWWIDTH (float)desktopMode.width
#define VIEWHEIGHT (float)desktopMode.height

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace pan;
	Game game(Settings::Beginner(4));

	enum gameState { playerInit, play };
	gameState gameState = playerInit;
	int currentPlayer = 0;

	sf::Mouse mouse;

	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(desktopMode), "Pandemic", sf::Style::Default);

	sf::View view(sf::FloatRect(0, 0, 3440, 1440));

	window.setView(view);

	sf::Texture mapG;
	mapG.loadFromFile("resources\\map.png");
	sf::Sprite map(mapG);
	map.setOrigin(map.getTexture()->getSize().x *0.5f, map.getTexture()->getSize().y *0.5f);
	map.setPosition(VIEWWIDTH*0.5f, VIEWHEIGHT*0.5f);
	map.setScale(VIEWHEIGHT / map.getTexture()->getSize().y, VIEWHEIGHT / map.getTexture()->getSize().y);

	std::string nameDisplayString = "";

	sf::Font titleFont;
	titleFont.loadFromFile("resources\\fonts\\UnitedKingdom.otf");

	sf::Text nameDisplayText;
	nameDisplayText.setFont(titleFont);
	nameDisplayText.setString(nameDisplayString);
	nameDisplayText.setCharacterSize(30);
	nameDisplayText.setFillColor(sf::Color(244, 244, 244));
	nameDisplayText.setPosition(VIEWWIDTH * 0.5f, VIEWHEIGHT * 0.5f);

	sf::Text enterNameText;
	enterNameText.setFont(titleFont);
	enterNameText.setString("Enter Player 1 Name");
	enterNameText.setCharacterSize(36);
	enterNameText.setFillColor(sf::Color(6, 69, 133));
	enterNameText.setPosition(VIEWWIDTH * 0.5f, VIEWHEIGHT * 0.5f - 42.0f);

	sf::Texture nextPlayerG;
	sf::Texture previousPlayerG;
	nextPlayerG.loadFromFile("resources\\nextPlayer.png");
	previousPlayerG.loadFromFile("resources\\previousPlayer.png");
	sf::Sprite nextPlayer(nextPlayerG);
	sf::Sprite previousPlayer(previousPlayerG);
	nextPlayer.setOrigin(nextPlayer.getTexture()->getSize().x *0.5f, nextPlayer.getTexture()->getSize().y *0.5f);
	previousPlayer.setOrigin(previousPlayer.getTexture()->getSize().x *0.5f, previousPlayer.getTexture()->getSize().y *0.5f);
	nextPlayer.setPosition(VIEWWIDTH*0.75f, VIEWHEIGHT*0.90f);
	previousPlayer.setPosition(VIEWWIDTH*0.25f, VIEWHEIGHT*0.90f);
	nextPlayer.setScale((VIEWHEIGHT / nextPlayer.getTexture()->getSize().y)*0.1f, (VIEWHEIGHT / nextPlayer.getTexture()->getSize().y)*0.1f);
	previousPlayer.setScale((VIEWHEIGHT / previousPlayer.getTexture()->getSize().y)*0.1f, (VIEWHEIGHT / previousPlayer.getTexture()->getSize().y)*0.1f);

	sf::Texture playerInfoBoxG;
	playerInfoBoxG.loadFromFile("resources\\playerInfoBox.png");
	sf::Sprite playerInfoBox(playerInfoBoxG);
	playerInfoBox.setOrigin(playerInfoBox.getTexture()->getSize().x * 0.5f, playerInfoBox.getTexture()->getSize().y * 0.5f);
	playerInfoBox.setPosition(VIEWWIDTH*0.5f, VIEWHEIGHT*0.90f);
	playerInfoBox.setScale((VIEWHEIGHT / playerInfoBox.getTexture()->getSize().y)*0.2f, (VIEWHEIGHT / playerInfoBox.getTexture()->getSize().y)*0.2f);


	sf::Text playerTurnText;
	playerTurnText.setFont(titleFont);
	playerTurnText.setString("Player 1's turn");
	playerTurnText.setCharacterSize(36);
	playerTurnText.setFillColor(sf::Color(244, 244, 244));
	playerTurnText.setPosition(VIEWWIDTH * 0.5f, VIEWHEIGHT * 0.025f);

	sf::Text playerInformation;
	playerInformation.setFont(titleFont);
	playerInformation.setString("Player Information");
	playerInformation.setCharacterSize(24);
	playerInformation.setFillColor(sf::Color(244, 244, 244));
	playerInformation.setPosition(VIEWWIDTH * 0.35f, VIEWHEIGHT * 0.825f);


	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Escape:
					window.close();
					break;

				}
			}


			switch (gameState)
			{
			case playerInit:
				switch (event.type)
				{
				case sf::Event::TextEntered:
					if (event.key.code > 31 && event.key.code < 126)
						nameDisplayString += event.key.code;
					break;

				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::BackSpace && nameDisplayString.size() > 0)
						nameDisplayString.pop_back();
					else if (event.key.code == sf::Keyboard::Return)
					{
						game.addRandomPlayer(nameDisplayString);
						nameDisplayString = "";
						enterNameText.setString("Enter player " + std::to_string(game.playerCount() + 1) + " name");
						if (game.playerCount() == 4)
						{
							gameState = play;
							currentPlayer = 0;
						}
					}
					break;
				}
				window.clear();
				nameDisplayText.setString(nameDisplayString);
				window.draw(nameDisplayText);
				window.draw(enterNameText);
				window.display();
				break;

			case play:
				switch (event.type)
				{
				case sf::Event::MouseButtonReleased:
					if (nextPlayer.getGlobalBounds().contains(float(mouse.getPosition().x), float(mouse.getPosition().y)))
					{
						currentPlayer++;
						if (currentPlayer == 3) currentPlayer = 0;
					}
					if (previousPlayer.getGlobalBounds().contains(float(mouse.getPosition().x), float(mouse.getPosition().y)))
					{
						currentPlayer--;
						if (currentPlayer == -1) currentPlayer = 3;
					}
					break;

				}
				playerInformation.setString(static_cast<const Game&>(game).getPlayer(currentPlayer).description());
				playerTurnText.setString(static_cast<const Game&>(game).getPlayer(currentPlayer).getName() + "'s turn");
				window.clear();
				window.draw(map);
				window.draw(playerTurnText);
				window.draw(nextPlayer);
				window.draw(previousPlayer);
				window.draw(playerInfoBox);
				window.draw(playerInformation);
				window.display();
				break;
			}
		}
	}
}

