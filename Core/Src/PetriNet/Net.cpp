#include "PetriNet/Net.h"

Net::Net(/* args */)
{
}

Net::Net(std::string name){

}

Net::~Net()
{
}

void Net::add_transition(std::shared_ptr<TransitionBase> pTransition){
    this->m_transitions.push();
}