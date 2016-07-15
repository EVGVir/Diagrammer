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


/// . .
const Pattern Horizontal_Dashed_Line{{
  {{'.', {C::DashedLineE}}, {' ', {C::DashedLineW, C::DashedLineE}}, {'.', {C::DashedLineW}}}
}};


/// .
/// .
const Pattern Vertical_Dashed_Line{{
  {{'.', {C::DashedLineS}}},
  {{'.', {C::DashedLineN}}}
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


// . . |
const Pattern Horizontal_Dashed_Line_From_W_To_Vertical_Solid_Line {{
  {{'.', {}}, {' ', {}}, {'.', {C::DashedLineE}}, {' ', {C::DashedLineW, C::DashedLineE}}, {'|', {C::DashedLineW}}}
}};


// . .|
const Pattern Horizontal_Dashed_Line_From_W_To_Vertical_Solid_Line_Without_Space {{
  {{'.', {}}, {' ', {}}, {'.', {C::DashedLineE}}, {'|', {C::DashedLineW}}}
}};


// | . .
const Pattern Horizontal_Dashed_Line_From_E_To_Vertical_Solid_Line {{
  {{'|', {C::DashedLineE}}, {' ', {C::DashedLineW, C::DashedLineE}}, {'.', {C::DashedLineW}}, {' ', {}}, {'.', {}}}
}};


// |. .
const Pattern Horizontal_Dashed_Line_From_E_To_Vertical_Solid_Line_Without_Space {{
  {{'|', {C::DashedLineE}}, {'.', {C::DashedLineW}}, {' ', {}}, {'.', {}}}
}};


// -
// .
// .
const Pattern Vertical_Dashed_Line_From_S_To_Horizontal_Solid_Line {{
  {{'-', {C::DashedLineS}}},
  {{'.', {C::DashedLineN}}},
  {{'.', {}}}
}};


// .
// .
// -
const Pattern Vertical_Dashed_Line_From_N_To_Horizontal_Solid_Line {{
  {{'.', {}}},
  {{'.', {C::DashedLineS}}},
  {{'-', {C::DashedLineN}}}
}};


// . . +
const Pattern Horizontal_Dashed_Line_From_W_To_Solid_Corner {{
  {{'.', {}}, {' ', {}}, {'.', {C::DashedLineE}}, {' ', {C::DashedLineW, C::DashedLineE}}, {'+', {C::DashedLineW}}}
}};


// . .+
const Pattern Horizontal_Dashed_Line_From_W_To_Solid_Corner_Without_Space {{
  {{'.', {}}, {' ', {}}, {'.', {C::DashedLineE}}, {'+', {C::DashedLineW}}}
}};


// + . .
const Pattern Horizontal_Dashed_Line_From_E_To_Solid_Corner {{
  {{'+', {C::DashedLineE}}, {' ', {C::DashedLineW, C::DashedLineE}}, {'.', {C::DashedLineW}}, {' ', {}}, {'.', {}}}
}};


// +. .
const Pattern Horizontal_Dashed_Line_From_E_To_Solid_Corner_Without_Space {{
  {{'+', {C::DashedLineE}}, {'.', {C::DashedLineW}}, {' ', {}}, {'.', {}}}
}};


// +
// .
// .
const Pattern Vertical_Dashed_Line_From_S_To_Solid_Corner {{
  {{'+', {C::DashedLineS}}},
  {{'.', {C::DashedLineN}}},
  {{'.', {}}}
}};


// .
// .
// +
const Pattern Vertical_Dashed_Line_From_N_To_Solid_Corner {{
  {{'.', {}}},
  {{'.', {C::DashedLineS}}},
  {{'+', {C::DashedLineN}}}
}};


void applyAllPatterns(Diagram &diagram) {
  diagram.applyPattern(Horizontal_Solid_Line);
  diagram.applyPattern(Vertical_Solid_Line);

  diagram.applyPattern(Horizontal_Dashed_Line);
  diagram.applyPattern(Vertical_Dashed_Line);

  diagram.applyPattern(Solid_Corner_NE);
  diagram.applyPattern(Solid_Corner_SE);
  diagram.applyPattern(Solid_Corner_SW);
  diagram.applyPattern(Solid_Corner_NW);

  diagram.applyPattern(Solid_Arrow_N);
  diagram.applyPattern(Solid_Arrow_S);
  diagram.applyPattern(Solid_Arrow_E);
  diagram.applyPattern(Solid_Arrow_W);

  diagram.applyPattern(Horizontal_Dashed_Line_From_W_To_Vertical_Solid_Line);
  diagram.applyPattern(Horizontal_Dashed_Line_From_W_To_Vertical_Solid_Line_Without_Space);
  diagram.applyPattern(Horizontal_Dashed_Line_From_E_To_Vertical_Solid_Line);
  diagram.applyPattern(Horizontal_Dashed_Line_From_E_To_Vertical_Solid_Line_Without_Space);
  diagram.applyPattern(Vertical_Dashed_Line_From_S_To_Horizontal_Solid_Line);
  diagram.applyPattern(Vertical_Dashed_Line_From_N_To_Horizontal_Solid_Line);

  diagram.applyPattern(Horizontal_Dashed_Line_From_W_To_Solid_Corner);
  diagram.applyPattern(Horizontal_Dashed_Line_From_W_To_Solid_Corner_Without_Space);
  diagram.applyPattern(Horizontal_Dashed_Line_From_E_To_Solid_Corner);
  diagram.applyPattern(Horizontal_Dashed_Line_From_E_To_Solid_Corner_Without_Space);
  diagram.applyPattern(Vertical_Dashed_Line_From_S_To_Solid_Corner);
  diagram.applyPattern(Vertical_Dashed_Line_From_N_To_Solid_Corner);
}
