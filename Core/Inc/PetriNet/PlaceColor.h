/*
 * PlaceColor.h
 *
 *  Created on: 2021年7月30日
 *      Author: jay chou
 */

#pragma once
#include "Eigen/Core"
#include "Eigen/Dense"
#include "PetriNet/PlaceVectorBase.h"
#include <any>
#include <string>
#include <tuple>
#include <queue>

template <int dim>
class PlaceColor : public PlaceVectorBase<dim>{
  private:
    std::string name = "";
    // Eigen::Vector3i      cl;
    Eigen::Matrix<int, dim, 1>            cl;  // dim代表颜色维度数目
    std::array<std::queue<std::any>, dim> array;  // 一共有dim组存数据的queue

  public:
    PlaceColor() {}
    // 命名构造
    PlaceColor(std::string name)
    {
        this->name = name;
    }
    ~PlaceColor() {}
    // // 禁止复制拷贝
    PlaceColor(const PlaceColor& other) = delete;
    PlaceColor& operator=(const PlaceColor& other) = delete;

    // PlaceColor传递数值构造
    PlaceColor(Eigen::Matrix<int, dim, 1>       data,
        std::array<std::queue<std::any>, dim>&& inputs)
    {
        this->cl    = std::move(data);
        this->array = std::move(inputs);
    }
    // //返回PlaceColor中的颜色token
    // Eigen::Vector3i getVector()
    // {
    //     return cl;
    // }
    // //返回PlaceColor中的队列
    // std::queue<std::any> getArray()
    // {
    //     return array;
    // }

    // PlaceBase 接口
    int size()
    {
        assert(false);  // 未实现此函数
    }
    void input_tokens(std::any&&)
    {
        assert(false);  // 未实现此函数
    };
    std::any output_tokens()
    {
        assert(false);  // 未实现此函数
    };

    //传入tokens，计算PlaceColor中color的变化同时传入对应数据
    void input_tokens(Eigen::Matrix<int, dim, 1> weights,
        std::queue<std::any>&&                   inputs)
    {
        for (int index = 0; index < dim; ++index) {
            if (weights(index, 0) != 0) {
                for (int i = 0; i < weights(index, 0); ++i) {
                    this->array[index].push(std::move(
                        inputs.front()));  // 要求数据的排列是按照颜色的顺序。
                    inputs.pop();
                }
            }
        }
        cl += weights;
    }

    //输出token，计算PlaceColor中color的变化同时传出对应数据
    std::queue<std::any> output_tokens(Eigen::Matrix<int, dim, 1> weights)
    {
        std::queue<std::any> outputs;
        cl -= weights;
        for (int idx = 0; idx < dim; ++idx) {
            if (weights(idx, 0) != 0) {
                outputs.push(std::move(this->array[idx].front()));
                this->array[idx].pop();
            }
        }
        return std::move(outputs);
    }

    Eigen::Matrix<int, dim, 1> vector_size()
    {
        return this->cl;
    }
};

