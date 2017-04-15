#include "stdafx.h"
#include "Data.h"

namespace pan{
	GameData::GameData() :
		initialized(false),
		state(GameState::InProgress),
		infectionRateMarker(0),
		outbreakMarker(0),
		researchStations(0)
	{
	}

	GameData::GameData(const Settings& s) : 
		settings(s),
		initialized(false),
		state(GameState::InProgress),
		infectionRateMarker(0), 
		outbreakMarker(0),
		researchStations(0)
	{
	}

	GameData::GameData(const GameData& o):
		settings(o.settings),
		initialized(o.initialized),
		state(o.state),
		infectionRateMarker(o.infectionRateMarker),
		outbreakMarker(o.outbreakMarker),
		researchStations(o.researchStations),
		diseases(o.diseases),
		diseaseCubes(o.diseaseCubes)
	{
	}

	GameData::~GameData()
	{
	}

	GameData& GameData::operator=(const GameData& o)
	{
		this->settings = o.settings;
		this->initialized = o.initialized;
		this->state = o.state;
		this->infectionRateMarker = o.infectionRateMarker;
		this->outbreakMarker = o.outbreakMarker;
		this->researchStations = o.researchStations;
		this->diseases = o.diseases;
		this->diseaseCubes = o.diseaseCubes;
		return *this;
	}

	GameData::GameData(GameData&& o) :
		settings(o.settings),
		initialized(o.initialized),
		state(o.state),
		infectionRateMarker(o.infectionRateMarker),
		outbreakMarker(o.outbreakMarker),
		researchStations(o.researchStations),
		diseases(std::move(o.diseases)),
		diseaseCubes(std::move(o.diseaseCubes))
	{
	}

	GameData& GameData::operator=(GameData&& o)
	{
		this->settings = o.settings;
		this->initialized = o.initialized;
		this->state = o.state;
		this->infectionRateMarker = o.infectionRateMarker;
		this->outbreakMarker = o.outbreakMarker;
		this->researchStations = o.researchStations;
		this->diseases = std::move(o.diseases);
		this->diseaseCubes = std::move(o.diseaseCubes);
		return *this;
	}

	bool GameData::operator==(const GameData& o) const
	{
		bool equal = (settings == o.settings
			&& initialized == o.initialized
			&& state == o.state
			&& infectionRateMarker == o.infectionRateMarker
			&& outbreakMarker == o.outbreakMarker
			&& researchStations == o.researchStations
			&& diseases.size() == o.diseases.size()
			&& diseaseCubes == o.diseaseCubes);
		if (!equal) return false;
		for (std::size_t i = 0; i < diseases.size(); i++){
			if (diseases[i] != o.diseases[i])
				return false;
		}
		return true;
	}

	bool GameData::operator!=(const GameData& o) const
	{
		return !((*this) == o);
	}

	std::string GameData::description() const
	{
		std::string res = "Settings: " + settings.description() +
			"\nInitialized: " + std::to_string(initialized) +
			"\nState: " + GameStateDescriptions.at(state) + 
			"\nInfection Rate Marker: " + std::to_string(infectionRateMarker) +
			"\nOutbreak Marker: " + std::to_string(outbreakMarker) +
			"\nResearch Stations: " + std::to_string(researchStations) +
			"\nDiseases:\n";
		for (const auto& d : diseases){
			res += d.description() + '\n';
		}
		res += "DiseaseCubes:\n";
		for (std::size_t i = 0; i < diseaseCubes.size(); i++){
			res += "DiseaseType: " + std::to_string(i) + " cubes: " + std::to_string(diseaseCubes[i]) + '\n';
		}
		return res;
	}

	PlayerData::PlayerData() : 
		occupiedRoles(RolesDescriptions.size(), false),
		stage(PlayerStage::Act),
		prevStage(PlayerStage::Act),
		turn(0),
		actionCounter(0)
	{
	}

	PlayerData::PlayerData(const PlayerData& o) :
		players(o.players),
		occupiedRoles(o.occupiedRoles),
		stage(o.stage),
		prevStage(o.prevStage),
		turn(o.turn),
		actionCounter(0)
	{
	}

	PlayerData::~PlayerData()
	{
	}

	PlayerData& PlayerData::operator=(const PlayerData& o)
	{
		this->players = o.players;
		this->occupiedRoles = o.occupiedRoles;
		this->stage = o.stage;
		this->prevStage = o.prevStage;
		this->turn = o.turn;
		this->actionCounter = o.actionCounter;
		return *this;
	}

	PlayerData::PlayerData(PlayerData&& o) :
		players(std::move(o.players)),
		occupiedRoles(std::move(o.occupiedRoles)),
		stage(o.stage),
		prevStage(o.prevStage),
		turn(o.turn),
		actionCounter(o.actionCounter)
	{
	}

	PlayerData& PlayerData::operator=(PlayerData&& o)
	{
		this->players = std::move(o.players);
		this->occupiedRoles = std::move(o.occupiedRoles);
		this->stage = o.stage;
		this->prevStage = o.prevStage;
		this->turn = o.turn;
		this->actionCounter = o.actionCounter;
		return *this;
	}

	bool PlayerData::operator==(const PlayerData& o) const
	{
		bool equal = (occupiedRoles == o.occupiedRoles && 
					stage == o.stage && prevStage == o.prevStage
					&& turn == o.turn
					&& actionCounter == o.actionCounter);
		if (!equal)
			return false;
		for (std::size_t i = 0; i < players.size(); i++){
			if (*players[i] != *o.players[i])
				return false;
		}
		return true;
	}

	bool PlayerData::operator!=(const PlayerData& o) const
	{
		return !((*this) == o);
	}

	std::string PlayerData::description() const
	{
		std::string res = "Players:\n";
		for (const auto& p : players){
			res += p->description() + '\n';
		}
		res += "Turn: " + std::to_string(turn);
		return res;
	}

	DeckData::DeckData()
	{
	}

	DeckData::DeckData(const DeckData& o) :
		infectionDeck(o.infectionDeck),
		infectionDiscardDeck(o.infectionDiscardDeck),
		playerDeck(o.playerDeck),
		playerDiscardDeck(o.playerDiscardDeck)
	{
	}

	DeckData::~DeckData()
	{
	}

	DeckData& DeckData::operator=(const DeckData& o)
	{
		this->infectionDeck = o.infectionDeck;
		this->infectionDiscardDeck = o.infectionDiscardDeck;
		this->playerDeck = o.playerDeck;
		this->playerDiscardDeck = o.playerDiscardDeck;
		return *this;
	}

	DeckData::DeckData(DeckData&& o) :
		infectionDeck(std::move(o.infectionDeck)),
		infectionDiscardDeck(std::move(o.infectionDiscardDeck)),
		playerDeck(std::move(o.playerDeck)),
		playerDiscardDeck(std::move(o.playerDiscardDeck))
	{
	}

	DeckData& DeckData::operator=(DeckData&& o)
	{
		this->infectionDeck = std::move(o.infectionDeck);
		this->infectionDiscardDeck = std::move(o.infectionDiscardDeck);
		this->playerDeck = std::move(o.playerDeck);
		this->playerDiscardDeck = std::move(o.playerDiscardDeck);
		return *this;
	}

	bool DeckData::operator==(const DeckData& o) const
	{
		bool equals = (infectionDeck.size() == o.infectionDeck.size()
			&& infectionDiscardDeck.size() == o.infectionDiscardDeck.size()
			&& playerDeck.size() == o.playerDeck.size()
			&& playerDiscardDeck.size() == o.playerDiscardDeck.size());
		if (!equals)
			return false;
		for (std::size_t i = 0; i < infectionDeck.size(); i++){
			if (*infectionDeck._Get_container()[i] != *o.infectionDeck._Get_container()[i])
				return false;
		}
		for (std::size_t i = 0; i < infectionDiscardDeck.size(); i++){
			if (*infectionDiscardDeck._Get_container()[i] != *o.infectionDiscardDeck._Get_container()[i])
				return false;
		}
		for (std::size_t i = 0; i < playerDeck.size(); i++){
			if (*playerDeck._Get_container()[i] != *o.playerDeck._Get_container()[i])
				return false;
		}
		for (std::size_t i = 0; i < playerDiscardDeck.size(); i++){
			if (*playerDiscardDeck._Get_container()[i] != *o.playerDiscardDeck._Get_container()[i])
				return false;
		}
		return true;
	}

	bool DeckData::operator!=(const DeckData& o) const
	{
		return !((*this) == o);
	}

	std::string DeckData::description() const
	{
		std::string res = "Player Deck:\n";
		for (const auto& c : playerDeck._Get_container()){
			res += c->description() + '\n';
		}
	    res += "Player Discard Deck:\n";
		for (const auto& c : playerDiscardDeck._Get_container()){
			res += c->description() + '\n';
		}
		res += "Infection Deck:\n";
		for (const auto& c : infectionDeck._Get_container()){
			res += c->description() + '\n';
		}
		res += "Infection Discard Deck:\n";
		for (const auto& c : infectionDiscardDeck._Get_container()){
			res += c->description() + '\n';
		}
		return res;
	}
}
