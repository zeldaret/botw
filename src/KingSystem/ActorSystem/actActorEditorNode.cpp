#include "KingSystem/ActorSystem/actActorEditorNode.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/System/KingEditor.h"

namespace ksys::act {

ActorEditorNode::ActorEditorNode() = default;

ActorEditorNode::~ActorEditorNode() {
    disconnect();
}

void ActorEditorNode::connect(const ConnectArg& arg) {
    if (isConnected())
        return;

    mRootAi = arg.root_ai;
    mActorName = arg.actor_name;
    mActorId = arg.actor_id;

    sead::FixedSafeString<256> message;
    message.format("[Connect][Actor:%s:%u]", mActorName.cstr(), mActorId);
    KingEditor::instance()->log("AIEditor", message.cstr());
    KingEditor::instance()->log("ASEditor", message.cstr());
    mState = State::Connected;
}

void ActorEditorNode::disconnect() {
    if (mState == State::Disconnected)
        return;

    sead::FixedSafeString<256> message;
    message.format("[Disconnect][Actor:%s:%u]", mActorName.cstr(), mActorId);
    KingEditor::instance()->log("AIEditor", message.cstr());
    KingEditor::instance()->log("ASEditor", message.cstr());
    mRootAi = nullptr;
    mActorName = sead::SafeString::cEmptyString;
    mActorId = 0xffffffff;
    mState = State::Disconnected;
}

void ActorEditorNode::onAiEnter() {
    if (!isConnected())
        return;

    sead::FixedSafeString<0x200> ai_path;
    if (mRootAi)
        mRootAi->getCurrentName(&ai_path, nullptr);

    sead::FixedSafeString<0x300> message;
    message.format("[AIPath][FromPick][Actor:%s:%u][AIPath:%s]", mActorName.cstr(), mActorId,
                   ai_path.cstr());
    KingEditor::instance()->log("AIEditor", message.cstr());
}

void ActorEditorNode::log(const sead::SafeString& system, const sead::SafeString& message) const {
    if (!isConnected())
        return;
    KingEditor::instance()->log(system.cstr(), message.cstr());
}

bool ActorEditorNode::isConnected() const {
    return mState == State::Connected;
}

}  // namespace ksys::act
