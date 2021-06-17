/*
 * Place.h
 *
 *  Created on: Jun 16, 2021
 *      Author: wyz
 */

#ifndef SRC_PETRINET_PLACE_H_
#define SRC_PETRINET_PLACE_H_

//#include "PetriNet/PlaceBase.h"
#include <queue>

template<typename T>
class Place {
public:
	Place(){}

	Place(std::queue<T> data){
		this->data = std::move(data);
	}

	virtual ~Place(){}

	Place(const Place &other) = delete;

	Place(Place &&other){
		this->data = std::move(other);
	}

	Place& operator=(const Place &other) = delete;

	Place& operator=(Place &&other){
		this->data = std::move(other);
	}

	int length(){
		return this->data.size();
	}

	void input_token(T data){
		this->data.push(data);
	}

	T output_token(){
		T res = this->data.front();
		this->data.pop();
		return res;
	}

private:
	std::queue<T> data;
};

#endif /* SRC_PETRINET_PLACE_H_ */
