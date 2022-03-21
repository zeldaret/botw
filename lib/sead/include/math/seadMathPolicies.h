#pragma once

#include <math/seadMathBase.h>

namespace sead
{
template <typename T>
class Policies
{
public:
    using Vec2Base = BaseVec2<T>;
    using Vec3Base = BaseVec3<T>;
    using Vec4Base = BaseVec4<T>;
    using QuatBase = BaseQuat<T>;
    using Mtx22Base = BaseMtx22<T>;
    using Mtx33Base = BaseMtx33<T>;
    using Mtx34Base = BaseMtx34<T>;
    using Mtx44Base = BaseMtx44<T>;
};

}  // namespace sead
