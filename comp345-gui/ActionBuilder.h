#pragma once
/**
*	@brief The class translates user actions to Action objects to apply to the Game
*	@author Hrachya Hakobyan
*/
class ActionBuilder
{
public:
	ActionBuilder();
	~ActionBuilder();
	void reset();
	void selectAction(pan::ActionType type);
	void selectCity(pan::CityIndex index);
	void selectPlayer(pan::PlayerIndex player);
	void selectDisease(pan::DiseaseType type);
	void selectCard(int index, const pan::CardBase& card);
	void setActivePlayer(pan::PlayerIndex index);
	bool isReady() const { return action != nullptr && next == 0; }
	const pan::ActionBase& getAction() const { return *action; }
private:
	enum SelectionState{
		Player, City, Card, Disease
	};
	std::map<pan::ActionType, std::vector<SelectionState>> actionStatesMap;
	std::size_t next;
	pan::PlayerIndex activePlayer;
	std::shared_ptr<pan::ActionBase> action;
};

