#pragma once
#include "detail\Factory.h"

namespace pan{
	namespace detail{
		class FactoryTest : public ::testing::Test
		{
		protected:
			class A;
			class D;
			typedef pan::detail::Factory<std::string, A, const D&> Factory;
			class D{};
			class A {
			public:
				A(){}
				A(const D& d) : d(d){
				}
				virtual ~A(){}
				virtual void foo(){
					std::cout << "A Foo" << std::endl;
				}
			protected:
				D d;
			};
			class B : public A{
			public:
				B(){}
				B(const D& d) : A(d){}
				virtual ~B(){}
				virtual void bFoo(){
					//std::cout << "B foo" << std::endl;
				}
			};
			class C : public B{
			public:
				C(const D& d) : B(d){}
			};
		};
	}
}

