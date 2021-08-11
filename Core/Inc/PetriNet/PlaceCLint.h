/*
 * PlaceCLint.h
 *
 *  Created on: 2021年7月30日
 *      Author: jay chou
 */

#pragma once
#include "PetriNet/PlaceVectorBase.h"
#include <Eigen/Dense>
#include <map>
#include <memory>

template <int dim>
class PlaceCLInt : public PlaceVectorBase<dim>
// Place color Int 类
{
  private:
    Eigen::Matrix<int, dim, 1>                                      cl;
    static std::map<unsigned int, std::shared_ptr<PlaceCLInt<dim>>> m_instances;
    PlaceCLInt(unsigned int ID) : PlaceVectorBase<dim>(ID) {}
    PlaceCLInt(unsigned int ID, Eigen::Matrix<int, dim, 1> cl)
        : PlaceVectorBase<dim>(ID)
    {
        this->cl = cl;
    }

  public:
    static std::shared_ptr<PlaceCLInt<dim>> get_instance(unsigned int ID)
    {
        if (m_instances.find(ID) == m_instances.end()) {
            // 没找到
            auto pointer = std::shared_ptr<PlaceCLInt<dim>>(new PlaceCLInt<dim>(ID));
            m_instances.insert(
                std::pair<unsigned int, std::shared_ptr<PlaceCLInt<dim>>>(ID, pointer));
            return pointer;
        }
        else {
            auto pointer = m_instances.at(ID);
            return pointer;
        }
    }
    static std::shared_ptr<PlaceCLInt<dim>> get_instance(unsigned int ID, Eigen::Matrix<int, dim, 1> cl)
    {
        auto pointer = std::shared_ptr<PlaceCLInt<dim>>(new PlaceCLInt<dim>(ID, cl));
        m_instances.insert(
            std::pair<unsigned int, std::shared_ptr<PlaceCLInt<dim>>>(ID, pointer));
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

    ~PlaceCLInt() {}
    // // 禁止复制拷贝
    PlaceCLInt(const PlaceCLInt& other) = delete;
    PlaceCLInt& operator=(const PlaceCLInt& other) = delete;

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
    Eigen::Matrix<int, dim, 1> vector_size()
    {
        return this->cl;
    }
};
template <int dim>
std::map<unsigned int, std::shared_ptr<PlaceCLInt<dim>>>
    PlaceCLInt<dim>::m_instances;
