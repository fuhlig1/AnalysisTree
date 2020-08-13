#include "Module.hpp"

namespace AnalysisTree {

bool operator==(const AnalysisTree::Module& that, const AnalysisTree::Module& other) {
  if (&that == &other) {
    return true;
  }
  if ((Container&) that != (Container&) other) {
    return false;
  }
  return that.number_ == other.number_ && that.signal_ == other.signal_;
}

void Module::Print() const {
  std::cout << "  number = " << number_ << "  signal = " << signal_ << std::endl;
}

}// namespace AnalysisTree