#pragma once
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
	void selectCard(int cardIndex);
	bool isReady() const { return action != nullptr && next == 0; }
	const pan::ActionBase& getAction() const { return *action; }
private:
	enum SelectionState{
		Player, City, Card, Disease
	};
	std::map<pan::ActionType, std::vector<SelectionState>> actionStatesMap;
	std::size_t next;
	std::shared_ptr<pan::ActionBase> action;

};

