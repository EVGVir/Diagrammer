#include "patterns.h++"
#include "diagram.h++"


namespace Patterns {
  using C = ElementClass;


  namespace Lines {
    /// --
    const Pattern Horizontal{{
      {{'-', {C::LineW, C::LineE}}, {'-', {C::LineW, C::LineE}}}
    }};

    /// |
    /// |
    const Pattern Vertical{{
      {{'|', {C::LineS, C::LineN}}},
      {{'|', {C::LineS, C::LineN}}}
    }};
  }


  namespace Corners {
    /// |
    /// +-
    const Pattern NE{{
      {{'|', {C::LineS, C::LineN}}, { 0 , {C::None}}},
      {{'+', {C::LineN, C::LineE}}, {'-', {C::LineW, C::LineE}}}
    }};

    /// +-
    /// |
    const Pattern SE{{
      {{'+', {C::LineS, C::LineE}}, {'-', {C::LineW, C::LineE}}},
      {{'|', {C::LineS, C::LineN}}, { 0 , {C::None}}}
    }};

    /// -+
    ///  |
    const Pattern SW{{
      {{'-', {C::LineW, C::LineE}}, {'+', {C::LineS, C::LineW}}},
      {{ 0 , {C::None}},            {'|', {C::LineS, C::LineN}}}
    }};

    ///  |
    /// -+
    const Pattern NW{{
      {{ 0 , {C::None}},            {'|', {C::LineS, C::LineN}}},
      {{'-', {C::LineW, C::LineE}}, {'+', {C::LineN, C::LineW}}}
    }};
  }


  namespace Arrows {
    /// ^
    /// |
    const Pattern N{{
      {{ 0 , {C::ArrowN}}},
      {{'^', {C::LineS, C::LineN}}},
      {{'|', {C::None}}}
    }};

    /// |
    /// v
    const Pattern S{{
      {{'|', {C::None}}},
      {{'v', {C::LineN, C::LineS}}},
      {{ 0 , {C::ArrowS}}}
    }};

    /// ->
    const Pattern E{{
      {{'-', {C::None}}, {'>', {C::LineW, C::LineE}},  { 0 , {C::ArrowE}}}
    }};

    /// <-
    const Pattern W{{
      {{ 0 , {C::ArrowW}}, {'<', {C::LineE, C::LineW}}, {'-', {C::None}}}
    }};
  }


  void applyAll(Diagram &diagram) {
    diagram.applyPattern(Lines::Horizontal);
    diagram.applyPattern(Lines::Vertical);
    diagram.applyPattern(Corners::NE);
    diagram.applyPattern(Corners::SE);
    diagram.applyPattern(Corners::SW);
    diagram.applyPattern(Corners::NW);
    diagram.applyPattern(Arrows::N);
    diagram.applyPattern(Arrows::S);
    diagram.applyPattern(Arrows::E);
    diagram.applyPattern(Arrows::W);
  }
}
