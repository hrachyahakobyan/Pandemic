#pragma once
#include "LoggerBase.h"
#include "Notifications.h"

namespace pan{
	class GlobalLogger : public LoggerBase
	{
	public:
		GlobalLogger (const std::string& filename, std::unique_ptr<LoggerBase> logger = nullptr);
		virtual ~GlobalLogger();
		GlobalLogger(const GlobalLogger&) = delete;
		GlobalLogger& operator=(const GlobalLogger&) = delete;
		void handleActionNotification(std::shared_ptr<ActionNotification> not);
		void handleCityUpdateNotification(std::shared_ptr<pan::CityUpdateNotification>);
		void handleGameDataUpdateNotification(std::shared_ptr<pan::GameDataUpdateNotification>);
		void handleDeckDataUpdateNotification(std::shared_ptr<pan::DeckDataUpdateNotification>);
		void handlePlayerDataUpdateNotification(std::shared_ptr<pan::PlayerDataUpdateNotification>);
		void handlePlayerUpdateNotification(std::shared_ptr<pan::PlayerUpdateNotification>);
	};
}