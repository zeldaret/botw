#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <math/seadMatrix.h>
#include <math/seadQuat.h>
#include <math/seadVector.h>

#ifdef __aarch64__
#include <arm_neon.h>
#endif

namespace ksys::phys {

inline void toVec3(sead::Vector3f* out, const hkVector4f& vec) {
    out->x = vec.getX();
    out->y = vec.getY();
    out->z = vec.getZ();
}

[[nodiscard]] inline sead::Vector3f toVec3(const hkVector4f& vec) {
    return {vec.getX(), vec.getY(), vec.getZ()};
}

inline void toHkVec4(hkVector4f* out, const sead::Vector3f& vec) {
    out->set(vec.x, vec.y, vec.z);
}

[[nodiscard]] inline hkVector4f toHkVec4(const sead::Vector3f& vec) {
    return {vec.x, vec.y, vec.z};
}

inline void toQuat(sead::Quatf* out, const hkQuaternionf& quat) {
    out->set(quat.m_vec.getW(), quat.m_vec.getX(), quat.m_vec.getY(), quat.m_vec.getZ());
}

[[nodiscard]] inline sead::Quatf toQuat(const hkQuaternionf& quat) {
    return {quat.m_vec.getW(), quat.m_vec.getX(), quat.m_vec.getY(), quat.m_vec.getZ()};
}

inline void toHkQuat(hkQuaternionf* out, const sead::Quatf& quat) {
    out->set(quat.x, quat.y, quat.x, quat.w);
}

[[nodiscard]] inline hkQuaternionf toHkQuat(const sead::Quatf& quat) {
    return {quat.x, quat.y, quat.x, quat.w};
}

inline void toMtx34(sead::Matrix34f* out, const hkTransformf& transform) {
    const hkRotationf& rotate = transform.getRotation();
    const hkVector4f& translate = transform.getTranslation();

    hkVector4f row0, row1, row2;

#ifdef __aarch64__
    // XXX: this leads to really poor codegen (compared to using getRows, which
    // is optimised into Neon zip/transpose instructions). Is Nintendo to blame
    // for this bad usage of Neon intrinsics, or did Havok mess up their Neon getRows?

    row0.v = vld1q_lane_f32(&rotate(0, 0), row0.v, 0);
    row1.v = vld1q_lane_f32(&rotate(1, 0), row1.v, 0);
    row2.v = vld1q_lane_f32(&rotate(2, 0), row2.v, 0);

    row0.v = vld1q_lane_f32(&rotate(0, 1), row0.v, 1);
    row1.v = vld1q_lane_f32(&rotate(1, 1), row1.v, 1);
    row2.v = vld1q_lane_f32(&rotate(2, 1), row2.v, 1);

    row0.v = vld1q_lane_f32(&rotate(0, 2), row0.v, 2);
    row1.v = vld1q_lane_f32(&rotate(1, 2), row1.v, 2);
    row2.v = vld1q_lane_f32(&rotate(2, 2), row2.v, 2);

    row0.v = vld1q_lane_f32(&translate(0), row0.v, 3);
    row1.v = vld1q_lane_f32(&translate(1), row1.v, 3);
    row2.v = vld1q_lane_f32(&translate(2), row2.v, 3);
#else
    rotate.getRows(row0, row1, row2);
    row0[3] = translate[0];
    row1[3] = translate[1];
    row2[3] = translate[2];
#endif

    row0.store<4>(out->m[0]);
    row1.store<4>(out->m[1]);
    row2.store<4>(out->m[2]);
}

}  // namespace ksys::phys
