// /*
//  * Transition_color.h
//  *
//  *  Created on: 2021年7月30日
//  *      Author: jay chou
//  */

// #ifndef INC_PETRINET_TRANSITION_COLOR_H_
// #define INC_PETRINET_TRANSITION_COLOR_H_

// class Transition
// {
//     using PlacePoint = std::shared_ptr<Place>;

// private:
//     std::vector<PlacePoint> m_input_places;
//     std::vector<PlacePoint> m_output_places;
//     std::vector<Eigen::Vector3i> m_input_weights;
//     std::vector<Eigen::Vector3i> m_output_weights;
//     std::vector<std::any> m_input_tokens;
//     std::vector<std::any> m_output_tokens;
//     std::function<void(std::vector<std::any> &&, std::vector<std::any> &)> m_func;

// public:
//     Transition(
//         std::vector<PlacePoint> input_places, std::vector<Eigen::Vector3i> input_weights,
//         std::vector<PlacePoint> output_places, std::vector<Eigen::Vector3i> output_weights,
//         std::function<void(std::vector<std::any> &&, std::vector<std::any> &)> func = nullptr)
//     {
//         this->m_input_places = input_places;
//         this->m_output_places = output_places;
//         this->m_input_weights = input_weights;
//         this->m_output_weights = output_weights;
//         this->m_input_tokens.resize(m_input_places.size());
//         this->m_output_tokens.resize(m_output_places.size());
//         this->m_func = func;
//     };
//     ~Transition(){};

//     bool is_ready()
//     {
//         for (int i = 0; i < m_input_places.size(); ++i)
//         {
//             if (( m_input_places[i]->getVector(i) < m_input_weights[i]) || (m_input_places[i] ->getArray().size() == 0))
//             {
//                 return false;
//             }
//         }
//         return true;
//     }

//     void run()
//     {
//         if (this->m_func == nullptr)
//         {
//             for (int i = 0; i < m_input_places.size(); ++i)
//             {
//                 m_input_places[i]->output_tokens(m_input_weights, i);
//             }

//             for (int i = 0; i < m_output_places.size(); ++i)
//             {
//                 m_output_places[i]->input_tokens(m_output_weights, i, std::move(std::any{}));
//             }
//         }
//         else
//         {
//             m_input_tokens.clear();
//             m_output_tokens.clear();
//             for (int i = 0; i < m_input_places.size(); ++i)
//             {
//                 for (int j; j < m_input_weights.size(); ++j)
//                 {
//                     m_input_tokens.push_back(std::move(m_input_places[i]->output_tokens(m_input_weights, i)));
//                 }
//             }
//             m_func(std::move(m_input_tokens), m_output_tokens);

//             for (int i = 0; i < m_output_places.size(); ++i)
//             {
//                 for (int j; j < m_output_weights.size(); ++j)
//                 {
//                     m_output_places[i]->input_tokens(m_output_weights, i, std::move(m_output_tokens[i]));
//                 }
//             }
//         }
//     }
// };



// #endif /* INC_PETRINET_TRANSITION_COLOR_H_ */
