#pragma once

#ifdef __aarch64__
#include <arm_neon.h>
#define HK_VECTOR4F_AARCH64_NEON
#else
#include <cmath>
#endif

// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
inline hkVector4f::hkVector4f(hkFloat32 x, hkFloat32 y, hkFloat32 z, hkFloat32 w) {
    set(x, y, z, w);
}

inline hkVector4f::hkVector4f(const hkVector4f& other) {
    v = other.v;
}

inline hkVector4f& hkVector4f::operator=(hkVector4fParameter other) {
    v = other.v;
    return *this;
}

inline void hkVector4f::set(hkFloat32 x, hkFloat32 y, hkFloat32 z, hkFloat32 w) {
#ifdef HK_VECTOR4F_AARCH64_NEON
    // Annoyingly, v = {x, y, z, w} and vcombine_f32({x, y}, {z, w}) lead to different codegen.
    // It is unclear why Havok decided to split the load in two parts.
    v = vcombine_f32(float32x2_t{x, y}, float32x2_t{z, w});
#else
    v = {x, y, z, w};
#endif
}

inline void hkVector4f::setXYZ(hkVector4fParameter xyz) {
#ifdef HK_VECTOR4F_AARCH64_NEON
    v = vsetq_lane_f32(vgetq_lane_f32(v, 3), xyz.v, 3);
#else
    auto newValue = xyz.v;
    newValue[3] = v[3];
    v = newValue;
#endif
}

inline void hkVector4f::setXYZ_W(hkVector4fParameter xyz, hkSimdFloat32Parameter w) {
#ifdef HK_VECTOR4F_AARCH64_NEON
    v = vsetq_lane_f32(w, xyz.v, 3);
#else
    auto newValue = xyz.v;
    newValue[3] = w;
    v = newValue;
#endif
}

inline void hkVector4f::setAll(hkReal x) {
    v = {x, x, x, x};
}

inline void hkVector4f::setAll(hkSimdFloat32Parameter x) {
    v = x.toQuad();
}

inline void hkVector4f::setZero() {
    setAll(0);
}

template <int I>
inline void hkVector4f::zeroComponent() {
    v[I] = 0;
}

inline void hkVector4f::zeroComponent(int i) {
    v[i] = 0;
}

inline void hkVector4f::add(hkVector4fParameter a) {
    setAdd(*this, a);
}

inline void hkVector4f::sub(hkVector4fParameter a) {
    setSub(*this, a);
}

inline void hkVector4f::mul(hkVector4fParameter a) {
    setMul(*this, a);
}

inline void hkVector4f::div(hkVector4fParameter a) {
    setDiv(*this, a);
}

inline void hkVector4f::setAdd(hkVector4fParameter a, hkVector4fParameter b) {
    v = a.v + b.v;
}

inline void hkVector4f::setSub(hkVector4fParameter a, hkVector4fParameter b) {
    v = a.v - b.v;
}

inline void hkVector4f::setMul(hkVector4fParameter a, hkVector4fParameter b) {
    v = a.v * b.v;
}

inline void hkVector4f::setDiv(hkVector4fParameter a, hkVector4fParameter b) {
    v = a.v / b.v;
}

inline void hkVector4f::add(hkSimdFloat32Parameter a) {
    setAdd(*this, a);
}

inline void hkVector4f::sub(hkSimdFloat32Parameter a) {
    setSub(*this, a);
}

inline void hkVector4f::mul(hkSimdFloat32Parameter a) {
    setMul(*this, a);
}

inline void hkVector4f::setMul(hkVector4fParameter a, hkSimdFloat32Parameter r) {
    v = a.v * r.toQuad();
}

inline void hkVector4f::setMul(hkSimdFloat32Parameter r, hkVector4fParameter a) {
    setMul(a, r);
}

inline void hkVector4f::setAdd(hkVector4fParameter a, hkSimdFloat32Parameter b) {
    v = a.v + b.toQuad();
}

inline void hkVector4f::setSub(hkVector4fParameter a, hkSimdFloat32Parameter b) {
    v = a.v - b.toQuad();
}

inline void hkVector4f::setReciprocal(hkVector4fParameter a) {
#ifdef HK_VECTOR4F_AARCH64_NEON
    auto result = vrecpeq_f32(a.v);
    result *= vrecpsq_f32(a.v, result);
    result *= vrecpsq_f32(a.v, result);
    v = result;
#else
    for (int i = 0; i < 4; ++i)
        v[i] = 1.0f / a[i];
#endif
}

inline void hkVector4f::setSqrt(hkVector4fParameter a) {
#ifdef HK_VECTOR4F_AARCH64_NEON
    v = vsqrtq_f32(a.v);
#else
    for (int i = 0; i < 4; ++i)
        v[i] = std::sqrt(a[i]);
#endif
}

inline void hkVector4f::setSqrtInverse(hkVector4fParameter a) {
#ifdef HK_VECTOR4F_AARCH64_NEON
    v = vrsqrteq_f32(a.v);
#else
    for (int i = 0; i < 4; ++i)
        v[i] = 1.0f / std::sqrt(a[i]);
#endif
}

inline void hkVector4f::addMul(hkVector4fParameter a, hkVector4fParameter b) {
    setAddMul(*this, a, b);
}

inline void hkVector4f::subMul(hkVector4fParameter a, hkVector4fParameter b) {
    setSubMul(*this, a, b);
}

inline void hkVector4f::setAddMul(hkVector4fParameter a, hkVector4fParameter b,
                                  hkVector4fParameter c) {
    v = a.v + b.v * c.v;
}

inline void hkVector4f::setSubMul(hkVector4fParameter a, hkVector4fParameter b,
                                  hkVector4fParameter c) {
    v = a.v - b.v * c.v;
}

inline void hkVector4f::addMul(hkVector4fParameter a, hkSimdFloat32Parameter r) {
    setAddMul(*this, a, r);
}

inline void hkVector4f::addMul(hkSimdFloat32Parameter r, hkVector4fParameter a) {
    addMul(a, r);
}

inline void hkVector4f::subMul(hkVector4fParameter a, hkSimdFloat32Parameter r) {
    setSubMul(*this, a, r);
}

inline void hkVector4f::subMul(hkSimdFloat32Parameter r, hkVector4fParameter a) {
    subMul(a, r);
}

inline void hkVector4f::setAddMul(hkVector4fParameter a, hkVector4fParameter b,
                                  hkSimdFloat32Parameter r) {
    v = a.v + r.toQuad() * b.v;
}

inline void hkVector4f::setSubMul(hkVector4fParameter a, hkVector4fParameter b,
                                  hkSimdFloat32Parameter r) {
    v = a.v - r.toQuad() * b.v;
}

inline void hkVector4f::setCross(hkVector4fParameter a, hkVector4fParameter b) {
    // 	z = a[0] * b[1] - b[0] * a[1]
    //	x = a[1] * b[2] - b[1] * a[2]
    //	y = a[2] * b[0] - b[2] * a[0]
    //      ----   ----   ----   ----
    //        1      2      3      4
#ifdef HK_VECTOR4F_AARCH64_NEON
    // Shuffle a and b to get the column vectors 2 and 4
    const auto a_yzwx = vextq_f32(a.v, a.v, 1);
    const auto b_yzwx = vextq_f32(b.v, b.v, 1);
    const auto a_yz = vget_low_f32(a_yzwx);
    const auto b_yz = vget_low_f32(b_yzwx);
    const auto a_wx = vget_high_f32(a_yzwx);
    const auto b_wx = vget_high_f32(b_yzwx);
    const auto a_xw = vrev64_f32(a_wx);
    const auto b_xw = vrev64_f32(b_wx);
    const auto a_yzxw = vcombine_f32(a_yz, a_xw);
    const auto b_yzxw = vcombine_f32(b_yz, b_xw);
    const auto cross = (a.v * b_yzxw) - (a_yzxw * b.v);
    // Shuffle `cross` back to the correct order (zxyw -> xyzw)
    const auto cross_yzwx = vextq_f32(cross, cross, 1);
    const auto c_xy = vget_low_f32(cross);
    const auto c_yz = vget_low_f32(cross_yzwx);
    v = vcombine_f32(c_yz, c_xy);
#else
    auto cross0 = a.v * __builtin_shufflevector(b.v, b.v, 1, 2, 0, 3);
    auto cross1 = b.v * __builtin_shufflevector(a.v, a.v, 1, 2, 0, 3);
    auto diff = cross0 - cross1;
    v = __builtin_shufflevector(diff, diff, 1, 2, 0, 3);
#endif
}

inline void hkVector4f::setInterpolate(hkVector4fParameter v0, hkVector4fParameter v1,
                                       hkSimdFloat32Parameter t) {
    // v = v0 + t * (v1 - v0)
    hkVector4f diff;
    diff.setSub(v1, v0);
    setAddMul(v0, diff, t);
}

inline hkVector4fComparison hkVector4f::less(hkVector4fParameter a) const {
    return hkVector4fComparison::convert(v < a.v);
}

inline hkVector4fComparison hkVector4f::lessEqual(hkVector4fParameter a) const {
    return hkVector4fComparison::convert(v <= a.v);
}

inline hkVector4fComparison hkVector4f::greater(hkVector4fParameter a) const {
    return hkVector4fComparison::convert(v > a.v);
}

inline hkVector4fComparison hkVector4f::greaterEqual(hkVector4fParameter a) const {
    return hkVector4fComparison::convert(v >= a.v);
}

inline hkVector4fComparison hkVector4f::equal(hkVector4fParameter a) const {
    return hkVector4fComparison::convert(v == a.v);
}

inline hkVector4fComparison hkVector4f::notEqual(hkVector4fParameter a) const {
    return hkVector4fComparison::convert(v != a.v);
}

inline hkVector4fComparison hkVector4f::lessZero() const {
    return hkVector4fComparison::convert(v < m128());
}

inline hkVector4fComparison hkVector4f::lessEqualZero() const {
    return hkVector4fComparison::convert(v <= m128());
}

inline hkVector4fComparison hkVector4f::greaterZero() const {
    return hkVector4fComparison::convert(v > m128());
}

inline hkVector4fComparison hkVector4f::greaterEqualZero() const {
    return hkVector4fComparison::convert(v >= m128());
}

inline hkVector4fComparison hkVector4f::equalZero() const {
    return hkVector4fComparison::convert(v == m128());
}

inline hkVector4fComparison hkVector4f::notEqualZero() const {
    return hkVector4fComparison::convert(v != m128());
}

template <int N>
inline hkBool32 hkVector4f::allEqual(hkVector4fParameter rhs,
                                     hkSimdFloat32Parameter epsilon) const {
    static_assert(1 <= N && N <= 4, "invalid N");

    if constexpr (N == 1) {
        hkSimdFloat32 t = getX() - rhs.getX();
        t.setAbs(t);
        return t <= epsilon;

    } else {
        hkVector4f diff;
        diff.setSub(*this, rhs);
        diff.setAbs(diff);
        hkVector4f epsilon_v;
        epsilon_v.setAll(epsilon);

        constexpr auto mask = static_cast<hkVector4fComparison::Mask>([] {
            int mask = 0;
            for (int i = 0; i < N; ++i)
                mask |= 1 << i;
            return mask;
        }());
        return diff.lessEqual(epsilon_v).allAreSet<mask>();
    }
}

inline void hkVector4f::setAbs(hkVector4fParameter a) {
#ifdef HK_VECTOR4F_AARCH64_NEON
    v = vabsq_f32(a.v);
#else
    for (int i = 0; i < 4; ++i)
        v[i] = std::abs(a[i]);
#endif
}

template <int N>
inline void hkVector4f::setNeg(hkVector4fParameter a) {
    static_assert(1 <= N && N <= 4, "invalid N");

#ifdef HK_VECTOR4F_AARCH64_NEON
    switch (N) {
    case 1: {
        auto xy = vget_low_f32(a.v);
        v = vsetq_lane_f32(vget_lane_f32(vneg_f32(xy), 0), a.v, 0);
        break;
    }
    case 2: {
        auto xy = vget_low_f32(a.v);
        auto zw = vget_high_f32(a.v);
        v = vcombine_f32(vneg_f32(xy), zw);
        break;
    }
    case 3: {
        auto zw = vget_high_f32(a.v);
        v = vnegq_f32(a.v);
        v = vsetq_lane_f32(vget_lane_f32(zw, 1), v, 3);
        break;
    }
    case 4:
        v = vnegq_f32(a.v);
        break;
    default:
        break;
    }
#else
    for (int i = 0; i < N; ++i)
        v[i] = -a[i];
#endif
}

inline void hkVector4f::setFlipSign(hkVector4fParameter a, hkVector4fComparisonParameter mask) {
    static constexpr m128u signbits = {0x80000000, 0x80000000, 0x80000000, 0x80000000};
    v = m128u(a.v) ^ (mask.m_mask & signbits);
}

inline void hkVector4f::setFlipSign(hkVector4fParameter a, hkVector4fParameter signs) {
    static constexpr m128u signbits = {0x80000000, 0x80000000, 0x80000000, 0x80000000};
    v = m128u(a.v) ^ (m128u(signs.v) & signbits);
}

inline void hkVector4f::setFlipSign(hkVector4fParameter a, hkSimdFloat32Parameter sign) {
    setFlipSign(a, hkVector4fComparison::convert(sign.toQuad()));
}

inline hkVector4fComparison hkVector4f::signBitSet() const {
    static constexpr m128u signbits = {0x80000000, 0x80000000, 0x80000000, 0x80000000};
    return hkVector4fComparison::convert((m128u(v) & signbits) != m128u());
}

inline hkVector4fComparison hkVector4f::signBitClear() const {
    static constexpr m128u signbits = {0x80000000, 0x80000000, 0x80000000, 0x80000000};
    return hkVector4fComparison::convert((m128u(v) & signbits) == m128u());
}

inline void hkVector4f::_setRotatedDir(const hkMatrix3f& a, hkVector4fParameter b) {
#ifdef HK_VECTOR4F_AARCH64_NEON
    const auto c0 = a.m_col0.v;
    const auto c1 = a.m_col1.v;
    const auto c2 = a.m_col2.v;
    auto col0 = vmulq_laneq_f32(c0, b.v, 0);
    auto col1 = vmulq_laneq_f32(c1, b.v, 1);
    auto col2 = vmulq_laneq_f32(c2, b.v, 2);
    v = col0 + col1 + col2;
#else
    setMul(a.m_col0, b[0]);
    addMul(a.m_col1, b[1]);
    addMul(a.m_col2, b[2]);
#endif
}

inline void hkVector4f::_setRotatedDir(hkQuaternionfParameter quat, hkVector4fParameter vec) {
    // Rodrigues' rotation formula

    const auto& u = quat.getImag();
    const hkSimdFloat32 s = quat.getRealPart();

    hkVector4f result;
    result.setMul(vec, s * s - hkSimdFloat32::getConstant<HK_QUADREAL_INV_2>());
    result.addMul(u, u.dot<3>(vec));

    hkVector4f cross;
    cross.setCross(u, vec);
    result.addMul(cross, s);

    setAdd(result, result);
}

inline void hkVector4f::_setRotatedInverseDir(hkQuaternionfParameter quat,
                                              hkVector4fParameter vec) {
    const auto& u = quat.getImag();
    const hkSimdFloat32 s = quat.getRealPart();

    hkVector4f result;
    result.setMul(vec, s * s - hkSimdFloat32::getConstant<HK_QUADREAL_INV_2>());
    result.addMul(u, u.dot<3>(vec));

    hkVector4f cross;
    cross.setCross(vec, u);
    result.addMul(cross, s);

    setAdd(result, result);
}

inline void hkVector4f::_setTransformedPos(const hkTransformf& a, hkVector4fParameter b) {
    hkVector4f t;
    t._setRotatedDir(a.getRotation(), b);
    setAdd(t, a.getTranslation());
}

#ifdef HK_VECTOR4F_AARCH64_NEON
template <int N>
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::dot(hkVector4fParameter a) const {
    if constexpr (N == 2) {
        float32x4_t x2 = v * a.v;
        float32x2_t low = vget_low_f32(x2);
        float32x2_t xy = vpadd_f32(low, low);
        return xy;
    } else if constexpr (N == 3 || N == 4) {
        float32x4_t x2 = v * a.v;
        float32x2_t low = vget_low_f32(x2);
        float32x2_t high = vget_high_f32(x2);
        if constexpr (N == 3)
            high = vset_lane_f32(0, high, 1);
        float32x2_t xy_zw = vpadd_f32(low, high);
        float32x2_t xyzw = vpadd_f32(xy_zw, xy_zw);
        return xyzw;
    } else {
        static_assert(2 <= N && N <= 4, "invalid N");
    }
}
#else
template <int N>
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::dot(hkVector4fParameter a) const {
    static_assert(2 <= N && N <= 4, "invalid N");
    float sum = 0.0f;
    for (int i = 0; i < N; ++i)
        sum += v[i] * a.v[i];
    return sum;
}
#endif

template <int N>
inline void hkVector4f::setDot(hkVector4fParameter a, hkVector4fParameter b) {
    setAll(a.dot<N>(b));
}

template <int N>
inline hkSimdFloat32 hkVector4f::length() const {
    return lengthSquared<N>().sqrt();
}

template <int N>
inline hkSimdFloat32 hkVector4f::lengthSquared() const {
    return dot<N>(*this);
}

template <int N>
inline hkSimdFloat32 hkVector4f::lengthInverse() const {
    const hkSimdFloat32 len = lengthSquared<N>();
    return len.sqrtInverse();
}

template <int N>
inline hkSimdFloat32 hkVector4f::lengthInverseUnsafe() const {
    const hkSimdFloat32 len = lengthSquared<N>();
    return len.sqrtInverseUnsafe();
}

template <int N>
inline void hkVector4f::normalize() {
    mul(lengthInverse<N>());
}

template <int N>
inline void hkVector4f::normalizeUnsafe() {
    mul(lengthInverseUnsafe<N>());
}

inline hkSimdFloat32 hkVector4f::dot4xyz1(hkVector4fParameter a) const {
#ifdef HK_VECTOR4F_AARCH64_NEON
    float32x4_t x2 = v * a.v;
    float32x2_t low = vget_low_f32(x2);
    float32x2_t high = vget_high_f32(x2);
    high = vset_lane_f32(vgetq_lane_f32(v, 3), high, 1);
    float32x2_t xy_zw = vpadd_f32(low, high);
    float32x2_t xyzw = vpadd_f32(xy_zw, xy_zw);
    return xyzw;
#else
    return (v[0] * a.v[0]) + (v[1] * a.v[1]) + (v[2] * a.v[2]) + v[3];
#endif
}

inline void hkVector4f::setInt24W(int value) {
    reinterpret_cast<hkInt32*>(&v)[3] = hkInt32(value) | 0x3f000000;
}

inline int hkVector4f::getInt24W() const {
    return reinterpret_cast<const hkInt32*>(&v)[3] & ~0x3f000000;
}

template <int Constant>
inline const hkVector4f& hkVector4f::getConstant() {
    return reinterpret_cast<const hkVector4f&>(g_vectorfConstants[Constant]);
}

template <int N>
inline void hkVector4f::load(const hkFloat32* in) {
    static_assert(1 <= N && N <= 4, "invalid N");
#ifdef HK_VECTOR4F_AARCH64_NEON
    switch (N) {
    case 1:
        v = vld1q_dup_f32(in);
        break;
    case 2: {
        auto xy = vld1_f32(in);
        v = vcombine_f32(xy, xy);
        break;
    }
    case 3: {
        auto xy = vld1_f32(in);
        auto zz = vld1_dup_f32(in + 2);
        v = vcombine_f32(xy, zz);
        break;
    }
    case 4:
        v = vld1q_f32(in);
        break;
    default:
        break;
    }
#else
    for (int i = 0; i < N; ++i)
        v[i] = in[i];
#endif
}

template <int N>
inline void hkVector4f::store(hkFloat32* out) const {
    static_assert(1 <= N && N <= 4, "invalid N");
#ifdef HK_VECTOR4F_AARCH64_NEON
    switch (N) {
    case 1:
        vst1q_lane_f32(out, v, 0);
        break;
    case 2:
        vst1_f32(out, vget_low_f32(v));
        break;
    case 3:
        vst1_f32(out, vget_low_f32(v));
        vst1q_lane_f32(out + 2, v, 2);
        break;
    case 4:
        vst1q_f32(out, v);
        break;
    default:
        break;
    }
#else
    for (int i = 0; i < N; ++i)
        out[i] = v[i];
#endif
}
