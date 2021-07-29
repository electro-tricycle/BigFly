#pragma once
#include "PlaceBase.h"

class Place : public PlaceBase
//Place Int 类
{
private:
    int data = 0;
    std::string name;
public:
    Place()
    {}
    // 命名构造
    Place(std::string name)
    {
        this -> name = name;
    }
    ~Place()
    {}
    // 禁止复制拷贝
    Place (const Place & other) = delete;
    Place & operator = (const Place& other) = delete;
    //Place传递数值构造
    Place(int num)
    {
            this->data = num;
    }

    int size()
    {
        return data;
    }


    void input_tokens(std::any && input)
    {
        ++data;
    }

    //输出token
    int output_tokens()
    {
        --data;
        return 0;
    }
};
