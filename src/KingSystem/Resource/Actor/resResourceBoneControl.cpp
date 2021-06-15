#include "KingSystem/Resource/Actor/resResourceBoneControl.h"

namespace ksys::res {

BoneControl::BoneControl() : ParamIO("bonectrl", 0) {}

BoneControl::~BoneControl() {
    mEyeSets.freeBuffer();
    mSpine.spineNodes.freeBuffer();

    for (auto& group : mBoneGroups)
        group.bones.freeBuffer();

    mBoneGroups.freeBuffer();
}

void BoneControl::doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) {}

// NON_MATCHING: mFootIkController.isInvalidFt (???)
bool BoneControl::parse_(u8* data, size_t size, sead::Heap* heap) {
    if (!data)
        return true;

    agl::utl::ResParameterArchive archive{data};
    const auto root = archive.getRootList();

    mWhole.neckAndEyeRatio.init(0.0, "neckAndEyeRatio", "首向けと眼球制御の比率", &mWhole.obj);
    mWhole.isFaceCtrlInvalid.init(true, "isFaceCtrlInvalid", "顔全体無効", &mWhole.obj);
    addObj(&mWhole.obj, "Whole");

    mEyeBall.isEyeBallCtrlInvalid.init(false, "isEyeBallCtrlInvalid", "無効にする", &mEyeBall.obj);
    mEyeBall.isEyeBallRotWorldAxis.init(false, "isEyeBallRotWorldAxis", "ワールド軸で回転する",
                                        &mEyeBall.obj);
    mEyeBall.eyeBallSRTName.init("", "eyeBallSRTName", "眼球SRT名", &mEyeBall.obj);
    mEyeBall.eyeRotRateLR.init(0.0, "eyeRotRateLR", "左右回転比率", &mEyeBall.obj);
    mEyeBall.eyeRotRateUD.init(0.0, "eyeRotRateUD", "上下回転比率", &mEyeBall.obj);
    mEyeBall.eyeMinRotPerFrame.init(0.5, "eyeMinRotPerFrame", "フレーム毎の最小回転量",
                                    &mEyeBall.obj);
    mEyeBall.eyeMaxRotPerFrame.init(6.0, "eyeMaxRotPerFrame", "フレーム毎の最大回転量",
                                    &mEyeBall.obj);
    mEyeBall.eyeSetNum.init(0, "eyeSetNum", "眼球セット数", &mEyeBall.obj);
    addObj(&mEyeBall.obj, "EyeBall");

    applyResParameterArchive(agl::utl::ResParameterArchive{data});

    const int eye_set_num = mEyeBall.eyeSetNum.ref();
    if (eye_set_num > 0) {
        if (!mEyeSets.tryAllocBuffer(eye_set_num, heap))
            return false;

        for (int i = 0; i < eye_set_num; ++i) {
            sead::FormatFixedSafeString<64> name("");
            name.format("EyeSet_%02d", i);

            mEyeSets[i].isControlTexture.init(false, "isControlTexture", "テクスチャ制御する",
                                              &mEyeSets[i].obj);
            mEyeSets[i].materialName.init("", "materialName", "マテリアル名", &mEyeSets[i].obj);
            mEyeSets[i].boneName.init("", "boneName", "ボーン名", &mEyeSets[i].obj);
            mEyeSets[i].forwardBoneName.init("", "forwardBoneName", "前方方向ボーン名",
                                             &mEyeSets[i].obj);
            mEyeSets[i].forwardAxis.init(1, "forwardAxis", "前方方向とする軸", &mEyeSets[i].obj);
            mEyeSets[i].axisLR.init(0, "axisLR", "左右回転軸", &mEyeSets[i].obj);
            mEyeSets[i].axisUD.init(0, "axisUD", "上下回転軸", &mEyeSets[i].obj);
            mEyeSets[i].lTransLimit.init(0.0, "lTransLimit", "左移動量上限", &mEyeSets[i].obj);
            mEyeSets[i].rTransLimit.init(0.0, "rTransLimit", "右移動量上限", &mEyeSets[i].obj);
            mEyeSets[i].dTransLimit.init(0.0, "dTransLimit", "下移動量上限", &mEyeSets[i].obj);
            mEyeSets[i].uTransLimit.init(0.0, "uTransLimit", "上移動量上限", &mEyeSets[i].obj);
            mEyeSets[i].isCorrectForward.init(false, "isCorrectForward", "前方方向を補正する",
                                              &mEyeSets[i].obj);
            mEyeSets[i].axisCorrect.init(0, "axisCorrect", "補正軸", &mEyeSets[i].obj);
            mEyeSets[i].correctRot.init(0.0, "correctRot", "補正量", &mEyeSets[i].obj);
            mEyeSets[i].lRotLimit.init(0.0, "lRotLimit", "左向き角上限", &mEyeSets[i].obj);
            mEyeSets[i].rRotLimit.init(0.0, "rRotLimit", "右向き角上限", &mEyeSets[i].obj);
            mEyeSets[i].dRotLimit.init(0.0, "dRotLimit", "下向き角上限", &mEyeSets[i].obj);
            mEyeSets[i].uRotLimit.init(0.0, "uRotLimit", "上向き角上限", &mEyeSets[i].obj);
            mEyeSets[i].offset.init({0.0, 0.0, 0.0}, "offset", "オフセット", &mEyeSets[i].obj);

            addObj(&mEyeSets[i].obj, name);
        }
    }

    mSpine.isInvalid.init(false, "isInvalid", "無効にする", &mSpine.obj);
    mSpine.isBasisSelfPosNeckLR.init(false, "isBasisSelfPosNeckLR",
                                     "左右計算を自分の位置基準にする", &mSpine.obj);
    mSpine.isBasisSelfPosNeckUD.init(false, "isBasisSelfPosNeckUD",
                                     "上下計算を自分の位置基準にする", &mSpine.obj);
    mSpine.isBattleNeckRecalcUD.init(false, "isBattleNeckRecalcUD",
                                     "戦闘時の首向け上下角を再計算する", &mSpine.obj);
    mSpine.spineDisableBaseDirAlongXZ.init(false, "spineDisableBaseDirAlongXZ",
                                           "基準方向をXZ平面に沿わせない", &mSpine.obj);
    mSpine.spineRotRate.init(0.0, "spineRotRate", "回転比率", &mSpine.obj);
    mSpine.spineRetRotRate.init(0.0, "spineRetRotRate", "戻り回転比率", &mSpine.obj);
    mSpine.spineNeckBaseBone.init("", "spineNeckBaseBone", "首向け基準位置ボーン名", &mSpine.obj);
    mSpine.neckPosOffset.init(sead::Vector3f::zero, "neckPosOffset", "オフセット", &mSpine.obj);
    mSpine.spineNodeNum.init(0, "spineNodeNum", "背骨ノード数", &mSpine.obj);
    mSpine.spineNeckNodeNum.init(0, "spineNeckNodeNum", "首とみなすノード数", &mSpine.obj);
    addObj(&mSpine.obj, "Spine");

    applyResParameterArchive(agl::utl::ResParameterArchive{data});

    const auto spine_node_num = mSpine.spineNodeNum.ref();
    if (spine_node_num > 0) {
        if (!mSpine.spineNodes.tryAllocBuffer(spine_node_num, heap))
            return false;

        for (int i = 0; i < spine_node_num; ++i) {
            sead::FormatFixedSafeString<64> name("");
            name.format("SpineNode_%02d", i);

            mSpine.spineNodes[i].boneName.init("", "boneName", "ボーン名",
                                               &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].isRotWorldAxis.init(
                false, "isRotWorldAxis", "ワールド軸で回転する", &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].axisLR.init(0, "axisLR", "左右回転軸", &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].axisUD.init(0, "axisUD", "上下回転軸", &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].lLimit.init(0.0, "lLimit", "左向き角上限",
                                             &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].rLimit.init(0.0, "rLimit", "右向き角上限",
                                             &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].dLimit.init(0.0, "dLimit", "下向き角上限",
                                             &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].uLimit.init(0.0, "uLimit", "上向き角上限",
                                             &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].lBattleLimit.init(0.0, "lBattleLimit", "左向き角上限（戦闘時）",
                                                   &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].rBattleLimit.init(0.0, "rBattleLimit", "右向き角上限（戦闘時）",
                                                   &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].dBattleLimit.init(0.0, "dBattleLimit", "下向き角上限（戦闘時）",
                                                   &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].uBattleLimit.init(0.0, "uBattleLimit", "上向き角上限（戦闘時）",
                                                   &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].minRotPerFrame.init(
                0.5, "minRotPerFrame", "フレーム毎の最小回転量", &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].maxRotPerFrame.init(
                6.0, "maxRotPerFrame", "フレーム毎の最大回転量", &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].isEnableCorrect.init(
                false, "isEnableCorrect", "左右回転時に補正する", &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].axisCorrect.init(0, "axisCorrect", "補正回転軸",
                                                  &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].lCorrect.init(0.0, "lCorrect", "左向き補正回転量",
                                               &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].rCorrect.init(0.0, "rCorrect", "右向き補正回転量",
                                               &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].lBattleCorrect.init(
                0.0, "lBattleCorrect", "左向き補正回転量（戦闘時）", &mSpine.spineNodes[i].obj);
            mSpine.spineNodes[i].rBattleCorrect.init(
                0.0, "rBattleCorrect", "右向き補正回転量（戦闘時）", &mSpine.spineNodes[i].obj);

            addObj(&mSpine.spineNodes[i].obj, name);
        }
    }

    mFootIkController.isInvalidFt.init(true, "isInvalidFt", "無効", &mFootIkController.obj);
    mFootIkController.calculateTypeFt.init(1, "calculateTypeFt", "計算タイプ",
                                           &mFootIkController.obj);
    mFootIkController.ankleOffsetYFt.init(0.125, "ankleOffsetYFt", "地面から足首(Ankle)までの高さ",
                                          &mFootIkController.obj);
    mFootIkController.ankleOffsetAngleDegFt.init(-27.0, "ankleOffsetAngleDegFt",
                                                 "足首オフセット角度(Deg)", &mFootIkController.obj);
    mFootIkController.ankleAngleLimitUpDegFt.init(
        90.0, "ankleAngleLimitUpDegFt", "上方向への足首回転最大角度(Deg)", &mFootIkController.obj);
    mFootIkController.ankleAngleLimitDownDegFt.init(-90.0, "ankleAngleLimitDownDegFt",
                                                    "下方向への足首回転最大角度(Deg)",
                                                    &mFootIkController.obj);
    mFootIkController.ankleHeightLimitRateFt.init(
        0.8, "ankleHeightLimitRateFt", "地面に対して足位置の制限比率", &mFootIkController.obj);
    mFootIkController.waistDownRateFt.init(0.7, "waistDownRateFt", "腰を落とす最長比率",
                                           &mFootIkController.obj);
    mFootIkController.kneeRotateAgnleMinDegFt.init(
        0.0, "kneeRotateAgnleMinDegFt", "ヒザの最小回転角度(Deg)", &mFootIkController.obj);
    mFootIkController.kneeRotateAgnleMaxDegFt.init(
        180.0, "kneeRotateAgnleMaxDegFt", "ヒザの最大回転角度(Deg)", &mFootIkController.obj);
    mFootIkController.enableLimitThighAngleFt.init(
        false, "enableLimitThighAngleFt", "モモの角度制限を行なうか?", &mFootIkController.obj);
    mFootIkController.thighRotateAngleMinDegFt.init(
        -180.0, "thighRotateAngleMinDegFt", "モモの最小回転角度(Deg)", &mFootIkController.obj);
    mFootIkController.thighRotateAngleMaxDegFt.init(
        180.0, "thighRotateAngleMaxDegFt", "モモの最大回転角度(Deg)", &mFootIkController.obj);
    addObj(&mFootIkController.obj, "FootIkController");

    const auto bone_groups = agl::utl::getResParameterList(root, "BoneGroups");
    if (bone_groups.ptr() && bone_groups.getResParameterListNum() != 0) {
        if (!mBoneGroups.tryAllocBuffer(bone_groups.getResParameterListNum(), heap))
            return false;

        sead::FixedSafeString<32> bone_group_name{"BoneGroup_"};
        const auto bone_group_name_base_len = bone_group_name.calcLength();

        sead::FixedSafeString<32> bone_name{"Bone_"};
        const auto bone_name_base_len = bone_name.calcLength();

        for (auto it = mBoneGroups.begin(), end = mBoneGroups.end(); it != end; ++it) {
            const auto list = bone_groups.getResParameterList(it.getIndex());
            if (!list.ptr())
                continue;

            const auto bones = agl::utl::getResParameterObj(list, "Bones");
            if (!bones.ptr())
                continue;

            it->groupName.init("", "GroupName", "グループ名", &it->paramObj);

            const auto num_bones = bones.getNum();
            if (num_bones != 0 && !it->bones.tryAllocBuffer(num_bones, heap))
                return false;

            auto& bones_obj = it->bonesObj;
            for (auto b = it->bones.begin(), bone_end = it->bones.end(); b != bone_end; ++b) {
                bone_name.trim(bone_name_base_len);
                bone_name.appendWithFormat("%d", b.getIndex());
                b->name.init("", bone_name, "ボーン名", &bones_obj);
            }

            it->list.addObj(&bones_obj, "Bones");
            it->list.addObj(&it->paramObj, "Param");

            bone_group_name.trim(bone_group_name_base_len);
            bone_group_name.appendWithFormat("%d", it.getIndex());
            mBoneGroupsList.addList(&it->list, bone_group_name);
        }

        addList(&mBoneGroupsList, "BoneGroups");
    }

    applyResParameterArchive(agl::utl::ResParameterArchive{data});
    return true;
}

const BoneControl::BoneGroup* BoneControl::getBoneGroup(const sead::SafeString& name) const {
    const auto idx = mBoneGroups.binarySearch(
        name, +[](const BoneGroup& group, const sead::SafeString& key) {
            return group.groupName.ref().compare(key);
        });
    if (idx == -1)
        return nullptr;
    return &mBoneGroups[idx];
}

}  // namespace ksys::res
