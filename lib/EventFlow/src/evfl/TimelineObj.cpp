#include <evfl/Action.h>
#include <evfl/ResActor.h>
#include <evfl/ResTimeline.h>
#include <evfl/TimelineObj.h>
#include <utility>

namespace evfl {

int TimelineObj::s_GlobalPlayCounter{};

// NON_MATCHING: didn't bother matching, clearly equivalent
TimelineObj::TimelineObj() = default;

void TimelineObj::Calc() {
    CalcImpl();
    for (auto* timeline : m_sub_timelines) {
        if (timeline)
            timeline->Calc();
    }
}

void TimelineObj::Reset() {
    m_play_counter = ++s_GlobalPlayCounter;
    m_started = false;
    m_state = TimelineState::kNotStarted;
    for (auto* timeline : m_sub_timelines) {
        if (timeline)
            timeline->Reset();
    }
}

void TimelineObj::SetState(TimelineState::Type state) {
    m_state = state;
}

void TimelineObj::Start(float start_time) {
    if (m_started)
        return;

    m_started = true;
    m_state = TimelineState::kPlaying;
    m_time = -1.0;
    m_last_trigger_idx = -1;
    m_last_oneshot_idx = -1;
    JumpTimeTo(start_time);
    Calc();

    for (auto* timeline : m_sub_timelines) {
        if (timeline && !timeline->m_started)
            timeline->Start(start_time);
    }
}

void TimelineObj::JumpTimeTo(float time) {
    JumpTimeToImpl(time);
}

void TimelineObj::AdvanceTimeTo(float time) {
    AdvanceTimeToImpl(time);
}

namespace {

TriggerType::Type ReverseTriggerType(TriggerType::Type clip_trigger_type) {
    switch (clip_trigger_type) {
    case TriggerType::kClipEnter:
        return TriggerType::kClipLeave;
    case TriggerType::kClipLeave:
        return TriggerType::kClipEnter;
    case TriggerType::kOneshot:
        return TriggerType::kOneshot;
    default:
        return {};
    }
}

float GetTriggerTime(TriggerType::Type type, const ResClip& clip) {
    switch (type) {
    case TriggerType::kEnter:
        return clip.start_time;
    case TriggerType::kLeave:
        return clip.start_time + clip.duration;
    default:
        return 0.0;
    }
}

float GetTriggerTimeReverse(TriggerType::Type type, const ResClip& clip) {
    switch (type) {
    case TriggerType::kEnter:
        return clip.start_time + clip.duration;
    case TriggerType::kLeave:
        return clip.start_time;
    default:
        return 0.0;
    }
}

}  // namespace

// NON_MATCHING: reorderings for the action binding stuff
void TimelineObj::CalcImpl() {
    if (m_time == m_new_time)
        return;

    const int direction = m_time < m_new_time ? 1 : -1;
    const auto time_max = m_time < m_new_time ? m_new_time : m_time;
    const auto time_min = m_time < m_new_time ? m_time : m_new_time;

    ore::Array<const ResTrigger> triggers{m_timeline->triggers.Get(), 2 * m_timeline->num_clips};
    ore::Array<const ResClip> clips{m_timeline->clips.Get(), m_timeline->num_clips};

    for (int trigger_idx = (m_time < m_new_time) + m_last_trigger_idx;
         u32(trigger_idx) < u32(triggers.size()); trigger_idx += direction) {
        const auto& trigger = triggers[trigger_idx];
        const auto& clip = clips[trigger.clip_index];
        const auto trigger_type = TriggerType::Type(trigger.trigger_type);

        const float trigger_time = GetTriggerTime(trigger_type, clip);
        if (trigger_time <= time_min || time_max < trigger_time)
            break;

        m_last_trigger_idx = trigger_idx;

        if (m_jumped_time) {
            const float rev_trigger_time = GetTriggerTimeReverse(trigger_type, clip);
            if (time_min < rev_trigger_time && rev_trigger_time <= time_max)
                continue;
        }

        const auto actor_idx = clip.actor_index;
        const auto& bindings = m_act_binder.GetBindings();
        const auto* actions = m_timeline->actors.Get()[actor_idx].actions.Get();
        const auto& binding = bindings[actor_idx];
        const ore::StringView name = *actions[clip.actor_action_index].name.Get();
        const auto* action = binding.GetAction(name);

        auto real_trigger_type = trigger_type;
        if (m_jumped_time && direction < 0)
            real_trigger_type = ReverseTriggerType(real_trigger_type);

        const ActionArg arg(&clip, binding.GetUserData(), action->user_data,
                            m_new_time - trigger_time, real_trigger_type, clip.params.Get());
        ActionDoneHandler handler{this};
        action->handler(arg, std::move(handler));
    }

    ore::Array<const ResOneshot> oneshots{m_timeline->oneshots.Get(), m_timeline->num_oneshots};
    for (int oneshot_idx = (m_time < m_new_time) + m_last_oneshot_idx;
         u32(oneshot_idx) < u32(oneshots.size()); oneshot_idx += direction) {
        const auto& oneshot = oneshots[oneshot_idx];
        const auto trigger_time = oneshot.time;
        if (trigger_time < time_min || time_max < trigger_time)
            break;

        m_last_oneshot_idx = oneshot_idx;

        if (m_jumped_time && trigger_time != m_new_time)
            continue;

        const auto actor_idx = oneshot.actor_index;
        const auto& bindings = m_act_binder.GetBindings();
        const auto& binding = bindings[actor_idx];
        const auto* actions = m_timeline->actors.Get()[actor_idx].actions.Get();
        const ore::StringView name = *actions[oneshot.actor_action_index].name.Get();
        const auto* action = binding.GetAction(name);

        const ActionArg arg(&oneshot, binding.GetUserData(), action->user_data,
                            m_new_time - trigger_time, oneshot.params.Get());
        ActionDoneHandler handler{this};
        action->handler(arg, std::move(handler));
    }

    m_time = m_new_time;
}

void TimelineObj::AdvanceTimeToImpl(float time) {
    m_new_time = time;
    m_jumped_time = false;
    for (auto* timeline : m_sub_timelines) {
        if (timeline)
            timeline->AdvanceTimeToImpl(time);
    }
}

void TimelineObj::JumpTimeToImpl(float time) {
    m_new_time = time;
    m_jumped_time = true;
    for (auto* timeline : m_sub_timelines) {
        if (timeline)
            timeline->JumpTimeToImpl(time);
    }
}

bool TimelineObj::RegisterSubtimeline(TimelineObj* obj) {
    ore::Array<const ResSubtimeline> subtimelines{m_timeline->subtimelines.Get(),
                                                  m_timeline->num_subtimelines};
    for (int i = 0; i < subtimelines.size(); ++i) {
        if (ore::StringView(*obj->m_timeline->name.Get()) == *subtimelines[i].name.Get()) {
            m_sub_timelines[i] = obj;
            return true;
        }
    }
    return false;
}

// NON_MATCHING: std::fill using obj->m_sub_timelines.size() rather than the byte size
bool TimelineObj::Builder::Build(TimelineObj* obj, AllocateArg allocate_arg) {
    if (!obj)
        return false;

    if (!allocate_arg.alloc || !allocate_arg.free)
        return false;

    obj->Finalize();

    EvflAllocator allocator{allocate_arg};
    obj->m_allocator = allocator;

    m_act_binder_builder.Build(&obj->m_act_binder, &obj->m_allocator,
                               {m_timeline->actors.Get(), m_timeline->num_actors});

    auto& bindings = obj->m_act_binder.GetBindings();
    for (auto it = bindings.begin(); it != bindings.end(); ++it)
        it->SetIsUsed(true);

    obj->m_timeline = m_timeline;
    obj->m_allocator = allocator;
    obj->m_sub_timelines.ConstructElements(m_timeline->num_subtimelines, &allocator);
    std::fill(obj->m_sub_timelines.begin(), obj->m_sub_timelines.end(), nullptr);

    return true;
}

}  // namespace evfl
