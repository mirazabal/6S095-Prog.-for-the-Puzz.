#include <cassert>
#include <cstdint>
#include <cmath>
#include <cstdlib>
#include <iostream>

// 8 queens problem using uint32_t to represent the chessboard. The 8 most significant bits are not used. A row is
// represented by 3 bits

static
bool check_row(uint32_t row, uint8_t column, uint32_t board)
{
  assert(column > 0);
  assert(column < 8);
  assert(row < 8);

  uint32_t copy_board;
  uint8_t col = 0;
  while(col < column ){
    copy_board = board;
     uint8_t pos = 29 - 3*col; 
     copy_board = copy_board << pos;
     copy_board = copy_board >> 29;
     copy_board = copy_board^row; 
     if(copy_board == 0) // there exists another row with the same number 
       return true;
     
     ++col;
 } 
  return false; // no conflict
}

static
bool check_dia(uint32_t row, uint8_t column, uint32_t board)
{
  assert(column > 0);
  assert(column < 8);
  assert(row < 8);

  uint8_t col_b = 0;
  uint32_t row_b;
  while(col_b < column){
    row_b = board;
    row_b = row_b << (29 - 3*col_b);
    row_b = row_b >> 29; 
    assert(row_b < 8); // as it has 3 bits, maximum at 111 => 7
    const uint8_t abs_dist_x = std::abs(static_cast<int64_t>(row_b)-static_cast<int64_t>(row));
    const uint8_t abs_dist_y = std::abs(static_cast<int64_t>(col_b) -static_cast<int64_t>(column)); 
    if(abs_dist_x == abs_dist_y)
      return true; // there is a confilct
    col_b++;
  }
  return false;
}

static
bool conflict(uint8_t row, uint8_t column,uint32_t board)
{
 if(column == 0) 
   return false; 

 const bool row_ans = check_row(row,column,board);
 const bool dia_ans = check_dia(row,column,board);

 return row_ans || dia_ans;
}

static
uint32_t place_queen(uint32_t row, uint8_t column,uint32_t board)
{
  assert(row < 8);
  uint8_t pos = column*3; 
  row = row << pos;
  return board | row;

}

static
bool queens_8(uint8_t row, uint8_t column, uint32_t board)
{
  if(conflict(row,column, board)){
    return false; 
  }

  board = place_queen(row, column, board);
  if(column == 7){
      std::cout<< "Answer found!!! " << board << '\n'; 
      uint32_t col = 0;
      uint32_t row;
      while(col < 8){
       row = board; 
       uint8_t pos = 29 - 3*col;  
       row = row << pos;
       row = row >> 29;
        std::cout << "Col =  " << col << " and row = " << row << '\n';
        ++col;
      }

     return true;
  }
  for(uint8_t i = 0; i < 8; i++){
      const bool ans = queens_8(i,column+1,board); 
      if(ans == true) 
        return true;
   }
  return false;
}

int main()
{
  // every queen in a column, takes 3 bits (i.e., 001, in the 0 column, there is one queen at row 1)
  uint32_t board = {0}; // most significant 8 bits are not used [3] = {0,0,0};
 
  for(int i = 0; i < 8; i++){
    queens_8(i,0,board);
  }

  return 0;
}
