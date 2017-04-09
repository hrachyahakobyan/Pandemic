#pragma once
#include "LoggerBase.h"
#include "Notifications.h"

namespace pan{
	class PlayerLogger : public LoggerBase
	{
	public:
		PlayerLogger(PlayerIndex index);
		PlayerLogger(PlayerIndex index, const std::string& filename, std::unique_ptr<LoggerBase> logger = nullptr);
		virtual ~PlayerLogger();
		PlayerLogger(const PlayerLogger&) = delete;
		PlayerLogger& operator=(const PlayerLogger&) = delete;

		void handlePlayerUpdateNotification(std::shared_ptr<PlayerUpdateNotification> not);
	private:
		PlayerIndex index;
	};
}
