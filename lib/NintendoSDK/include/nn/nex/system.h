/**
 * @file system.h
 * @brief System state / component interface for NEX.
 */

#pragma once

#include <nn/nex/reference.h>

namespace nn {
namespace nex {
class String;

class SystemComponent : public nn::nex::RefCountedObject {
public:
    enum _State {
        State_Uninitialized = 1 << 0,
        State_Initializing = 1 << 1,
        State_Ready = 1 << 2,
        State_ReadyInUse = 1 << 3,
        State_Terminating = 1 << 4,
        State_TerminatingWhileInUse = 1 << 5,
        State_Terminated = 1 << 6,
        State_Faulty = 1 << 7,
        State_Unknown = 1 << 8,
        State_HighestState = 1 << 8
    };

    SystemComponent(nn::nex::String const&);

    virtual ~SystemComponent();

    virtual char* GetType() const;
    virtual bool IsAKindOf(char const*) const;
    virtual void EnforceDeclareSysComponentMacro() = 0;
    virtual void StateTransition(nn::nex::SystemComponent::_State);
    virtual void OnInitialize();
    virtual void OnTerminate();
    virtual bool BeginInitialization();
    virtual bool EndInitialization();
    virtual bool BeginTermination();
    virtual bool EndTermination();
    virtual bool ValidTransition(nn::nex::SystemComponent::_State);
    virtual bool UseIsAllowed();
    virtual nn::nex::SystemComponent::_State TestState();
    virtual void DoWork();

    nn::nex::SystemComponent::_State Initialize();
    nn::nex::SystemComponent::_State Terminate();

    u8 SystemComponent_xC;
    u8 _D;
    u8 _E;
    u8 _F;
    u64 _10;
    u64 _18;
    u64 _20;
    u32 _28;
    u32 _2C;
    u64 _30;
    nn::nex::SystemComponent::_State mState;  // _38
    u32 _3C;
    u64 _40;
};
};  // namespace nex
};  // namespace nn