#pragma once
#include "Observer.h"
#include "Notification.h"

namespace pan{
	namespace detail{
		class NotificationCenter
		{
		public:
			NotificationCenter();
			~NotificationCenter();
		
			void addObserver(const ObserverBase& observer);
			void removeObserver(const ObserverBase& observer);
			
			bool hasObserver(const ObserverBase& observer) const;
	
			void postNotification(std::shared_ptr<Notification> not) const;
			bool hasObservers() const;
			std::size_t countObservers() const;
			static NotificationCenter& defaultCenter();

		private:
			typedef std::shared_ptr<ObserverBase> ObserverBasePtr;
			typedef std::vector<ObserverBasePtr> ObserverList;

			ObserverList observers;
		};
	}
}

