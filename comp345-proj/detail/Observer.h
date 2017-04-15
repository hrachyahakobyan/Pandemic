#pragma once
#include "ObserverBase.h"
#include "Notification.h"

namespace pan{
	namespace detail{
		/**
		*	@brief Class to represent the Observer entity.
		*	@param C the Client class, i.e. the class wishing to be notified
		*	@param N the Notification type
		*	@author Hrachya Hakobyan
		*/
		template <class C, class N>
		class Observer : public ObserverBase
		{
		public:
			typedef void (C::*Callback)(std::shared_ptr<N>);

			Observer(C& client, Callback method) :
				client(&client),
				callback(method)
			{
			}

			Observer(const Observer& observer) :
				ObserverBase(observer),
				client(observer.client),
				callback(observer.callback)
			{
			}

			~Observer()
			{
			}

			Observer& operator = (const Observer& observer)
			{
				if (&observer != this){
					client = observer.client;
					callback = observer.callback;
				}
				return *this;
			}

			/**
			*	Notify the observer with a notification
			*	@param notBase a shared pointer to notification object
			*/
			void notify(std::shared_ptr<Notification> notBase) const
			{
				if (client){
					std::shared_ptr<N> notDerived = std::dynamic_pointer_cast<N>(notBase);
					if (notDerived){
						(client->*callback)(notDerived);
					}
				}
			}

			/**
			*	Compares two observers for equality
			*	@param base the observer object to compare with
			*	@return true if two objects are equal. The objects are equal
			*	if they are of the same type and they refer to the same client
			*/
			bool equals(const ObserverBase& base) const
			{
				const Observer* pObs = dynamic_cast<const Observer*>(&base);
				return pObs && pObs->client == client && pObs->callback == callback;
			}

			/**
			*	Check if the object accepts notification of the specified type
			*	@param notification a shared pointer to Notification class/subclass
			*	@return true if this observer object accepts the specified notification
			*/
			bool accepts(std::shared_ptr<Notification> notification) const
			{
				return std::dynamic_pointer_cast<N>(notification) != nullptr;
			}

			ObserverBase* clone() const
			{
				return new Observer(*this);
			}

			void disable()
			{
				client = 0;
			}

		private:
			Observer();
			C*       client;
			Callback callback;
		};
	}
}

