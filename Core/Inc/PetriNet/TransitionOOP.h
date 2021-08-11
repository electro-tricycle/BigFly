/*
 * TransitionOOP.h
 *
 *  Created on: 2021年6月21日
 *      Author: wyz
 */

#ifndef INC_PETRINET_TRANSITIONOOP_H_
#define INC_PETRINET_TRANSITIONOOP_H_

#include "PlaceBase.h"
#include "TransitionBase.h"
#include <any>
#include <functional>
#include <map>
#include <memory>
#include <queue>
#include <vector>

void queue_clear(std::queue<std::any>& q)
{
    std::queue<std::any> empty;
    std::swap(empty, q);
}

// 变迁类
class TransitionOOP : public TransitionBase {
    using PlacePoint = std::shared_ptr<PlaceBase>;

  private:
    bool                    completed_flag = true;
    std::vector<PlacePoint> m_input_places;
    std::vector<PlacePoint> m_output_places;
    std::vector<int>        m_input_weights;
    std::vector<int>        m_output_weights;
    std::queue<std::any>    m_input_tokens;
    std::queue<std::any>    m_output_tokens;
    std::function<void(std::queue<std::any>&&, std::queue<std::any>&)> m_func;
    std::function<bool(void)> m_is_completed_func;
    static std::map<unsigned int, std::shared_ptr<TransitionOOP>> m_instances;

    TransitionOOP(unsigned int  ID,
        std::vector<PlacePoint> input_places,
        std::vector<int>        input_weights,
        std::vector<PlacePoint> output_places,
        std::vector<int>        output_weights,
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
    };

  public:
    static std::shared_ptr<TransitionOOP> get_instance(unsigned int ID,
        std::vector<PlacePoint> input_places,
        std::vector<int>        input_weights,
        std::vector<PlacePoint> output_places,
        std::vector<int>        output_weights,
        std::function<void(std::queue<std::any>&&, std::queue<std::any>&)>
                                  func              = nullptr,
        std::function<bool(void)> is_completed_func = nullptr,
        int                       priority          = 0)
    {
        if (m_instances.find(ID) == m_instances.end()) {
            auto pointer = std::shared_ptr<TransitionOOP>(new TransitionOOP(ID,
                input_places, input_weights, output_places, output_weights,
                func, is_completed_func, priority));
            m_instances.insert(
                std::pair<unsigned int, std::shared_ptr<TransitionOOP>>(
                    ID, pointer));
            return pointer;
        }
        else {
            auto pointer = m_instances.at(ID);
            return pointer;
        }
    }
    static std::shared_ptr<TransitionOOP> get_instance(unsigned int ID)
    {
        auto pointer = m_instances.at(ID);
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
    TransitionOOP(const TransitionOOP&) = delete;
    TransitionOOP& operator=(const TransitionOOP&) = delete;
    ~TransitionOOP(){};

    bool is_ready()
    {
        if (m_is_completed_func) {  // 完毕状态才可进行下一次激发
            for (unsigned int i = 0; i < m_input_places.size(); ++i) {
                if (m_input_places[i]->size() < m_input_weights[i])
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
        if (this->m_func == nullptr) {  // 没有挂载函数
            // 取出对于数量的tokens
            for (unsigned int i = 0; i < m_input_places.size(); ++i) {
                for (int j = 0; j < m_input_weights[i]; ++j)
                    m_input_places[i]->output_tokens();
            }
            //输入对应数量的tokens, 因为没有挂载函数，所以生成空值std::any
            for (unsigned int i = 0; i < m_output_places.size(); ++i) {
                for (int j = 0; j < m_output_weights[i]; ++j)
                    m_output_places[i]->input_tokens(std::move(std::any{}));
            }
        }
        else {  // 挂载了函数
            // 清空缓存用的输入输出
            queue_clear(m_input_tokens);
            queue_clear(m_output_tokens);
            // 取出对应数量的tokens
            for (unsigned int i = 0; i < m_input_places.size(); ++i) {
                for (int j = 0; j < m_input_weights[i]; ++j)
                    m_input_tokens.push(std::move(
                        m_input_places[i]
                            ->output_tokens()));  // 取出的tokens放到Transition的缓存中，准备输给挂载的函数
            }

            // 运行挂载的函数，函数将输出值填充进m_output_tokens
            m_func(std::move(m_input_tokens), m_output_tokens);

            if (this->m_is_completed_func !=
                nullptr) {  // 有挂载completed函数的才需要
                this->completed_flag = false;
            }
            else {  // 否则直接输出
                for (unsigned int i = 0; i < m_output_places.size(); ++i) {
                    for (int j = 0; j < m_output_weights[i]; ++j) {
                        m_output_places[i]->input_tokens(
                            std::move(m_output_tokens.front()));
                        m_output_tokens.pop();
                    }
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
                for (unsigned int i = 0; i < m_output_places.size(); ++i) {
                    for (int j = 0; j < m_output_weights[i]; ++j) {
                        m_output_places[i]->input_tokens(
                            std::move(m_output_tokens.front()));
                        m_output_tokens.pop();
                    }
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

std::map<unsigned int, std::shared_ptr<TransitionOOP>>
    TransitionOOP::m_instances;

#endif /* INC_PETRINET_TRANSITIONOOP_H_ */
