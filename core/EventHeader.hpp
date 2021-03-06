#ifndef ANALYSISTREE_BASEEVENTHEADER_H
#define ANALYSISTREE_BASEEVENTHEADER_H

#include "Container.hpp"
#include <TVector3.h>
#include <array>

namespace AnalysisTree {

/**
 * A class for an event header
 */
class EventHeader : public Container {
 public:
  EventHeader() = default;
  explicit EventHeader(Integer_t id) : Container(id){};
  EventHeader(const EventHeader& eh) = default;
  EventHeader(EventHeader&& eh) = default;
  EventHeader& operator=(EventHeader&& eh) = default;
  EventHeader& operator=(const EventHeader& eh) = default;

  /**
   * @return 3D-position of the vertex
   */
  [[nodiscard]] inline TVector3 GetVertexPosition3() const {
    return TVector3(vtx_pos_[Exyz::kX], vtx_pos_[Exyz::kY], vtx_pos_[Exyz::kZ]);
  }

  void SetVertexPosition3(const TVector3& pos) {
    vtx_pos_[Exyz::kX] = pos.Px();
    vtx_pos_[Exyz::kY] = pos.Py();
    vtx_pos_[Exyz::kZ] = pos.Pz();
  }

  template<typename T>
  T GetField(Integer_t iField) const {
    if (iField >= 0)
      return Container::GetField<T>(iField);
    else {
      switch (iField) {
        case EventHeaderFields::kVertexX: return GetVertexX();
        case EventHeaderFields::kVertexY: return GetVertexY();
        case EventHeaderFields::kVertexZ: return GetVertexZ();
        default: throw std::out_of_range("EventHeader::GetField - Index " + std::to_string(iField) + " is not found");
      }
    }
  }

  [[nodiscard]] inline Floating_t GetVertexX() const { return vtx_pos_[Exyz::kX]; }
  [[nodiscard]] inline Floating_t GetVertexY() const { return vtx_pos_[Exyz::kY]; }
  [[nodiscard]] inline Floating_t GetVertexZ() const { return vtx_pos_[Exyz::kZ]; }

  static constexpr size_t GetNumberOfChannels() { return 1; }// needed in order to have EventHeader similar to Detector
  [[nodiscard]] const EventHeader& GetChannel(int i) const {
    if (i == 0) {
      return *this;
    }
    throw std::out_of_range("EventHeader::GetChannel - Input " + std::to_string(i) + " !=0");
  }// needed in order to have EventHeader similar to Detector

 protected:
  std::array<Floating_t, 3> vtx_pos_{{UndefValueFloat, UndefValueFloat, UndefValueFloat}};
};

}// namespace AnalysisTree
#endif//ANALYSISTREE_BASEEVENTHEADER_H
