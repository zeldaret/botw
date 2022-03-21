#include <evfl/Action.h>
#include <evfl/Flowchart.h>

namespace evfl {

ActionDoneHandler::ActionDoneHandler(FlowchartObj* obj, FlowchartContext* context, int node_idx)
    : m_context(context) {
    m_node_idx = node_idx;
    m_obj = obj;
    m_node_counter = context->GetNode(node_idx).GetNodeCounter();
}

FlowchartContextNode* ActionDoneHandler::GetContextNode() {
    if (!m_context)
        return nullptr;

    auto& node = m_context->GetNode(m_node_idx);
    if (node.GetNodeCounter() != m_node_counter)
        return nullptr;

    return &node;
}

void ActionDoneHandler::InvokeFromFlowchartImpl() {
    auto* node = GetContextNode();
    if (!node)
        return;

    node->m_state = FlowchartContextNode::State::kDone;
    m_context->ProcessContext();
}

void ActionDoneHandler::InvokeFromTimelineImpl() {}

bool ActionDoneHandler::IsWaitingJoin() {
    if (!m_context)
        return false;

    const auto& node = m_context->GetNode(m_node_idx);
    if (node.GetNodeCounter() != m_node_counter)
        return false;

    return node.GetState() == FlowchartContextNode::State::kWaiting;
}

bool ActionDoneHandler::CancelWaiting() {
    auto* node = GetContextNode();
    if (!node)
        return false;

    node->m_state = FlowchartContextNode::State::kInvoked;
    m_handled = false;
    return true;
}

}  // namespace evfl
