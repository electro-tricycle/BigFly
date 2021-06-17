/*
 * Place.h
 *
 *  Created on: Jun 16, 2021
 *      Author: wyz
 */

#ifndef SRC_PETRINET_PLACEBASE_H_
#define SRC_PETRINET_PLACEBASE_H_

#include <memory>

class PlaceBase {
public:
	PlaceBase(){}
	virtual ~PlaceBase(){};
	virtual int length() = 0;

	void input_token(std::unique_ptr<void>) = 0;

	std::unique_ptr<void> output_token() = 0;


};

#endif /* SRC_PETRINET_PLACE_H_ */
