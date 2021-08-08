#pragma once

#include <string>
#include <memory>
#include <queue>
#include "PetriNet/Transition.h"
#include "PetriNet/TransitionBase.h"

class Net
{
private:
  std::priority_queue<std::shared_ptr<TransitionBase>> m_transitions;

public:
    Net();
    Net(std::string name);
    ~Net();

    void add_transition(std::shared_ptr<TransitionBase> pTransition);
};


