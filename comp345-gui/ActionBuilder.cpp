#include "stdafx.h"
#include "ActionBuilder.h"


ActionBuilder::ActionBuilder() :
next(0)
{
	using pan::ActionType;
	actionStatesMap[ActionType::Discard] = std::vector<SelectionState>{Player, Card};
	actionStatesMap[ActionType::Move] = std::vector<SelectionState>{Player, City};
	actionStatesMap[ActionType::DirectFlight] = std::vector<SelectionState>{Player, City};
	actionStatesMap[ActionType::CharterFlight] = std::vector<SelectionState>{Player, City};
	actionStatesMap[ActionType::BuildStation] = std::vector<SelectionState>{Player};
	actionStatesMap[ActionType::TreatDisease] = std::vector<SelectionState>{Player, Disease};
	actionStatesMap[ActionType::ShuttleFlight] = std::vector<SelectionState>{Player, City};
	actionStatesMap[ActionType::ShareKnowledge] = std::vector<SelectionState>{Player, Card, Player};
	actionStatesMap[ActionType::Infect] = std::vector<SelectionState>{Player};
	actionStatesMap[ActionType::Draw] = std::vector<SelectionState>{Player};
	actionStatesMap[ActionType::DiscoverCure] = std::vector<SelectionState>{Player, Disease};
}


ActionBuilder::~ActionBuilder()
{
}

void ActionBuilder::reset()
{
	action.reset();
	next = 0;
}

void ActionBuilder::selectAction(pan::ActionType type)
{
	reset();
	using namespace pan;
	if (type == ActionType::BuildStation)
		action.reset(new BuildResearchStation());
	if (type == ActionType::Move)
		action.reset(new Move());
	if (type == ActionType::CharterFlight)
		action.reset(new CharterFlight());
	if (type == ActionType::Discard)
		action.reset(new DiscardCard());
	if (type == ActionType::DirectFlight)
		action.reset(new DirectFlight());
	if (type == ActionType::TreatDisease)
		action.reset(new TreatDisease());
	if (type == ActionType::ShuttleFlight)
		action.reset(new ShuttleFlight());
	if (type == ActionType::ShareKnowledge)
		action.reset(new ShareKnowledge());
	if (type == ActionType::Infect)
		action.reset(new PlayerInfect());
	if (type == ActionType::Draw)
		action.reset(new DrawPlayerCards());
	if (type == ActionType::DiscoverCure)
		action.reset(new DiscoverCure());
}

void ActionBuilder::selectCity(pan::CityIndex index)
{
	using namespace pan;
	if (action == nullptr) return;
	ActionType t = action->getActionType();
	if (!(t == ActionType::DirectFlight || t == ActionType::CharterFlight || t == ActionType::ShuttleFlight || t == ActionType::Move)) return;
	if (next != 1) return;
	if (t == ActionType::DirectFlight)
		static_cast<DirectFlight&>(*action).targetCity = index;
	if (t == ActionType::CharterFlight)
		static_cast<CharterFlight&>(*action).targetCity = index;
	if (t == ActionType::ShuttleFlight)
		static_cast<ShuttleFlight&>(*action).targetCity = index;
	if (t == ActionType::Move)
		static_cast<Move&>(*action).targetCity = index;
	next = 0;
}

void ActionBuilder::selectPlayer(pan::PlayerIndex player)
{
	using namespace pan;
	if (action == nullptr) return;
	ActionType type = action->getActionType();
	if (type == ActionType::ShareKnowledge){
		if (next == 0){
			static_cast<ShareKnowledge&>(*action).player = player;
		}
		else if (next == 2){
			static_cast<ShareKnowledge&>(*action).target = player;
		}
		next = (next + 1) % actionStatesMap[type].size();
		return;
	}
	if (next != 0) return;
	if (type == ActionType::BuildStation)
		static_cast<BuildResearchStation&>(*action).player = player;
	else if (type == ActionType::CharterFlight)
		static_cast<CharterFlight&>(*action).player = player;
	else if (type == ActionType::Discard)
		static_cast<DiscardCard&>(*action).player = player;
	else if (type == ActionType::DirectFlight)
		static_cast<DirectFlight&>(*action).player = player;
	else if (type == ActionType::TreatDisease)
		static_cast<TreatDisease&>(*action).player = player;
	else if (type == ActionType::ShuttleFlight)
		static_cast<ShuttleFlight&>(*action).player = player;
	else if (type == ActionType::Infect)
		static_cast<PlayerInfect&>(*action).player = player;
	else if (type == ActionType::Draw)
		static_cast<DrawPlayerCards&>(*action).player = player;
	else if (type == ActionType::DiscoverCure)
		static_cast<DiscoverCure&>(*action).player = player;
	else if (type == ActionType::Move)
		static_cast<Move&>(*action).player = player;
	next = (next + 1) % actionStatesMap[type].size();
}

void ActionBuilder::selectDisease(pan::DiseaseType d)
{
	using namespace pan;
	if (action == nullptr) return;
	ActionType type = action->getActionType();
	if (type != ActionType::TreatDisease && type != ActionType::DiscoverCure) return;
	if (next != 1) return;
	if (type == ActionType::TreatDisease)
		static_cast<TreatDisease&>(*action).diseaseType = d;
	else
		static_cast<DiscoverCure&>(*action).diseaseType = d;
	next = (next + 1) % actionStatesMap[type].size();
}

void ActionBuilder::selectCard(int cardIndex)
{
	using namespace pan;
	if (action == nullptr) return;
	ActionType type = action->getActionType();
	if (type == ActionType::Discard){
		if (next != 1) return;
		static_cast<DiscardCard&>(*action).index = cardIndex;
		next = (next + 1) % actionStatesMap[type].size();
	}
	else if (type == ActionType::ShareKnowledge){
		if (next != 1) return;
		static_cast<ShareKnowledge&>(*action).cardIndex = cardIndex;
		next = (next + 1) % actionStatesMap[type].size();
	}
}
