#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <prim/seadStorageFor.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

// FIXME: incomplete
class ModelList : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(ModelList, Resource)
public:
    struct ControllerInfo {
        agl::utl::Parameter<sead::Color4f> _2b0;
        agl::utl::Parameter<sead::Color4f> _2d8;
        agl::utl::ParameterObj mControllerInfo;
        agl::utl::Parameter<sead::Vector3f> mBaseScale;
        agl::utl::Parameter<sead::SafeString> _358;
        agl::utl::Parameter<s32> _380;
        agl::utl::Parameter<sead::SafeString> _3a0;
        agl::utl::Parameter<s32> _3c8;
        agl::utl::Parameter<sead::SafeString> _3e8;
    };
    KSYS_CHECK_SIZE_NX150(ControllerInfo, 0x160);

    struct Attention {
        agl::utl::Parameter<bool> _0;
        agl::utl::Parameter<sead::SafeString> _20;
        agl::utl::Parameter<sead::Vector3f> _48;
        agl::utl::Parameter<f32> _70;
        agl::utl::Parameter<f32> _90;
        agl::utl::Parameter<sead::SafeString> _b0;
        agl::utl::Parameter<sead::Vector3f> _d8;
        agl::utl::Parameter<sead::SafeString> _100;
        agl::utl::Parameter<sead::Vector3f> _128;
        agl::utl::Parameter<sead::SafeString> _150;
        agl::utl::Parameter<sead::Vector3f> _178;
        agl::utl::Parameter<sead::SafeString> _1a0;
        agl::utl::Parameter<sead::Vector3f> _1c8;
        agl::utl::Parameter<f32> _1f0;
        agl::utl::Parameter<sead::SafeString> _210;
        agl::utl::Parameter<sead::Vector3f> _238;
        agl::utl::Parameter<bool> _260;
        agl::utl::Parameter<sead::SafeString> _280;
        agl::utl::Parameter<sead::Vector3f> _2a8;
        agl::utl::ParameterObj _2d0;
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

    ModelList();
    ~ModelList() override;

    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;
    bool needsParse() const override { return true; }
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

    const ControllerInfo& getControllerInfo() const { return mControllerInfo.ref(); }
    const Attention& getAttention() const { return mAttention.ref(); }
    const sead::Buffer<ModelData>& getModelData() const { return mModelData; }
    const sead::Buffer<AnmTarget>& getAnmTargets() const { return mAnmTargets; }
    bool is7C8() const { return _7c8; }

private:
    sead::StorageFor<ControllerInfo> mControllerInfo{sead::ZeroInitializeTag{}};
    sead::StorageFor<Attention> mAttention{sead::ZeroInitializeTag{}};
    u8* mRawData{};
    sead::Buffer<ModelData> mModelData;
    agl::utl::ParameterList mModelDataList;
    sead::Buffer<AnmTarget> mAnmTargets;
    agl::utl::ParameterList mAnmTargetList;
    bool _7c8 = false;
};
KSYS_CHECK_SIZE_NX150(ModelList, 0x7d0);

}  // namespace ksys::res
