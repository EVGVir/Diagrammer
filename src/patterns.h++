#pragma once

#include "diagram.h++"


namespace Patterns {
  namespace Lines {
    extern const Pattern Horizontal;
    extern const Pattern Vertical;
  }
  namespace Corners {
    extern const Pattern NE;
    extern const Pattern SE;
    extern const Pattern SW;
    extern const Pattern NW;
  }
  namespace Arrows {
    extern const Pattern N;
    extern const Pattern S;
    extern const Pattern E;
    extern const Pattern W;
  }

  /// Applies all available patterns to a diagram.
  ///
  /// @param diagram Diagram, patterns to be applied to.
  void applyAll(Diagram &diagram);
}
