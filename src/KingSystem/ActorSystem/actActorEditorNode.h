#pragma once

#include <prim/seadSafeString.h>

namespace ksys::act {

namespace ai {
class RootAi;
}

class ActorEditorNode {
public:
    struct ConnectArg {
        ai::RootAi* root_ai;
        sead::SafeString actor_name;
        u32 actor_id;
    };

    ActorEditorNode();
    virtual ~ActorEditorNode();

    void connect(const ConnectArg& arg);
    void disconnect();
    void onAiEnter();
    void log(const sead::SafeString& system, const sead::SafeString& message) const;
    bool isConnected() const;

private:
    enum class State : u8 {
        Disconnected = 0,
        Connected = 1,
    };

    State mState = State::Disconnected;
    ai::RootAi* mRootAi = nullptr;
    sead::SafeString mActorName;
    u32 mActorId = 0xffffffff;
};

}  // namespace ksys::act
