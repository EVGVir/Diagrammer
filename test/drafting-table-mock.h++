#pragma once

#include "drafting-table.h++"
#include "gmock/gmock.h"

class DraftingTableMock: public DraftingTable {
public:
  DraftingTableMock(): DraftingTable(0, 0, 0.0) {}
  MOCK_CONST_METHOD1(saveToPNG, void(const std::string &filename));
  MOCK_METHOD3(drawCharacter, void(size_t x, size_t y, char c));
  MOCK_METHOD2(drawLineN, void(size_t x, size_t y));
  MOCK_METHOD2(drawLineS, void(size_t x, size_t y));
  MOCK_METHOD2(drawLineE, void(size_t x, size_t y));
  MOCK_METHOD2(drawLineW, void(size_t x, size_t y));
  MOCK_METHOD2(drawArrowN, void(size_t x, size_t y));
  MOCK_METHOD2(drawArrowS, void(size_t x, size_t y));
  MOCK_METHOD2(drawArrowE, void(size_t x, size_t y));
  MOCK_METHOD2(drawArrowW, void(size_t x, size_t y));
};
