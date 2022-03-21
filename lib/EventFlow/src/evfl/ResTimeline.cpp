#include <evfl/ResActor.h>
#include <evfl/ResTimeline.h>
#include <ore/Array.h>
#include <ore/ResEndian.h>
#include <ore/ResMetaData.h>

namespace evfl {

using ore::SwapEndian;

void SwapEndian(ore::ResEndian* endian, ResTrigger* trigger) {
    SwapEndian(&trigger->clip_index);
}

void SwapEndian(ore::ResEndian* endian, ResCut* cut) {
    if (endian->is_serializing) {
        if (auto* params = cut->params.ToPtr(endian->base))
            SwapEndian(endian, params);
        SwapEndian(&cut->start_time);
    } else {
        SwapEndian(&cut->start_time);
        if (auto* params = cut->params.ToPtr(endian->base))
            SwapEndian(endian, params);
    }
}

void SwapEndian(ore::ResEndian* endian, ResClip* clip) {
    const auto swap_fields = [&] {
        SwapEndian(&clip->start_time);
        SwapEndian(&clip->duration);
        SwapEndian(&clip->actor_index);
        SwapEndian(&clip->actor_action_index);
    };

    const auto swap_params = [&] {
        if (auto* params = clip->params.ToPtr(endian->base))
            SwapEndian(endian, params);
    };

    if (endian->is_serializing) {
        swap_params();
        swap_fields();
    } else {
        swap_fields();
        swap_params();
    }
}

void SwapEndian(ore::ResEndian* endian, ResOneshot* oneshot) {
    const auto swap_fields = [&] {
        SwapEndian(&oneshot->time);
        SwapEndian(&oneshot->actor_index);
        SwapEndian(&oneshot->actor_action_index);
    };

    const auto swap_params = [&] {
        if (auto* params = oneshot->params.ToPtr(endian->base))
            SwapEndian(endian, params);
    };

    if (endian->is_serializing) {
        swap_params();
        swap_fields();
    } else {
        swap_fields();
        swap_params();
    }
}

void SwapEndian(ore::ResEndian* endian, ResSubtimeline* subtimeline) {}

static void SwapEndianForTimelineData(ore::ResEndian* endian, ResTimeline* timeline) {
    ore::Array<ResClip> clips{timeline->clips.ToPtr(endian->base), timeline->num_clips};
    for (auto& clip : clips)
        SwapEndian(endian, &clip);

    ore::Array<ResOneshot> oneshots{timeline->oneshots.ToPtr(endian->base), timeline->num_oneshots};
    for (auto& oneshot : oneshots)
        SwapEndian(endian, &oneshot);

    ore::Array<ResActor> actors{timeline->actors.ToPtr(endian->base), timeline->num_actors};
    for (auto& actor : actors)
        SwapEndian(endian, &actor);

    const int num_triggers = timeline->num_clips * 2;
    ore::Array<ResTrigger> triggers{timeline->triggers.ToPtr(endian->base), num_triggers};
    for (auto& trigger : triggers)
        SwapEndian(endian, &trigger);

    ore::Array<ResCut> cuts{timeline->cuts.ToPtr(endian->base), timeline->num_cuts};
    for (auto& cut : cuts)
        SwapEndian(endian, &cut);

    if (auto* params = timeline->params.ToPtr(endian->base))
        SwapEndian(endian, params);
}

void SwapEndian(ore::ResEndian* endian, ResTimeline* timeline) {
    const auto swap_fields = [&] {
        SwapEndian(&timeline->duration);
        SwapEndian(&timeline->num_actors);
        SwapEndian(&timeline->num_actions);
        SwapEndian(&timeline->num_clips);
        SwapEndian(&timeline->num_oneshots);
        SwapEndian(&timeline->num_subtimelines);
        SwapEndian(&timeline->num_cuts);
    };

    if (endian->is_serializing) {
        SwapEndianForTimelineData(endian, timeline);
        swap_fields();
    } else {
        swap_fields();
        SwapEndianForTimelineData(endian, timeline);
    }
}

}  // namespace evfl
