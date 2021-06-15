#pragma once

#include <hostio/seadHostIONode.h>
#include <mc/seadJob.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::world {

enum class JobType {
    Time,
    Sky,
    ShootingStar,
    Weather,
    Temp,
    Wind,
    Env,
    Dof,
    Chemical,
};
constexpr int NumJobTypes = 9;

class Job : public sead::Job, public sead::hostio::Node {
    SEAD_RTTI_BASE(Job)
public:
    Job();
    ~Job() override;
    void invoke() override;
    void init(sead::Heap* heap);

protected:
    virtual void init_(sead::Heap* heap) {}
    virtual void calc_() {}
    virtual void calcType1_() {}
    virtual void calcType2_() {}
    virtual void m9() {}
    virtual void m10() {}
    virtual void m11() {}

    virtual JobType getType() const = 0;
};
KSYS_CHECK_SIZE_NX150(Job, 0x20);

}  // namespace ksys::world
