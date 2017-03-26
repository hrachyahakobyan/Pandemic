#pragma once

namespace pan{
	namespace detail{
		class Notification;
		class ObserverBase
		{
		public:
			virtual ~ObserverBase();
			virtual ObserverBase* clone() const = 0;
			virtual void disable() = 0;
			virtual bool equals(const ObserverBase&) const = 0;
			virtual void notify(std::shared_ptr<Notification> notBase) const = 0;
		protected:
			ObserverBase();
			ObserverBase(const ObserverBase&);
			ObserverBase& operator=(const ObserverBase&);
		};
	}
}

