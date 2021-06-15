#include "KingSystem/Resource/Actor/resResourceASResourceExtension.h"
#include <container/seadSafeArray.h>
#include <optional>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actASSetting.h"
#include "KingSystem/Resource/resResourceASSetting.h"

namespace ksys::res {

bool ASFrameCtrlParser::parse(const ASParamParser::ParseArgs& args) {
    mRate.init(1.0, "Rate", "再生速度", "Min=0.f,Max=10.f", &mObj);
    mStartFrame.init(0.0, "StartFrame", "開始フレーム", "Min=0.f,Max=100.f", &mObj);
    mEndFrame.init(-1.0, "EndFrame", "終了フレーム", "Min=-1.f,Max=100.f", &mObj);
    mLoopStopCount.init(-1.0, "LoopStopCount", "ループ停止回数", "Min=-1.f,Max=10.f", &mObj);
    mLoopStopCountRandom.init(0.0, "LoopStopCountRandom", "ランダムループ追加回数",
                              "Min=0.f,Max=10.f", &mObj);
    mReversePlay.init(false, "ReversePlay", "逆再生", "", &mObj);
    mUseGlobalFrame.init(false, "UseGlobalFrame", "グローバルフレーム使う", "", &mObj);
    mFootType.init(0, "FootType", "足解決", "", &mObj);
    mConnect.init(false, "Connect", "接続", "", &mObj);
    mAnmLoop.init(0, "AnmLoop", "ループ設定", "", &mObj);

    mList.addObj(&mObj, "FrameCtrl0");
    return true;
}

bool ASTriggerEventsParser::parse(const ASParamParser::ParseArgs& args) {
    const int num_objs = args.res_list.getResParameterObjNum();
    if (num_objs == 0)
        return true;

    if (!mEvents.tryAllocBuffer(num_objs, args.heap))
        return false;

    auto it = mEvents.begin();
    const auto end = mEvents.end();

    sead::FixedSafeString<32> obj_name{"Event"};
    const auto obj_name_prefix_len = obj_name.calcLength();

    auto res_it = args.res_list.objBegin();
    const auto res_end = args.res_list.objEnd();

    while (res_it != res_end && it != end) {
        u32 type_index = -1;
        const auto TypeIndex = agl::utl::getResParameter(res_it.getObj(), "TypeIndex");
        if (TypeIndex.ptr())
            type_index = *TypeIndex.getData<int>();

        // TODO: add a TypeIndex enum
        it->type_index = type_index > 33 ? 88 : int(type_index) + 54;

        it->frame.init(0.0, "Frame", "フレーム", "Min=0.f,Max=100.f", &it->obj);
        it->value.init("", "Value", "値", "", &it->obj);

        obj_name.trim(obj_name_prefix_len);
        obj_name.appendWithFormat("%d", it.getIndex());
        mList.addObj(&it->obj, obj_name);

        ++res_it;
        ++it;
    }

    return true;
}

bool ASHoldEventsParser::parse(const ASParamParser::ParseArgs& args) {
    const int num_objs = args.res_list.getResParameterObjNum();
    if (num_objs == 0)
        return true;

    if (!mEvents.tryAllocBuffer(num_objs, args.heap))
        return false;

    auto it = mEvents.begin();
    const auto end = mEvents.end();

    sead::FixedSafeString<32> obj_name{"Event"};
    const auto obj_name_prefix_len = obj_name.calcLength();

    auto res_it = args.res_list.objBegin();
    const auto res_end = args.res_list.objEnd();

    while (res_it != res_end && it != end) {
        u32 type_index = -1;
        const auto TypeIndex = agl::utl::getResParameter(res_it.getObj(), "TypeIndex");
        if (TypeIndex.ptr())
            type_index = *TypeIndex.getData<int>();

        // TODO: add a TypeIndex enum
        it->type_index = type_index > 53 ? 88 : int(type_index);

        it->start_frame.init(0.0, "StartFrame", "開始フレーム", "Min=0.f,Max=100.f", &it->obj);
        it->end_frame.init(0.0, "EndFrame", "終了フレーム", "Min=0.f,Max=100.f", &it->obj);
        it->value.init("", "Value", "値", "", &it->obj);

        obj_name.trim(obj_name_prefix_len);
        obj_name.appendWithFormat("%d", it.getIndex());
        mList.addObj(&it->obj, obj_name);

        ++res_it;
        ++it;
    }

    return true;
}

bool ASStringArrayParser::parse(const ASParamParser::ParseArgs& args) {
    const int size = args.res_list.getResParameterObj(0).getNum();
    if (size != 0) {
        if (!mValues.tryAllocBuffer(size, args.heap))
            return false;

        sead::FixedSafeString<32> param_name{"Value"};
        const auto param_name_prefix_len = param_name.calcLength();

        for (int i = 0; i < size; ++i) {
            param_name.trim(param_name_prefix_len);
            param_name.appendWithFormat("%d", i);
            mValues[i].value.init("", param_name, "値", "", &mObj);
        }
    }

    mList.addObj(&mObj, "StringArray0");
    return true;
}

bool ASRangesParser::parse(const ASParamParser::ParseArgs& args) {
    const int num_objs = args.res_list.getResParameterObjNum();
    if (num_objs == 0)
        return true;

    if (!mRanges.tryAllocBuffer(num_objs, args.heap))
        return false;

    auto it = mRanges.begin();
    const auto end = mRanges.end();

    sead::FixedSafeString<32> obj_name{"Range"};
    const auto obj_name_prefix_len = obj_name.calcLength();

    auto res_it = args.res_list.objBegin();
    const auto res_end = args.res_list.objEnd();

    while (res_it != res_end && it != end) {
        obj_name.trim(obj_name_prefix_len);
        obj_name.appendWithFormat("%d", it.getIndex());

        it->start.init(0.0, "Start", "開始", "Min=0.f,Max=1.f", &it->obj);
        it->end.init(0.0, "End", "終了", "Min=0.f,Max=1.f", &it->obj);

        mList.addObj(&it->obj, obj_name);

        ++res_it;
        ++it;
    }

    return true;
}

bool ASFloatArrayParser::parse(const ASParamParser::ParseArgs& args) {
    const int size = args.res_list.getResParameterObj(0).getNum();
    if (size != 0) {
        if (!mValues.tryAllocBuffer(size, args.heap))
            return false;

        sead::FixedSafeString<32> param_name{"Value"};
        const auto param_name_prefix_len = param_name.calcLength();

        for (int i = 0; i < size; ++i) {
            param_name.trim(param_name_prefix_len);
            param_name.appendWithFormat("%d", i);
            mValues[i].value.init(1.0, param_name, "値", "", &mObj);
        }
    }

    mList.addObj(&mObj, "FloatArray0");
    return true;
}

bool ASIntArrayParser::parse(const ASParamParser::ParseArgs& args) {
    const int size = args.res_list.getResParameterObj(0).getNum();
    if (size != 0) {
        if (!mValues.tryAllocBuffer(size, args.heap))
            return false;

        sead::FixedSafeString<32> param_name{"Value"};
        const auto param_name_prefix_len = param_name.calcLength();

        for (int i = 0; i < size; ++i) {
            param_name.trim(param_name_prefix_len);
            param_name.appendWithFormat("%d", i);
            mValues[i].value.init(1, param_name, "値", "", &mObj);
        }
    }

    mList.addObj(&mObj, "IntArray0");
    return true;
}

bool ASBitIndexParser::parse(const ASParamParser::ParseArgs& args) {
    const auto obj = args.res_list.getResParameterObj(0);
    if (obj.getNum() < 1)
        return true;

    const auto TypeIndex = agl::utl::getResParameter(obj, "TypeIndex");
    if (!TypeIndex.ptr())
        return true;

    mTypeIndex = *TypeIndex.getData<int>();
    return true;
}

template <typename T>
static ASParamParser* factoryImpl_(sead::Heap* heap) {
    return new (heap) T;
}

static ASParamParser* dummyASParserFactoryImpl_(sead::Heap*) {
    return nullptr;
}

namespace {
struct Factory {
    const char* name;
    ASParamParser* (*make)(sead::Heap* heap);
};

sead::SafeArray<Factory, ASParamParser::NumTypes> sASFactories{{
    {"FrameCtrl", factoryImpl_<ASFrameCtrlParser>},
    {"TriggerEvents", factoryImpl_<ASTriggerEventsParser>},
    {"HoldEvents", factoryImpl_<ASHoldEventsParser>},
    {"StringArray", factoryImpl_<ASStringArrayParser>},
    {"Ranges", factoryImpl_<ASRangesParser>},
    {"FloatArray", factoryImpl_<ASFloatArrayParser>},
    {"IntArray", factoryImpl_<ASIntArrayParser>},
    {"BitIndex", factoryImpl_<ASBitIndexParser>},
    {"BlenderBone", dummyASParserFactoryImpl_},
}};
}  // namespace

ASExtensions::~ASExtensions() {
    for (auto*& parser : mParsers) {
        if (parser && parser->getType() != ASParamParser::Type::BlenderBone)
            delete parser;
        parser = nullptr;
    }
    mParsers.freeBuffer();
}

bool ASExtensions::parse(const ASExtensions::ParseArgs& args) {
    const auto Extend = agl::utl::getResParameterList(args.res_list, "Extend");
    if (!Extend)
        return true;

    const auto num_extensions = Extend.getResParameterListNum();
    if (num_extensions == 0)
        return true;

    if (!mParsers.tryAllocBuffer(num_extensions, args.heap))
        return false;
    for (int i = 0, n = mParsers.size(); i < n; ++i)
        mParsers(i) = nullptr;

    auto it = mParsers.begin();
    const auto end = mParsers.end();

    ASParamParser::ParseArgs parse_args{};
    parse_args.list = &mList;
    parse_args.heap = args.heap;

    auto res_it = Extend.listBegin();
    const auto res_end = Extend.listEnd();

    for (; it != end && res_it != res_end; ++it, ++res_it) {
        parse_args.res_list = res_it.getList();
        *it = makeParser(parse_args);

        constexpr int bone = int(ASParamParser::Type::BlenderBone);
        if (*it == nullptr && parse_args.res_list.getParameterListNameHash() !=
                                  agl::utl::ParameterBase::calcHash(sASFactories[bone].name)) {
            return false;
        }
    }

    args.list->addList(&mList, "Extend");
    return true;
}

ASParamParser* ASExtensions::makeParser(const ASParamParser::ParseArgs& args) const {
    const auto is_factory = [&args](int i) {
        return args.res_list.getParameterListNameHash() ==
               agl::utl::ParameterBase::calcHash(sASFactories[i].name);
    };

    std::optional<int> type;
    for (int i = 0; i < ASParamParser::NumTypes - 1; ++i) {
        if (!is_factory(i))
            continue;
        type = i;
        break;
    }

    if (!type.has_value() && is_factory(int(ASParamParser::Type::BlenderBone))) {
        const auto obj = args.res_list.getResParameterObj(0);
        if (obj.getNum() > 0) {
            const sead::SafeString name = obj.getResParameter(0).getData<const char>();
            return act::ASSetting::instance()->getBoneParams(name);
        }
    }

    if (!type.has_value())
        return nullptr;

    const auto& factory = sASFactories[*type];

    auto* parser = factory.make(args.heap);
    if (!parser)
        return nullptr;

    if (!parser->parse(args)) {
        delete parser;
        return nullptr;
    }

    args.list->addList(&parser->getList(), factory.name);
    return parser;
}

ASParamParser* ASExtensions::getParser(ASParamParser::Type type) const {
    for (int i = 0, n = mParsers.size(); i < n; ++i) {
        auto* parser = mParsers[i];
        if (parser && parser->getType() == type)
            return parser;
    }
    return nullptr;
}

}  // namespace ksys::res
