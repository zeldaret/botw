#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAttention.h"
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class AttClient : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(AttClient, Resource)
public:
    struct Check {};

    AttClient() : ParamIO("atcl", 0) {}
    ~AttClient() override;

    act::AttType getAttType() const { return mAttType; }
    act::AttActionCode getActionCode() const { return mActionCode; }
    act::AttPriorityType getPriorityType() const { return mPriorityType; }
    const sead::SafeString& getPriorityTypeStr() const { return mPriorityTypeStr; }
    const sead::Buffer<Check*>& getChecks() const { return mChecks; }

    void doCreate_(u8*, u32, sead::Heap*) override {}
    bool needsParse() const override { return true; }
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

private:
    act::AttType mAttType = act::AttType::Action;
    act::AttActionCode mActionCode = act::AttActionCode::None;
    act::AttPriorityType mPriorityType = act::AttPriorityType::Default;
    sead::FixedSafeString<32> mPriorityTypeStr;
    agl::utl::ParameterObj mAttClientParamsObj;
    agl::utl::Parameter<sead::FixedSafeString<32>> mAttTypeParam;
    agl::utl::Parameter<sead::FixedSafeString<32>> mActionTypeParam;
    agl::utl::Parameter<sead::FixedSafeString<32>> mPriorityTypeParam;
    sead::Buffer<Check*> mChecks;
};
KSYS_CHECK_SIZE_NX150(AttClient, 0x428);

}  // namespace ksys::res
