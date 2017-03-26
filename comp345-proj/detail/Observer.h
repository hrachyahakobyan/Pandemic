#pragma once
#include "ObserverBase.h"
#include "Notification.h"

namespace pan{
	namespace detail{
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

			void notify(std::shared_ptr<Notification> notBase) const
			{
				if (client){
					std::shared_ptr<N> notDerived = std::dynamic_pointer_cast<N>(notBase);
					if (notDerived){
						(client->*callback)(notDerived);
					}
				}
			}

			bool equals(const ObserverBase& base) const
			{
				const Observer* pObs = dynamic_cast<const Observer*>(&base);
				return pObs && pObs->client == client && pObs->callback == callback;
			}

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

