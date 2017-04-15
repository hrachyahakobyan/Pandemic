#include "stdafx.h"
#include "GlobalLogger.h"
#include "detail\NotificationCenter.h"

namespace pan{
	GlobalLogger::GlobalLogger(const std::string& filename, std::unique_ptr<LoggerBase> logger) :
	LoggerBase(filename, std::move(logger))
	{
		pan::detail::Observer<GlobalLogger, pan::CityUpdateNotification> cityObserver(*this, &GlobalLogger::handleCityUpdateNotification);
		pan::detail::Observer<GlobalLogger, pan::DeckDataUpdateNotification> deckObserver(*this, &GlobalLogger::handleDeckDataUpdateNotification);
		pan::detail::Observer<GlobalLogger, pan::GameDataUpdateNotification> gameObserver(*this, &GlobalLogger::handleGameDataUpdateNotification);
		pan::detail::Observer<GlobalLogger, pan::PlayerDataUpdateNotification> playersObserver(*this, &GlobalLogger::handlePlayerDataUpdateNotification);
		pan::detail::Observer<GlobalLogger, pan::PlayerUpdateNotification> playerObserver(*this, &GlobalLogger::handlePlayerUpdateNotification);
		pan::detail::Observer<GlobalLogger, pan::ActionNotification> actionObserver(*this, &GlobalLogger::handleActionNotification);
		pan::detail::NotificationCenter::defaultCenter().addObserver(cityObserver);
		pan::detail::NotificationCenter::defaultCenter().addObserver(deckObserver);
		pan::detail::NotificationCenter::defaultCenter().addObserver(gameObserver);
		pan::detail::NotificationCenter::defaultCenter().addObserver(playersObserver);
		pan::detail::NotificationCenter::defaultCenter().addObserver(actionObserver);
	}

	GlobalLogger::~GlobalLogger(){
		pan::detail::NotificationCenter::defaultCenter().removeObserver(pan::detail::Observer<GlobalLogger, pan::CityUpdateNotification>(*this, &GlobalLogger::handleCityUpdateNotification));
		pan::detail::NotificationCenter::defaultCenter().removeObserver(pan::detail::Observer<GlobalLogger, pan::DeckDataUpdateNotification>(*this, &GlobalLogger::handleDeckDataUpdateNotification));
		pan::detail::NotificationCenter::defaultCenter().removeObserver(pan::detail::Observer<GlobalLogger, pan::GameDataUpdateNotification>(*this, &GlobalLogger::handleGameDataUpdateNotification));
		pan::detail::NotificationCenter::defaultCenter().removeObserver(pan::detail::Observer<GlobalLogger, pan::PlayerDataUpdateNotification>(*this, &GlobalLogger::handlePlayerDataUpdateNotification));
		pan::detail::NotificationCenter::defaultCenter().removeObserver(pan::detail::Observer<GlobalLogger, pan::PlayerUpdateNotification>(*this, &GlobalLogger::handlePlayerUpdateNotification));
		pan::detail::NotificationCenter::defaultCenter().removeObserver(pan::detail::Observer<GlobalLogger, pan::ActionNotification>(*this, &GlobalLogger::handleActionNotification));
	}

	void GlobalLogger::handleCityUpdateNotification(std::shared_ptr<pan::CityUpdateNotification> n)
	{
		if (!stream || !stream.get()) return;
		*stream <<  getDateString() << "\n------CITY UPDATE------" << std::endl;
		*stream << n->city.description() << std::endl << std::endl;
		if (stream.use_count() != 1)
			stream->flush();
	}

	void GlobalLogger::handleGameDataUpdateNotification(std::shared_ptr<pan::GameDataUpdateNotification> n)
	{
		if (!stream || !stream.get()) return;
		*stream << getDateString() << "\n------GAME DATA UPDATE------" << std::endl;
		*stream << n->data.description() << std::endl << std::endl;
		if (stream.use_count() != 1)
			stream->flush();
	}

	void GlobalLogger::handleDeckDataUpdateNotification(std::shared_ptr<pan::DeckDataUpdateNotification> deck)
	{
		if (!stream || !stream.get()) return;
		*stream << getDateString() << "\n-------DECK DATA UPDATE-------" << std::endl;
		*stream << deck->data.description() << std::endl << std::endl;
		if (stream.use_count() != 1)
			stream->flush();
	}

	void GlobalLogger::handlePlayerDataUpdateNotification(std::shared_ptr<pan::PlayerDataUpdateNotification> not)
	{
		if (!stream || !stream.get()) return;
		*stream << getDateString() << "\n------PLAYER DATA UPDATE------" << std::endl;
		*stream << not->data.description() << std::endl << std::endl;
		if (stream.use_count() != 1)
			stream->flush();
	}

	void GlobalLogger::handlePlayerUpdateNotification(std::shared_ptr<pan::PlayerUpdateNotification> n)
	{
		if (!stream || !stream.get()) return;
		*stream << getDateString() << "\n------PLAYER UPDATE------" << std::endl;
		*stream << n->player.description() << std::endl << std::endl;
		if (stream.use_count() != 1)
			stream->flush();
	}

	void GlobalLogger::handleActionNotification(std::shared_ptr<ActionNotification> not)
	{
		if (!stream || !stream.get()) return;
		*stream << getDateString() << "\n------ACTION UPDATE------" << std::endl;
		*stream << not->action->description() << std::endl << std::endl;
		if (stream.use_count() != 1)
			stream->flush();
	}
}

