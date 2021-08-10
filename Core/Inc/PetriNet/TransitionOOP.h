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
    std::vector<PlacePoint> m_input_places;
    std::vector<PlacePoint> m_output_places;
    std::vector<int>        m_input_weights;
    std::vector<int>        m_output_weights;
    std::queue<std::any>    m_input_tokens;
    std::queue<std::any>    m_output_tokens;
    std::function<void(std::queue<std::any>&&, std::queue<std::any>&)> m_func;

  public:
    TransitionOOP(std::vector<PlacePoint> input_places,
        std::vector<int>                  input_weights,
        std::vector<PlacePoint>           output_places,
        std::vector<int>                  output_weights,
        std::function<void(std::queue<std::any>&&, std::queue<std::any>&)>
            func     = nullptr,
        int priority = 0)
        : TransitionBase(priority)
    {
        this->m_func           = func;
        this->m_input_places   = input_places;
        this->m_output_places  = output_places;
        this->m_input_weights  = input_weights;
        this->m_output_weights = output_weights;
    };
    ~TransitionOOP(){};

    bool is_ready()
    {
        for (int i = 0; i < m_input_places.size(); ++i) {
            if (m_input_places[i]->size() < m_input_weights[i])
                return false;
        }
        return true;
    }

    void run()
    {
        if (this->m_func == nullptr) {  // 没有挂载函数
            // 取出对于数量的tokens
            for (int i = 0; i < m_input_places.size(); ++i) {
                for (int j = 0; j < m_input_weights[i]; ++j)
                    m_input_places[i]->output_tokens();
            }
            //输入对应数量的tokens, 因为没有挂载函数，所以生成空值std::any
            for (int i = 0; i < m_output_places.size(); ++i) {
                for (int j = 0; j < m_output_weights[i]; ++j)
                    m_output_places[i]->input_tokens(std::move(std::any{}));
            }
        }
        else {  // 挂载了函数
            // 清空缓存用的输入输出
            queue_clear(m_input_tokens);
            queue_clear(m_output_tokens);
            // 取出对应数量的tokens
            for (int i = 0; i < m_input_places.size(); ++i) {
                for (int j = 0; j < m_input_weights[i]; ++j)
                    m_input_tokens.push(std::move(
                        m_input_places[i]
                            ->output_tokens()));  // 取出的tokens放到Transition的缓存中，准备输给挂载的函数
            }

            // 运行挂载的函数，函数将输出值填充进m_output_tokens
            m_func(std::move(m_input_tokens), m_output_tokens);

            // 将函数输出输给对应的place对象
            for (int i = 0; i < m_output_places.size(); ++i) {
                for (int j = 0; j < m_output_weights[i]; ++j) {
                    m_output_places[i]->input_tokens(
                        std::move(m_output_tokens.front()));
                    m_output_tokens.pop();
                }
            }
        }
    }
};

#endif /* INC_PETRINET_TRANSITIONOOP_H_ */
