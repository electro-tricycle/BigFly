#pragma once
#include "PlaceBase.h"
#include <assert.h>
#include <map>
#include <memory>
#include <string>
class Place : public PlaceBase
// Place Int 类
{
  private:
    int data = 0;

    static std::map<unsigned int, std::shared_ptr<Place>> m_instances;
    Place(unsigned int ID) : PlaceBase(ID) {}
    Place(unsigned int ID, int num) : PlaceBase(ID)
    {
        this->data = num;
    }

  public:
    static std::shared_ptr<Place> get_instance(unsigned int ID)
    {
        if (m_instances.find(ID) == m_instances.end()) {
            // 没找到
            auto pointer = std::shared_ptr<Place>(new Place(ID));
            m_instances.insert(
                std::pair<unsigned int, std::shared_ptr<Place>>(ID, pointer));
            return pointer;
        }
        else {
            auto pointer = m_instances.at(ID);
            return pointer;
        }
    }
    static std::shared_ptr<Place> get_instance(unsigned int ID, int num)
    {
        auto pointer = std::shared_ptr<Place>(new Place(ID, num));
        m_instances.insert(
            std::pair<unsigned int, std::shared_ptr<Place>>(ID, pointer));
        return pointer;
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

    ~Place() {}
    // 禁止复制拷贝
    Place(const Place& other) = delete;
    Place& operator=(const Place& other) = delete;

    int size()
    {
        return data;
    }

    void input_tokens(std::any&& input)
    {
        ++data;
    }

    std::any output_tokens()
    {
        --data;
        return std::any{};
    }

    // std::any output_tokens(std::vector<int>)
    // {
    //     assert(false);  // 没有实现的函数
    // }

    // std::any peek(unsigned int idx = 0)
    // {
    //     assert(false);  // 没有实现的函数
    // }

    // //输出token
    // int output_tokens()
    // {
    //     --data;
    //     return 0;
    // }
};

std::map<unsigned int, std::shared_ptr<Place>> Place::m_instances;
