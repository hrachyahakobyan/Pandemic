#include "stdafx.h"
#include "ActionLogger.h"
#include "detail\NotificationCenter.h"

namespace pan{
	ActionLogger::ActionLogger(const std::set<ActionType>& types) :
	types(types)
	{
		pan::detail::Observer<ActionLogger, pan::ActionNotification> playerObserver(*this, &ActionLogger::handleActionNotification);
		pan::detail::NotificationCenter::defaultCenter().addObserver(playerObserver);
	}

	ActionLogger::ActionLogger(const std::set<ActionType>& types, const std::string& filename, std::unique_ptr<LoggerBase> logger) :
		LoggerBase(filename, std::move(logger)), types(types)
	{
		pan::detail::Observer<ActionLogger, pan::ActionNotification> playerObserver(*this, &ActionLogger::handleActionNotification);
		pan::detail::NotificationCenter::defaultCenter().addObserver(playerObserver);
	}

	ActionLogger::~ActionLogger(){
		pan::detail::NotificationCenter::defaultCenter().removeObserver(pan::detail::Observer<ActionLogger, pan::ActionNotification>(*this, &ActionLogger::handleActionNotification));
	}

	void ActionLogger::handleActionNotification(std::shared_ptr<ActionNotification> not){
		if (!stream || !stream.get()) return;
		if (not == nullptr) return;
		auto action = not->action;
		if (types.find(action->getActionType()) == types.end())
			return;
		*stream << getDateString() << "\n-------ACTION UPDATE-------" << std::endl;
		*stream << action->description() << std::endl << std::endl;
		if (stream.use_count() != 1)
			stream->flush();
	}
}