#pragma once

#include "PetriNet/Transition.h"
#include "PetriNet/TransitionBase.h"
#include <memory>
#include <list>
#include <string>

class Net {
  private:
    std::list<std::shared_ptr<TransitionBase>> m_transitions;
    Net();
    Net(const Net&) = delete;
    Net& operator=(const Net&) = delete;
    ~Net();

  private:
    static Net m_Instance;

  public:
    static Net& get_instance()
    {
        return m_Instance;
    }
    void add_transition(std::shared_ptr<TransitionBase> pTransition);
    void del_transition(std::shared_ptr<TransitionBase> pTransition);
    void run();
};


