/*
 * PlaceOOP.h
 *
 *  Created on: 2021年6月21日
 *      Author: wyz
 */

#ifndef INC_PETRINET_PLACEOOP_H_
#define INC_PETRINET_PLACEOOP_H_

#include "PlaceBase.h"
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <vector>

class PlaceOOP : public PlaceBase {
  private:
    std::queue<std::any>                                     array;
    static std::map<unsigned int, std::shared_ptr<PlaceOOP>> m_instances;
    PlaceOOP(unsigned int ID) : PlaceBase(ID){};
    PlaceOOP(unsigned int ID, std::queue<std::any>&& array) : PlaceBase(ID)
    {
        this->array = std::move(array);
    };

  public:
    PlaceOOP(const PlaceOOP&) = delete;
    PlaceOOP& operator=(const PlaceOOP&) = delete;

    static std::shared_ptr<PlaceOOP> get_instance(unsigned int ID)
    {
        if (m_instances.find(ID) == m_instances.end()) {
            // 没找到
            auto pointer = std::shared_ptr<PlaceOOP>(new PlaceOOP(ID));
            m_instances.insert(
                std::pair<unsigned int, std::shared_ptr<PlaceOOP>>(
                    ID, pointer));
            return pointer;
        }
        else {
            auto pointer = m_instances.at(ID);
            return pointer;
        }
    }

    static std::shared_ptr<PlaceOOP> get_instance(unsigned int ID,
        std::queue<std::any>&&                                 array)
    {
        if (m_instances.find(ID) == m_instances.end()) {
            // 没找到
            auto pointer = std::shared_ptr<PlaceOOP>(new PlaceOOP(ID, std::move(array)));
            m_instances.insert(
                std::pair<unsigned int, std::shared_ptr<PlaceOOP>>(
                    ID, pointer));
            return pointer;
        }
        else {
            auto pointer = m_instances.at(ID);
            return pointer;
        }
    }

    static void del_instance(unsigned int ID)
    {
        for (auto iter = m_instances.begin(); iter != m_instances.end();
             ++iter) {
            if ((*iter).first == ID) {
                m_instances.erase(iter);
                break;
            }
        }
    }

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

    int size()
    {
        return this->array.size();
    }

    virtual ~PlaceOOP(){};
};

std::map<unsigned int, std::shared_ptr<PlaceOOP>> PlaceOOP::m_instances;

#endif /* INC_PETRINET_PLACEOOP_H_ */
