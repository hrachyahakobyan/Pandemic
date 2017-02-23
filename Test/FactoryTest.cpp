#include "stdafx.h"
#include "FactoryTest.h"

namespace pan{
	namespace detail{
		/**
		*	@brief tests the register functionality of the Factory
		*	@author Hrachya Hakobyan
		*/
		TEST_F(FactoryTest, registers){
			Factory fac;
			ASSERT_EQ(fac.mObjectCreator.size(), 0);
			const std::string aKey("A");
			const std::string bKey("B");
			const std::string cKey("C");
			fac.registerClass<A>(aKey);
			ASSERT_EQ(fac.mObjectCreator.size(), 1);
			fac.registerClass<A>(aKey);
			ASSERT_EQ(fac.mObjectCreator.size(), 1);
			fac.registerClass<B>(bKey);
			ASSERT_EQ(fac.mObjectCreator.size(), 2);
			fac.registerClass<C>(std::string(""));
			ASSERT_EQ(fac.mObjectCreator.size(), 3);
		}
		/**
		*	@brief tests the object construction functionality of the Factory
		*	@author Hrachya Hakobyan
		*/
		TEST_F(FactoryTest, constructs){
			Factory fac;
			const D d;
			const std::string aKey("A");
			const std::string bKey("B");
			// Not registered, must be NULL
			A* aNullptr = fac.createObject(aKey, d);
			ASSERT_TRUE(aNullptr == NULL);
			fac.registerClass<A>(aKey);
			A* aReal = fac.createObject(aKey, d);
			// Must not be null
			ASSERT_TRUE(aReal != NULL);
			ASSERT_TRUE(dynamic_cast<B*>(aReal) == NULL);
			// Registering for the same key does not change the object under the key
			fac.registerClass<B>(aKey);
			// Must be A
			A* stillA = fac.createObject(aKey, d);
			ASSERT_TRUE(dynamic_cast<B*>(stillA) == NULL);
			fac.registerClass<B>(bKey);
			// Must be really B
			A* aButB = fac.createObject(bKey, d);
			ASSERT_TRUE(aButB != NULL);
			B* bReal = dynamic_cast<B*>(aButB);
			ASSERT_TRUE(bReal != NULL);

			// Make sure we do not delete twice
			delete aReal;
			delete stillA;
			delete aButB;
		}
	}
}