#pragma once

#include <basis/seadTypes.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>

class hkaPose;
class hkaSkeleton;
class hkQsTransformf;

namespace sead {
class Heap;
}

namespace ksys::phys {

class BoneAccessor : public sead::hostio::Node {
public:
    enum class Propagate : bool { Yes = true, No = false };

    struct Indices {
        Indices(s16 unk_, s16 havok_index) : unk(unk_), havok_index(havok_index) {}

        s16 unk;
        s16 havok_index;
    };

    BoneAccessor();
    virtual ~BoneAccessor();

    bool init(const hkaSkeleton* skeleton, sead::Heap* heap);
    virtual void finalize();

    void resetPoseData();

    const hkaSkeleton* getSkeleton() const;
    hkaPose* getPoseInternal() const;
    hkaPose* getPose() const;

    void setScale(float scale);

    void setBoneLocalSpace(const Indices& index, const hkQsTransformf& bone_local);
    const hkQsTransformf& getBoneLocalSpace(const Indices& index) const;

    void setBoneModelSpace(const Indices& index, const hkQsTransformf& bone_model,
                           Propagate propagate);
    const hkQsTransformf& getBoneModelSpace(const Indices& index) const;

    Indices getBoneIndex(const sead::SafeString& name) const;

protected:
    /// Extracts the actual bone name from a complex bone name like "Link:Leg_1_R".
    /// @example Link:Leg_1_R -> Leg_1_R, Head -> Head
    static sead::SafeString getBoneName(const sead::SafeString& name);

    hkaPose* mPose{};
    u32 mPoseDataSize{};
    u8* mPoseData{};
};

}  // namespace ksys::phys
