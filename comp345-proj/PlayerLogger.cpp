#include "stdafx.h"
#include "PlayerLogger.h"
#include "detail\NotificationCenter.h"

namespace pan{
	PlayerLogger::PlayerLogger(PlayerIndex index) :
	index(index)
	{
		pan::detail::Observer<PlayerLogger, pan::PlayerUpdateNotification> playerObserver(*this, &PlayerLogger::handlePlayerUpdateNotification);
		pan::detail::NotificationCenter::defaultCenter().addObserver(playerObserver);
	}

	PlayerLogger::PlayerLogger(PlayerIndex index, const std::string& filename, std::unique_ptr<LoggerBase> logger) :
	LoggerBase(filename, std::move(logger)), index(index)
	{
		pan::detail::Observer<PlayerLogger, pan::PlayerUpdateNotification> playerObserver(*this, &PlayerLogger::handlePlayerUpdateNotification);
		pan::detail::NotificationCenter::defaultCenter().addObserver(playerObserver);
	}

	PlayerLogger::~PlayerLogger(){

		pan::detail::NotificationCenter::defaultCenter().removeObserver(pan::detail::Observer<PlayerLogger, pan::PlayerUpdateNotification>(*this, &PlayerLogger::handlePlayerUpdateNotification));
	}

	void PlayerLogger::handlePlayerUpdateNotification(std::shared_ptr<PlayerUpdateNotification> not){
		if (!stream || !stream.get()) return;
		if (not == nullptr) return;
		const auto& p = not->player;
		if (p.index != index) return;
		*stream << getDateString() << ": PLAYER UPDATE" << std::endl;
		*stream << p.description() << std::endl << std::endl;
	}
}