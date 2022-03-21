#pragma once

#include <evfl/EvflAllocator.h>
#include <evfl/ResActor.h>
#include <ore/Array.h>
#include <ore/EnumUtil.h>
#include <ore/Types.h>

namespace evfl {

struct ResTimeline;

ORE_ENUM(TimelineState, kNotStarted, kPlaying, kStop, kPause)

class TimelineObj {
public:
    class Builder {
    public:
        explicit Builder(const ResTimeline* timeline) : m_timeline(timeline) {}

        bool Build(TimelineObj* obj, AllocateArg allocate_arg);

    private:
        const ResTimeline* m_timeline = nullptr;
        ActBinder::Builder m_act_binder_builder;
    };

    TimelineObj();

    void Calc();
    void Reset();
    void SetState(TimelineState::Type state);
    void Start(float start_time);
    void JumpTimeTo(float time);
    void AdvanceTimeTo(float time);
    bool RegisterSubtimeline(TimelineObj* obj);

    ActBinder& GetActBinder() { return m_act_binder; }
    const ActBinder& GetActBinder() const { return m_act_binder; }
    const ore::Array<TimelineObj*>& GetSubTimelines() const { return m_sub_timelines; }
    const ResTimeline* GetTimeline() const { return m_timeline; }
    float GetTime() const { return m_time; }
    float GetNewTime() const { return m_new_time; }
    int GetLastTriggerIdx() const { return m_last_trigger_idx; }
    int GetLastOneshotIdx() const { return m_last_oneshot_idx; }
    int GetPlayCounter() const { return m_play_counter; }
    bool IsStarted() const { return m_started; }
    bool IsJumpedTime() const { return m_jumped_time; }
    TimelineState::Type GetState() const { return m_state; }

private:
    void CalcImpl();
    void JumpTimeToImpl(float time);
    void AdvanceTimeToImpl(float time);

    static int s_GlobalPlayCounter;

    void Finalize() {
        m_timeline = nullptr;
        m_act_binder.Reset();
        m_sub_timelines.Clear(&m_allocator);
    }

    EvflAllocator m_allocator;
    ore::Array<TimelineObj*> m_sub_timelines;
    const ResTimeline* m_timeline{};
    ActBinder m_act_binder{};
    float m_time{};
    float m_new_time{};
    int m_last_trigger_idx = -1;
    int m_last_oneshot_idx = -1;
    int m_play_counter = 0;
    bool m_started = false;
    bool m_jumped_time = false;
    ore::SizedEnum<TimelineState::Type, u8> m_state = TimelineState::kNotStarted;
};

}  // namespace evfl
