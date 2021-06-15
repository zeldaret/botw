#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class ASResource;

class AS : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(AS, Resource)
public:
    AS();
    ~AS() override;
    AS(const AS&) = delete;
    auto operator=(const AS&) = delete;

    void doCreate_(u8*, u32, sead::Heap*) override;
    bool needsParse() const override { return true; }
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;
    void finalize_() override;

    const sead::Buffer<ASResource*>& getElementResources() const { return mElementResources; }
    const auto& getRandomRateMin() const { return *mRandomRateMin; }
    const auto& getRandomRateMax() const { return *mRandomRateMax; }
    const auto& getForbidPartialDemoAs() const { return *mForbidPartialDemoAS; }
    const auto& getUseIk() const { return *mUseIK; }

    ASResource* getFirstResource() const;
    float getRandomRate() const;

private:
    friend class ASList;

    sead::Buffer<ASResource*> mElementResources;
    agl::utl::ParameterList mElementsList;

    agl::utl::ParameterObj mCommonParams;
    agl::utl::Parameter<f32> mRandomRateMin;
    agl::utl::Parameter<f32> mRandomRateMax;
    agl::utl::Parameter<bool> mForbidPartialDemoAS;
    agl::utl::Parameter<bool> mUseIK;
    u8 _3b8{};
    u8 _3b9{};
    u8 _3ba{};
    u8 _3bb{};
    sead::Heap* mHeap{};
};
KSYS_CHECK_SIZE_NX150(AS, 0x3c8);

}  // namespace ksys::res
