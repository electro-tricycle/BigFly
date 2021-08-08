#pragma once
#include "PlaceBase.h"
#include <assert.h>
#include <string>
class Place : public PlaceBase
// Place Int 类
{
  private:
    int         data = 0;
    std::string name;

  public:
    Place() {}
    // 命名构造
    Place(std::string name)
    {
        this->name = name;
    }
    Place(int num)
    {
        this->data = num;
    }
    ~Place() {}
    // 禁止复制拷贝
    Place(const Place& other) = delete;
    Place& operator=(const Place& other) = delete;
    // Place传递数值构造

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
        return;
    }
    std::any output_tokens(std::vector<int>)
    {
        assert(false);  // 没有实现的函数
    }

    std::any peek(unsigned int idx = 0)
    {
        assert(false);  // 没有实现的函数
    }

    // //输出token
    // int output_tokens()
    // {
    //     --data;
    //     return 0;
    // }
};
