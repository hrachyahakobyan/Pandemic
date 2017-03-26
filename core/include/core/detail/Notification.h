#pragma once

namespace pan{
	namespace detail{
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

