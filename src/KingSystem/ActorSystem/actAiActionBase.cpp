#include "KingSystem/ActorSystem/actAiActionBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/Resource/Actor/resResourceAIProgram.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"

namespace ksys::act::ai {

ActionBase::ActionBase(const InitArg& arg)
    : mActor{arg.actor}, mDefinitionIdx{s16(arg.def_idx)}, mRootIdx{s8(arg.root_idx)} {}

inline res::AIProgram* ActionBase::getAIProg() const {
    return mActor->getParam()->getRes().mAIProgram;
}

inline auto& ActionBase::getDef() const {
    return getAIProg()->getAction(getType(), mDefinitionIdx);
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

    return getDef().mClassName;
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
        return getDef().mName;

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
        indices = &getDef().mBehaviorIndices;
    }

    auto* root = mActor->getRootAi();
    for (auto indice : *indices)
        root->setBehavior(root->getBehaviors().getClasses()[indice]);
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

void ActionBase::setRootAiFlagBit(int bit) const {
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
        indices = &getDef().mBehaviorIndices;
    }

    auto* root = mActor->getRootAi();
    for (auto indice : *indices)
        root->resetBehavior(root->getBehaviors().getClasses()[indice]);
}

bool ActionBase::oneShot(InlineParamPack* params) {
    if (params)
        params->copyToParamPack(mParams);
    return oneShot_();
}

res::GParamList* ActionBase::getGParamList() const {
    return mActor->getParam()->getRes().mGParamList;
}

Action* ActionBase::getCurrentAction() {
    auto action = std::ref(*this);
    while (true) {
        auto* next = action.get().getCurrentChild();
        if (!next)
            return sead::DynamicCast<Action>(&action.get());
        action = *next;
    }
}

bool ActionBase::handleMessage(Message* message) {
    auto* action = this;
    while (!action->handleMessage_(message)) {
        action = action->getCurrentChild();
        if (!action)
            return false;
    }
    return true;
}

bool ActionBase::handleMessage2(Message* message) {
    auto* action = this;
    while (!action->handleMessage2_(message)) {
        action = action->getCurrentChild();
        if (!action)
            return false;
    }
    return true;
}

void ActionBase::setFinished() {
    mFlags.set(Flag::Finished);
    mFlags.reset(Flag::Failed);
}

void ActionBase::setFailed() {
    mFlags.set(Flag::Failed);
    mFlags.reset(Flag::Finished);
}

void ActionBase::getCurrentName(sead::BufferedSafeString* name, ActionBase* last) const {
    if (!sead::IsDerivedFrom<RootAi>(this))
        name->appendWithFormat("/%s", getName());

    if (this != last && getCurrentChild())
        getCurrentChild()->getCurrentName(name, last);
}

void ActionBase::getParams(ParamNameTypePairs* pairs, bool update_use_count) const {
    mParams.getPairs(pairs, update_use_count);
}

void ActionBase::resetRootAiFlagBit(int bit) const {
    mActor->getRootAi()->_16c.reset(RootAiFlag(1u << bit));
}

bool ActionBase::testRootAiFlag2Bit(int bit) const {
    return mActor->getRootAi()->_16e.isOn(RootAiFlag2(1u << bit));
}

template <typename T>
bool ActionBase::getStaticParam(T* value, const sead::SafeString& key) const {
    return getAIProg()->getSInstParam(value, getDef(), key);
}

template bool ActionBase::getStaticParam(const char**, const sead::SafeString&) const;
template bool ActionBase::getStaticParam(sead::SafeString*, const sead::SafeString&) const;
template bool ActionBase::getStaticParam(const int**, const sead::SafeString&) const;
template bool ActionBase::getStaticParam(const float**, const sead::SafeString&) const;
template bool ActionBase::getStaticParam(const sead::Vector3f**, const sead::SafeString&) const;
template bool ActionBase::getStaticParam(const bool**, const sead::SafeString&) const;

void ActionBase::logMissingParam(const sead::SafeString& param) const {
    // Stubbed in release versions
    const auto type = getType();
    static_cast<void>(type);
}

template <typename T>
bool ActionBase::getMapUnitParam(T* value, const sead::SafeString& key) const {
    return mActor->getRootAi()->getMapUnitParam(value, key);
}

template bool ActionBase::getMapUnitParam(sead::SafeString*, const sead::SafeString&) const;
template bool ActionBase::getMapUnitParam(const int**, const sead::SafeString&) const;
template bool ActionBase::getMapUnitParam(const float**, const sead::SafeString&) const;
template bool ActionBase::getMapUnitParam(const sead::Vector3f**, const sead::SafeString&) const;
template bool ActionBase::getMapUnitParam(const bool**, const sead::SafeString&) const;

template <typename T>
bool ActionBase::getAITreeVariable(T** value, const sead::SafeString& key) const {
    return mActor->getRootAi()->getAITreeVariable(value, key);
}

template bool ActionBase::getAITreeVariable(sead::SafeString**, const sead::SafeString&) const;
template bool ActionBase::getAITreeVariable(s32**, const sead::SafeString&) const;
template bool ActionBase::getAITreeVariable(f32**, const sead::SafeString&) const;
template bool ActionBase::getAITreeVariable(sead::Vector3f**, const sead::SafeString&) const;
template bool ActionBase::getAITreeVariable(bool**, const sead::SafeString&) const;
template bool ActionBase::getAITreeVariable(void**, const sead::SafeString&) const;

namespace {

BaseProcLink sDefaultBaseProcLink;
sead::FixedSafeString<32> sDefaultString32;
int sDefaultInt;
float sDefaultFloat;
bool sDefaultBool;
Rail* sDefaultRail;
struct ComplexDefaults {
    util::InitConstants init_constants;
    BaseProcHandle* base_proc_handle;
    sead::Vector3f vec3{0, 0, 0};
    sead::SafeString string;
    MesTransceiverId transceiver_id;
};
ComplexDefaults sDefaults;

}  // namespace

sead::SafeString* getDefaultString() {
    return &sDefaults.string;
}

s32* getDefaultInt() {
    return &sDefaultInt;
}

f32* getDefaultFloat() {
    return &sDefaultFloat;
}

sead::Vector3f* getDefaultVec3() {
    return &sDefaults.vec3;
}

bool* getDefaultBool() {
    return &sDefaultBool;
}

BaseProcLink* getDefaultBaseProcLink() {
    return &sDefaultBaseProcLink;
}

MesTransceiverId* getDefaultMesTransceiverId() {
    return &sDefaults.transceiver_id;
}

BaseProcHandle** getDefaultBaseProcHandle() {
    return &sDefaults.base_proc_handle;
}

Rail** getDefaultRail() {
    return &sDefaultRail;
}

sead::FixedSafeString<32>* getDefaultString32() {
    return &sDefaultString32;
}

}  // namespace ksys::act::ai
