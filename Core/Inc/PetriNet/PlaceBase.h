/*
 * Place.h
 *
 *  Created on: Jun 16, 2021
 *      Author: wyz
 */

#ifndef SRC_PETRINET_PLACEBASE_H_
#define SRC_PETRINET_PLACEBASE_H_

#include <any>
#include <vector>

class PlaceBase {
  private:
    /* data */
  public:
    // PlaceBase(/* args */);
    virtual void     input_tokens(std::any&&)        = 0;
    virtual std::any output_tokens()                 = 0;
    virtual std::any output_tokens(std::vector<int>) = 0;
    virtual std::any peek(unsigned int idx = 0)      = 0;
    virtual int      size()                          = 0;
    virtual ~PlaceBase(){};
};

#endif /* SRC_PETRINET_PLACE_H_ */
