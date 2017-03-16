#pragma once
#include "ActionHandler.h"

namespace pan{
	/**
	*	@brief Top level abstraction of the Action entity.
	*	Store the Command in the Command pattern. All actions that modify the state
	*	of the game, are encapsulated as subclasses of ActionBase.
	*	@author Hrachya Hakobyan
	*/
	class ActionBase{
	public:
		ActionBase(){}
		virtual ~ActionBase(){};
		virtual bool validate(const ActionHandler& h) const = 0;
		virtual bool execute(ActionHandler& h) const = 0;
		virtual ActionBase* clone() const = 0;
	};

	/**
	*	@brief A class containing the implementation of abstract methods of ActionBase.
	*	Subclasses may modify the methods for custom implementation, however it is not needed.
	*	@author Hrachya Hakobyan
	*/
	template<typename Derived, typename Base>
	class ActionImpl : public Base{
	public:
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


