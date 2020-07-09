#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

typedef struct coordinate_s
{
  uint32_t r;
  uint32_t c;
} Coordinate_t;

int recursiveCourtYard(std::vector<std::vector<int>>& courtyard, uint32_t size, Coordinate_t origin, Coordinate_t miss, int nextPiece)
{
  // missing square: 0 (upper left), 1 (upper right), 2 (lower left), 3 (lower right)
  const uint32_t s_half = size/2;
  const uint32_t missing_square = 2*(miss.r >= s_half) + (miss.c >= s_half); 

  if(size == 2){
    for(int i = 0; i < 2; ++i){ // row
      for(int j = 0; j < 2; ++j){ // column
        if(missing_square != 2*i+j)
          courtyard[origin.r + i][origin.c +j] = nextPiece; 
      } 
    }
    return nextPiece + 1; 
  }       

  // divide in four the courtyard
  for(int i = 0; i < 4; ++i){
    Coordinate_t new_origin = origin;
    new_origin.r += s_half*(i>1);  
    new_origin.c += s_half*(i%2);  
    if(i == missing_square){ // missing hole is in this square 
      Coordinate_t new_missing = miss;
      if(i == 1){
        new_missing.c -= s_half; 
      } else if(i == 2){
        new_missing.r -= s_half; 
      } else if (i == 3){
        new_missing.c -= s_half; 
        new_missing.r -= s_half; 
      }
      nextPiece = recursiveCourtYard(courtyard, s_half, new_origin, new_missing,nextPiece);
    } else {
      Coordinate_t new_missing;
      const int down = (i > 1) ? 1 : 0; 
      const int right = i % 2 ? 1 : 0;
      new_missing.r = (down == false) ? s_half -1 : 0;
      new_missing.c = (right == false) ? s_half -1 : 0;
      nextPiece = recursiveCourtYard(courtyard,s_half,new_origin,new_missing,nextPiece);
    }
  }
  // colocate the next L-shape
  for(int i = 0; i < 2; ++i){
    for(int j = 0; j < 2; ++j){
      if(missing_square != 2*i+j){
        const int row_val = origin.r+s_half-1+i;
        const int col_val = origin.c+s_half-1+j;
        // no previous tile when we colocate the new one
        assert( courtyard[row_val][col_val] == 0); 
        courtyard[row_val][col_val] = nextPiece; 
      }
    }
  } 
  return nextPiece + 1;
}

int main()
{
  std::cout << "Enter the square by square courtyard: \n"; 
  uint32_t num_squares;
  std::cin >> num_squares;

  uint32_t row;
  std::cout << "Enter the row of the square to let empty: \n"; 
  std::cin >> row;

  uint32_t col;
  std::cout << "Enter the col of the square to let empty: \n"; 
  std::cin >> col;

  std::vector<std::vector<int>> courtyard(std::pow(2,num_squares));
  for(auto & v : courtyard)
     std::fill_n(std::back_inserter(v), std::pow(2,num_squares), 0);

  Coordinate_t ori = {0,0};
  Coordinate_t miss = {row,col};
  const int next_piece = 1; 
 recursiveCourtYard(courtyard, std::pow(2,num_squares), ori, miss, next_piece);
  
  for(auto const& vv : courtyard){
    for(auto v : vv){
      if (v < 10)
        std::cout << v << "  ";  
      else
        std::cout << v << " ";  
    } 
    std::cout << '\n';
  }
  return 0;
}
