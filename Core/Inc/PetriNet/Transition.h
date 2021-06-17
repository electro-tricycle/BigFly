/*
 * Transition.h
 *
 *  Created on: Jun 16, 2021
 *      Author: wyz
 */

#ifndef INC_PETRINET_TRANSITION_H_
#define INC_PETRINET_TRANSITION_H_

#include <functional>
#include "Place.h"
#include <memory>
#include <tuple>

template <typename input_type_tuple, typename output_type_tuple> class Transition;
template <typename ...IArgs, typename ... OArgs>
class Transition<std::tuple<IArgs...>, std::tuple<OArgs...>> {
public:
	Transition(const std::tuple<std::shared_ptr<Place<IArgs>>... > input_place_points,
			const std::tuple<std::shared_ptr<Place<OArgs>>... > output_place_points,
			std::function<std::tuple<OArgs...>(IArgs...)> action_function) {
		this->input_place_points = input_place_points;
		this->output_place_points = output_place_points;
		this->action_function = action_function;

	}
	virtual ~Transition(){}
	Transition(const Transition &other){}
	Transition(Transition &&other){}
	Transition& operator=(const Transition &other){}
	Transition& operator=(Transition &&other){}

	template <std::size_t... I, typename Tuple>
	void output_impl(Tuple tuple){
        static_cast<void>(std::initializer_list<int>{(std::get<I>(this->output_place_points)->input_token(std::get<I>(tuple)), 0)...});
    }

    void run(){
        std::tuple<IArgs...> inputs;
       	inputs = std::apply([](auto &&...args) { return std::make_tuple(args->output_token()...); },
                   this->input_place_points);
        std::tuple<OArgs...> outputs;
        outputs =  std::apply(this->action_function, inputs);
        // auto o1 = std::get<0>(outputs);
        // std::get<0>(this->output_place_points)->input_token(o1);

        output_impl<0, 1>(outputs);
    }

private:
	std::function<std::tuple<OArgs...>(IArgs...)> action_function;
	std::tuple<std::shared_ptr<Place<IArgs>>... > input_place_points;
	std::tuple<std::shared_ptr<Place<OArgs>>... > output_place_points;

};

#endif /* INC_PETRINET_TRANSITION_H_ */
