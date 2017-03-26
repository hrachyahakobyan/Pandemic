#include "stdafx.h"
#include "NotificationCenter.h"

namespace pan{
	namespace detail{
		NotificationCenter::NotificationCenter()
		{
		}

		NotificationCenter::~NotificationCenter()
		{
		}

		void NotificationCenter::addObserver(const ObserverBase& observer)
		{
			observers.push_back(ObserverBasePtr(observer.clone()));
		}

		void NotificationCenter::removeObserver(const ObserverBase& observer)
		{
			for (ObserverList::iterator it = observers.begin(); it != observers.end(); ++it){
				if (observer.equals(**it))	{
					(*it)->disable();
					observers.erase(it);
					return;
				}
			}
		}

		bool NotificationCenter::hasObserver(const ObserverBase& observer) const
		{
			for (ObserverList::const_iterator it = observers.begin(); it != observers.end(); ++it)
				if (observer.equals(**it))
					return true;
			return false;
		}

		void NotificationCenter::postNotification(std::shared_ptr<Notification> notPtr) const
		{
			if (notPtr == nullptr)
				return;
			for (ObserverList::const_iterator it = observers.begin(); it != observers.end(); ++it){
				(*it)->notify(notPtr);
			}
		}

		bool NotificationCenter::hasObservers() const
		{
			return !observers.empty();
		}

		std::size_t NotificationCenter::countObservers() const
		{
			return observers.size();
		}

		NotificationCenter& NotificationCenter::defaultCenter()
		{
			static NotificationCenter center;
			return center;
		}
	}
}