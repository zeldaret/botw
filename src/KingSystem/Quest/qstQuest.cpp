#include "KingSystem/Quest/qstQuest.h"
#include "agl/Utils/aglParameter.h"

namespace ksys::qst {

// chunks missing
Quest::~Quest() {
    mSteps.freeBuffer();
}

// NON_MATCHING
Quest::Quest(const sead::SafeString& name, sead::Heap* heap) : mName(name), mHeap(heap) {
    _8 = 0;
    _c = 0;
    _10 = 0;
    mNameHash = agl::utl::ParameterBase::calcHash(mName);
    mAocVersionFlags = 0;
}

void Quest::initFlags(gdt::Manager* gdm) {
    if (gdm == nullptr)
        return;

    mReady = gdm->getBoolHandle([&] {
        sead::FixedSafeString<64> ready;
        ready.format("%s_Ready", mName.cstr());
        return ready;
    }());

    mCancelled = gdm->getBoolHandle([&] {
        sead::FixedSafeString<64> cancelled;
        cancelled.format("%s_Cancelled", mName.cstr());
        return cancelled;
    }());

    switch (mQuestDependencyFlagType) {
    default:
        mDependencyFlag = gdt::InvalidHandle;
        break;
    case 0:
        mDependencyFlag = gdm->getBoolHandle(mQuestDependencyFlag);
        break;
    case 1:
        mDependencyFlag = gdm->getF32Handle(mQuestDependencyFlag);
        break;
    case 2:
        mDependencyFlag = gdm->getS32Handle(mQuestDependencyFlag);
        break;
    }
}

void Quest::setField31() {
    _31 = 1;
}

bool Quest::x_1() const {
    bool result = false;

    if (gdt::Manager::instance() == nullptr || mCancelled == gdt::InvalidHandle)
        return result;

    gdt::Manager::instance()->getBool(mCancelled, &result, true);
    return result;
}

void Quest::x_3() {
    if (_c == 1 || _c == 2)
        return;

    auto handle = mReady;
    if (handle != ksys::gdt::InvalidHandle) {
        bool result = false;
        auto* gdm = gdt::Manager::instance();
        if (gdm != nullptr) {
            if (gdm->getBool(handle, &result, true); !result)
                gdm->setBool(true, handle);
        }
    }
    _8 = _c;
    _c = 1;
    _10 = 0;
}

bool Quest::x_6(act::Actor* actor) const {
    if (!isStepUnderSize() || !mSteps[_140]->attention_off)
        return false;

    return mSteps[_140]->sub_7100FDB89C(actor);
}

bool Quest::x_7() const {
    if (!isStepUnderSize())
        return false;

    return mSteps[_140]->attention_off;
}

bool Quest::x_8(act::Actor* actor) {
    if (isStepUnderCapacity())
        mSteps[_140]->sub_7100FDB538(actor, mName);

    return true;
}

void Quest::x_9(act::Actor* actor) {
    if (isStepUnderCapacity())
        mSteps[_140]->sub_7100FDB794(actor);
}

const char* Quest::x_11() {
    if (!isNextStepUnderSize())
        return &sead::SafeString::cNullChar;

    return mSteps[_140 + 1]->name;
}

}  // namespace ksys::qst
