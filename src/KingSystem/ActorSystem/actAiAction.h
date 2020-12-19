#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include "KingSystem/ActorSystem/actAiActionBase.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act::ai {

class Action : public ActionBase {
    SEAD_RTTI_OVERRIDE(Action, ActionBase)
public:
    explicit Action(const InitArg& arg);

    void calc() override;
    ActionType getType() const override { return ActionType::Action; }

protected:
    virtual void calc_() {}
};
KSYS_CHECK_SIZE_NX150(Action, 0x20);

struct ActionFactory {
    using CreateFn = Action* (*)(const Action::InitArg& arg, sead::Heap* heap);
    u32 hash;
    CreateFn create_fn;
};

class Actions {
public:
    Actions();
    ~Actions();

    void finalize();

    bool init(Actor* actor, sead::Heap* heap);
    bool onActorPreDelete2() const;
    void onActorPreDelete1() const;

    static Action* clone(const Action& action, sead::Heap* heap);
    static ActionFactory* getFactory(const sead::SafeString& name);
    static void setFactories(int count, ActionFactory* factories);

    sead::Buffer<Action*> classes;
    // Non-owning buffer.
    sead::Buffer<Action*> predelete1_callbacks;
    // Non-owning buffer.
    sead::Buffer<Action*> predelete2_callbacks;

private:
    static inline sead::Buffer<ActionFactory> sFactories;
};

}  // namespace ksys::act::ai
