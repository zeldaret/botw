#pragma once

#include "framework/seadMethodTree.h"
#include "framework/seadTaskBase.h"

namespace sead
{
class CalculateTask : public TaskBase
{
    SEAD_RTTI_OVERRIDE(CalculateTask, TaskBase)
public:
    explicit CalculateTask(const TaskConstructArg& arg);
    CalculateTask(const TaskConstructArg& arg, const char* name);
    ~CalculateTask() override;
    void pauseCalc(bool b) override;
    void pauseDraw(bool b) override;
    void pauseCalcRec(bool b) override;
    void pauseDrawRec(bool b) override;
    void pauseCalcChild(bool b) override;
    void pauseDrawChild(bool b) override;
    void attachCalcImpl() override;
    void attachDrawImpl() override;
    void detachCalcImpl() override;
    void detachDrawImpl() override;
    const RuntimeTypeInfo::Interface* getCorrespondingMethodTreeMgrTypeInfo() const override;
    MethodTreeNode* getMethodTreeNode(s32 method_type) override;
    virtual void calc() {}

protected:
    MethodTreeNode mCalcNode{nullptr};
};
}  // namespace sead
