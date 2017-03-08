// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define _TEST_MEMLEAK 0

#ifdef _DEBUG
#include <gtest\gtest.h>

#if _TEST_MEMLEAK
#include <vld.h>
#endif

#endif

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include <fstream>
#include <memory>
#include <algorithm>
#include <iterator>
#include <boost/config/user.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>
#include <boost\serialization\export.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/map.hpp>
#include <boost/graph/adj_list_serialize.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "common.h"

// TODO: reference additional headers your program requires here
