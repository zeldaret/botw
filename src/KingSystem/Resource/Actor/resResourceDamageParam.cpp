#include "KingSystem/Resource/Actor/resResourceDamageParam.h"

namespace ksys::res {

bool DamageParam::parse_(u8* data, size_t, sead::Heap* heap) {
    mDamageRateBuffer.allocBufferAssert(DamageSource::size(), heap);
    mDamageTypeBuffer.allocBufferAssert(DamageSource::size() * DamageSize::size(), heap);

    sead::FormatFixedSafeString<64> str;
    for (int i = 0; i < DamageSource::size(); ++i) {
        str.format("%s", DamageSource::text(i));
        mDamageRateBuffer[i].init(1.0, str, "", &mDamageRateObj);
    }

    for (int source = 0; source < DamageSource::size(); ++source) {
        for (int size = 0; size < DamageSize::size(); ++size) {
            str.format("%s-%s", DamageSource::text(source), DamageSize::text(size));
            if (source == DamageSource::Arrow) {
                mDamageTypeBuffer.get(source * 4 + size)
                    ->init("通常ダメージ", str, "", &mReactionTableObj);
            } else if (size == DamageSize::Large || size == DamageSize::Huge ||
                       source == DamageSource::Bomb || source == DamageSource::LargeSword) {
                mDamageTypeBuffer.get(source * 4 + size)
                    ->init("吹っ飛び", str, "", &mReactionTableObj);
            } else if (size == DamageSize::Middle) {
                mDamageTypeBuffer.get(source * 4 + size)
                    ->init("中ダメージ", str, "", &mReactionTableObj);
            } else {
                mDamageTypeBuffer.get(source * 4 + size)
                    ->init("通常ダメージ", str, "", &mReactionTableObj);
            }
        }
    }

    mBreakable.init(false, "Breakable", "壊れるかどうか(AI無しで破壊エフェクト・消滅挙動を行う)",
                    "", &mParametersObj);
    mHammerAffect.init(
        false, "HammerAffect",
        "ハンマーが有効かどうか(ハンマー属性にチェックを入れた武器で攻撃されると即死する)", "",
        &mParametersObj);
    mWeakBreakerAffect.init(false, "WeakBreakerAffect", "Objを一撃破壊しない武器設定が有効か", "",
                            &mParametersObj);
    mChemicalAttackAffect.init(true, "ChemicalAttackAffect",
                               "ケミカルAtによる追加ダメージを受けるか(Ex:ロッドの玉)", "",
                               &mParametersObj);
    mSpAffectRatio.init(1.0, "SpAffectRatio", "特効ダメージ倍率(武器倍率と掛け算される)", "",
                        &mParametersObj);
    mSpAffectDamage.init(0, "SpAffectDamage", "特効ダメージ加算値(ダメージ計算後に加算される)", "",
                         &mParametersObj);
    mVanishAffect.init(false, "VanishAffect", "消滅攻撃有効(Ex:古代の矢)", "", &mParametersObj);
    mIsCriticalBlowOff.init(true, "IsCriticalBlowOff", "クリティカルで吹き飛ぶ", "",
                            &mParametersObj);
    mIsAcceptAtkImpulse.init(false, "IsAcceptAtkImpulse",
                             "攻撃的衝撃力を受けるかどうか(Ex:ボコブリンの石)", "",
                             &mParametersObj);
    mIsCommonCalcImpuleDamage.init(
        true, "IsCommonCalcImpuleDamage",
        "衝撃力ダメージを自動計算する(Offの場合のみImpulseDamageTableが有効になります)", "",
        &mParametersObj);
    mIsHeavyBreak.init(false, "IsHeavyBreak", "巨体属性でへし折れる", "", &mParametersObj);
    mImpulseThresholdLv0.init(-1.0, "ImpulseThresholdLv0", "(Small)衝撃力ダメージ閾値", "",
                              &mParametersObj);
    mImpulseDamageLv0.init(0.0, "ImpulseDamageLv0", "(Small)衝撃力ダメージ値", "", &mParametersObj);
    mImpulseThresholdLv1.init(-1.0, "ImpulseThresholdLv1", "(Middle)衝撃力ダメージ閾値", "",
                              &mParametersObj);
    mImpulseDamageLv1.init(0.0, "ImpulseDamageLv1", "(Middle)衝撃力ダメージ値", "",
                           &mParametersObj);
    mImpulseThresholdLv2.init(-1.0, "ImpulseThresholdLv2", "(Large)衝撃力ダメージ閾値", "",
                              &mParametersObj);
    mImpulseDamageLv2.init(0.0, "ImpulseDamageLv2", "(Large)衝撃力ダメージ値", "", &mParametersObj);
    mImpulseThresholdLv3.init(-1.0, "ImpulseThresholdLv3", "(Huge)衝撃力ダメージ閾値", "",
                              &mParametersObj);
    mImpulseDamageLv3.init(0.0, "ImpulseDamageLv3", "(Huge)衝撃力ダメージ値", "", &mParametersObj);
    mImpulseThresholdLv4.init(-1.0, "ImpulseThresholdLv4", "(即死)衝撃力ダメージ閾値", "",
                              &mParametersObj);
    mFallDamageStartHeight.init(10000.0, "FallDamageStartHeight", "落下ダメージ開始高さ", "",
                                &mParametersObj);
    mFallDamageMin.init(0, "FallDamageMin", "落下ダメージ最低値", "", &mParametersObj);
    mFallDamagePerMeter.init(0.0, "FallDamagePerMeter", "1mあたりの加算落下ダメージ量", "",
                             &mParametersObj);
    mFallDamageHighStart.init(-1.0, "FallDamageHighStart", "強落下ダメージ開始高さ(-1で無効)", "",
                              &mParametersObj);
    mFallDamageHighPerMeter.init(0, "FallDamageHighPerMeter",
                                 "強落下時1mあたりの加算落下ダメージ量", "", &mParametersObj);
    mFallDamageNoWaterDepth.init(-1.0, "FallDamageNoWaterDepth", "落下ダメージ受けない水深", "",
                                 &mParametersObj);
    mWeakPointBone.init(sead::SafeString(""), "WeakPointBone", "弱手ボーン名(空白だとモデル原点)",
                        "", &mParametersObj);
    mWeakPointCalcArea.init(0.0, "WeakPointCalcArea", "弱点判定エリア(弱点不要アクターはここを0に)",
                            "", &mParametersObj);
    mWeakPointCalcOffset.init({0, 0, 0}, "WeakPointCalcOffset",
                              "弱手判定エリアの指定ボーンからのオフセット(ローカル座標系)", "",
                              &mParametersObj);
    mWeakPointArea.init(0.0, "WeakPointArea", "弱点エリア", "", &mParametersObj);
    mWeakPointOffset.init({0, 0, 0}, "WeakPointOffset",
                          "弱点エリアの指定ボーンからのオフセット(ローカル座標系)", "",
                          &mParametersObj);
    mWeakPointRatio.init(4.0, "WeakPointRatio", "弱点ダメージ倍率", "", &mParametersObj);
    mWeakPointNoUIFlag.init(false, "WeakPointNoUIFlag", "ヒット時説明UIを出さない", "",
                            &mParametersObj);
    mWeakPointBone2.init(sead::SafeString(""), "WeakPointBone2", "弱手ボーン名(空白だとモデル原点)",
                         "", &mParametersObj);
    mWeakPointCalcArea2.init(0.0, "WeakPointCalcArea2",
                             "弱点判定エリア(弱点不要アクターはここを0に)", "", &mParametersObj);
    mWeakPointCalcOffset2.init({0, 0, 0}, "WeakPointCalcOffset2",
                               "弱手判定エリアの指定ボーンからのオフセット(ローカル座標系)", "",
                               &mParametersObj);
    mWeakPointArea2.init(0.0, "WeakPointArea2", "弱点エリア", "", &mParametersObj);
    mWeakPointOffset2.init({0, 0, 0}, "WeakPointOffset2",
                           "弱点エリアの指定ボーンからのオフセット(ローカル座標系)", "",
                           &mParametersObj);
    mWeakPointRatio2.init(1.0, "WeakPointRatio2", "弱点ダメージ倍率", "", &mParametersObj);
    mWeakPointNoUIFlag2.init(false, "WeakPointNoUIFlag2", "ヒット時説明UIを出さない", "",
                             &mParametersObj);
    mSillentKillMultRatio.init(1.0, "SillentKillMultRatio", "奇襲ダメージ乗算倍率", "",
                               &mParametersObj);
    mSillentKillAddDamage.init(0, "SillentKillAddDamage", "奇襲ダメージ加算値", "",
                               &mParametersObj);
    mIsDeadBurnout.init(false, "IsDeadBurnout", "燃え尽きでライフ0", "", &mParametersObj);
    mIsMetamorBurnout.init(false, "IsMetamorBurnout", "燃え尽きでアクタ変化", "", &mParametersObj);
    mIsMatamorFromTg.init(true, "IsMatamorFromTg", "炎剣で切っても変化する", "", &mParametersObj);
    mBurnable.init(false, "Burnable", "燃え状態有効", "", &mParametersObj);
    mBurnDamage.init(10, "BurnDamage", "燃えダメージLv1(-1でダメージ受けない)", "",
                     &mParametersObj);
    mBurnDamage2.init(-1, "BurnDamage2", "燃えダメージLv2(-1でLv1と同じ)", "", &mParametersObj);
    mBurnDamage3.init(-1, "BurnDamage3", "燃えダメージLv3(-1でLv2と同じ)", "", &mParametersObj);
    mBurnDamage4.init(-1, "BurnDamage4", "燃えダメージLv4(-1でLv3と同じ)", "", &mParametersObj);
    mBurnDamage5.init(-1, "BurnDamage5", "燃えダメージLv5(-1でLv4と同じ)", "", &mParametersObj);
    mBurnTime.init(10, "BurnTime", "燃え時間", "", &mParametersObj);
    mBurnDamageInterval.init(-1, "BurnDamageInterval", "[火に接触時]燃えダメージ間隔(-1で無し)", "",
                             &mParametersObj);
    mBurnContinuousDamage.init(0, "BurnContinuousDamage", "[火に接触時]燃え継続ダメージ", "",
                               &mParametersObj);
    mBurnCritical.init(false, "BurnCritical", "火異常がクリティカル扱いか", "", &mParametersObj);
    mProofBurnAtSmallDamage.init(false, "ProofBurnAtSmallDamage",
                                 "火弾無効時小ダメージアクションをとるか", "", &mParametersObj);
    mIsDeadIce.init(false, "IsDeadIce", "凍結でライフ0", "", &mParametersObj);
    mIsMetamorIce.init(false, "IsMetamorIce", "凍結でアクタ変化", "", &mParametersObj);
    mIceable.init(false, "Iceable", "凍結状態有効", "", &mParametersObj);
    mIceDamage.init(10, "IceDamage", "凍結ダメージ", "", &mParametersObj);
    mIceTime.init(10, "IceTime", "凍結時間(f)", "", &mParametersObj);
    mIceBreakableByAtk.init(true, "IceBreakableByAtk", "凍結時攻撃で割れるか", "", &mParametersObj);
    mIceBreakDamageRatio.init(4.0, "IceBreakDamageRatio", "凍結破壊ダメージ倍率", "",
                              &mParametersObj);
    mIceCritical.init(false, "IceCritical",
                      "凍結異常がクリティカル扱いか(濡れたら死ぬようになります)", "",
                      &mParametersObj);
    mProofIceAtSmallDamage.init(false, "ProofIceAtSmallDamage",
                                "冷凍弾無効時小ダメージアクションをとるか", "", &mParametersObj);
    mIsDeadElectric.init(false, "IsDeadElectric", "帯電でライフ0", "", &mParametersObj);
    mIsMetamorElectric.init(false, "IsMetamorElectric", "帯電でアクタ変化", "", &mParametersObj);
    mElectricable.init(false, "Electricable", "痺れ状態有効", "", &mParametersObj);
    mElectricDamage.init(0, "ElectricDamage", "痺れダメージ", "", &mParametersObj);
    mElectricTime.init(10, "ElectricTime", "痺れ時間(f)", "", &mParametersObj);
    mElecCancelableByAtk.init(false, "ElecCancelableByAtk", "痺れ時攻撃でキャンセルされるか", "",
                              &mParametersObj);
    mProofElecAtSmallDamage.init(false, "ProofElecAtSmallDamage",
                                 "電気弾無効時小ダメージアクションをとるか", "", &mParametersObj);
    mWetAffect.init(false, "WetAffect", "濡れ有効", "", &mParametersObj);
    mLightningAffect.init(true, "LightningAffect", "落雷有効", "", &mParametersObj);
    mLightningDamage.init(999999, "LightningDamage", "落雷ダメージ", "", &mParametersObj);
    mGerudoHeroAffect.init(true, "GerudoHeroAffect", "英傑加護(雷)有効", "", &mParametersObj);
    mGerudoHeroDamage.init(100, "GerudoHeroDamage", "英傑加護(雷)ダメージ", "", &mParametersObj);
    mGerudoHeroTime.init(300, "GerudoHeroTime", "英傑加護(雷)痺れ時間(0だと吹っ飛び)", "",
                         &mParametersObj);
    mGustAffect.init(true, "GustAffect", "突風有効", "", &mParametersObj);
    mDrownHeight.init(-1.0, "DrownHeight", "溺れる水深(-1で溺れない)", "", &mParametersObj);
    mDrownDamage.init(0, "DrownDamage", "溺れた瞬間に食らうダメージ(特殊な場合を除き0でいい)", "",
                      &mParametersObj);
    mColdWaterFrozenTime.init(-1, "ColdWaterFrozenTime", "冷たい水地形で凍結する時間", "",
                              &mParametersObj);
    mColdWaterAffect.init(true, "ColdWaterAffect", "冷たい水地形でダメージ有", "", &mParametersObj);
    mColdWaterDamage.init(0, "ColdWaterDamage", "冷たい水ダメージ値", "", &mParametersObj);
    mColdWaterDamageInterval.init(-1, "ColdWaterDamageInterval", "冷たい水ダメージ最浅間隔", "",
                                  &mParametersObj);
    mColdWaterDamageStartDepth.init(0.0, "ColdWaterDamageStartDepth", "冷たい水ダメージ最浅閾値",
                                    "", &mParametersObj);
    mColdWaterDamageIntervalDeep.init(-1, "ColdWaterDamageIntervalDeep",
                                      "冷たい水ダメージ最深間隔(-1なら使わない)", "",
                                      &mParametersObj);
    mColdWaterDamageDeepDepth.init(-1.0, "ColdWaterDamageDeepDepth",
                                   "冷たい水ダメージ最深閾値(-1で最深間隔は使わない)", "",
                                   &mParametersObj);
    mHotWaterBoiledTime.init(
        -1, "HotWaterBoiledTime",
        "熱湯地形で茹であがる時間(-1で無効,有効にする場合は以下は無効設定にして下さい)", "",
        &mParametersObj);
    mHotWaterHealAffect.init(false, "HotWaterHealAffect", "温泉地形で影響有", "", &mParametersObj);
    mHotWaterHeal.init(0, "HotWaterHeal", "温泉回復値", "", &mParametersObj);
    mHotWaterHealInterval.init(-1, "HotWaterHealInterval", "温泉影響最浅間隔", "", &mParametersObj);
    mHotWaterHealStartDepth.init(0.0, "HotWaterHealStartDepth", "温泉影響最浅閾値", "",
                                 &mParametersObj);
    mHotWaterHealIntervalDeep.init(-1, "HotWaterHealIntervalDeep",
                                   "温泉影響最深間隔(-1なら使わない)", "", &mParametersObj);
    mHotWaterHealDeepDepth.init(-1.0, "HotWaterHealDeepDepth",
                                "温泉影響最深閾値(-1で最深間隔は使わない)", "", &mParametersObj);
    mHotWaterChemCrit.init(false, "HotWaterChemCrit", "温泉入るとケミカルクリティカル", "",
                           &mParametersObj);
    mPoisonBogAffect.init(true, "PoisonBogAffect", "毒沼地形でダメージ有", "", &mParametersObj);
    mPoisonBogDamage.init(0, "PoisonBogDamage", "毒沼ダメージ値", "", &mParametersObj);
    mPoisonBogDamageInterval.init(-1, "PoisonBogDamageInterval", "毒沼ダメージ間隔", "",
                                  &mParametersObj);
    mLavaAffect.init(true, "LavaAffect", "溶岩地形でダメージ有", "", &mParametersObj);
    mLavaDamage.init(999999, "LavaDamage", "溶岩ダメージ値", "", &mParametersObj);
    mLavaDamageInterval.init(-1, "LavaDamageInterval", "溶岩ダメージ間隔", "", &mParametersObj);
    mLavaDeepDepth.init(-1.0, "LavaDeepDepth", "深い溶岩閾値", "", &mParametersObj);
    mLavaDeepDamage.init(999999, "LavaDeepDamage", "深い溶岩ダメージ値", "", &mParametersObj);
    mCurseAffect.init(false, "CurseAffect", "怨念ダメージ状態有効", "", &mParametersObj);
    mCurseDamage.init(30, "CurseDamage", "怨念ダメージ", "", &mParametersObj);
    mCurseInterval.init(60, "CurseInterval", "怨念ダメージ間隔(-1で無し)", "", &mParametersObj);
    mCurseContinuousDamage.init(5, "CurseContinuousDamage", "怨念継続ダメージ", "",
                                &mParametersObj);
    mHeavySnowColdTime.init(-1, "HeavySnowColdTime", "大雪時凍るまでの時間(-1で凍らない)", "",
                            &mParametersObj);

    mKeyString.init(sead::SafeString(""), "key", "", &mDamageTypeObj);

    mParamList.addObj(&mDamageRateObj, "DamageRate");
    mParamList.addObj(&mReactionTableObj, "ReactionTable");
    mParamList.addObj(&mParametersObj, "Parameters");
    mParamList.addObj(&mDamageTypeObj, "DamageType");
    addList(&mParamList, "damage_param");

    if (data)
        applyResParameterArchive(agl::utl::ResParameterArchive(data));

    return true;
}

f32 DamageParam::getDamageRate(const sead::SafeString& damage_source) {
    u32 hash = agl::utl::ParameterBase::calcHash(damage_source);

#pragma clang loop unroll(full)
    for (int idx = 0; idx != 10; ++idx) {
        if (hash == mDamageRateBuffer[idx].getNameHash())
            return mDamageRateBuffer[idx].ref();
    }
    return 0.0;
}

const sead::SafeString& DamageParam::getDamageReaction(const sead::SafeString& damage_source,
                                                       const sead::SafeString& size) {
    sead::FormatFixedSafeString<128> key("%s-%s", damage_source.cstr(), size.cstr());

    u32 hash = agl::utl::ParameterBase::calcHash(key);

#pragma clang loop unroll(full)
    for (int idx = 0; idx != 40; ++idx) {
        if (hash == mDamageTypeBuffer.get(idx)->getNameHash())
            return mDamageTypeBuffer.get(idx)->ref();
    }
    return sead::SafeString::cEmptyString;
}

}  // namespace ksys::res
