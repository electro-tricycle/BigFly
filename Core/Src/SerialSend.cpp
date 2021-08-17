#include "PetriNet/Core.h"
#include <memory>

void serial_initial()
{
    // 添加进网络
    Net& net = Net::get_instance();

//    auto place_p    = PlaceColor<NUMBER_OF_COLORS>::get_instance(1);
//    auto transition = TransitionColor<NUMBER_OF_COLORS>::get_instance(
//        1, {place_p}, {{1, 0, 0}}, {place_p}, {{1, 0, 0}});
//    net.add_transition(transition);
}
