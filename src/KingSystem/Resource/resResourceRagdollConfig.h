#pragma once

#include <array>

#include "KingSystem/Physics/Ragdoll/physRagdollConfig.h"
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

class RagdollConfig : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(RagdollConfig, Resource)
public:
    RagdollConfig();
    ~RagdollConfig() override;

    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;
    bool needsParse() const override { return true; }
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

    const phys::RagdollConfig& getConfig() const { return mConfig; }

    static const int cNumReceiveObjs;
    static const int cNumImpulseObjs;
    static const int cNumImpulseParams;
    static const std::array<char, 64> cImpulseParamNames[10];

private:
    phys::RagdollConfig mConfig;
};

}  // namespace ksys::res
