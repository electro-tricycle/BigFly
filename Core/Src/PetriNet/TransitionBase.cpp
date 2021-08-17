#include "PetriNet/TransitionBase.h"

void queue_clear(std::queue<std::any>& q)
{
    std::queue<std::any> empty;
    std::swap(empty, q);
}
