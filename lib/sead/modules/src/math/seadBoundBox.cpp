#include <limits>

#include <math/seadBoundBox.h>

namespace sead
{
template <typename T>
static BoundBox2<T> getUndefined2()
{
    Vector2<T> min(std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
    Vector2<T> max(std::numeric_limits<T>::min(), std::numeric_limits<T>::min());
    return {min, max};
}

template <typename T>
static BoundBox3<T> getUndefined3()
{
    Vector3<T> min(std::numeric_limits<T>::max(), std::numeric_limits<T>::max(),
                   std::numeric_limits<T>::max());
    Vector3<T> max(std::numeric_limits<T>::min(), std::numeric_limits<T>::min(),
                   std::numeric_limits<T>::min());
    return {min, max};
}

template <>
const BoundBox2<s32> BoundBox2<s32>::cUndefined = getUndefined2<s32>();
template <>
const BoundBox2<u32> BoundBox2<u32>::cUndefined = getUndefined2<u32>();
template <>
const BoundBox2<s64> BoundBox2<s64>::cUndefined = getUndefined2<s64>();
template <>
const BoundBox2<u64> BoundBox2<u64>::cUndefined = getUndefined2<u64>();
template <>
const BoundBox2<f32> BoundBox2<f32>::cUndefined = getUndefined2<f32>();
template <>
const BoundBox2<f64> BoundBox2<f64>::cUndefined = getUndefined2<f64>();

template <>
const BoundBox3<s32> BoundBox3<s32>::cUndefined = getUndefined3<s32>();
template <>
const BoundBox3<u32> BoundBox3<u32>::cUndefined = getUndefined3<u32>();
template <>
const BoundBox3<s64> BoundBox3<s64>::cUndefined = getUndefined3<s64>();
template <>
const BoundBox3<u64> BoundBox3<u64>::cUndefined = getUndefined3<u64>();
template <>
const BoundBox3<f32> BoundBox3<f32>::cUndefined = getUndefined3<f32>();
template <>
const BoundBox3<f64> BoundBox3<f64>::cUndefined = getUndefined3<f64>();
}  // namespace sead
