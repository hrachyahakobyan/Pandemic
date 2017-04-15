#pragma once
#include "Observer.h"
#include "Notification.h"
#include <mutex>

namespace pan{
	namespace detail{
		/**
		*	@brief Handles the registration, deregistration and invokation of Notification objects
		*	to Observers.
		*	@author Hrachya Hakobyan
		*/
		class NotificationCenter
		{
		public:
			NotificationCenter();
			~NotificationCenter();
		
			/**
			*	Adds a new observer
			*	@param observer the observer object to add
			*/
			void addObserver(const ObserverBase& observer);
			/**
			*	Removes the specified observer if such exists
			*	@param observer the observer to remove
			*/
			void removeObserver(const ObserverBase& observer);
			/**
			*	Checks if a specified observer exists
			*	@param observer to check
			*	@return true if the specified observer is registered
			*/
			bool hasObserver(const ObserverBase& observer) const;
	
			/**
			*	Post a new notification
			*	@param not a shared pointer to a Notification object
			*/
			void postNotification(std::shared_ptr<Notification> not) const;
			/**
			*	Checks if there are any observers
			*	@return true if there is at least one registered observer
			*/
			bool hasObservers() const;
			/**
			*	Returns the number of registered observers
			*	@return the number of registered observers
			*/
			std::size_t countObservers() const;
			/**
			*	Get the default notification center object
			*	@return a reference to a singleton of NotificationCenter tyoe
			*/
			static NotificationCenter& defaultCenter();

		private:
			typedef std::shared_ptr<ObserverBase> ObserverBasePtr;
			typedef std::vector<ObserverBasePtr> ObserverList;
			ObserverList observers;
			mutable std::mutex mutex;
		};
	}
}

