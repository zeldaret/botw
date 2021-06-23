
#include "KingSystem/Quest/qstManager.h"
#include "KingSystem/Quest/qstActorData.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::qst {

SEAD_SINGLETON_DISPOSER_IMPL(Manager)

Manager::~Manager() {
    cleanUp();
    util::safeDeleteHeap(mHeap);
}

void Manager::init(sead::Heap* heap) {
    if (sDisable)
        return;

    mHeap = util::DualHeap::tryCreate(0x99999, "QuestHeap", heap, util::getDebugHeap(), 8,
                                      sead::Heap::cHeapDirection_Forward, true);
    cleanUp();

    _e4 = -0x51;
    mFlags = 0;
    _28 = _2c;
    _2c = 0;
    _30 = 0;
}

void Manager::cleanUp() {
    _44 = 0;
    _48.freeBuffer();
    mQuests.freeBuffer();
    mHandle.unloadAndResetUnitFlag20000();
}

bool Manager::isQuestActor(act::Actor* actor) const {
    for (int i = 0; i < mQuests.size(); ++i) {
        const auto* quest = mQuests[i];
        if (quest->x_6(actor))
            return true;
    }
    return false;
}

// NON_MATCHING: leftovers from a stripped debug function
void Manager::auto0(act::Actor* actor) {
    if (actor == nullptr)
        return;

    for (int i = 0; i < mQuests.size(); ++i) {
        Quest* quest = mQuests[i];
        if (quest->_c != 2 && quest->flagStuff())
            quest->x_9(actor);
    }
}

bool Manager::auto4(act::Actor* actor) const {
    auto end = mQuests.end();
    for (auto it = mQuests.begin(); it != end; ++it) {
        if (it->_c != 2 && it->flagStuff() && !it->x_8(actor))
            return false;
    }
    return true;
}

// NON_MATCHING: loops are nonmatching
bool Manager::sub_7100FD78F8() {
    s32 size = mQuests.size();
    u32 data_count = 0;

    for (int i = 0; i < size; ++i) {
        data_count += mQuests[i]->_148;
    }

    if (data_count == 0)
        return true;
    if (!_48.tryAllocBuffer(data_count, mHeap, 8))
        return false;

    for (int i = 0; i < size; ++i) {
        s32 num2 = mQuests[i]->_148;
        for (int j = 0; j < num2; ++j) {
            ActorData* data = mQuests[i]->sub_7100FDA5F8(j);
            if (data != nullptr) {
                _48.pushBack(data);
            }
        }
    }
    return true;
}

bool Manager::sub_7100FD7B30(const sead::SafeString& quest_name, const sead::SafeString& step_name,
                             bool setAocVersionFlag1) {
    return setQuestStep(quest_name, step_name, false, false, setAocVersionFlag1);
}

bool Manager::setQuestStepFromEvent(const sead::SafeString& quest_name,
                                    const sead::SafeString& step_name, bool force_run_telop,
                                    bool setAocVersionFlag1) {
    return setQuestStep(quest_name, step_name, true, force_run_telop, setAocVersionFlag1);
}

// NON_MATCHING: quest is dereferenced several times
bool Manager::setQuestStep(const sead::SafeString& quest_name, const sead::SafeString& step_name,
                           bool copy_name, bool force_run_telop, bool setAocVersionFlag1) {
    u32 hash = sead::HashCRC32::calcStringHash(quest_name.cstr());
    Quest* quest;
    for (auto& q : mQuests) {
        if (q._c - 1 <= 1 && q.mNameHash == hash) {
            quest = &q;
            break;
        }
    }
    if (quest == nullptr)
        return false;

    quest->setField31();

    quest->_e8.copy(step_name);

    quest->_e0 = false;
    quest->mForceRunTelop = false;

    if (copy_name) {
        quest->_e0 = true;
        const char* x = quest->x_11();
        if (step_name.isEmpty())
            quest->_e8.copy(sead::SafeString(x));
    }
    if (force_run_telop)
        quest->mForceRunTelop = true;
    if (setAocVersionFlag1)
        quest->mAocVersionFlags |= 1;
    return true;
}

}  // namespace ksys::qst
