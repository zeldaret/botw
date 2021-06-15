#include "KingSystem/Resource/Actor/resResourceRagdollBlendWeight.h"

namespace ksys::res {

void RagdollBlendWeight::doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) {}

bool RagdollBlendWeight::parse_(u8* data, size_t size, sead::Heap* heap) {
    if (!data)
        return false;

    using FormatString = sead::FormatFixedSafeString<32>;

    agl::utl::ResParameterArchive archive{data};
    const auto root = archive.getRootList();
    const auto num_states = root.getResParameterListNum();

    if (num_states != 0) {
        mStates.allocBufferAssert(num_states, heap);

        int state_idx = 1;
        for (auto it = mStates.begin(), end = mStates.end(); it != end; ++it) {
            const auto State =
                agl::utl::getResParameterList(root, FormatString("%s%d", "State_", state_idx));

            if (State) {
                it->state_key.init("", "StateKey", "ステートキー", "", &it->setting_obj);
                it->system_key.init("", "SystemKey", "システムキー", "", &it->setting_obj);

                const auto InputWeightList =
                    agl::utl::getResParameterList(State, "InputWeightList");

                if (int num_weights; InputWeightList &&
                                     (num_weights = InputWeightList.getResParameterObjNum()) != 0) {
                    it->input_weights.allocBufferAssert(num_weights, heap);

                    int weight_idx = 1;
                    for (auto wit = it->input_weights.begin(), wend = it->input_weights.end();
                         wit != wend; ++wit) {
                        wit->rigid_name.init("", "RigidName", "ボーン名", "", &wit->obj);
                        wit->blend_rate.init(1.0, "BlendRate", "ブレンド率", "", &wit->obj);

                        it->input_weight_list.addObj(
                            &wit->obj, FormatString("%s%d", "InputWeight_", weight_idx));
                        ++weight_idx;
                    }
                }
            }

            it->list.addObj(&it->setting_obj, FormatString("Setting"));
            it->list.addList(&it->input_weight_list, FormatString("InputWeightList"));

            addList(&it->list, FormatString("%s%d", "State_", state_idx));
            ++state_idx;
        }
    }

    applyResParameterArchive(archive);
    return true;
}

const sead::SafeString& RagdollBlendWeight::getWeightRigidName(int state_idx,
                                                               int weight_idx) const {
    return mStates[state_idx].input_weights[weight_idx].rigid_name.ref();
}

float RagdollBlendWeight::getWeightBlendRate(int state_idx, int weight_idx) const {
    return mStates[state_idx].input_weights[weight_idx].blend_rate.ref();
}

int RagdollBlendWeight::findStateIdx(const sead::SafeString& key) const {
    for (int i = 0; i < mStates.size(); ++i) {
        if (mStates[i].state_key.ref() == key)
            return i;
    }
    return -1;
}

}  // namespace ksys::res
