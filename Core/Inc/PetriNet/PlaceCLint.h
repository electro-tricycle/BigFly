/*
 * PlaceCLint.h
 *
 *  Created on: 2021年7月30日
 *      Author: jay chou
 */

#pragma once
#include "PetriNet/PlaceVectorBase.h"
#include <Eigen/Dense>
template <int dim>
class PlaceCLInt : public PlaceVectorBase<dim>
// Place color Int 类
{
  private:
    std::string                name = " ";
    Eigen::Matrix<int, dim, 1> cl;

  public:
    PlaceCLInt() {}
    // 命名构造
    PlaceCLInt(std::string name)
    {
        this->name = name;
    }
    ~PlaceCLInt() {}
    // // 禁止复制拷贝
    PlaceCLInt(const PlaceCLInt& other) = delete;
    PlaceCLInt& operator=(const PlaceCLInt& other) = delete;
    // Place传递数值构造
    PlaceCLInt(Eigen::Matrix<int, dim, 1> nums)
    {
        this->cl = nums;
    }

    int size()
    {
        assert(false);  // 未实现
    }

    void input_tokens(std::any&&)
    {
        assert(false);  // 未实现
    };
    std::any output_tokens()
    {
        assert(false);  // 未实现
    };

    void input_tokens(Eigen::Matrix<int, dim, 1> weights,
        std::queue<std::any>&&)
    {
        cl += weights;
    }

    //输出token
    std::queue<std::any> output_tokens(Eigen::Matrix<int, dim, 1> weights)
    {
        cl -= weights;
        std::queue<std::any> null;
        return null;
    }
    Eigen::Matrix<int, dim, 1> vector_size(){
        return this->cl;
    }
};
