#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

class RagdollBlendWeight : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(RagdollBlendWeight, Resource)
public:
    struct InputWeight {
        agl::utl::Parameter<sead::SafeString> rigid_name;
        agl::utl::Parameter<float> blend_rate;
        agl::utl::ParameterObj obj;
    };

    struct State {
        agl::utl::ParameterList list;
        agl::utl::Parameter<sead::SafeString> state_key;
        agl::utl::Parameter<sead::SafeString> system_key;
        agl::utl::ParameterObj setting_obj;
        agl::utl::ParameterList input_weight_list;
        sead::Buffer<InputWeight> input_weights;
    };

    RagdollBlendWeight() : ParamIO("rgbw", 0) {}
    ~RagdollBlendWeight() override { mStates.freeBuffer(); }

    const sead::Buffer<State>& getStates() const { return mStates; }

    const sead::SafeString& getWeightRigidName(int state_idx, int weight_idx) const;
    float getWeightBlendRate(int state_idx, int weight_idx) const;
    int findStateIdx(const sead::SafeString& key) const;

    bool ParamIO_m0(char* data) override { return true; }
    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;
    bool needsParse() const override { return true; }
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

private:
    sead::Buffer<State> mStates;
};

}  // namespace ksys::res
