#pragma once
#include "PetriNet/PlaceVectorBase.h"
#include "PetriNet/TransitionBase.h"
#include <any>
#include <functional>
#include <memory>
#include <queue>
#include <vector>

extern void queue_clear(std::queue<std::any>& q);

template <int dim> class TransitionColor : public TransitionBase {
    using PlacePoint = std::shared_ptr<PlaceVectorBase<dim>>;

  private:
    bool                                    completed_flag = true;
    std::vector<PlacePoint>                 m_input_places;
    std::vector<PlacePoint>                 m_output_places;
    std::vector<Eigen::Matrix<int, dim, 1>> m_input_weights;
    std::vector<Eigen::Matrix<int, dim, 1>> m_output_weights;
    std::queue<std::any>                    m_input_tokens;
    std::queue<std::any>                    m_output_tokens;
    std::function<void(std::queue<std::any>&&, std::queue<std::any>&)> m_func;
    std::function<bool(void)> m_is_completed_func;
    static std::map<unsigned int, std::shared_ptr<TransitionColor<dim>>> m_instances;

    TransitionColor(unsigned int                ID,
        std::vector<PlacePoint>                 input_places,
        std::vector<Eigen::Matrix<int, dim, 1>> input_weights,
        std::vector<PlacePoint>                 output_places,
        std::vector<Eigen::Matrix<int, dim, 1>> output_weights,
        std::function<void(std::queue<std::any>&&, std::queue<std::any>&)>
                                  func              = nullptr,
        std::function<bool(void)> is_completed_func = nullptr,
        int                       priority          = 0)
        : TransitionBase(priority, ID)
    {
        this->m_func              = func;
        this->m_is_completed_func = is_completed_func;
        this->m_input_places      = input_places;
        this->m_output_places     = output_places;
        this->m_input_weights     = input_weights;
        this->m_output_weights    = output_weights;
    }

  public:
    ~TransitionColor(){};

    static std::shared_ptr<TransitionColor<dim>> get_instance(unsigned int ID,
        std::vector<PlacePoint>                 input_places,
        std::vector<Eigen::Matrix<int, dim, 1>> input_weights,
        std::vector<PlacePoint>                 output_places,
        std::vector<Eigen::Matrix<int, dim, 1>> output_weights,
        std::function<void(std::queue<std::any>&&, std::queue<std::any>&)>
                                  func              = nullptr,
        std::function<bool(void)> is_completed_func = nullptr,
        int                       priority          = 0)
    {
        if (m_instances.find(ID) == m_instances.end()) {
            auto pointer = std::shared_ptr<TransitionColor<dim>>(new TransitionColor<dim>(ID,
                input_places, input_weights, output_places, output_weights,
                func, is_completed_func, priority));
            m_instances.insert(
                std::pair<unsigned int, std::shared_ptr<TransitionColor<dim>>>(
                    ID, pointer));
            return pointer;
        }
        else {
            auto pointer = m_instances.at(ID);
            return pointer;
        }
    }

    bool is_ready()
    {
        if (m_is_completed_func) {  // 完毕状态才可进行下一次激发
            for (unsigned int i = 0; i < m_input_places.size(); ++i) {
                auto res =
                    m_input_places[i]->vector_size() - m_input_weights[i];
                if ((res.array() < 0).any())  // 存在小于的情况
                    return false;
            }
            return true;
        }
        else {
            return false;
        }
    }
    void run()
    {
        if (this->m_func == nullptr) {  // 无挂载
            for (unsigned  int i = 0; i < m_input_places.size(); ++i) {
                m_input_places[i]->output_tokens(m_input_weights[i]);
            }
            for (unsigned  int j = 0; j < m_output_places.size(); ++j) {
                m_output_places[j]->input_tokens(m_output_weights[j], {});
            }
        }
        else {  // 挂载了函数
            // queue_clear(m_input_tokens);
            // queue_clear(m_output_tokens);

            for (unsigned  int i = 0; i < m_input_places.size(); ++i) {
                m_input_tokens = std::move(
                    m_input_places[i]->output_tokens(m_input_weights[i]));
            }

            m_func(std::move(m_input_tokens), m_output_tokens);  // 调用函数

            if (this->m_is_completed_func !=
                nullptr) {  // 有挂载completed函数的才需要
                this->completed_flag = false;
            }
            else {
                for (unsigned  int j = 0; j < m_output_places.size(); ++j) {
                    m_output_places[j]->input_tokens(
                        m_output_weights[j], std::move(m_output_tokens));
                }
            }
        }
    }
    bool is_completed()
    {
        if (!this->completed_flag)  // 有挂载且为假的才需要判断
        {
            if (this->m_is_completed_func()) {
                // 将函数输出输给对应的place对象
                for (unsigned  int j = 0; j < m_output_places.size(); ++j) {
                    m_output_places[j]->input_tokens(
                        m_output_weights[j], std::move(m_output_tokens));
                }
                this->completed_flag = true;
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return true;
        }
    }
};

template<int dim>
std::map<unsigned int, std::shared_ptr<TransitionColor<dim>>> TransitionColor<dim>::m_instances;
