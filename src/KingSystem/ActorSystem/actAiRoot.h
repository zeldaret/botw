#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actAiParam.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act::ai {

class Action;
class Ai;
class Behavior;
class Query;

class IRootAi {
public:
    virtual ~IRootAi() = default;
};

template <typename Class>
class ClassContainer {
public:
    ClassContainer();
    ~ClassContainer();

    void finalize();

private:
    sead::Buffer<Class> classes;
    // TODO: rename
    sead::Buffer<Class> x;
    // TODO: rename
    sead::Buffer<Class> y;
};

class RootAi : public Ai, public IRootAi {
    SEAD_RTTI_OVERRIDE(RootAi, Ai)
public:
    explicit RootAi(const InitArg& arg);
    ~RootAi() override;

    bool isFlag4Set() const override { return true; }
    bool init_(sead::Heap* heap) override;
    void enter_(InlineParamPack* params) override;
    void leave_() override;
    bool m16() override;
    void calc() override;

    const ParamPack& getMapUnitParams() const { return mMapUnitParams; }
    const ParamPack& getAiTreeParams() const { return mAiTreeParams; }

private:
    // TODO: rename and put this in a different translation unit
    struct SomeStruct {
        SomeStruct();
        virtual ~SomeStruct();

        void* _8{};
    };
    KSYS_CHECK_SIZE_NX150(SomeStruct, 0x10);

    void calc_() override;

    f32 _40 = 1.0;
    u32 _44{};
    ClassContainer<Action> mActions;
    ClassContainer<Ai> mAis;
    ClassContainer<Behavior> mBehaviors;
    ClassContainer<Query> mQueries;
    sead::SafeArray<Behavior*, 3> mBehaviorsByStopAndCalcTiming[2]{};
    void* _138{};
    SomeStruct* _140{};
    u32 mMA_I{};
    u16 mAt{};
    u8 _14e{};
    void* _150{};
    void* _158{};
    void* _160{};
    // TODO: is this really an atomic?
    sead::Atomic<f32> _168 = 1.0;
    u16 _16c{};
    u16 _16e{};
    ParamPack mMapUnitParams;
    ParamPack mAiTreeParams;
};
KSYS_CHECK_SIZE_NX150(RootAi, 0x180);

}  // namespace ksys::act::ai
