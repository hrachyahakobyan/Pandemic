#include "stdafx.h"
#include "NotificationCenterTest.h"
#include <core\detail\NotificationCenter.h>
#include <core\detail\Observer.h>

namespace pan{
	namespace detail{
		TEST_F(NotificationCenterTest, Test1){
			NotificationCenter center;
			ASSERT_EQ(center.countObservers(), 0);
			ASSERT_FALSE(center.hasObservers());

			ClientA aClient;
			Observer<ClientA, NotificationA> observer(aClient, &ClientA::handleANotification);
			ASSERT_TRUE(observer.equals(observer));
			center.addObserver(observer);
			ASSERT_TRUE(center.hasObservers());
			ASSERT_EQ(center.countObservers(), 1);
			ASSERT_TRUE(center.hasObserver(observer));

			center.postNotification(std::make_shared<NotificationA>());
			ASSERT_EQ(aClient.notificationAReceiveCounter, 1);
			ASSERT_EQ(aClient.notificationBReceiveCounter, 0);
			center.postNotification(std::make_shared<NotificationB>());
			ASSERT_EQ(aClient.notificationAReceiveCounter, 1);
			ASSERT_EQ(aClient.notificationBReceiveCounter, 0);

			Observer<ClientA, NotificationB> observer2(aClient, &ClientA::handleBNotification);
			center.addObserver(observer2);
			ASSERT_TRUE(center.hasObservers());
			ASSERT_EQ(center.countObservers(), 2);
			ASSERT_TRUE(center.hasObserver(observer2));

			center.postNotification(std::make_shared<NotificationB>());
			ASSERT_EQ(aClient.notificationAReceiveCounter, 1);
			ASSERT_EQ(aClient.notificationBReceiveCounter, 1);
			center.postNotification(std::make_shared<NotificationA>());
			ASSERT_EQ(aClient.notificationAReceiveCounter, 2);
			ASSERT_EQ(aClient.notificationBReceiveCounter, 1);

			center.removeObserver(observer2);
			ASSERT_TRUE(center.hasObservers());
			ASSERT_EQ(center.countObservers(), 1);
			ASSERT_FALSE(center.hasObserver(observer2));

			center.postNotification(std::make_shared<NotificationB>());
			ASSERT_EQ(aClient.notificationAReceiveCounter, 2);
			ASSERT_EQ(aClient.notificationBReceiveCounter, 1);

			center.postNotification(std::make_shared<NotificationA>());
			ASSERT_EQ(aClient.notificationAReceiveCounter, 3);
			ASSERT_EQ(aClient.notificationBReceiveCounter, 1);

			center.removeObserver(observer);
			ASSERT_FALSE(center.hasObservers());
			ASSERT_EQ(center.countObservers(), 0);
			ASSERT_FALSE(center.hasObserver(observer));

			center.postNotification(std::make_shared<NotificationB>());
			ASSERT_EQ(aClient.notificationAReceiveCounter, 3);
			ASSERT_EQ(aClient.notificationBReceiveCounter, 1);

			center.postNotification(std::make_shared<NotificationA>());
			ASSERT_EQ(aClient.notificationAReceiveCounter, 3);
			ASSERT_EQ(aClient.notificationBReceiveCounter, 1);
		}
	}
}
