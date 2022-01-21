#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkMotionState;

namespace hkSweptTransformUtil {

void freezeMotionState(hkSimdFloat32Parameter time, hkMotionState& motionState);

}  // namespace hkSweptTransformUtil
