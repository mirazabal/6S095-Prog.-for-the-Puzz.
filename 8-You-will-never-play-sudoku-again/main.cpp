#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <stdlib.h>

struct Coordinate
{
  int32_t row;
  int32_t col;
};

static
Coordinate find_next_empty_cell(const std::array<std::array<uint32_t,9>,9>& table)
{
  for(auto i = 0; i < table.size(); i++){
    for(auto j = 0; j < table[0].size(); ++j ){
      if(table[i][j] == 0){
        return {i,j}; 
      } 
    }
  }
  return {-1,-1}; 
}

static
bool check_valid_row(const std::array<std::array<uint32_t,9>,9>& table, uint32_t row, uint32_t val)
{
  auto it = std::find(std::begin(table[row]), std::end(table[row]), val);
  if(it != std::end(table[row]))
    return false;
  return true; 
}

static
bool check_valid_col(const std::array<std::array<uint32_t,9>,9>& table, uint32_t col, uint32_t val)
{
  for(auto i = 0; i < 9; ++i){
    if(table[i][col] == val)
      return false;
  }
  return true;
}

static
bool check_valid_sector(const std::array<std::array<uint32_t,9>,9>& table, uint32_t row, uint32_t col, uint32_t val)
{
  const int sector_row = 3*(row/3);
  const int sector_col = 3*(col/3);
  for(int i = 0; i < 3; ++i){
    for(int j = 0; j < 3; ++j){
      if(table[sector_row+i][sector_col+j] == val)
        return false;
    } 
  }
  return true;
}

static
bool is_valid(const std::array<std::array<uint32_t,9>,9>& table, uint32_t row, uint32_t col, uint32_t val)
{
  // check row
  bool valid_row = check_valid_row(table, row, val); 
  if(valid_row == false)
    return false;
 // check column
  bool valid_col = check_valid_col(table, col, val); 
  if(valid_col == false)
    return false;
  // check 3x3 sector
  return check_valid_sector(table, row, col, val);
} 

static
bool solve_sudoku(std::array<std::array<uint32_t, 9>, 9>& table )
{
  auto c = find_next_empty_cell(table);
  if(c.col == -1 && c.row == -1) // no more empty cells && all the requirements are valid 
    return true;
  for(int i = 1 ; i < 10; ++i){
    if(is_valid(table, c.row, c.col, i)){
      table[c.row][c.col] = i; 
      if(solve_sudoku(table) == false){
        table[c.row][c.col] = 0; 
      } else
        return true;
    } 
  }
  return false;
}

static
void print_sudoku(std::array<std::array<uint32_t, 9>, 9> const& table)
{
  int counter_rows = 0;
  for(auto& arr: table){
    int counter_cols = 0;
    for(auto v : arr){
      if(counter_cols%3 == 0)
        std::cout << "   "; 
      std::cout<< v << ", ";  
      counter_cols++;
    } 
    std::cout << '\n';
    ++counter_rows;
    if(counter_rows%3 == 0)
      std::cout << '\n';
  }
}

int main()
{
  std::array<std::array<uint32_t, 9>, 9> table = {{ { 0, 0, 0,   1, 0, 4,  0, 0, 0 },
    { 0, 0, 1,   0, 0, 0,  8, 0, 0 },
    { 0, 8, 0,   7, 0, 3,  0, 6, 0 },

    { 9, 0, 7,   0, 0, 0,  1, 0, 6 },
    { 0, 0, 0,   0, 0, 0,  0, 0, 0 },
    { 3, 0, 4,   0, 0, 0,  5, 0, 8 },

    { 0, 5, 0,   2, 0, 6,  0, 3, 0 },
    { 0, 0, 9,   0, 0, 0,  6, 0, 0 },
    { 0, 0, 0,   8, 0, 5,  0, 0, 0 }
  }};

  if(solve_sudoku(table) == true){
    print_sudoku(table);
  } else {
    std::cout << "Not solvable sudoku inserted!!!\n"; 
  }
  return 0;
}

