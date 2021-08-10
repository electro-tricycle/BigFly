/*
 * PlaceOOP.h
 *
 *  Created on: 2021年6月21日
 *      Author: wyz
 */

#ifndef INC_PETRINET_PLACEOOP_H_
#define INC_PETRINET_PLACEOOP_H_

#include "PlaceBase.h"
#include <vector>
#include <string>

template <typename T> class PlaceOOP : public PlaceBase {
  private:
    std::queue<std::any> array;
    std::string          name;

  public:
    PlaceOOP(){};
    PlaceOOP(std::string name)
    {
        this->name = name;
    };

    void input_tokens(std::any&& input)
    {
        this->array.push(std::move(input));
    }

    std::any output_tokens()
    {
        std::any output = std::move(this->array.front());
        this->array.pop();
        return output;
    }

    // std::any output_tokens(std::vector<int>)
    // {
    //     assert(false);  // 没有实现的函数
    // }
    // std::any peek(unsigned int idx = 0)
    // {
        
    // }

    int size()
    {
        return this->array.size();
    }

    virtual ~PlaceOOP(){};
};

#endif /* INC_PETRINET_PLACEOOP_H_ */
