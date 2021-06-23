#include "KingSystem/Quest/qstStep.h"
#include <memory>
#include "KingSystem/Quest/qstActorData.h"
#include "KingSystem/Quest/qstIndicator.h"

namespace ksys::qst {

// NON_MATCHING: regalloc
Step::Step(const u8** iter_data, sead::Heap* heap) : heap(heap) {
    if (*iter_data != nullptr) {
        iter = new (heap, std::nothrow_t()) al::ByamlIter(*iter_data);
    }
}

bool Step::sub_7100FDB89C(act::Actor* actor) const {
    for (int i = 0; i < links.size(); ++i) {
        if (!links[i]->link.hasProc())
            continue;
        if (links[i]->link.hasProcById(actor))
            return true;
    }
    return false;
}

bool Step::sub_7100FDB538(act::Actor* actor, const sead::SafeString& name) const {
    if (actor == nullptr)
        return false;
    if (!_28)
        return true;

    for (int i = 0; i < links.size(); ++i) {
        sead::SafeString actName(actor->getName());
        sead::SafeString uniqName(actor->getUniqueName());
        if (actName != links[i]->name)
            continue;

        if (uniqName != links[i]->unique_name)
            continue;

        if (links[i]->sub_71012B43D0(actor, name)) {
            return true;
        }
    }
    return false;
}

bool Step::initActorData([[maybe_unused]] u32 unused, sead::BufferedSafeString* out_message) {
    if (actor_data != nullptr) {
        // The photo object has already been created.
        out_message->format("写真対象は既に作成されています。");
        return false;
    }

    actor_data = new (heap, std::nothrow_t()) ActorData(heap);
    if (actor_data == nullptr) {
        // Due to insufficient memory, photo data could not be created.
        out_message->format("メモリ不足のため、写真情報を作成できませんでした。");
        return false;
    }
    return actor_data->init(iter, out_message);
}

bool Step::initIndicator([[maybe_unused]] u32 unused, sead::BufferedSafeString* out_message) {
    if (indicator_info != nullptr) {
        // The indicator information has already been created.
        out_message->format("光点情報は既に作成されています。");
        return false;
    }

    indicator_info = new (heap, std::nothrow_t()) Indicator(this, heap);
    if (indicator_info == nullptr) {
        // Due to insufficient memory, indicator information could not be created.
        out_message->format("メモリ不足のため、光点情報を作成できませんでした。");
        return false;
    }
    return indicator_info->init(iter, out_message);
}

bool Step::sub_7100FDC2A4(al::ByamlIter* iter) {
    al::ByamlIter evt_iter;
    al::ByamlIter trg_iter;
    const char* value;

    if (!iter->tryGetIterByKey(&evt_iter, "TriggerEvents"))
        return false;

    for (int i = 0; i < evt_iter.getSize(); ++i) {
        if (evt_iter.tryGetIterByIndex(&trg_iter, i) && trg_iter.isValid() &&
            trg_iter.tryGetStringByKey(&value, "Trigger")) {
            if (sead::SafeString("StepStart") == value)
                return true;
        }
    }
    return false;
}

}  // namespace ksys::qst
