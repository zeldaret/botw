#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterIO.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadSafeArray.h>
#include <hostio/seadHostIONode.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>

namespace ksys::phys {

class RagdollConfig : public agl::utl::IParameterIO, public sead::hostio::Node {
public:
    class PartImpulseInfo : public agl::utl::ParameterList, public sead::hostio::Node {
    public:
        class ReceiveObj : public agl::utl::ParameterObj {
        public:
            ReceiveObj();

            const auto& getTypeName() const { return *mTypeName; }
            const auto& getDivideFlag() const { return *mDivideFlag; }
            const auto& getImpulseRate() const { return *mImpulseRate; }
            const auto& getDivideRate() const { return *mDivideRate; }
            bool is100() const { return _100; }

        private:
            agl::utl::Parameter<sead::FixedSafeString<64>> mTypeName;
            agl::utl::Parameter<bool> mDivideFlag;
            agl::utl::Parameter<float> mImpulseRate;
            agl::utl::Parameter<float> mDivideRate;
            bool _100 = true;
        };

        class ImpulseObj : public agl::utl::ParameterObj {
        public:
            ImpulseObj();

            const auto& getTypeName() const { return *mTypeName; }
            const auto& getUseFlag() const { return *mUseFlag; }
            const auto& getAttackVector() const { return *mAttackVector; }
            const auto& getAttackPoint() const { return *mAttackPoint; }
            const auto& getImpulsePower() const { return *mImpulsePower; }
            bool is130() const { return _130; }

        private:
            agl::utl::Parameter<sead::FixedSafeString<64>> mTypeName;
            agl::utl::Parameter<bool> mUseFlag;
            agl::utl::Parameter<sead::Vector3f> mAttackVector;
            agl::utl::Parameter<sead::Vector3f> mAttackPoint;
            agl::utl::Parameter<float> mImpulsePower;
            bool _130 = false;
        };

        PartImpulseInfo();

        const auto& getReceiveObjs() const { return mReceiveObjs; }
        const auto& getImpulseObjs() const { return mImpulseObjs; }
        const bool& isUseReceiveImpulse() const { return *mIsUseReceiveImpulse; }
        const bool& isUseFixedImpulse() const { return *mIsUseFixedImpulse; }

    private:
        sead::SafeArray<ReceiveObj, 3> mReceiveObjs;
        sead::SafeArray<ImpulseObj, 5> mImpulseObjs;
        agl::utl::IParameterObj mObj;
        agl::utl::Parameter<bool> mIsUseReceiveImpulse;
        agl::utl::Parameter<bool> mIsUseFixedImpulse;
    };

    class ImpactImpulseInfo : public agl::utl::ParameterList, public sead::hostio::Node {
    public:
        ImpactImpulseInfo();

        const auto& getPartImpulseInfo() const { return mPartImpulseInfo; }
        bool isUsed(int idx) const { return *mUseFlags[idx]; }

    private:
        static constexpr int NumParts = 3;

        sead::SafeArray<PartImpulseInfo, NumParts> mPartImpulseInfo;
        agl::utl::IParameterObj mObj;
        sead::SafeArray<agl::utl::Parameter<bool>, NumParts> mUseFlags;
    };

    RagdollConfig();
    ~RagdollConfig() override;

    const auto& getImpactImpulseInfo() const { return mImpactImpulseInfo; }
    const float& getImpulseUseRate() const { return *mImpulseUseRate; }
    const float& getImpulsePower() const { return *mImpulsePower; }
    const float& getLargeAttackRate() const { return *mLargeAttackRate; }
    const float& getBlastOffAttackRateSmall() const { return *mBlastOffAttackRateSmall; }
    const float& getBlastOffAttackRateLarge() const { return *mBlastOffAttackRateLarge; }
    const float& getSpecialAttackRate() const { return *mSpecialAttackRate; }

    const PartImpulseInfo& getImpulseInfo(u32 impact_idx, int part_idx) const;
    float getImpulsePower(int attack_rate_type, bool is_blast_off) const;

private:
    sead::SafeArray<ImpactImpulseInfo, 2> mImpactImpulseInfo;
    agl::utl::IParameterObj mObj;
    agl::utl::Parameter<float> mImpulseUseRate;
    agl::utl::Parameter<float> mImpulsePower;
    agl::utl::Parameter<float> mLargeAttackRate;
    agl::utl::Parameter<float> mBlastOffAttackRateSmall;
    agl::utl::Parameter<float> mBlastOffAttackRateLarge;
    agl::utl::Parameter<float> mSpecialAttackRate;
};

}  // namespace ksys::phys
