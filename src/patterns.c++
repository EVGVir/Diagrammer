#include "patterns.h++"
#include "diagram.h++"


using C = ElementClass;


/// --
const Pattern Horizontal_Solid_Line{{
  {{'-', {C::SolidLineW, C::SolidLineE}}, {'-', {C::SolidLineW, C::SolidLineE}}}
}};


/// |
/// |
const Pattern Vertical_Solid_Line{{
  {{'|', {C::SolidLineS, C::SolidLineN}}},
  {{'|', {C::SolidLineS, C::SolidLineN}}}
}};


/// |
/// +-
const Pattern Solid_Corner_NE{{
  {{'|', {C::SolidLineS, C::SolidLineN}}, { 0 , {}}},
  {{'+', {C::SolidLineN, C::SolidLineE}}, {'-', {C::SolidLineW, C::SolidLineE}}}
}};


/// +-
/// |
const Pattern Solid_Corner_SE{{
  {{'+', {C::SolidLineS, C::SolidLineE}}, {'-', {C::SolidLineW, C::SolidLineE}}},
  {{'|', {C::SolidLineS, C::SolidLineN}}, { 0 , {}}}
}};


/// -+
///  |
const Pattern Solid_Corner_SW{{
  {{'-', {C::SolidLineW, C::SolidLineE}}, {'+', {C::SolidLineS, C::SolidLineW}}},
  {{ 0 , {}},                             {'|', {C::SolidLineS, C::SolidLineN}}}
}};


///  |
/// -+
const Pattern Solid_Corner_NW{{
  {{ 0 , {}},                             {'|', {C::SolidLineS, C::SolidLineN}}},
  {{'-', {C::SolidLineW, C::SolidLineE}}, {'+', {C::SolidLineN, C::SolidLineW}}}
}};


/// ^
/// |
const Pattern Solid_Arrow_N{{
  {{ 0 , {C::ArrowN}}},
  {{'^', {C::SolidLineS, C::SolidLineN}}},
  {{'|', {C::SolidLineS, C::SolidLineN}}}
}};


/// |
/// v
const Pattern Solid_Arrow_S{{
  {{'|', {C::SolidLineN, C::SolidLineS}}},
  {{'v', {C::SolidLineN, C::SolidLineS}}},
  {{ 0 , {C::ArrowS}}}
}};


/// ->
const Pattern Solid_Arrow_E{{
  {{'-', {C::SolidLineW, C::SolidLineE}}, {'>', {C::SolidLineW, C::SolidLineE}},  { 0 , {C::ArrowE}}}
}};


/// <-
const Pattern Solid_Arrow_W{{
  {{ 0 , {C::ArrowW}}, {'<', {C::SolidLineE, C::SolidLineW}}, {'-', {C::SolidLineE, C::SolidLineW}}}
}};


void applyAllPatterns(Diagram &diagram) {
  diagram.applyPattern(Horizontal_Solid_Line);
  diagram.applyPattern(Vertical_Solid_Line);

  diagram.applyPattern(Solid_Corner_NE);
  diagram.applyPattern(Solid_Corner_SE);
  diagram.applyPattern(Solid_Corner_SW);
  diagram.applyPattern(Solid_Corner_NW);

  diagram.applyPattern(Solid_Arrow_N);
  diagram.applyPattern(Solid_Arrow_S);
  diagram.applyPattern(Solid_Arrow_E);
  diagram.applyPattern(Solid_Arrow_W);
}
