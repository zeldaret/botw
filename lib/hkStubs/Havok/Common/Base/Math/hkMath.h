#pragma once

#include <Havok/Common/Base/Types/hkBaseTypes.h>

class hkVector4f;
using hkVector4fParameter = const hkVector4f&;
class hkVector4fComparison;
using hkVector4fComparisonParameter = const hkVector4fComparison&;

#include <Havok/Common/Base/Math/Vector/hkVector4.h>
#include <Havok/Common/Base/Math/Vector/hkVector4Comparison.h>

using hkVector4 = hkVector4f;
using hkVector4Parameter = const hkVector4f&;
using hkVector4Comparison = hkVector4fComparison;
using hkVector4ComparisonParameter = hkVector4fComparisonParameter;
