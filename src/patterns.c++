#include "patterns.h++"
#include "diagram.h++"


namespace Patterns {
  using C = ElementClass;


  namespace Lines {
    namespace Solid {
      /// --
      const Pattern Horizontal{{
        {{'-', {C::SolidLineW, C::SolidLineE}}, {'-', {C::SolidLineW, C::SolidLineE}}}
      }};

      /// |
      /// |
      const Pattern Vertical{{
        {{'|', {C::SolidLineS, C::SolidLineN}}},
        {{'|', {C::SolidLineS, C::SolidLineN}}}
      }};
    }
  }


  namespace Corners {
    namespace Solid {
      /// |
      /// +-
      const Pattern NE{{
        {{'|', {C::SolidLineS, C::SolidLineN}}, { 0 , {}}},
        {{'+', {C::SolidLineN, C::SolidLineE}}, {'-', {C::SolidLineW, C::SolidLineE}}}
      }};

      /// +-
      /// |
      const Pattern SE{{
        {{'+', {C::SolidLineS, C::SolidLineE}}, {'-', {C::SolidLineW, C::SolidLineE}}},
        {{'|', {C::SolidLineS, C::SolidLineN}}, { 0 , {}}}
      }};

      /// -+
      ///  |
      const Pattern SW{{
        {{'-', {C::SolidLineW, C::SolidLineE}}, {'+', {C::SolidLineS, C::SolidLineW}}},
        {{ 0 , {}},                             {'|', {C::SolidLineS, C::SolidLineN}}}
      }};

      ///  |
      /// -+
      const Pattern NW{{
        {{ 0 , {}},                             {'|', {C::SolidLineS, C::SolidLineN}}},
        {{'-', {C::SolidLineW, C::SolidLineE}}, {'+', {C::SolidLineN, C::SolidLineW}}}
      }};
    }
  }


  namespace Arrows {
    /// ^
    /// |
    const Pattern N{{
      {{ 0 , {C::ArrowN}}},
      {{'^', {C::SolidLineS, C::SolidLineN}}},
      {{'|', {C::SolidLineS, C::SolidLineN}}}
    }};

    /// |
    /// v
    const Pattern S{{
      {{'|', {C::SolidLineN, C::SolidLineS}}},
      {{'v', {C::SolidLineN, C::SolidLineS}}},
      {{ 0 , {C::ArrowS}}}
    }};

    /// ->
    const Pattern E{{
      {{'-', {C::SolidLineW, C::SolidLineE}}, {'>', {C::SolidLineW, C::SolidLineE}},  { 0 , {C::ArrowE}}}
    }};

    /// <-
    const Pattern W{{
      {{ 0 , {C::ArrowW}}, {'<', {C::SolidLineE, C::SolidLineW}}, {'-', {C::SolidLineE, C::SolidLineW}}}
    }};
  }


  void applyAll(Diagram &diagram) {
    diagram.applyPattern(Lines::Solid::Horizontal);
    diagram.applyPattern(Lines::Solid::Vertical);
    diagram.applyPattern(Corners::Solid::NE);
    diagram.applyPattern(Corners::Solid::SE);
    diagram.applyPattern(Corners::Solid::SW);
    diagram.applyPattern(Corners::Solid::NW);
    diagram.applyPattern(Arrows::N);
    diagram.applyPattern(Arrows::S);
    diagram.applyPattern(Arrows::E);
    diagram.applyPattern(Arrows::W);
  }
}
