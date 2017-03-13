#include "stdafx.h"
#include "Game.h"

namespace pan{

	Game::Game(const Settings& s) :
		actionHandler(*this),
		settings(s)
	{
	}

	Game::Game(const Settings& s, const Map& m) :
		actionHandler(*this),
		settings(s),
		map(m)
	{
		for (auto diseaseType : map.getRegions()){
			diseases.push_back(Disease(diseaseType));
		}
	}

	Game::Game(const Game& o) :
		actionHandler(*this),
		map(o.map),
		diseases(o.diseases),
		players(o.players)
	{
	}

	Game::Game(Game&& o) :
		actionHandler(*this),
		diseases(std::move(o.diseases)),
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
		this->diseases = o.diseases;
		return *this;
	}

	Game& Game::operator=(Game&& o)
	{
		this->map = std::move(o.map);
		this->players = std::move(o.players);
		this->diseases = std::move(o.diseases);
		return *this;
	}

	bool Game::operator==(const Game& o) const
	{
		if (this->players.size() != o.players.size())
			return false;
		if (this->diseases.size() != o.diseases.size())
			return false;
		if (this->settings != o.settings)
			return false;
		if (this->map != o.map)
			return false;
		std::size_t size = this->players.size();
		for (std::size_t i = 0; i < size; i++){
			if (*(this->players[i]) != *(o.players[i]))
				return false;
		}
		size = this->diseases.size();
		for (std::size_t i = 0; i < size; i++){
			if ((this->diseases[i]) != (o.diseases[i]))
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
		res += "Diseases: \n";
		for (const auto& d : diseases){
			res += d.description() + '\n';
		}
		return res;
	}
}