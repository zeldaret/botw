#ifndef SEAD_TASK_ID_H_
#define SEAD_TASK_ID_H_

#include <basis/seadTypes.h>

namespace sead
{
class HeapArray;
class TaskBase;
class TaskMgr;
class TaskParameter;

struct TaskConstructArg
{
    TaskConstructArg() = default;

    HeapArray* heap_array;
    TaskMgr* mgr;
    TaskParameter* param;
};

typedef TaskBase* (*TaskFactory)(const TaskConstructArg&);

class TaskClassID
{
public:
    enum Type
    {
        cInvalid = 0,
        cInt = 1,
        cFactory = 2,
        cString = 3
    };

public:
    Type mType;
    union
    {
        s32 mInt;
        TaskFactory mFactory;
        const char* mString;
    } mID;
};

class TaskUserID
{
public:
    s32 mID;
};

}  // namespace sead

#endif  // SEAD_TASK_ID_H_
