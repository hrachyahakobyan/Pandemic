#pragma once
#include "detail\Notification.h"
#include "PlayerBase.h"
#include "City.h"
#include "Disease.h"
#include "Data.h"
#include "common.h"

namespace pan{
	class CityUpdateNotification : public detail::Notification{
	public:
		CityUpdateNotification(const pan::City& c, pan::CityIndex i) :city(c), index(i){}
		const pan::City& city;
		pan::CityIndex index;
	};

	class PlayerUpdateNotification : public detail::Notification{
	public:
		PlayerUpdateNotification(const pan::PlayerBase& p) : player(p){}
		const pan::PlayerBase& player;
	};

	class GameDataUpdateNotification : public detail::Notification{
	public:
		GameDataUpdateNotification(const GameData& d) : data(d){}
		const GameData& data;
	};

	class DeckDataUpdateNotification : public detail::Notification{
	public:
		DeckDataUpdateNotification(const DeckData& d) : data(d){}
		const DeckData& data;
	};

	class PlayerDataUpdateNotification : public detail::Notification{
	public:
		PlayerDataUpdateNotification(const PlayerData& d) : data(d){}
		const PlayerData& data;
	};
}