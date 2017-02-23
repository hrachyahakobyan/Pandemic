#include "stdafx.h"
#include "Game.h"

namespace pan{
	Game::Game() :
		actionHandler(*this)
	{
	}

	Game::Game(const Map& m) :
		actionHandler(*this),
		map(m)
	{
	}

	Game::Game(const Game& o) :
		actionHandler(*this),
		map(o.map),
		players(o.players)
	{
	}

	Game::Game(Game&& o) :
		actionHandler(*this),
		map(std::move(o.map)),
		players(std::move(o.players))
	{
	}

	Game::~Game()
	{

	}

	Game& Game::operator=(const Game& o)
	{
		this->map = o.map;
		this->players = o.players;
		return *this;
	}

	Game& Game::operator=(Game&& o)
	{
		this->map = std::move(o.map);
		this->players = std::move(o.players);
		return *this;
	}

	bool Game::operator==(const Game& o) const
	{
		if (this->map != o.map)
			return false;
		if (this->players.size() != o.players.size())
			return false;
		std::size_t size = this->players.size();
		for (std::size_t i = 0; i < size; i++){
			if (*(this->players[i]) != *(o.players[i]))
				return false;
		}
		return true;
	}

	std::string Game::description() const
	{
		std::string res = "Game: \n";
		res += "Map: \n" + map.description() + '\n';
		res += "Players: \n";
		for (const auto& p : players){
			res += p->description() + '\n';
		}
		return res;
	}
}