#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include <prim/seadStorageFor.h>
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

class ModelList : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(ModelList, Resource)
public:
    struct ControllerInfo {
        agl::utl::Parameter<sead::Color4f> mAddColor;
        agl::utl::Parameter<sead::Color4f> mMulColor;
        agl::utl::ParameterObj mObj;
        agl::utl::Parameter<sead::Vector3f> mBaseScale;
        agl::utl::Parameter<sead::SafeString> mVariationMatAnim;
        agl::utl::Parameter<s32> mVariationMatAnimFrame;
        agl::utl::Parameter<sead::SafeString> mVariationShaderAnim;
        agl::utl::Parameter<s32> mVariationShaderAnimFrame;
        agl::utl::Parameter<sead::SafeString> mCalcAABBASKey;
    };
    KSYS_CHECK_SIZE_NX150(ControllerInfo, 0x160);

    struct Attention {
        agl::utl::Parameter<bool> mIsEnableAttention;
        agl::utl::Parameter<sead::SafeString> mLookAtBone;
        agl::utl::Parameter<sead::Vector3f> mLookAtOffset;
        agl::utl::Parameter<f32> mCursorOffsetY;
        agl::utl::Parameter<f32> mAIInfoOffsetY;
        agl::utl::Parameter<sead::SafeString> mCutTargetBone;
        agl::utl::Parameter<sead::Vector3f> mCutTargetOffset;
        agl::utl::Parameter<sead::SafeString> mGameCameraBone;
        agl::utl::Parameter<sead::Vector3f> mGameCameraOffset;
        agl::utl::Parameter<sead::SafeString> mBowCameraBone;
        agl::utl::Parameter<sead::Vector3f> mBowCameraOffset;
        agl::utl::Parameter<sead::SafeString> mAttackTargetBone;
        agl::utl::Parameter<sead::Vector3f> mAttackTargetOffset;
        agl::utl::Parameter<f32> mAttackTargetOffsetBack;
        agl::utl::Parameter<sead::SafeString> mAtObstacleChkOffsetBone;
        agl::utl::Parameter<sead::Vector3f> mAtObstacleChkOffset;
        agl::utl::Parameter<bool> mAtObstacleChkUseLookAtPos;
        agl::utl::Parameter<sead::SafeString> mCursorAIInfoBaseBone;
        agl::utl::Parameter<sead::Vector3f> mCursorAIInfoBaseOffset;
        agl::utl::ParameterObj mObj;
    };
    KSYS_CHECK_SIZE_NX150(Attention, 0x300);

    struct Unit {
        agl::utl::Parameter<sead::SafeString> unit_name;
        agl::utl::Parameter<sead::SafeString> bind_bone;
        agl::utl::ParameterObj obj;
    };
    KSYS_CHECK_SIZE_NX150(Unit, 0x80);

    struct ModelData {
        agl::utl::Parameter<sead::SafeString> folder;
        agl::utl::ParameterObj base_obj;
        sead::Buffer<Unit> units;
        agl::utl::ParameterList unit_list;
        agl::utl::ParameterList list;
    };
    KSYS_CHECK_SIZE_NX150(ModelData, 0xf8);

    // Misspelling of "partical", which is a misspelling of "particle"?
    struct Partial {
        agl::utl::Parameter<sead::SafeString> bone;
        agl::utl::Parameter<s32> bind_flag;
        agl::utl::Parameter<bool> recursible;
        agl::utl::ParameterObj obj;
    };
    KSYS_CHECK_SIZE_NX150(Partial, 0x98);

    struct AnmTarget {
        agl::utl::Parameter<s32> num_as_slot;
        agl::utl::Parameter<bool> is_partical_enable;
        agl::utl::Parameter<s32> target_type;
        agl::utl::ParameterObj base_obj;
        sead::Buffer<Partial> partials;
        agl::utl::ParameterList partial_list;
        agl::utl::ParameterList list;
    };
    KSYS_CHECK_SIZE_NX150(AnmTarget, 0x130);

    struct ModelDataInfo {
        std::array<std::array<const char*, 8>, 1> unit_names;
        std::array<std::array<const char*, 8>, 1> unit_bind_bones;
        std::array<int, 1> num_units;
        std::array<const char*, 1> folder_name;
        int num_model_data;
        sead::Vector3f base_scale;
    };
    KSYS_CHECK_SIZE_NX150(ModelDataInfo, 0xa0);

    struct AttentionInfo {
        const char* look_at_bone;
        sead::Vector3f look_at_offset;
        float cursor_offset_y;
        float ai_info_offset_y;
        const char* cut_target_bone;
        sead::Vector3f cut_target_offset;
        const char* game_camera_bone;
        sead::Vector3f game_camera_offset;
        const char* bow_camera_bone;
        sead::Vector3f bow_camera_offset;
        const char* attack_target_bone;
        sead::Vector3f attack_target_offset;
        float attack_target_offset_back;
        const char* at_obstacle_chk_bone;
        sead::Vector3f at_obstacle_chk_offset;
        const char* cursor_ai_info_base_bone;
        sead::Vector3f cursor_ai_info_base_offset;
    };
    KSYS_CHECK_SIZE_NX150(AttentionInfo, 0xb0);

    struct PartialInfo {
        sead::SafeString bone;
        int bind_flag;
        bool recursible;
    };
    KSYS_CHECK_SIZE_NX150(PartialInfo, 0x18);

    ModelList();
    ~ModelList() override;

    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;
    bool needsParse() const override { return true; }
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

    const ControllerInfo& getControllerInfo() const { return mControllerInfo.ref(); }
    const Attention& getAttention() const { return mAttention.ref(); }
    const sead::Buffer<ModelData>& getModelData() const { return mModelData; }
    const sead::Buffer<AnmTarget>& getAnmTargets() const { return mAnmTargets; }

    bool isDummy() const { return mIsDummy; }
    void markAsDummy() { mIsDummy = true; }

    int getNumAnmTargets() const;
    void getModelDataInfo(ModelDataInfo* info) const;
    bool getAttentionInfo(AttentionInfo* info) const;
    bool getLocatorInfo(act::InfoData::Locator* info, act::InfoData::Locator::Type type) const;
    bool isParticalEnable(int anm_target_idx) const;
    int getNumASSlot(int anm_target_idx) const;
    int getNumPartials(int anm_target_idx) const;
    void getPartialInfo(PartialInfo* info, int anm_target_idx, int partial_idx) const;

    static act::InfoData::Locator::Type getLocatorTypeFromStr(const sead::SafeString& type);

private:
    bool parseModelData(const agl::utl::ResParameterList& res, sead::Heap* heap);
    bool parseAnmTarget(const agl::utl::ResParameterList& res, sead::Heap* heap);

    sead::StorageFor<ControllerInfo, true> mControllerInfo{sead::ZeroInitializeTag{}};
    sead::StorageFor<Attention, true> mAttention{sead::ZeroInitializeTag{}};
    u8* mRawData{};
    sead::Buffer<ModelData> mModelData;
    agl::utl::ParameterList mModelDataList;
    sead::Buffer<AnmTarget> mAnmTargets;
    agl::utl::ParameterList mAnmTargetList;
    bool mIsDummy = false;
};
KSYS_CHECK_SIZE_NX150(ModelList, 0x7d0);

}  // namespace ksys::res
