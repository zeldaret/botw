#include "KingSystem/ActorSystem/actAiActionBase.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Resource/resResourceAIProgram.h"

namespace ksys::act::ai {

ActionBase::ActionBase(const InitArg& arg)
    : mActor{arg.actor}, mDefinitionIdx{s16(arg.def_idx)}, mRootIdx{s8(arg.root_idx)} {}

inline res::AIProgram* ActionBase::getAIProg() const {
    return mActor->getParam()->getRes().mAIProgram;
}

bool ActionBase::init(sead::Heap* heap, bool skip_loading_map_or_tree_params) {
    initFlags(getAIProg(), mDefinitionIdx, getType());

    AIDefSet set;
    set.dynamic_params.num_params = 0;
    set.ai_tree_params.num_params = 0;
    if (getType() == ActionType::Action)
        AIClassDef::instance()->getDef(getClassName(), &set, AIDefType::Action);
    else
        AIClassDef::instance()->getDef(getClassName(), &set, AIDefType::AI);

    if (!initChildren(set, heap))
        return false;

    if (!skip_loading_map_or_tree_params) {
        if (!mActor->getRootAi()->loadMapUnitParams(set.map_unit_params, heap))
            return false;
        if (!mActor->getRootAi()->loadAITreeParams(set.ai_tree_params, heap))
            return false;
    }

    if (set.dynamic_params.num_params > 0 && mFlags.isOff(Flag::DynamicParamChild)) {
        if (!mParams.load(*mActor, set.dynamic_params, heap, AIDefInstParamKind::Dynamic))
            return false;
    }

    loadParams_();
    return init_(heap);
}

void ActionBase::initFlags(res::AIProgram* aiprog, s32 def_idx, ActionType type) {
    if (def_idx < 0)
        return;

    if (aiprog->getActionsOrAIs(type)[def_idx].mTriggerAction)
        mFlags.set(Flag::TriggerAction);

    if (aiprog->getActionsOrAIs(type)[def_idx].mDynamicParamChild)
        mFlags.set(Flag::DynamicParamChild);
}

const char* ActionBase::getClassName() const {
    if (mDefinitionIdx < 0) {
        if (mRootIdx < 0)
            return "";
        return getDefaultName(getType(), mRootIdx);
    }

    return getAIProg()->getAction(getType(), mDefinitionIdx).mClassName;
}

bool ActionBase::isRootAiParamINot5() const {
    return mActor->getRootAi()->getI() != 5;
}

bool ActionBase::isActorDeletedOrDeleting() const {
    return mActor->getRootAi()->isActorDeletedOrDeleting();
}

bool ActionBase::isActorGoingBackToRootAi() const {
    return mActor->getRootAi()->mNewChildIdx == 0;
}

void ActionBase::enter(InlineParamPack* params, const sead::SafeString& context) {
    if (getType() == ActionType::Action || (getType() == ActionType::AI && getNumChildren() == 0)) {
        mActor->onAiEnter(getName(), context.cstr());
    }

    resetFlags();
    if (params)
        params->copyToParamPack(mParams);
    updateBehaviorsOnEnter();
    enter_(params);
}

const char* ActionBase::getName() const {
    if (mDefinitionIdx >= 0)
        return getAIProg()->getAction(getType(), mDefinitionIdx).mName;

    if (mRootIdx >= 0)
        return getDefaultName(getType(), mRootIdx);

    return "";
}

void ActionBase::updateBehaviorsOnEnter() {
    if (!mActor)
        return;

    const sead::Buffer<u8>* indices;
    if (mDefinitionIdx < 0) {
        if (mRootIdx != 0 || getType() != ActionType::AI)
            return;
        indices = &getAIProg()->getDemoBehaviorIndices();
    } else {
        indices = &getAIProg()->getAction(getType(), mDefinitionIdx).mBehaviorIndices;
    }

    auto* root = mActor->getRootAi();
    for (auto indice : *indices)
        root->setBehavior(root->getBehaviors().classes[indice]);
}

bool ActionBase::takeOver(ActionBase* src, const sead::SafeString& context) {
    bool ret = false;

    if (src->mDefinitionIdx == mDefinitionIdx && src->mRootIdx == mRootIdx) {
        if (getType() == ActionType::Action)
            mActor->onAiEnter(getName(), context.cstr());

        // Copy the flags.
        mFlags = src->mFlags;

        // Copy the param pack.
        InlineParamPack pack;
        src->copyParams(&pack, true);
        pack.copyToParamPack(mParams);

        // Transition.
        if (auto* child = getCurrentChild())
            child->leave();
        updateBehaviorsOnEnter();
        ret = reenter(src, context);
    }

    mActor->getRootAi()->_16c.set(RootAiFlag::_100);
    return ret;
}

void ActionBase::copyParams(InlineParamPack* dest, bool x) const {
    auto* action = this;
    while (action->mFlags.isOff(Flag::_80)) {
        action->mParams.copy(dest, x);
        if (action->mFlags.isOff(Flag::DynamicParamChild))
            return;
        action = action->getCurrentChild();
        if (!action)
            return;
    }

    for (s32 i = 0, n = action->getNumChildren(); i < n; ++i) {
        action->getChild(i)->copyParams(dest, x);
    }
}

void ActionBase::leave() {
    if (auto* child = getCurrentChild())
        child->leave();

    updateBehaviorsOnLeave();
    leave_();
    postLeave();
}

void ActionBase::setRootAiFlagBit(int bit) {
    mActor->getRootAi()->_16c.set(RootAiFlag(1u << bit));
}

bool ActionBase::reenter_(ActionBase* other, bool x) {
    if (x)
        return true;
    enter_(nullptr);
    mFlags.set(Flag::_40);
    return true;
}

void ActionBase::updateBehaviorsOnLeave() {
    if (!mActor)
        return;

    const sead::Buffer<u8>* indices;
    if (mDefinitionIdx < 0) {
        if (mRootIdx != 0 || getType() != ActionType::AI)
            return;
        indices = &getAIProg()->getDemoBehaviorIndices();
    } else {
        indices = &getAIProg()->getAction(getType(), mDefinitionIdx).mBehaviorIndices;
    }

    auto* root = mActor->getRootAi();
    for (auto indice : *indices)
        root->resetBehavior(root->getBehaviors().classes[indice]);
}

bool ActionBase::oneShot(InlineParamPack* params) {
    if (params)
        params->copyToParamPack(mParams);
    return oneShot_();
}

void ActionBase::setFinished() {
    mFlags.set(Flag::Finished);
    mFlags.reset(Flag::Failed);
}

void ActionBase::setFailed() {
    mFlags.set(Flag::Failed);
    mFlags.reset(Flag::Finished);
}

}  // namespace ksys::act::ai
