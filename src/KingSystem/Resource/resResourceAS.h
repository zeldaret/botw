#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class AS : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(AS, Resource)
public:
    struct Element {};

    AS();

    void doCreate_(u8*, u32, sead::Heap*) override {}
    bool needsParse() const override { return true; }
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;
    void finalize_() override;

private:
    friend class ASList;

    sead::Buffer<Element*> mElements;
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
