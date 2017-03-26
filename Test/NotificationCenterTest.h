#pragma once
#include <core\detail\Notification.h>
#include <string>
#include <memory>

namespace pan{
	namespace detail{
		class NotificationCenterTest : public ::testing::Test
		{
		protected:
			class NotificationA : public Notification{
			public:
				std::string stringData;
				int intData;
			};

			class NotificationB : public Notification{
			public:
				double doubleData;
			};

			class ClientA{
			public:
				int notificationAReceiveCounter = 0;
				int notificationBReceiveCounter = 0;
				void handleANotification(std::shared_ptr<NotificationA> not){
					notificationAReceiveCounter++;
				}
				void handleBNotification(std::shared_ptr<NotificationB> not){
					notificationBReceiveCounter++;
				}
			};
		};
	}
}
