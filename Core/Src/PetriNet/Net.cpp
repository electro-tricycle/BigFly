#include "PetriNet/Net.h"

class TransitionCMP {
  public:
    bool operator()(const std::shared_ptr<TransitionBase> p1,
        const std::shared_ptr<TransitionBase>             p2)
    {
        return p1->get_priority() > p2->get_priority();
    }
};


Net Net::m_Instance;
Net::Net(/* args */) {}

Net::~Net() {}

void Net::add_transition(std::shared_ptr<TransitionBase> pTransition)
{
    this->m_transitions.push_back(pTransition);
    // 排序
    this->m_transitions.sort(TransitionCMP());
}

void Net::del_transition(std::shared_ptr<TransitionBase> pTransition) {}

void Net::run()
{
    for (auto iter = m_running_transitions.begin();
         iter != m_running_transitions.end(); ++iter) {
        if ((*iter)->is_completed()) {
            iter = m_running_transitions.erase(iter);  // 从running列表去除
        }
    }

    for (auto transition : this->m_transitions) {  // 因为是share指针
        if (transition->is_ready()) {
            transition->run();
            if (!transition->is_completed()) {
                this->m_running_transitions.push_back(transition);
            }
        }
        break;
    }
}
