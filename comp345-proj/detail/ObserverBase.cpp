#include "stdafx.h"
#include "ObserverBase.h"

namespace pan{
	namespace detail{
		ObserverBase::ObserverBase()
		{
		}

		ObserverBase::ObserverBase(const ObserverBase&)
		{
		}

		ObserverBase& ObserverBase::operator=(const ObserverBase&)
		{
			return *this;
		}

		ObserverBase::~ObserverBase()
		{
		}
	}
}