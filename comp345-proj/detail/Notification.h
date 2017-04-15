#pragma once

namespace pan{
	namespace detail{
		/**
		*	@brief base class for all Notifications
		*	@author Hrachya Hakobyan
		*/
		class Notification
		{
		public:
			Notification();
			Notification(const Notification&);
			Notification& operator=(const Notification&);
			virtual ~Notification();
		};
	}
}

