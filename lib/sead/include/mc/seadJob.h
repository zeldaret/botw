#pragma once

#include "prim/seadDelegate.h"
#include "prim/seadNamable.h"

namespace sead
{
class Job : public INamable
{
public:
    virtual ~Job();
    virtual void invoke() = 0;
};

template <typename T>
class Job0 : public Job
{
public:
    Job0(const Delegate<T>& delegate) : mDelegate(delegate) {}
    void invoke() override { mDelegate.invoke(); }

protected:
    Delegate<T> mDelegate;
};
}  // namespace sead
