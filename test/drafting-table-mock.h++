#pragma once

#include "drafting-table.h++"
#include "gmock/gmock.h"

class DraftingTableMock: public DraftingTable {
public:
  DraftingTableMock(): DraftingTable(0, 0, 0.0) {}
  MOCK_CONST_METHOD1(saveToPNG, void(const std::string &filename));
  MOCK_METHOD3(drawCharacter, void(size_t x, size_t y, char c));
  MOCK_METHOD2(drawSolidLineN, void(size_t x, size_t y));
  MOCK_METHOD2(drawSolidLineS, void(size_t x, size_t y));
  MOCK_METHOD2(drawSolidLineE, void(size_t x, size_t y));
  MOCK_METHOD2(drawSolidLineW, void(size_t x, size_t y));
  MOCK_METHOD2(drawDashedLineN, void(size_t x, size_t y));
  MOCK_METHOD2(drawDashedLineS, void(size_t x, size_t y));
  MOCK_METHOD2(drawDashedLineE, void(size_t x, size_t y));
  MOCK_METHOD2(drawDashedLineW, void(size_t x, size_t y));
  MOCK_METHOD2(drawArrowNtoCenter, void(size_t x, size_t y));
  MOCK_METHOD2(drawArrowStoCenter, void(size_t x, size_t y));
  MOCK_METHOD2(drawArrowEtoCenter, void(size_t x, size_t y));
  MOCK_METHOD2(drawArrowWtoCenter, void(size_t x, size_t y));
  MOCK_METHOD2(drawArrowNtoEdge, void(size_t x, size_t y));
  MOCK_METHOD2(drawArrowStoEdge, void(size_t x, size_t y));
  MOCK_METHOD2(drawArrowEtoEdge, void(size_t x, size_t y));
  MOCK_METHOD2(drawArrowWtoEdge, void(size_t x, size_t y));
};
