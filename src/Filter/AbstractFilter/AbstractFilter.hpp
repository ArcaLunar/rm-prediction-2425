#ifndef __ABSTRACTFILTER_HPP__
#define __ABSTRACTFILTER_HPP__

#include <string>
#include <Eigen/Core>

class AbstractFilter {
  private:
    std::string m_Model;

  public:
    virtual void Reset();
    virtual void Predict();
    virtual Eigen::MatrixBase<double> Correct();
    virtual 
    void SetModel(const std::string &);
};

#endif