/*
 * PlaceColor.h
 *
 *  Created on: 2021年7月30日
 *      Author: jay chou
 */

#ifndef INC_PETRINET_PLACECOLOR_H_
#define INC_PETRINET_PLACECOLOR_H_

#include <any>
#include <queue>
#include <string>
#include <vector>
class Place
// Place color 类
{
  private:
    std::string                  name;
    std::vector<Eigen::Vector3i> cl;
    std::queue<std::any>         array;

  public:
    Place() {}
    // 命名构造
    Place(std::string name)
    {
        this->name = name;
    }
    ~Place() {}
    // // 禁止复制拷贝
    Place(const Place& other) = delete;
    Place& operator=(const Place& other) = delete;
    // Place传递数值构造
    Place(Eigen::Vector3i(data), std::any&& input)
    {
        this->cl.push_back(std::move(data));
        this->array.push(std::move(input));
    }
    //获取
    Eigen::Vector3i getVector(int i)
    {
        return cl[i];
    }
    //获取队列内容
    std::queue<std::any> getArray()
    {
        return array;
    }
    //获取color vector 的长度
    int size()
    {
        return cl.size();
    }
    //输入token
    void input_tokens(std::vector<Eigen::Vector3i> output_weights,
        int                                        i,
        std::any&&                                 input)
    {
        cl[i] += output_weights[i];
        this->array.push(std::move(input));
    }

    //输出token
    std::any output_tokens(std::vector<Eigen::Vector3i> input_weights, int i)
    {
        cl[i] -= input_weights[i];
        std::any output = std::move(this->array.front());
        this->array.pop();
        return output;
    }
};

#endif /* INC_PETRINET_PLACECOLOR_H_ */
