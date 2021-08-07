/*
 * PlaceColor.h
 *
 *  Created on: 2021年7月30日
 *      Author: jay chou
 */

#ifndef INC_PETRINET_PLACECOLOR_H_
#define INC_PETRINET_PLACECOLOR_H_

class Place
//Place color 类
{
private:
    std::string name;
    Eigen::Vector3i cl;
    std::queue<std::any> array;

public:
    Place()
    {
    }
    // 命名构造
    Place(std::string name)
    {
        this->name = name;
    }
    ~Place()
    {
    }
    // // 禁止复制拷贝
    Place(const Place &other) = delete;
    Place &operator=(const Place &other) = delete;
    //Place传递数值构造
    Place(Eigen::Vector3i(data), std::any &&input)
    {
        this->cl = std::move(data);
        this->array.push(std::move(input));
    }
    //返回Place中的颜色token
    Eigen::Vector3i getVector()
    {
        return cl;
    }
    //返回Place中的队列
    std::queue<std::any> getArray()
    {
        return array;
    }
    //返回size
    int size()
    {
        return cl.size();
    }
    //传入tokens，计算place中color的变化同时传入对应数据
    void input_tokens(std::vector<Eigen::Vector3i> output_weights, int i, std::any &&input)
    {
        cl += output_weights[i];
        this->array.push(std::move(input));
    }

    //输出token，计算place中color的变化同时传出对应数据
    std::any output_tokens(std::vector<Eigen::Vector3i> input_weights, int i)
    {
        cl -= input_weights[i];
        std::any output = std::move(this->array.front());
        this->array.pop();
        return output;
    }
};



#endif /* INC_PETRINET_PLACECOLOR_H_ */
