#include "stdafx.h"
#include "Epidemic.h"


namespace pan{
	ActionBase* Epidemic::clone() const
	{
		return new Epidemic(*this);
	}
}
