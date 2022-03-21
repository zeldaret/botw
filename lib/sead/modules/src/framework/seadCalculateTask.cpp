#include "framework/seadCalculateTask.h"

namespace sead
{
CalculateTask::CalculateTask(const TaskConstructArg& arg) : TaskBase(arg)
{
    mCalcNode.bind(sead::Delegate<CalculateTask>{this, &CalculateTask::calc}, "CalculateTask");
}

CalculateTask::CalculateTask(const TaskConstructArg& arg, const char* name) : TaskBase(arg, name)
{
    mCalcNode.bind(sead::Delegate<CalculateTask>{this, &CalculateTask::calc}, name);
}

CalculateTask::~CalculateTask() = default;
}  // namespace sead
