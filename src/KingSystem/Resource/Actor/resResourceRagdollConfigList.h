#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class RagdollConfig;

class RagdollConfigList : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(RagdollConfigList, Resource)
public:
    struct ImpulseParam {
        const char* getFileName() const { return file_name.ref().cstr(); }

        agl::utl::Parameter<sead::SafeString> file_name;
        agl::utl::ParameterObj obj;
        RagdollConfig* config;
    };
    KSYS_CHECK_SIZE_NX150(ImpulseParam, 0x60);

    struct BodyParam : agl::utl::ParameterObj {
        agl::utl::Parameter<sead::SafeString> rigid_name;
        agl::utl::Parameter<f32> friction_scale;
        agl::utl::Parameter<f32> buoyancy_scale;
    };
    KSYS_CHECK_SIZE_NX150(BodyParam, 0x98);

    RagdollConfigList();
    ~RagdollConfigList() override;
    RagdollConfigList(const RagdollConfigList&) = delete;
    auto operator=(const RagdollConfigList&) = delete;

    void doCreate_(u8*, u32, sead::Heap*) override;
    bool needsParse() const override { return true; }
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;
    bool finishParsing_() override;
    bool m7_() override;

    const sead::Buffer<ImpulseParam>& getImpulseParams() const { return mImpulseParams; }
    f32 getUpperLimitHeight() const { return mUpperLimitHeight.ref(); }
    f32 getLowerLimitHeight() const { return mLowerLimitHeight.ref(); }
    const sead::Buffer<BodyParam>& getBodyParams() const { return mBodyParams; }

    void addImpulseParamConfig_(s32 index, RagdollConfig* config) {
        mImpulseParams[index].config = config;
    }

private:
    agl::utl::ParameterList mImpulseParamList;
    sead::Buffer<ImpulseParam> mImpulseParams;

    agl::utl::ParameterObj mCommonData;
    agl::utl::Parameter<f32> mUpperLimitHeight;
    agl::utl::Parameter<f32> mLowerLimitHeight;

    agl::utl::ParameterList mBodyParamList;
    sead::Buffer<BodyParam> mBodyParams;
};
KSYS_CHECK_SIZE_NX150(RagdollConfigList, 0x3d0);

}  // namespace ksys::res
