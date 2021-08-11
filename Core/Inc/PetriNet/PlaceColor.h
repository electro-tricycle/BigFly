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
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <tuple>

template <int dim> class PlaceColor : public PlaceVectorBase<dim> {
  private:
    Eigen::Matrix<int, dim, 1>            cl;  // dim代表颜色维度数目
    std::array<std::queue<std::any>, dim> array;  // 一共有dim组存数据的queue
    static std::map<unsigned int, std::shared_ptr<PlaceColor<dim>>> m_instances;
    PlaceColor(unsigned int ID) : PlaceVectorBase<dim>(ID) {}
    // PlaceColor传递数值构造
    PlaceColor(unsigned int                     ID,
        Eigen::Matrix<int, dim, 1>              data,
        std::array<std::queue<std::any>, dim>&& inputs)
        : PlaceVectorBase<dim>(ID)
    {
        this->cl    = std::move(data);
        this->array = std::move(inputs);
    }

  public:
    static std::shared_ptr<PlaceColor<dim>> get_instance(unsigned int ID)
    {
        if (m_instances.find(ID) == m_instances.end()) {
            // 没找到
            auto pointer =
                std::shared_ptr<PlaceColor<dim>>(new PlaceColor<dim>(ID));
            m_instances.insert(
                std::pair<unsigned int, std::shared_ptr<PlaceColor<dim>>>(
                    ID, pointer));
            return pointer;
        }
        else {
            auto pointer = m_instances.at(ID);
            return pointer;
        }
    }

    static std::shared_ptr<PlaceColor<dim>> get_instance(unsigned int ID,
        Eigen::Matrix<int, dim, 1>                                    data,
        std::array<std::queue<std::any>, dim>&&                       inputs)
    {
        if (m_instances.find(ID) == m_instances.end()) {
            // 没找到
            auto pointer =
                std::shared_ptr<PlaceColor<dim>>(new PlaceColor<dim>(ID, data, std::move(inputs)));
            m_instances.insert(
                std::pair<unsigned int, std::shared_ptr<PlaceColor<dim>>>(
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

    ~PlaceColor() {}
    // // 禁止复制拷贝
    PlaceColor(const PlaceColor& other) = delete;
    PlaceColor& operator=(const PlaceColor& other) = delete;

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

template<int dim>
std::map<unsigned int, std::shared_ptr<PlaceColor<dim>>>
    PlaceColor<dim>::m_instances;