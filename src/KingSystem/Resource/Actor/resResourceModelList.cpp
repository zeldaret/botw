#include "KingSystem/Resource/Actor/resResourceModelList.h"
#include <container/seadSafeArray.h>
#include "KingSystem/Resource/resModelResourceDivide.h"

namespace ksys::res {

namespace {
sead::SafeString str_ModelData{"ModelData"};
sead::SafeString str_Unit{"Unit"};
sead::SafeString str_AnmTarget{"AnmTarget"};
sead::SafeString str_Partial{"Partial"};

sead::SafeArray<const char*, 6> sLocatorTypes{{
    "Trunk",
    "Branch",
    "GlowStone",
    "OnTree",
    "MagnePos",
    "StopTimerPos",
}};

constexpr u32 NumUnitMax = 8;
}  // namespace

ModelList::ModelList() : ParamIO("modellist", 0) {}

ModelList::~ModelList() {
    for (auto& entry : mModelData)
        entry.units.freeBuffer();
    mModelData.freeBuffer();

    for (auto& entry : mAnmTargets)
        entry.partials.freeBuffer();
    mAnmTargets.freeBuffer();
}

void ModelList::doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) {}

// NON_MATCHING: reorderings
bool ModelList::parse_(u8* data, size_t size, sead::Heap* heap) {
    agl::utl::ResParameterArchive archive{data};
    const auto root = archive.getRootList();

    const auto model_data_list = agl::utl::getResParameterList(root, str_ModelData);
    if (model_data_list.ptr() && model_data_list.getResParameterListNum() > 0) {
        if (!parseModelData(model_data_list, heap))
            return false;
    }
    addList(&mModelDataList, str_ModelData);

    const auto anm_target_list = agl::utl::getResParameterList(root, str_AnmTarget);
    if (anm_target_list.ptr() && anm_target_list.getResParameterListNum() > 0) {
        if (!parseAnmTarget(anm_target_list, heap))
            return false;
    }
    addList(&mAnmTargetList, str_AnmTarget);

    mControllerInfo->mAddColor.init({0.0, 0.0, 0.0, 0.0}, "AddColor", "", &mControllerInfo->mObj);
    mControllerInfo->mMulColor.init({1.0, 1.0, 1.0, 1.0}, "MulColor", "", &mControllerInfo->mObj);
    mControllerInfo->mBaseScale.init(sead::Vector3f::ones, "BaseScale", "", &mControllerInfo->mObj);
    mControllerInfo->mVariationMatAnim.init("", "VariationMatAnim", "", &mControllerInfo->mObj);
    mControllerInfo->mVariationMatAnimFrame.init(0, "VariationMatAnimFrame", "",
                                                 &mControllerInfo->mObj);
    mControllerInfo->mVariationShaderAnim.init("", "VariationShaderAnim", "",
                                               &mControllerInfo->mObj);
    mControllerInfo->mVariationShaderAnimFrame.init(0, "VariationShaderAnimFrame", "",
                                                    &mControllerInfo->mObj);
    mControllerInfo->mCalcAABBASKey.init("Wait", "CalcAABBASKey", "", &mControllerInfo->mObj);
    addObj(&mControllerInfo->mObj, sead::FormatFixedSafeString<128>("ControllerInfo"));

    mAttention->mIsEnableAttention.init(false, "IsEnableAttention", "", &mAttention->mObj);
    mAttention->mLookAtBone.init("", "LookAtBone", "", &mAttention->mObj);
    mAttention->mLookAtOffset.init(sead::Vector3f::zero, "LookAtOffset", "", &mAttention->mObj);
    mAttention->mCursorOffsetY.init(0.0, "CursorOffsetY", "", &mAttention->mObj);
    mAttention->mAIInfoOffsetY.init(0.0, "AIInfoOffsetY", "", &mAttention->mObj);
    mAttention->mCutTargetBone.init("", "CutTargetBone", "", &mAttention->mObj);
    mAttention->mCutTargetOffset.init(sead::Vector3f::zero, "CutTargetOffset", "",
                                      &mAttention->mObj);
    mAttention->mGameCameraBone.init("", "GameCameraBone", "", &mAttention->mObj);
    mAttention->mGameCameraOffset.init(sead::Vector3f::zero, "GameCameraOffset", "",
                                       &mAttention->mObj);
    mAttention->mBowCameraBone.init("", "BowCameraBone", "", &mAttention->mObj);
    mAttention->mBowCameraOffset.init(sead::Vector3f::zero, "BowCameraOffset", "",
                                      &mAttention->mObj);
    mAttention->mAttackTargetBone.init("", "AttackTargetBone", "", &mAttention->mObj);
    mAttention->mAttackTargetOffset.init(sead::Vector3f::zero, "AttackTargetOffset", "",
                                         &mAttention->mObj);
    mAttention->mAttackTargetOffsetBack.init(0.0, "AttackTargetOffsetBack", "", &mAttention->mObj);
    mAttention->mAtObstacleChkUseLookAtPos.init(true, "AtObstacleChkUseLookAtPos", "",
                                                &mAttention->mObj);
    mAttention->mAtObstacleChkOffsetBone.init("", "AtObstacleChkOffsetBone", "", &mAttention->mObj);
    mAttention->mAtObstacleChkOffset.init(sead::Vector3f::zero, "AtObstacleChkOffset", "",
                                          &mAttention->mObj);
    mAttention->mCursorAIInfoBaseBone.init("", "CursorAIInfoBaseBone", "", &mAttention->mObj);
    mAttention->mCursorAIInfoBaseOffset.init(sead::Vector3f::zero, "CursorAIInfoBaseOffset", "",
                                             &mAttention->mObj);
    addObj(&mAttention->mObj, sead::FormatFixedSafeString<128>("Attention"));

    if (data) {
        applyResParameterArchive(agl::utl::ResParameterArchive{data});
        mRawData = data;
    }

    return true;
}

bool ModelList::parseModelData(const agl::utl::ResParameterList& res, sead::Heap* heap) {
    if (!mModelData.tryAllocBuffer(res.getResParameterListNum() != 0, heap))
        return false;

    sead::FixedSafeString<32> list_name{str_ModelData};
    list_name.append("_");
    const auto list_name_base_len = list_name.calcLength();

    for (auto it = mModelData.begin(), it_end = mModelData.end(); it != it_end; ++it) {
        list_name.trim(list_name_base_len);
        list_name.appendWithFormat("%d", it.getIndex());

        it->folder.init("", "Folder", "", &it->base_obj);
        it->list.addObj(&it->base_obj, "Base");

        const auto unit_list =
            agl::utl::getResParameterList(res.getResParameterList(it.getIndex()), str_Unit);
        if (unit_list.ptr()) {
            const u32 num_units = unit_list.getResParameterObjNum();
            if (num_units != 0) {
                if (!it->units.tryAllocBuffer(std::min(num_units, NumUnitMax), heap))
                    return false;

                sead::FixedSafeString<32> unit_name{str_Unit};
                unit_name.append("_");
                const auto unit_name_base_len = unit_name.calcLength();

                for (auto unit = it->units.begin(), end = it->units.end(); unit != end; ++unit) {
                    unit_name.trim(unit_name_base_len);
                    unit_name.appendWithFormat("%d", unit.getIndex());

                    unit->unit_name.init("", "UnitName", "", &unit->obj);
                    unit->bind_bone.init("", "BindBone", "", &unit->obj);
                    it->unit_list.addObj(&unit->obj, unit_name);
                }
            }
        }

        it->list.addList(&it->unit_list, str_Unit);
        mModelDataList.addList(&it->list, list_name);
    }

    return true;
}

bool ModelList::parseAnmTarget(const agl::utl::ResParameterList& res, sead::Heap* heap) {
    if (!mAnmTargets.tryAllocBuffer(std::min<u32>(res.getResParameterListNum(), NumUnitMax), heap))
        return false;

    sead::FixedSafeString<32> list_name{str_AnmTarget};
    list_name.append("_");
    const auto list_name_base_len = list_name.calcLength();

    for (auto it = mAnmTargets.begin(), it_end = mAnmTargets.end(); it != it_end; ++it) {
        list_name.trim(list_name_base_len);
        list_name.appendWithFormat("%d", it.getIndex());

        it->num_as_slot.init(0, "NumASSlot", "", &it->base_obj);
        // "is particle enabled" (particle is misspelled as "partical" [sic])
        it->is_partical_enable.init(false, "IsParticalEnable", "", &it->base_obj);
        it->target_type.init(0, "TargetType", "", &it->base_obj);
        it->list.addObj(&it->base_obj, "Base");

        const auto partials =
            agl::utl::getResParameterList(res.getResParameterList(it.getIndex()), str_Partial);
        if (partials.ptr() && partials.getResParameterObjNum() != 0) {
            if (!it->partials.tryAllocBuffer(partials.getResParameterObjNum(), heap))
                return false;

            sead::FixedSafeString<32> partial_name{str_Partial};
            partial_name.append("_");
            const auto partial_name_base_len = partial_name.calcLength();

            for (auto partial = it->partials.begin(), partial_end = it->partials.end();
                 partial != partial_end; ++partial) {
                partial_name.trim(partial_name_base_len);
                partial_name.appendWithFormat("%d", partial.getIndex());

                partial->bone.init("", "Bone", "", &partial->obj);
                partial->bind_flag.init(0, "BindFlg", "", &partial->obj);
                partial->recursible.init(true, "Recursible", "", &partial->obj);
                it->partial_list.addObj(&partial->obj, partial_name);
            }
        }

        it->list.addList(&it->partial_list, str_Partial);
        mAnmTargetList.addList(&it->list, list_name);
    }

    return true;
}

int ModelList::getNumAnmTargets() const {
    return mAnmTargets.size();
}

void ModelList::getModelDataInfo(ModelList::ModelDataInfo* info) const {
    *info = {};

    if (mModelData.size() > 0) {
        info->num_model_data = mModelData.size();
        for (auto it = mModelData.begin(), end = mModelData.end(); it != end; ++it) {
            const s32 idx = it.getIndex();

            info->folder_name[idx] = it->folder.ref().cstr();
            info->num_units[idx] = it->units.size();

            for (auto unit = it->units.begin(), uend = it->units.end(); unit != uend; ++unit) {
                const s32 unit_idx = unit.getIndex();
                info->unit_names[idx][unit_idx] = unit->unit_name.ref().cstr();
                info->unit_bind_bones[idx][unit_idx] = unit->bind_bone.ref().cstr();
            }

            if (info->unit_names[idx][0]) {
                const char* name = ModelResourceDivide::instance()->getModelResource(
                    info->folder_name[idx], info->unit_names[idx][0]);
                if (name)
                    info->folder_name[idx] = name;
            }
        }
    }

    info->base_scale = mControllerInfo->mBaseScale.ref();
}

bool ModelList::getAttentionInfo(AttentionInfo* info) const {
    if (!mAttention->mIsEnableAttention.ref()) {
        info->look_at_bone = {};
        info->look_at_offset = sead::Vector3f::zero;

        info->cursor_offset_y = {};
        info->ai_info_offset_y = {};

        info->cut_target_bone = {};
        info->cut_target_offset = sead::Vector3f::zero;

        info->game_camera_bone = {};
        info->game_camera_offset = sead::Vector3f::zero;

        info->bow_camera_bone = {};
        info->bow_camera_offset = sead::Vector3f::zero;

        info->attack_target_bone = {};
        info->attack_target_offset = sead::Vector3f::zero;
        info->attack_target_offset_back = {};

        info->cursor_ai_info_base_bone = {};
        info->cursor_ai_info_base_offset = sead::Vector3f::zero;

        return false;
    }

    info->look_at_bone = mAttention->mLookAtBone.ref().cstr();
    info->look_at_offset = mAttention->mLookAtOffset.ref();

    info->cursor_offset_y = mAttention->mCursorOffsetY.ref();
    info->ai_info_offset_y = mAttention->mAIInfoOffsetY.ref();

    info->cut_target_bone = mAttention->mCutTargetBone.ref().cstr();
    info->cut_target_offset = mAttention->mCutTargetOffset.ref();

    info->game_camera_bone = mAttention->mGameCameraBone.ref().cstr();
    info->game_camera_offset = mAttention->mGameCameraOffset.ref();

    info->bow_camera_bone = mAttention->mBowCameraBone.ref().cstr();
    info->bow_camera_offset = mAttention->mBowCameraOffset.ref();

    info->attack_target_bone = mAttention->mAttackTargetBone.ref().cstr();
    info->attack_target_offset = mAttention->mAttackTargetOffset.ref();
    info->attack_target_offset_back = mAttention->mAttackTargetOffsetBack.ref();

    if (mAttention->mAtObstacleChkUseLookAtPos.ref()) {
        info->at_obstacle_chk_bone = mAttention->mLookAtBone.ref().cstr();
        info->at_obstacle_chk_offset = mAttention->mLookAtOffset.ref();
    } else {
        info->at_obstacle_chk_bone = mAttention->mAtObstacleChkOffsetBone.ref().cstr();
        info->at_obstacle_chk_offset = mAttention->mAtObstacleChkOffset.ref();
    }

    info->cursor_ai_info_base_bone = mAttention->mCursorAIInfoBaseBone.ref().cstr();
    info->cursor_ai_info_base_offset = mAttention->mCursorAIInfoBaseOffset.ref();

    const auto clear_if_empty = [](const char** s) {
        if (!(*s)[0])
            *s = nullptr;
    };

    clear_if_empty(&info->look_at_bone);
    clear_if_empty(&info->cut_target_bone);
    clear_if_empty(&info->game_camera_bone);
    clear_if_empty(&info->bow_camera_bone);
    clear_if_empty(&info->attack_target_bone);
    clear_if_empty(&info->at_obstacle_chk_bone);
    clear_if_empty(&info->cursor_ai_info_base_bone);

    return true;
}

act::InfoData::Locator::Type ModelList::getLocatorTypeFromStr(const sead::SafeString& type) {
    for (s32 i = 0; i < sLocatorTypes.size(); ++i) {
        if (type == sLocatorTypes[i])
            return act::InfoData::Locator::Type(i);
    }
    return act::InfoData::Locator::Type::Invalid;
}

// NON_MATCHING: weird unrolling and Vector3f store (str should be a stp)
bool ModelList::getLocatorInfo(act::InfoData::Locator* info,
                               act::InfoData::Locator::Type type) const {
    agl::utl::ResParameterArchive archive{mRawData};
    const auto root = archive.getRootList();

    for (int i = 0;; ++i) {
        const auto obj =
            agl::utl::getResParameterObj(root, sead::FormatFixedSafeString<32>("Locator_%d", i));
        if (!obj.ptr())
            return false;

        const char* expected_type_str = sLocatorTypes[u32(type)];

        if (sead::SafeString(getString(obj, "Type", "")) != expected_type_str)
            continue;

        info->pos = getVec3(obj, "Pos", sead::Vector3f::zero);
        info->rot = getVec3(obj, "Rot", sead::Vector3f::zero);
        info->type = type;
        return true;
    }

    return false;
}

bool ModelList::isParticalEnable(int anm_target_idx) const {
    return mAnmTargets[anm_target_idx].is_partical_enable.ref();
}

int ModelList::getNumASSlot(int anm_target_idx) const {
    return mAnmTargets[anm_target_idx].num_as_slot.ref();
}

int ModelList::getNumPartials(int anm_target_idx) const {
    return mAnmTargets[anm_target_idx].partials.size();
}

void ModelList::getPartialInfo(PartialInfo* info, int anm_target_idx, int partial_idx) const {
    if (mAnmTargets.size() > 0) {
        const auto& partial = mAnmTargets[anm_target_idx].partials[partial_idx];
        info->bone = partial.bone.ref();
        info->bind_flag = partial.bind_flag.ref();
        info->recursible = partial.recursible.ref();
    } else {
        info->bone = "";
        info->bind_flag = 0;
        info->recursible = true;
    }
}

}  // namespace ksys::res
