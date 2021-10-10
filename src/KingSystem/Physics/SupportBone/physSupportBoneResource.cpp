#include "KingSystem/Physics/SupportBone/physSupportBoneResource.h"

#include <cmath>

namespace ksys::phys {

SupportBoneResource::Bone::~Bone() = default;

SupportBoneResource::BaseBone::BaseBone()
    : bone(-1, "bone", "bone", this), aim(sead::Vector3f::ez, "aim", "aim", this),
      up(sead::Vector3f::ey, "up", "up", this), space(-1, "space", "space", this),
      base_rotate(sead::Quatf::unit, "base_rotate", "base_rotate", this),
      base_translate(sead::Vector3f::zero, "base_translate", "base_translate", this) {}

SupportBoneResource::SupportBone::SupportBone()
    : bendH(-1, "bendH", "bendH", this), bendV(-1, "bendV", "bendV", this),
      roll(-1, "roll", "roll", this), translateX(-1, "translateX", "translateX", this),
      translateY(-1, "translateY", "translateY", this),
      translateZ(-1, "translateZ", "translateZ", this) {}

SupportBoneResource::SupportBoneResource()
    : IParameterIO("physsb", 0), mBoneNum(0, "bone_num", "bone_num", &mSupportBoneHeader),
      mConnectionLinearNum(0, "connection_linear_num", "connection_linear_num",
                           &mSupportBoneHeader),
      mConnectionCurveNum(0, "connection_curve_num", "connection_curve_num", &mSupportBoneHeader),
      mOutputSingleNum(0, "output_single_num", "output_single_num", &mSupportBoneHeader),
      mOutputDoubleNum(0, "output_double_num", "output_double_num", &mSupportBoneHeader),
      // labels have two underscores instead of a single one
      mMainBoneNum(0, "main_bone_num", "main_bone__num" /* sic */, &mSupportBoneHeader),
      mSupportBoneNum(0, "support_bone_num", "support_bone__num" /* sic */, &mSupportBoneHeader) {
    addObj(&mSupportBoneHeader, "support_bone_header");
    addList(&mSupportBoneData, "support_bone_data");
}

SupportBoneResource::~SupportBoneResource() {
    freeBuffers();
}

void SupportBoneResource::freeBuffers() {
    boneBuffer.freeBuffer();
    mConnectionLinearBuffer.freeBuffer();
    mConnectionCurveBuffer.freeBuffer();
    mOutputSingleBuffer.freeBuffer();
    mOutputDoubleBuffer.freeBuffer();
    mMainBoneBuffer.freeBuffer();
    mSupportBoneBuffer.freeBuffer();
}

bool uninlineAllocDoubleBuffer(sead::Buffer<ksys::phys::SupportBoneResource::OutputDouble>* buffer,
                               int size, sead::Heap* heap, s32 alignment = sizeof(void*)) {
    return buffer->allocBufferAssert(size, heap, alignment);
}

void SupportBoneResource::doCreate_(u8* data, u32 actualFileSize, sead::Heap* heap) {
    init(agl::utl::ResParameterArchive(data), heap);
}

float SupportBoneResource::somethingGetLinearConnection(u32 a2, float a3) {
    sead::Vector2f slope_intercept = mConnectionLinearBuffer[a2].slope_intercept.ref();
    float result = slope_intercept.x * a3 + slope_intercept.y;
    return std::isnan(result) ? 0.0f : result;
}

int SupportBoneResource::getSupportBoneIndexByName(const sead::SafeString& name) {
    s32 support_bone_num = mSupportBoneNum.ref();
    for (s32 i = 0; i < support_bone_num; i++) {
        int bone_index = mSupportBoneBuffer[i].bone.ref();
        sead::SafeString bone_name = boneBuffer[bone_index].name.ref().cstr();
        if (name == bone_name)
            return i;
    }
    return -1;
}

bool SupportBoneResource::init(agl::utl::ResParameterArchive archive, sead::Heap* heap) {
    agl::utl::ResParameterList param_list = archive.getRootList();
    const auto support_bone_list = param_list.getResParameterList(0);
    mSupportBoneHeader.applyResParameterObj(param_list.getResParameterObj(0));

    int bone_num = mBoneNum.ref();
    if (bone_num < 1)
        return false;
    mSupportBoneData.addList(&mBoneList, "bone_list");
    boneBuffer.allocBufferAssert(bone_num, heap);
    for (int i = 0; i < bone_num; i++) {
        auto bone_name = sead::FormatFixedSafeString<32>("bone_%d", i);
        mBoneList.addObj(&boneBuffer[i], bone_name);
        boneBuffer[i].name.init(sead::FixedSafeString<64>::cEmptyString, "name", "name",
                                &boneBuffer[i]);
    }

    int connection_linear_num = mConnectionLinearNum.ref();
    if (connection_linear_num > 0) {
        mSupportBoneData.addList(&mConnectionLinearList, "connection_linear_list");
        mConnectionLinearBuffer.allocBufferAssert(connection_linear_num, heap);

        for (int i = 0; i < connection_linear_num; i++) {
            auto connection_name = sead::FormatFixedSafeString<32>("connection_linear_%d", i);
            mConnectionLinearList.addObj(&mConnectionLinearBuffer[i], connection_name);
            mConnectionLinearBuffer[i].bone_attribute.init(
                0, "bone_attribute", "bone_attribute",
                &mConnectionLinearBuffer[i]);  // initialised with 0 instead of -1
            mConnectionLinearBuffer[i].slope_intercept.init(
                {1, -1}, "slope_intercept", "slope_intercept", &mConnectionLinearBuffer[i]);
        }
    }

    int connection_curve_num = mConnectionCurveNum.ref();
    if (connection_curve_num > 0) {
        mSupportBoneData.addList(&mConnectionCurveList, "connection_curve_list");
        mConnectionCurveBuffer.allocBufferAssert(connection_curve_num, heap);

        for (int i = 0; i < connection_curve_num; i++) {
            auto connection_name = sead::FormatFixedSafeString<32>("connection_curve_%d", i);
            mConnectionCurveList.addObj(&mConnectionCurveBuffer[i], connection_name);
            mConnectionCurveBuffer[i].bone_attribute.init(-1, "bone_attribute", "bone_attribute",
                                                          &mConnectionCurveBuffer[i]);
            mConnectionCurveBuffer[i].constant_in.init(true, "constant_in", "constant_in",
                                                       &mConnectionCurveBuffer[i]);
            mConnectionCurveBuffer[i].constant_out.init(true, "constant_out", "constant_out",
                                                        &mConnectionCurveBuffer[i]);
            mConnectionCurveBuffer[i].key0.init({0, 0, 1, 1}, "key_0", "key_0",
                                                &mConnectionCurveBuffer[i]);
            mConnectionCurveBuffer[i].key1.init({0.5, 0.5, 1, 1}, "key_1", "key_1",
                                                &mConnectionCurveBuffer[i]);
            mConnectionCurveBuffer[i].key2.init({1, 1, 1, 1}, "key_2", "key_2",
                                                &mConnectionCurveBuffer[i]);
        }
    }

    int output_single_num = mOutputSingleNum.ref();
    if (output_single_num > 0) {
        mSupportBoneData.addList(&mOutputSingleList, "output_single_list");
        mOutputSingleBuffer.allocBufferAssert(output_single_num, heap);

        for (int i = 0; i < output_single_num; i++) {
            auto output_name = sead::FormatFixedSafeString<32>("output_single_%d", i);
            mOutputSingleList.addObj(&mOutputSingleBuffer[i], output_name);
            mOutputSingleBuffer[i].connection.init(0, "connection", "connection",
                                                   &mOutputSingleBuffer[i]);
            mOutputSingleBuffer[i].weight.init(0, "weight", "weight", &mOutputSingleBuffer[i]);
        }
    }

    int output_double_num = mOutputDoubleNum.ref();
    if (output_double_num > 0) {
        mSupportBoneData.addList(&mOutputDoubleList, "output_double_list");
        uninlineAllocDoubleBuffer(&mOutputDoubleBuffer, output_double_num, heap);

        for (int i = 0; i < output_double_num; i++) {
            auto output_name = sead::FormatFixedSafeString<32>("output_double_%d", i);
            mOutputDoubleList.addObj(&mOutputDoubleBuffer[i], output_name);
            mOutputDoubleBuffer[i].connection_0.init(0, "connection_0", "connection_0",
                                                     &mOutputDoubleBuffer[i]);
            mOutputDoubleBuffer[i].weight_0.init(0, "weight_0", "weight_0",
                                                 &mOutputDoubleBuffer[i]);
            mOutputDoubleBuffer[i].connection_1.init(0, "connection_1", "connection_1",
                                                     &mOutputDoubleBuffer[i]);
            mOutputDoubleBuffer[i].weight_1.init(0, "weight_1", "weight_1",
                                                 &mOutputDoubleBuffer[i]);
        }
    }

    int main_bone_num = mMainBoneNum.ref();
    if (main_bone_num < 1)
        return false;
    mSupportBoneData.addList(&mMainBoneList, "main_bone_list");
    mMainBoneBuffer.allocBufferAssert(main_bone_num, heap);
    for (int i = 0; i < main_bone_num; i++) {
        auto name = sead::FormatFixedSafeString<32>("main_bone_%d", i);
        mMainBoneList.addObj(&mMainBoneBuffer[i], name);
    }

    int support_bone_num = mSupportBoneNum.ref();
    if (support_bone_num < 1)
        return false;
    mSupportBoneData.addList(&mSupportBoneList, "support_bone_list");
    mSupportBoneBuffer.allocBufferAssert(support_bone_num, heap);
    for (int i = 0; i < support_bone_num; i++) {
        auto name = sead::FormatFixedSafeString<32>("support_bone_%d", i);
        mSupportBoneList.addObj(&mSupportBoneBuffer[i], name);
    }

    mSupportBoneData.applyResParameterList(support_bone_list);
    return true;
}

inline float cubicHermiteInterpolate(const sead::Vector4f& key1, const sead::Vector4f& key2,
                                     float lookup) {
    if (key1.x == key2.x) {
        return key2.y;
    }
    float diff = key2.x - key1.x;
    float t = (lookup - key1.x) / diff;
    float h00 = (2 * t * t * t) - (3 * t * t) + 1;
    float h01 = (-2 * t * t * t) + (3 * t * t);
    float h10 = (t * t * t) - (2 * t * t) + t;
    float h10_scaled = h10 * diff;
    float h11 = (t * t * t) - (t * t);
    float h11_scaled = h11 * diff;
    return (h00 * key1.y) + (h01 * key2.y) + (h10_scaled * key1.w) + (h11_scaled * key2.z);
}

float SupportBoneResource::getInterpolatedConnectionCurve(u32 index, float lookup) {
    auto& connection_curve = mConnectionCurveBuffer[index];
    float result;
    float x0 = connection_curve.key0->x;  // lowest (always minus pi?)
    float x1 = connection_curve.key1->x;  // middle (0 in most cases)
    float x2 = connection_curve.key2->x;  // highest
    if (x0 == lookup) {
        result = connection_curve.key0->y;
    } else if (x1 == lookup) {
        result = connection_curve.key1->y;
    } else if (x2 == lookup) {
        result = connection_curve.key2->y;
    } else if (x0 > lookup) {
        result = connection_curve.key0->y;
        if (!connection_curve.constant_in.ref())
            result -= (x0 - lookup) * connection_curve.key0->z;
    } else if (x1 > lookup) {
        result = cubicHermiteInterpolate(connection_curve.key0.ref(), connection_curve.key1.ref(),
                                         lookup);
    } else if (x2 > lookup) {
        result = cubicHermiteInterpolate(connection_curve.key1.ref(), connection_curve.key2.ref(),
                                         lookup);
    } else {
        if (!connection_curve.constant_out.ref())
            result = connection_curve.key2->y + ((lookup - x2) * connection_curve.key2->z);
        else
            result = connection_curve.key2->y;
    }

    return std::isnan(result) ? 0.0f : result;
}

void SupportBoneResource::BaseBone::postRead_() {
    sead::Vector3f aim_local = aim.ref();
    sead::Vector3f up_local = up.ref();
    aim_local.normalize();

    side.setCross(aim_local, up_local);
    // XXX: this looks like a hack. Why does this not match without an inline function?
    [&] { side.normalize(); }();

    up_local.setCross(side, aim_local);
    up_local.normalize();
    up = up_local;
    aim = aim_local;

    base_rotate->normalize();
    base_rotate->inverse(&reverse_rotate);
}

}  // namespace ksys::phys
