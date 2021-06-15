#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class BoneControl : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(BoneControl, Resource)
public:
    struct Whole {
        agl::utl::ParameterObj obj;
        agl::utl::Parameter<bool> isFaceCtrlInvalid;
        agl::utl::Parameter<float> neckAndEyeRatio;
    };
    KSYS_CHECK_SIZE_NX150(Whole, 0x70);

    struct EyeBall {
        agl::utl::ParameterObj obj;
        agl::utl::Parameter<bool> isEyeBallCtrlInvalid;
        agl::utl::Parameter<bool> isEyeBallRotWorldAxis;
        agl::utl::Parameter<sead::SafeString> eyeBallSRTName;
        agl::utl::Parameter<float> eyeRotRateLR;
        agl::utl::Parameter<float> eyeRotRateUD;
        agl::utl::Parameter<float> eyeMinRotPerFrame;
        agl::utl::Parameter<float> eyeMaxRotPerFrame;
        agl::utl::Parameter<int> eyeSetNum;
    };
    KSYS_CHECK_SIZE_NX150(EyeBall, 0x138);

    struct EyeSet {
        agl::utl::ParameterObj obj;
        agl::utl::Parameter<sead::SafeString> boneName;
        agl::utl::Parameter<bool> isControlTexture;
        agl::utl::Parameter<sead::SafeString> materialName;
        agl::utl::Parameter<sead::SafeString> forwardBoneName;
        agl::utl::Parameter<int> forwardAxis;
        agl::utl::Parameter<int> axisLR;
        agl::utl::Parameter<int> axisUD;
        agl::utl::Parameter<float> lTransLimit;
        agl::utl::Parameter<float> rTransLimit;
        agl::utl::Parameter<float> dTransLimit;
        agl::utl::Parameter<float> uTransLimit;
        agl::utl::Parameter<bool> isCorrectForward;
        agl::utl::Parameter<int> axisCorrect;
        agl::utl::Parameter<float> correctRot;
        agl::utl::Parameter<float> lRotLimit;
        agl::utl::Parameter<float> rRotLimit;
        agl::utl::Parameter<float> dRotLimit;
        agl::utl::Parameter<float> uRotLimit;
        agl::utl::Parameter<sead::Vector3f> offset;
    };
    KSYS_CHECK_SIZE_NX150(EyeSet, 0x2b0);

    struct Bone {
        agl::utl::Parameter<sead::SafeString> name;
    };
    KSYS_CHECK_SIZE_NX150(Bone, 0x28);

    struct BoneGroup {
        agl::utl::ParameterList list;
        agl::utl::ParameterObj paramObj;
        agl::utl::ParameterObj bonesObj;
        agl::utl::Parameter<sead::SafeString> groupName;
        sead::Buffer<Bone> bones;
    };
    KSYS_CHECK_SIZE_NX150(BoneGroup, 0xe0);

    struct SpineNode {
        agl::utl::ParameterObj obj;
        agl::utl::Parameter<sead::SafeString> boneName;
        agl::utl::Parameter<bool> isRotWorldAxis;
        agl::utl::Parameter<int> axisLR;
        agl::utl::Parameter<int> axisUD;
        agl::utl::Parameter<float> lLimit;
        agl::utl::Parameter<float> rLimit;
        agl::utl::Parameter<float> dLimit;
        agl::utl::Parameter<float> uLimit;
        agl::utl::Parameter<float> lBattleLimit;
        agl::utl::Parameter<float> rBattleLimit;
        agl::utl::Parameter<float> dBattleLimit;
        agl::utl::Parameter<float> uBattleLimit;
        agl::utl::Parameter<bool> isEnableCorrect;
        agl::utl::Parameter<int> axisCorrect;
        agl::utl::Parameter<float> lCorrect;
        agl::utl::Parameter<float> rCorrect;
        agl::utl::Parameter<float> lBattleCorrect;
        agl::utl::Parameter<float> rBattleCorrect;
        agl::utl::Parameter<float> minRotPerFrame;
        agl::utl::Parameter<float> maxRotPerFrame;
    };
    KSYS_CHECK_SIZE_NX150(SpineNode, 0x2b8);

    struct Spine {
        agl::utl::ParameterObj obj;
        agl::utl::ParameterList list;
        agl::utl::Parameter<bool> isInvalid;
        agl::utl::Parameter<bool> isBasisSelfPosNeckLR;
        agl::utl::Parameter<bool> isBasisSelfPosNeckUD;
        agl::utl::Parameter<bool> isBattleNeckRecalcUD;
        agl::utl::Parameter<bool> spineDisableBaseDirAlongXZ;
        agl::utl::Parameter<float> spineRotRate;
        agl::utl::Parameter<float> spineRetRotRate;
        agl::utl::Parameter<sead::SafeString> spineNeckBaseBone;
        agl::utl::Parameter<sead::Vector3f> neckPosOffset;
        agl::utl::Parameter<int> spineNeckNodeNum;
        agl::utl::Parameter<int> spineNodeNum;
        sead::Buffer<SpineNode> spineNodes;
    };
    KSYS_CHECK_SIZE_NX150(Spine, 0x1f8);

    struct FootIkController {
        agl::utl::ParameterObj obj;
        agl::utl::Parameter<bool> isInvalidFt;
        agl::utl::Parameter<int> calculateTypeFt;
        agl::utl::Parameter<float> ankleOffsetYFt;
        agl::utl::Parameter<float> ankleOffsetAngleDegFt;
        agl::utl::Parameter<float> ankleAngleLimitUpDegFt;
        agl::utl::Parameter<float> ankleAngleLimitDownDegFt;
        agl::utl::Parameter<float> ankleHeightLimitRateFt;
        agl::utl::Parameter<float> waistDownRateFt;
        agl::utl::Parameter<float> kneeRotateAgnleMinDegFt;
        agl::utl::Parameter<float> kneeRotateAgnleMaxDegFt;
        agl::utl::Parameter<bool> enableLimitThighAngleFt;
        agl::utl::Parameter<float> thighRotateAngleMinDegFt;
        agl::utl::Parameter<float> thighRotateAngleMaxDegFt;
    };
    KSYS_CHECK_SIZE_NX150(FootIkController, 0x1d0);

    BoneControl();
    ~BoneControl() override;

    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;
    bool ParamIO_m0(char* data) override { return true; }
    bool needsParse() const override { return true; }

    const Whole& getWhole() const { return mWhole; }
    const Spine& getSpine() const { return mSpine; }
    const EyeBall& getEyeBall() const { return mEyeBall; }
    const sead::Buffer<EyeSet>& getEyeSets() const { return mEyeSets; }
    const FootIkController& getFootIkController() const { return mFootIkController; }
    const sead::Buffer<BoneGroup>& getBoneGroups() const { return mBoneGroups; }

    const BoneGroup* getBoneGroup(const sead::SafeString& name) const;

private:
    Whole mWhole;
    Spine mSpine;
    EyeBall mEyeBall;
    agl::utl::ParameterList _650;
    sead::Buffer<EyeSet> mEyeSets;
    FootIkController mFootIkController;
    agl::utl::ParameterList mBoneGroupsList;
    sead::Buffer<BoneGroup> mBoneGroups;
};
KSYS_CHECK_SIZE_NX150(BoneControl, 0x8d0);

}  // namespace ksys::res
