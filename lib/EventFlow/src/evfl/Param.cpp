#include <algorithm>
#include <evfl/Flowchart.h>
#include <evfl/Param.h>
#include <evfl/ResFlowchart.h>
#include <ore/BinaryFile.h>
#include <ore/ResDic.h>

namespace evfl {

namespace {

constexpr ore::ResMetaData::DataType::Type
ConvertMetaDataPackTypeToMDType(MetaDataPack::DataType::Type type) {
    if (u32(type) < u32(MetaDataPack::DataType::Invalid()))
        return ore::ResMetaData::DataType::Type(ore::ResMetaData::DataType::kInt + type);

#ifdef MATCHING_HACK_NX_CLANG
    // Force a branch to be generated (instead of CSEL)
    __builtin_assume(type >= 0);
#endif
    return ore::ResMetaData::DataType::Invalid();
}

}  // namespace

void MetaDataPack::AddInt(const char* key, int value) {
    auto& entry = AddEntry();
    entry.key = key;
    entry.value.i = value;
    entry.type = DataType::kInt;
}

// NON_MATCHING: ???
void MetaDataPack::AddBool(const char* key, bool value) {
    auto& entry = AddEntry();
    entry.key = key;
    entry.value.i = value;
    entry.type = DataType::kBool;
}

void MetaDataPack::AddFloat(const char* key, float value) {
    auto& entry = AddEntry();
    entry.key = key;
    entry.value.f = value;
    entry.type = DataType::kFloat;
}

void MetaDataPack::AddStringPtr(const char* key, const char* value) {
    auto& entry = AddEntry();
    entry.key = key;
    entry.value.str = value;
    entry.type = DataType::kString;
}

void MetaDataPack::AddWStringPtr(const char* key, const wchar_t* value) {
    auto& entry = AddEntry();
    entry.key = key;
    entry.value.wstr = value;
    entry.type = DataType::kWString;
}

MetaDataPack::Entry* MetaDataPack::Find(const ore::StringView& key) const {
    for (auto& entry : GetEntries()) {
        if (entry.IsKey(key))
            return &entry;
    }
    return nullptr;
}

bool MetaDataPack::FindInt(int* value, const ore::StringView& key) const {
    auto* entry = Find(key);
    if (!entry || entry->type != DataType::kInt)
        return false;
    *value = entry->value.i;
    return true;
}

bool MetaDataPack::FindBool(bool* value, const ore::StringView& key) const {
    auto* entry = Find(key);
    if (!entry || entry->type != DataType::kBool)
        return false;
    *value = entry->value.i == 1;
    return true;
}

bool MetaDataPack::FindFloat(float* value, const ore::StringView& key) const {
    auto* entry = Find(key);
    if (!entry || entry->type != DataType::kFloat)
        return false;
    *value = entry->value.f;
    return true;
}

bool MetaDataPack::FindString(ore::StringView* value, const ore::StringView& key) const {
    auto* entry = Find(key);
    if (!entry || entry->type != DataType::kString)
        return false;
    *value = entry->value.str;
    return true;
}

bool MetaDataPack::FindWString(ore::WStringView* value, const ore::StringView& key) const {
    auto* entry = Find(key);
    if (!entry || entry->type != DataType::kWString)
        return false;
    *value = entry->value.wstr;
    return true;
}

ore::ResMetaData::DataType::Type MetaDataPack::GetType(const ore::StringView& key) const {
    auto* entry = Find(key);
    return ConvertMetaDataPackTypeToMDType(entry ? entry->type : DataType::Invalid());
}

// NON_MATCHING: two add operands swapped
void MetaDataPack::Builder::CalcMemSize() {
    m_entries_byte_size = sizeof(Entry) * m_num_entries;
    m_required_size = 0;
    m_alignment_real = 16;
    if (m_num_entries != 0) {
        m_alignment_real = std::max(16, m_alignment);
        m_buffer_offset = ore::AlignUpToPowerOf2(_14, m_alignment) - _14;
        m_required_size = m_buffer_offset + m_entries_byte_size;
    }
}

bool MetaDataPack::Builder::Build(MetaDataPack* pack, ore::Buffer buffer) {
    if (m_alignment_real <= 0)
        return false;
    if (m_required_size > buffer.size)
        return false;
    pack->m_buffer.data = buffer.data;
    pack->m_buffer.size = buffer.size;
    const int byte_size = m_entries_byte_size;
    pack->m_entries = reinterpret_cast<Entry*>(buffer.data + m_buffer_offset);
    pack->m_entries_capacity = byte_size / int(sizeof(Entry));
    pack->m_entries_num = 0;
    return true;
}

ParamAccessor::ParamAccessor(const ore::ResMetaData* metadata) : m_metadata(metadata) {}

ParamAccessor::ParamAccessor(const FlowchartContext* context, int node_idx)
    : m_context(context), m_node_idx(node_idx) {
    m_node_counter = context->GetNode(node_idx).GetNodeCounter();
}

const ore::ResMetaData* ParamAccessor::GetFrontResMetaData() const {
    if (m_node_idx == -1)
        return m_metadata;

    const auto& node = m_context->GetNode(m_node_idx);
    const auto& event = node.GetObj()->GetFlowchart()->events.Get()[node.GetEventIdx()];
    return event.params.Get();
}

int ParamAccessor::GetParamCount() const {
    auto* meta = GetFrontResMetaData();
    return meta ? meta->num_items : 0;
}

ore::StringView ParamAccessor::GetParamName(int idx) const {
    auto* meta = GetFrontResMetaData();
    return meta->dictionary.Get()->GetEntries()[1 + idx].GetKey();
}

ParamAccessor::Type ParamAccessor::GetParamType(int idx) const {
    Type type = ore::ResMetaData::DataType::Invalid();

    const ore::ResMetaData* metadata;
    const MetaDataPack* metadata_pack;
    const VariablePack* variable_pack;
    const auto param_name = GetParamName(idx);
    const auto real_name =
        TrackBackArgument(&metadata, &metadata_pack, &variable_pack, nullptr, param_name);

    if (metadata) {
        const int entry_idx = metadata->dictionary.Get()->FindIndex(real_name);
        if (entry_idx == -1)
            return ore::ResMetaData::DataType::Invalid();
        type = (&metadata->value.container + entry_idx)->Get()->type;
    } else if (variable_pack) {
        type = variable_pack->GetVariableType(real_name);
    } else if (metadata_pack) {
        type = metadata_pack->GetType(real_name);
    }

    if (type == ore::ResMetaData::DataType::Invalid())
        return ore::ResMetaData::DataType::Invalid();

    return type;
}

ore::StringView ParamAccessor::TrackBackArgument(const ore::ResMetaData** out_metadata,
                                                 const MetaDataPack** out_metadata_pack,
                                                 const VariablePack** out_variable_pack,
                                                 FlowchartObj** out_obj,
                                                 const ore::StringView& argument) const {
    *out_metadata = nullptr;
    *out_metadata_pack = nullptr;
    *out_variable_pack = nullptr;
    if (out_obj)
        *out_obj = nullptr;

    if (m_node_idx == -1) {
        *out_metadata = m_metadata;
        return argument;
    }

    auto ret = argument;

    for (int i = m_node_idx; i != 0xffff; i = m_context->GetNode(i).GetNextNodeIdx()) {
        const auto& node = m_context->GetNode(i);
        const auto* variable_pack = node.GetVariablePack();
        const auto* events = node.GetObj()->GetFlowchart()->events.Get();
        const auto& event = events[node.GetEventIdx()];

        if (!((event.type == ResEvent::EventType::kAction && i == m_node_idx) ||
              (event.type == ResEvent::EventType::kSwitch && i == m_node_idx) ||
              event.type == ResEvent::EventType::kSubFlow)) {
            continue;
        }

        const auto* params = event.params.Get();
        if (!params)
            return {};

        const auto* param = params->Get(ret, Type::kArgument);
        if (param) {
            ret = *param->value.str.Get();
            if (variable_pack && variable_pack->Contains(ret)) {
                *out_variable_pack = variable_pack;
                return ret;
            }
            continue;
        }

        *out_metadata = params;
        if (out_obj)
            *out_obj = node.GetObj();
        return ret;
    }

    *out_metadata_pack = m_context->GetMetaDataPack();
    if (*out_metadata_pack == nullptr)
        return {};
    return ret;
}

int ParamAccessor::GetInt(int idx) const {
    int value;
    FindInt(&value, GetParamName(idx));
    return value;
}

bool ParamAccessor::FindInt(int* value, const ore::StringView& name) const {
    const ore::ResMetaData* metadata;
    const MetaDataPack* metadata_pack;
    const VariablePack* variable_pack;
    const auto real_name =
        TrackBackArgument(&metadata, &metadata_pack, &variable_pack, nullptr, name);

    if (metadata) {
        const auto* entry = metadata->Get(real_name, Type::kInt);
        if (entry != nullptr) {
            *value = entry->value.i;
            return true;
        }
    }

    if (variable_pack && variable_pack->FindInt(value, real_name))
        return true;

    if (metadata_pack && metadata_pack->FindInt(value, real_name))
        return true;

    return false;
}

bool ParamAccessor::GetBool(int idx) const {
    bool value;
    FindBool(&value, GetParamName(idx));
    return value;
}

bool ParamAccessor::FindBool(bool* value, const ore::StringView& name) const {
    const ore::ResMetaData* metadata;
    const MetaDataPack* metadata_pack;
    const VariablePack* variable_pack;
    const auto real_name =
        TrackBackArgument(&metadata, &metadata_pack, &variable_pack, nullptr, name);

    if (metadata) {
        const auto* entry = metadata->Get(real_name, Type::kBool);
        if (entry != nullptr) {
            *value = entry->value.i != 0;
            return true;
        }
    }

    if (variable_pack && variable_pack->FindBool(value, real_name))
        return true;

    if (metadata_pack && metadata_pack->FindBool(value, real_name))
        return true;

    return false;
}

float ParamAccessor::GetFloat(int idx) const {
    float value;
    FindFloat(&value, GetParamName(idx));
    return value;
}

bool ParamAccessor::FindFloat(float* value, const ore::StringView& name) const {
    const ore::ResMetaData* metadata;
    const MetaDataPack* metadata_pack;
    const VariablePack* variable_pack;
    const auto real_name =
        TrackBackArgument(&metadata, &metadata_pack, &variable_pack, nullptr, name);

    if (metadata) {
        const auto* entry = metadata->Get(real_name, Type::kFloat);
        if (entry != nullptr) {
            *value = entry->value.f;
            return true;
        }
    }

    if (variable_pack && variable_pack->FindFloat(value, real_name))
        return true;

    if (metadata_pack && metadata_pack->FindFloat(value, real_name))
        return true;

    return false;
}

ore::StringView ParamAccessor::GetString(int idx) const {
    ore::StringView value;
    FindString(&value, GetParamName(idx));
    return value;
}

bool ParamAccessor::FindString(ore::StringView* value, const ore::StringView& name) const {
    const ore::ResMetaData* metadata;
    const MetaDataPack* metadata_pack;
    const VariablePack* variable_pack;
    const auto real_name =
        TrackBackArgument(&metadata, &metadata_pack, &variable_pack, nullptr, name);

    if (metadata) {
        const auto* entry = metadata->Get(real_name, Type::kString);
        if (entry) {
            *value = *entry->value.str.Get();
            return true;
        }
        return false;
    }

    if (metadata_pack)
        return metadata_pack->FindString(value, real_name);

    return false;
}

ore::WStringView ParamAccessor::GetWString(int idx) const {
    ore::WStringView value;
    FindWString(&value, GetParamName(idx));
    return value;
}

bool ParamAccessor::FindWString(ore::WStringView* value, const ore::StringView& name) const {
    const ore::ResMetaData* metadata;
    const MetaDataPack* metadata_pack;
    const VariablePack* variable_pack;
    const auto real_name =
        TrackBackArgument(&metadata, &metadata_pack, &variable_pack, nullptr, name);

    if (metadata) {
        const auto* entry = metadata->Get(real_name, Type::kWString);
        if (entry) {
            *value = *entry->value.wstr.Get();
            return true;
        }
        return false;
    }

    if (metadata_pack)
        return metadata_pack->FindWString(value, real_name);

    return false;
}

ParamAccessor::IntRange ParamAccessor::GetIntArray(int idx) const {
    IntRange value;
    FindIntArray(&value, GetParamName(idx));
    return value;
}

bool ParamAccessor::FindIntArray(ParamAccessor::IntRange* value,
                                 const ore::StringView& name) const {
    const ore::ResMetaData* metadata;
    const MetaDataPack* metadata_pack;
    const VariablePack* variable_pack;
    const auto real_name =
        TrackBackArgument(&metadata, &metadata_pack, &variable_pack, nullptr, name);

    if (metadata) {
        const auto* entry = metadata->Get(real_name, Type::kIntArray);
        if (entry) {
            *value = IntRange{&entry->value.i, entry->num_items};
            return true;
        }
    }

    if (variable_pack) {
        ore::DynArrayList<int>* list;
        if (variable_pack->FindIntList(&list, real_name)) {
            *value = IntRange{*list};
            return true;
        }
    }

    return false;
}

ParamAccessor::FloatRange ParamAccessor::GetFloatArray(int idx) const {
    FloatRange value;
    FindFloatArray(&value, GetParamName(idx));
    return value;
}

bool ParamAccessor::FindFloatArray(ParamAccessor::FloatRange* value,
                                   const ore::StringView& name) const {
    const ore::ResMetaData* metadata;
    const MetaDataPack* metadata_pack;
    const VariablePack* variable_pack;
    const auto real_name =
        TrackBackArgument(&metadata, &metadata_pack, &variable_pack, nullptr, name);

    if (metadata) {
        const auto* entry = metadata->Get(real_name, Type::kFloatArray);
        if (entry) {
            *value = FloatRange{&entry->value.f, entry->num_items};
            return true;
        }
    }

    if (variable_pack) {
        ore::DynArrayList<float>* list;
        if (variable_pack->FindFloatList(&list, real_name)) {
            *value = FloatRange{*list};
            return true;
        }
    }

    return false;
}

ParamAccessor::StringRange ParamAccessor::GetStringArray(int idx) const {
    StringRange value;
    FindStringArray(&value, GetParamName(idx));
    return value;
}

bool ParamAccessor::FindStringArray(ParamAccessor::StringRange* value,
                                    const ore::StringView& name) const {
    const ore::ResMetaData* metadata;
    const MetaDataPack* metadata_pack;
    const VariablePack* variable_pack;
    const auto real_name =
        TrackBackArgument(&metadata, &metadata_pack, &variable_pack, nullptr, name);

    if (metadata) {
        const auto* entry = metadata->Get(real_name, Type::kStringArray);
        if (entry) {
            *value = StringRange{&entry->value.str, entry->num_items};
            return true;
        }
    }

    return false;
}

ParamAccessor::WStringRange ParamAccessor::GetWStringArray(int idx) const {
    WStringRange value;
    FindWStringArray(&value, GetParamName(idx));
    return value;
}

bool ParamAccessor::FindWStringArray(ParamAccessor::WStringRange* value,
                                     const ore::StringView& name) const {
    const ore::ResMetaData* metadata;
    const MetaDataPack* metadata_pack;
    const VariablePack* variable_pack;
    const auto real_name =
        TrackBackArgument(&metadata, &metadata_pack, &variable_pack, nullptr, name);

    if (metadata) {
        const auto* entry = metadata->Get(real_name, Type::kWStringArray);
        if (entry) {
            *value = WStringRange{&entry->value.wstr, entry->num_items};
            return true;
        }
    }

    return false;
}

VariablePack::VariableType VariablePack::GetVariableType(const ore::StringView& name) const {
    if (!Contains(name))
        return ore::ResMetaData::DataType::Invalid();
    return GetVariableEntry(name)->type;
}

bool VariablePack::FindInt(int* value, const ore::StringView& name) const {
    if (GetVariableType(name) != ore::ResMetaData::DataType::kInt)
        return false;
    *value = GetVariableEntry(name)->value.i;
    return true;
}

bool VariablePack::FindBool(bool* value, const ore::StringView& name) const {
    if (GetVariableType(name) != ore::ResMetaData::DataType::kBool)
        return false;
    *value = GetVariableEntry(name)->value.i;
    return true;
}

bool VariablePack::FindFloat(float* value, const ore::StringView& name) const {
    if (GetVariableType(name) != ore::ResMetaData::DataType::kFloat)
        return false;
    *value = GetVariableEntry(name)->value.f;
    return true;
}

bool VariablePack::FindIntList(ore::DynArrayList<int>** value, const ore::StringView& name) const {
    if (GetVariableType(name) != ore::ResMetaData::DataType::kIntArray)
        return false;
    *value = GetVariableEntry(name)->value.int_array;
    return true;
}

bool VariablePack::FindFloatList(ore::DynArrayList<float>** value,
                                 const ore::StringView& name) const {
    if (GetVariableType(name) != ore::ResMetaData::DataType::kFloatArray)
        return false;
    *value = GetVariableEntry(name)->value.float_array;
    return true;
}

bool ParamAccessor::FindActorIdentifier(ore::StringView* actor_name,
                                        ore::StringView* actor_sub_name,
                                        const ore::StringView& name) const {
    const ore::ResMetaData* metadata;
    const MetaDataPack* metadata_pack;
    const VariablePack* variable_pack;
    const auto real_name =
        TrackBackArgument(&metadata, &metadata_pack, &variable_pack, nullptr, name);

    if (metadata) {
        const auto* entry = metadata->Get(real_name, Type::kActorIdentifier);
        if (entry) {
            *actor_name = *entry->value.actor.name.Get();
            *actor_sub_name = *entry->value.actor.sub_name.Get();
            return true;
        }
    }

    return false;
}

bool VariablePack::Contains(const ore::StringView& name) const {
    return m_names->FindIndex(name) != -1;
}

VariablePack::VariablePack() = default;

VariablePack::~VariablePack() {
    Dispose();
}

void VariablePack::Dispose() {
    auto* variables = m_variables.data();
    if (!variables)
        return;

    for (auto& variable : m_variables) {
        switch (variable.type) {
        case ore::ResMetaData::DataType::kIntArray:
            if (variable.value.int_array)
                GetAllocator()->DeleteAndNull(variable.value.int_array);
            break;
        case ore::ResMetaData::DataType::kFloatArray:
            if (variable.value.float_array)
                GetAllocator()->DeleteAndNull(variable.value.float_array);
            break;
        default:
            break;
        }
    }
    GetAllocator()->FreeImpl(variables);
}

void VariablePack::Init(AllocateArg arg, const ResEntryPoint* entry_point) {
    Dispose();
    m_names = entry_point->variable_defs_names.Get();
    m_allocator = evfl::EvflAllocator{arg};
    m_variables.ConstructElements(m_names->num_entries, GetAllocator());

    const ResVariableDef* def = entry_point->variable_defs.Get();
    for (auto& variable : m_variables) {
        variable.type = def->type;
        variable.value = {};
        switch (variable.type) {
        case ore::ResMetaData::DataType::kArgument:
        case ore::ResMetaData::DataType::kContainer:
            break;
        case ore::ResMetaData::DataType::kInt:
        case ore::ResMetaData::DataType::kBool:
            variable.value.i = def->value.i;
            break;
        case ore::ResMetaData::DataType::kFloat:
            variable.value.f = def->value.f;
            break;
        case ore::ResMetaData::DataType::kString:
        case ore::ResMetaData::DataType::kWString:
            break;
        case ore::ResMetaData::DataType::kIntArray: {
            variable.value.int_array = GetAllocator()->New<ore::DynArrayList<int>>();
            variable.value.int_array->Init(GetAllocator(), 2);
            ore::Array<const int> values{def->value.int_array.Get(), def->num};
            variable.value.int_array->OverwriteWith(values.begin(), values.end());
            break;
        }
        case ore::ResMetaData::DataType::kBoolArray:
            break;
        case ore::ResMetaData::DataType::kFloatArray: {
            variable.value.float_array = GetAllocator()->New<ore::DynArrayList<float>>();
            variable.value.float_array->Init(GetAllocator(), 2);
            ore::Array<const float> values{def->value.float_array.Get(), def->num};
            variable.value.float_array->OverwriteWith(values.begin(), values.end());
            break;
        }
        case ore::ResMetaData::DataType::kStringArray:
        case ore::ResMetaData::DataType::kWStringArray:
        case ore::ResMetaData::DataType::kActorIdentifier:
            break;
        }
        ++def;
    }
}

const VariablePack::Entry* VariablePack::GetVariableEntry(const ore::StringView& name) const {
    return &m_variables[m_names->FindIndex(name)];
}

ore::StringView VariablePack::GetVariableName(int idx) const {
    return *m_names->GetEntries()[1 + idx].name.Get();
}

int VariablePack::GetVariableCount() const {
    return m_names->num_entries;
}

VariablePack::Entry* VariablePack::GetVariableEntry(const ore::StringView& name) {
    return &m_variables[m_names->FindIndex(name)];
}

void VariablePack::SetInt(const ore::StringView& name, int value) {
    m_variables[m_names->FindIndex(name)].value.i = value;
}

void VariablePack::SetFloat(const ore::StringView& name, float value) {
    m_variables[m_names->FindIndex(name)].value.f = value;
}

void VariablePack::SetBool(const ore::StringView& name, bool value) {
    m_variables[m_names->FindIndex(name)].value.i = value;
}

int VariablePack::GetInt(const ore::StringView& name) const {
    int value;
    FindInt(&value, name);
    return value;
}

bool VariablePack::GetBool(const ore::StringView& name) const {
    bool value;
    FindBool(&value, name);
    return value;
}

float VariablePack::GetFloat(const ore::StringView& name) const {
    float value;
    FindFloat(&value, name);
    return value;
}

ore::DynArrayList<int>* VariablePack::GetIntList(const ore::StringView& name) const {
    ore::DynArrayList<int>* value;
    FindIntList(&value, name);
    return value;
}

ore::DynArrayList<float>* VariablePack::GetFloatList(const ore::StringView& name) const {
    ore::DynArrayList<float>* value;
    FindFloatList(&value, name);
    return value;
}

}  // namespace evfl
