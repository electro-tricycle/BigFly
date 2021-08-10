#pragma once
#include "Eigen/Core"
#include "PetriNet/PlaceBase.h"
#include <queue>

template <int dim> class PlaceVectorBase : public PlaceBase {
  private:
    /* data */
  public:
    virtual void input_tokens(Eigen::Matrix<int, dim, 1> weights,
        std::queue<std::any>&&) = 0;
    virtual std::queue<std::any> output_tokens(
        Eigen::Matrix<int, dim, 1> weights) = 0;
    // virtual std::any peek(Eigen::Matrix<int, dim, 1> = 0) = 0;
    virtual Eigen::Matrix<int, dim, 1> vector_size() = 0;
    virtual ~PlaceVectorBase(){};
};
