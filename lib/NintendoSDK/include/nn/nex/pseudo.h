/**
 * @file psuedo.h
 * @brief Psuedo variable implementation for NEX.
 */

#pragma once

#include <nn/nex/RootObject.h>
#include <nn/nex/instance.h>

namespace nn {
namespace nex {
class PseudoGlobalVariableList;

class PseudoGlobalVariableRoot : public nn::nex::RootObject {
public:
    PseudoGlobalVariableRoot();

    virtual ~PseudoGlobalVariableRoot();

    virtual void AllocateExtraContexts() = 0;
    virtual void FreeExtraContexts() = 0;
    virtual void ResetContext(u32) = 0;
    virtual PseudoGlobalVariableRoot* GetNext() = 0;
    virtual void SetNext(PseudoGlobalVariableRoot* pNextVariable) = 0;

    static void ResetContextForAllVariables(u32);
    static void AllocateExtraContextsForAllVariables(u64);
    static void FreeExtraContextsForAllVariables();
    static s64 GetNbOfExtraContexts();

    nn::nex::PseudoGlobalVariableRoot* mNextRoot;  // _8

    static s64 s_uiNbOfExtraContexts;
    static PseudoGlobalVariableList s_oList;
};

class PseudoGlobalVariableList : public nn::nex::RootObject {
public:
    PseudoGlobalVariableList();

    virtual ~PseudoGlobalVariableList();

    void AddVariable(nn::nex::PseudoGlobalVariableRoot*);
    void RemoveVariable(nn::nex::PseudoGlobalVariableRoot*);
    static nn::nex::PseudoGlobalVariableRoot* GetVariable(u32 idx);
    static u32 FindVariableIndex(nn::nex::PseudoGlobalVariableRoot*);
    void AllocateExtraContextsForAllVariables();
    void FreeExtraContextsForAllVariables();
    void ResetContextForAllVariables(u32);
    static u32 GetNbOfVariables();

    static PseudoGlobalVariableRoot* s_pVariableListHead;
    static u32 m_uiNbOfVariables;
};

template <typename T>
class PseudoGlobalVariable : public nn::nex::PseudoGlobalVariableRoot {
public:
    PseudoGlobalVariable();

    virtual ~PseudoGlobalVariable();

    virtual void AllocateExtraContexts();
    virtual void FreeExtraContexts();
    virtual void ResetContext(u32);
    virtual PseudoGlobalVariableRoot* GetNext();
    virtual void SetNext(PseudoGlobalVariableRoot* pNextVariable);
};

class PseudoSingleton : public nn::nex::InstanceControl {
public:
    PseudoSingleton(u32);

    virtual ~PseudoSingleton();

    static bool s_bUseInstantiationContext;
};
};  // namespace nex
};  // namespace nn