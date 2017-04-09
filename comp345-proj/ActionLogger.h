#pragma once
#include "LoggerBase.h"
#include "Notifications.h"
#include "ActionBase.h"

namespace pan{
	class ActionLogger : public LoggerBase
	{
	public:
		ActionLogger(const std::set<ActionType>& types);
		ActionLogger(const std::set<ActionType>& types, const std::string& filename, std::unique_ptr<LoggerBase> logger = nullptr);
		virtual ~ActionLogger();
		ActionLogger(const ActionLogger&) = delete;
		ActionLogger& operator=(const ActionLogger&) = delete;
		void handleActionNotification(std::shared_ptr<ActionNotification> not);
	private:
		std::set<ActionType> types;
	};
}
