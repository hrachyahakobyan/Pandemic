#pragma once
#include "ActionHandler.h"

namespace pan{
	enum class ActionType{
		Move = 0, CharterFlight, DirectFlight, ShuttleFlight,
		BuildStation, TreatDisease, ShareKnowledge, DiscoverCure, Draw, Discard,
		Infect, Outbreak, Epidemic, GovGrant, Airlift
	};

	static const std::map<ActionType, std::string> ActionTypeDescriptions{
		{ ActionType::BuildStation, "Build Research Station" },
		{ ActionType::CharterFlight, "Charter Flight" },
		{ ActionType::DirectFlight, "Direct Flight" },
		{ ActionType::Discard, "Discard cards" },
		{ ActionType::DiscoverCure, "Discover cure" },
		{ ActionType::Draw, "Draw cards" },
		{ ActionType::Epidemic, "Epidemic" },
		{ ActionType::Infect, "Infect" },
		{ ActionType::Move, "Drive/Ferry" },
		{ ActionType::Outbreak, "Outbreak" },
		{ActionType::ShareKnowledge, "Share Knowledge"},
		{ActionType::ShuttleFlight, "Shuttle Flight"},
		{ ActionType::TreatDisease, "Treat disease" },
		{ ActionType::GovGrant, "Government Grant" },
		{ ActionType::Airlift, "Airlift" }
	};

	bool isRegular(ActionType type);
	bool isEvent(ActionType type);
	/**
	*	@brief Top level abstraction of the Action entity.
	*	Store the Command in the Command pattern. All actions that modify the state
	*	of the game, are encapsulated as subclasses of ActionBase.
	*	@author Hrachya Hakobyan
	*/
	class ActionBase{
	public:
		ActionBase(ActionType type) : type(type) {}
		virtual ~ActionBase(){};
		virtual bool validate(const ActionHandler& h) const = 0;
		virtual bool execute(ActionHandler& h) const = 0;
		virtual ActionBase* clone() const = 0;
		ActionType getActionType() const { return type; }
		bool isRegularAction() const;
		virtual std::string description() const;
	protected:
		ActionType type;
	};

	/**
	*	@brief A class containing the implementation of abstract methods of ActionBase.
	*	Subclasses may modify the methods for custom implementation, however it is not needed.
	*	@author Hrachya Hakobyan
	*/
	template<typename Derived, typename Base>
	class ActionImpl : public Base{
	public:
		ActionImpl(ActionType type) : Base(type){}
		virtual ~ActionImpl(){};
		virtual bool validate(const ActionHandler& h) const {
			return h.validate<Derived>(static_cast<const Derived&>(*this));
		}

		virtual bool execute(ActionHandler& h) const {
			return h.execute<Derived>(static_cast<const Derived&>(*this));
		}
		virtual Base* clone() const
		{
			return new Derived(static_cast<Derived const &>(*this));
		}
	};
}


