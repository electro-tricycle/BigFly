/*
 * operator.h
 *
 *  Created on: 2021年7月30日
 *      Author: jay chou
 */

#ifndef INC_PETRINET_OPERATOR_H_
#define INC_PETRINET_OPERATOR_H_

bool operator<(const Eigen::Vector3i &a, const Eigen::Vector3i &b)
{
    Eigen::Vector3i res;
    res = a - b;
    for (int i = 0; i < a.size(); ++i)
    {
        if (res[i] < 0)
        {
            return true;
        }
    }
    return false;
};




#endif /* INC_PETRINET_OPERATOR_H_ */
