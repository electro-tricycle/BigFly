/*
 * PlaceCLint.h
 *
 *  Created on: 2021年7月30日
 *      Author: jay chou
 */

#ifndef INC_PETRINET_PLACECLINT_H_
#define INC_PETRINET_PLACECLINT_H_

#pragma once
#include "PlaceBase.h"
#include <Eigen/Dense>

class Place
//Place color Int 类
{
private:
    std::string name;
    Eigen::Vector3i cl;
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
    // // 禁止复制拷贝
    Place (const Place & other) = delete;
    Place & operator = (const Place& other) = delete;
    //Place传递数值构造
    Place(int a, int b, int c)
    {
            this -> cl = std::move(Eigen::Vector3i(a,b,c));
    }

    Eigen::Vector3i getVector()
    {
        return cl;
    }

    int size()
    {
        return cl.size();
    }


    void input_tokens(std::vector<Eigen::Vector3i> output_weights,int i)
    {
        cl += output_weights[i];
    }

    //输出token
    void output_tokens(std::vector<Eigen::Vector3i> input_weights,int i)
    {
        cl -= input_weights[i];
    }
};




#endif /* INC_PETRINET_PLACECLINT_H_ */
