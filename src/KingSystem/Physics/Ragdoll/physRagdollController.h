#pragma once

#include <container/seadBuffer.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>

class hkaRagdollRigidBodyController;

namespace ksys::phys {

class RagdollInstance;

// TODO
class RagdollController : public sead::hostio::Node {
public:
    RagdollController();
    virtual ~RagdollController();

    const sead::SafeString& getName() const { return mName; }

    // 0x00000071012ab3a0
    bool init(const sead::SafeString& name, const sead::SafeString& system_key,
              RagdollInstance* instance, sead::Heap* heap);

    bool setBoneWeight(int index, float weight);
    bool setBoneWeight(const sead::SafeString& rigid_name, float weight);
    void setFactor(float factor);
    void recalculateEffectiveBoneWeight(int index);

    void reset();
    void reinitController();

    void setMultiplier(int index, float multiplier) { mMultipliers[index] = multiplier; }
    void resetMultipliers();

    static void forceDefaultWeights(bool force);

private:
    sead::FixedSafeString<32> mName;
    hkaRagdollRigidBodyController* mRagdollRigidBodyCtrl = nullptr;
    sead::Buffer<float> mConfiguredBoneWeights;
    sead::Buffer<float> mEffectiveBoneWeights;
    sead::Buffer<float> mMultipliers;
    // If = 0, effective_weight = multiplier * configured_weight
    // If < 0, effective_weight linearly decreases from (multiplier * configured_weight) to 0
    // If > 0, effective_weight linearly increases from (multiplier * configured_weight) to 1
    float mFactor = 0.0;
    RagdollInstance* mInstance = nullptr;
};

}  // namespace ksys::phys
