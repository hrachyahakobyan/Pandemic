#include "stdafx.h"
#include "GuiTest.h"
#define VIEWWIDTH (float)desktopMode.width
#define VIEWHEIGHT (float)desktopMode.height

pan::GuiTest::GuiTest()
{	
	pan::Game game = Game();

	enum gameState {playerInit, play};
	gameState gameState = playerInit;
	int currentPlayer = 0;
	
	sf::Mouse mouse;
	
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(desktopMode), "Pandemic", sf::Style::Fullscreen);

	sf::View view(sf::FloatRect(0, 0, 3440, 1440));

	window.setView(view);

	sf::Texture mapG;
	mapG.loadFromFile("assets\\img\\map.png");
	sf::Sprite map(mapG);
	map.setOrigin(map.getTexture()->getSize().x *0.5, map.getTexture()->getSize().y *0.5);
	map.setPosition(VIEWWIDTH*0.5, VIEWHEIGHT*0.5);
	map.setScale(VIEWHEIGHT / map.getTexture()->getSize().y, VIEWHEIGHT / map.getTexture()->getSize().y);

	std::string nameDisplayString = "";

	sf::Font titleFont;
	titleFont.loadFromFile("assets\\fonts\\UnitedKingdom.otf");

	sf::Text nameDisplayText;
	nameDisplayText.setFont(titleFont);
	nameDisplayText.setString(nameDisplayString);
	nameDisplayText.setCharacterSize(30);
	nameDisplayText.setColor(sf::Color(244, 244, 244));
	nameDisplayText.setPosition(VIEWWIDTH * 0.5, VIEWHEIGHT * 0.5);

	sf::Text enterNameText;
	enterNameText.setFont(titleFont);
	enterNameText.setString("Enter Player 1 Name");
	enterNameText.setCharacterSize(36);
	enterNameText.setColor(sf::Color(6, 69, 133));
	enterNameText.setPosition(VIEWWIDTH * 0.5, VIEWHEIGHT * 0.5 - 42);

	sf::Texture nextPlayerG;
	sf::Texture previousPlayerG;
	nextPlayerG.loadFromFile("assets\\img\\nextPlayer.png");
	previousPlayerG.loadFromFile("assets\\img\\previousPlayer.png");
	sf::Sprite nextPlayer(nextPlayerG);
	sf::Sprite previousPlayer(previousPlayerG);
	nextPlayer.setOrigin(nextPlayer.getTexture()->getSize().x *0.5, nextPlayer.getTexture()->getSize().y *0.5);
	previousPlayer.setOrigin(previousPlayer.getTexture()->getSize().x *0.5, previousPlayer.getTexture()->getSize().y *0.5);
	nextPlayer.setPosition(VIEWWIDTH*0.75, VIEWHEIGHT*0.90);
	previousPlayer.setPosition(VIEWWIDTH*0.25, VIEWHEIGHT*0.90);
	nextPlayer.setScale((VIEWHEIGHT / nextPlayer.getTexture()->getSize().y)*0.1, (VIEWHEIGHT / nextPlayer.getTexture()->getSize().y)*0.1);
	previousPlayer.setScale((VIEWHEIGHT / previousPlayer.getTexture()->getSize().y)*0.1, (VIEWHEIGHT / previousPlayer.getTexture()->getSize().y)*0.1);

	sf::Texture playerInfoBoxG;
	playerInfoBoxG.loadFromFile("assets\\img\\playerInfoBox.png");
	sf::Sprite playerInfoBox(playerInfoBoxG);
	playerInfoBox.setOrigin(playerInfoBox.getTexture()->getSize().x * 0.5, playerInfoBox.getTexture()->getSize().y * 0.5);
	playerInfoBox.setPosition(VIEWWIDTH*0.5, VIEWHEIGHT*0.90);
	playerInfoBox.setScale((VIEWHEIGHT / playerInfoBox.getTexture()->getSize().y)*0.2, (VIEWHEIGHT / playerInfoBox.getTexture()->getSize().y)*0.2);


	sf::Text playerTurnText;
	playerTurnText.setFont(titleFont);
	playerTurnText.setString("Player 1's turn");
	playerTurnText.setCharacterSize(36);
	playerTurnText.setColor(sf::Color(244, 244, 244));
	playerTurnText.setPosition(VIEWWIDTH * 0.5, VIEWHEIGHT * 0.025);

	sf::Text playerInformation;
	playerInformation.setFont(titleFont);
	playerInformation.setString("Player Information");
	playerInformation.setCharacterSize(24);
	playerInformation.setColor(sf::Color(244, 244, 244));
	playerInformation.setPosition(VIEWWIDTH * 0.35, VIEWHEIGHT * 0.825);


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
						game.addPlayer<Roles::Medic>(nameDisplayString);
						nameDisplayString = "";
						enterNameText.setString("Enter player " + std::to_string(game.playerCount() + 1) + " name");
						if (game.playerCount() > 3)
						{
							gameState = play;
							currentPlayer = 1;
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
					if (nextPlayer.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y))
					{
						currentPlayer++;
						if (currentPlayer == 5) currentPlayer = 1;
					}
					if (previousPlayer.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y))
					{
						currentPlayer--;
						if (currentPlayer == 0) currentPlayer = 4;
					}
					break;

				}
				playerInformation.setString(static_cast<const Game&>(game).getPlayer(currentPlayer - 1).description());
				playerTurnText.setString(static_cast<const Game&>(game).getPlayer(currentPlayer - 1).getName() + "'s turn");
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