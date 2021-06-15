#include "KingSystem/Physics/Ragdoll/physRagdollConfig.h"
#include "KingSystem/Resource/Actor/resResourceRagdollConfig.h"

namespace ksys::phys {

RagdollConfig::PartImpulseInfo::ReceiveObj::ReceiveObj()
    : mTypeName({"null"}, "TypeName", "適用するラグドール剛体名", this),
      mDivideFlag(false, "DivideFlag", "インパルスを親子に分散させるか", this),
      mImpulseRate(1.0, "ImpulseRate", "インパルスの適用比率", this),
      mDivideRate(0.5, "DivideRate", "親子へのインパルス分配比率", this) {}

RagdollConfig::PartImpulseInfo::ImpulseObj::ImpulseObj()
    : mTypeName({""}, "TypeName", "適用するラグドール剛体名", this),
      mUseFlag(false, "UseFlag", "このスロットのインパルス情報を使うかどうか", this),
      mAttackVector({0, 0, 0}, "AttackVector", "インパルスの方向", this),
      mAttackPoint({0, 0, 0}, "AttackPoint", "インパルスを与える点", this),
      mImpulsePower(0.1, "ImpulsePower", "インパルスの強さ", this) {}

RagdollConfig::PartImpulseInfo::PartImpulseInfo()
    : mIsUseReceiveImpulse(true, "IsUseReceiveImpulse", "攻撃インパルスを反映させるかどうか",
                           &mObj),
      mIsUseFixedImpulse(true, "IsUseFixedImpulse", "固定インパルスを反映させるかどうか", &mObj) {
    for (int i = 0; i < res::RagdollConfig::cNumReceiveObjs; ++i) {
        sead::FormatFixedSafeString<128> name("ReceiveObj%02d", i + 1);
        addObj(&mReceiveObjs(i), name);
    }

    for (int i = 0; i < res::RagdollConfig::cNumImpulseObjs; ++i) {
        sead::FormatFixedSafeString<128> name("ImpulseObj%02d", i + 1);
        addObj(&mImpulseObjs(i), name);
    }

    addObj(&mObj, "PartImpulseData");
}

RagdollConfig::ImpactImpulseInfo::ImpactImpulseInfo() {
    for (int i = 0; i < NumParts; ++i) {
        sead::FormatFixedSafeString<128> name("PartImpulseInfo%02d", i + 1);
        addList(&mPartImpulseInfo[i], name);

        sead::FormatFixedSafeString<32> use_flag_name("UseFlag%02d", i + 1);
        mUseFlags[i].init(true, use_flag_name, "攻撃インパルスを反映させるかどうか", &mObj);
    }

    addObj(&mObj, "ImpactImpulseData");
}

RagdollConfig::RagdollConfig()
    : agl::utl::IParameterIO("rgconfig", 0),
      mImpulseUseRate(0.5, "ImpulseUseRate", "攻撃インパルスの混合率", &mObj),
      mImpulsePower(0.1, "ImpulsePower", "インパルスの強さ", &mObj),
      mLargeAttackRate(1.5, "LargeAttackRate", "大攻撃のインパルス倍率", &mObj),
      mBlastOffAttackRateSmall(2.0, "BlastOffAttackRateSmall", "小攻撃のふっ飛ばしインパルス倍率",
                               &mObj),
      mBlastOffAttackRateLarge(3.0, "BlastOffAttackRateLarge", "大攻撃のふっ飛ばしインパルス倍率",
                               &mObj),
      mSpecialAttackRate(10.0, "SpecialAttackRate", "特殊攻撃のふっ飛ばしインパルス倍率", &mObj) {
    for (int i = 0; i < mImpactImpulseInfo.size(); ++i) {
        sead::FormatFixedSafeString<128> name("ImpactImpulseInfo%02d", i + 1);
        addList(&mImpactImpulseInfo[i], name);
    }

    addObj(&mObj, "AttackTypeImpulseData");
}

RagdollConfig::~RagdollConfig() = default;

const RagdollConfig::PartImpulseInfo& RagdollConfig::getImpulseInfo(u32 impact_idx,
                                                                    int part_idx) const {
    return mImpactImpulseInfo.getBufferPtr()[impact_idx].getPartImpulseInfo()(part_idx);
}

float RagdollConfig::getImpulsePower(int attack_rate_type, bool is_blast_off) const {
    switch (attack_rate_type) {
    case 0:
        if (!is_blast_off)
            return *mImpulsePower;
        return *mImpulsePower * *mBlastOffAttackRateSmall;
    case 1:
        if (!is_blast_off)
            return *mImpulsePower * *mLargeAttackRate;
        return *mImpulsePower * *mBlastOffAttackRateLarge;
    case 2:
        return *mImpulsePower * *mBlastOffAttackRateLarge;
    case 3:
        return *mImpulsePower * *mSpecialAttackRate;
    default:
        return 0.0;
    }
}

}  // namespace ksys::phys
