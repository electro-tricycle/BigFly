#include "PetriNet/Net.h"

Net Net::m_Instance;
Net::Net(/* args */) {}

Net::~Net() {}

void Net::add_transition(std::shared_ptr<TransitionBase> pTransition)
{
    this->m_transitions.push_back(pTransition);
    // 排序
}

void Net::del_transition(std::shared_ptr<TransitionBase> pTransition) {}

void Net::run()
{
    while(true)
    {
        for (auto transition : this->m_transitions) {
            if (transition->is_ready()) {
                transition->run();
            }
            break;
        }
    }
}