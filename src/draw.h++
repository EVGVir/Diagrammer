#pragma once

#include "diagram.h++"
#include "drafting-table.h++"


/// Draws a diagram using a drafting table.
///
/// @note Patterns must be applied to the diagram prio to its drawing.
///
/// @param diagram Diagram to be drawn.
/// @param table Drafting table that is used to draw the diagram.
void drawDiagram(Diagram &diagram, DraftingTable &table);


/// Draws a diagram element on a drafting table.
///
/// @param e The element to be drawn.
/// @param table The drafting table that is used to draw the element.
/// @param x Character to be drawn horizontal position.
/// @param y Character to be drawn vertical position.
void drawElement(const DiagramElement &e, DraftingTable &table, size_t x, size_t y);
