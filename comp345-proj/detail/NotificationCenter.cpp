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
			std::lock_guard<std::mutex> lock(mutex);
			observers.push_back(ObserverBasePtr(observer.clone()));
		}

		void NotificationCenter::removeObserver(const ObserverBase& observer)
		{
			std::lock_guard<std::mutex> lock(mutex);
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
			std::lock_guard<std::mutex> lock(mutex);
			for (ObserverList::const_iterator it = observers.begin(); it != observers.end(); ++it)
				if (observer.equals(**it))
					return true;
			return false;
		}

		void NotificationCenter::postNotification(std::shared_ptr<Notification> notPtr) const
		{
			std::lock_guard<std::mutex> lock(mutex);
			if (notPtr == nullptr)
				return;
			for (ObserverList::const_iterator it = observers.begin(); it != observers.end(); ++it){
				(*it)->notify(notPtr);
			}
		}

		bool NotificationCenter::hasObservers() const
		{
			std::lock_guard<std::mutex> lock(mutex);
			return !observers.empty();
		}

		std::size_t NotificationCenter::countObservers() const
		{
			std::lock_guard<std::mutex> lock(mutex);
			return observers.size();
		}

		NotificationCenter& NotificationCenter::defaultCenter()
		{
			static NotificationCenter center;
			return center;
		}
	}
}