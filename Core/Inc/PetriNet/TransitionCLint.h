// #ifndef INC_PETRINET_TRANSITIONOOP_H_
// #define INC_PETRINET_TRANSITIONOOP_H_

// #include "PlaceBase.h"
// #include <any>
// #include <functional>
// #include <memory>
// #include <vector>
// #include <Eigen/Dense>

// class Transition
// {
// 	//定义TransitionColorInt
//     using PlacePoint = std::shared_ptr<Place>;
//     private:
// 			std::vector<PlacePoint> m_input_places;
//     		std::vector<PlacePoint> m_output_places;
//     		std::vector<Eigen::Vector3i> m_input_weights;
//     		std::vector<Eigen::Vector3i> m_output_weights;
//     		std::vector<Eigen::Vector3i> m_input_tokens;
//             std::vector<Eigen::Vector3i> m_output_tokens;
//     public:
//         Transition(
//         std::vector<PlacePoint> input_places, std::vector<Eigen::Vector3i> input_weights,
//         std::vector<PlacePoint> output_places, std::vector<Eigen::Vector3i> output_weights)
//         {
//         	this->m_input_places = input_places;
//         	this->m_output_places = output_places;
//         	this->m_input_weights = input_weights;
//         	this->m_output_weights = output_weights;
//         	this->m_input_tokens.resize(m_input_places.size());
//         	this->m_output_tokens.resize(m_output_places.size());
//         };
//     ~Transition(){};

//     bool is_ready()
//     {
//         for(int i = 0; i < m_input_places.size(); ++i)
//         {
//             if(m_input_places[i] ->getVector(i) < m_input_weights[i])
//             {
//                 return false;
//             }

//         }
//         return true;
//     }

//     void run()
//     {
//         for (int i = 0; i < m_input_places.size(); ++i)
//       	{
//              m_input_places[i] -> output_tokens(m_input_weights,i);
//         }

//         for (int i = 0; i < m_output_places.size(); ++i)
//         {
//              m_output_places[i] -> input_tokens(m_output_weights,i);

//          }
//     }

// };
