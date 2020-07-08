#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>


static int solution_num = 0;

static
bool check_rows(uint32_t pos, uint32_t col, const std::vector<uint32_t>& board)
{
  for(int i = 0; i < col; ++i){
    if(board[i] == pos) // conflict
      return true;  
  }
  return false;
}

static 
bool check_dia(uint32_t pos, uint32_t col, const std::vector<uint32_t>& board)
{
  for(int i = 0; i < col; ++i){
    const uint32_t horizontal = col - i; 
    const uint32_t vertical = std::abs(static_cast<int64_t>(board[i]) - static_cast<int64_t>(pos)); 
    if(vertical == horizontal)
      return true;
  }
  return false;
}

static
bool conflict(uint32_t pos, uint32_t col, std::vector<uint32_t> board)
{
  if(col == 0)
    return false;

  const bool row = check_rows(pos,col,board);
  const bool dia = check_dia(pos,col,board);

  return row | dia;
}

static
bool queens(uint32_t col, uint32_t size, std::vector<uint32_t> board)
{
  if(col == size){
    std::cout<< "Solution number " << solution_num <<" found! \n";  
    ++solution_num;
    for(auto it = std::begin(board); it != std::end(board); ++it){
      std::cout << "Column  " << std::distance(std::begin(board), it) <<  " Row " << *it << '\n';  
    }
    return true;
  }

  for(int i =0; i < size; ++i){
    if(!conflict(i,col,board)){
      board[col] = i;
      queens(col+1,size,board); // check all the solutions 
//      if(queens(col+1,size,board) == true){ // check the first solution
//        return true; 
//      }
      }   
  }
  return false; 
}

int main()
{
  std::cout << "Insert the number of queens desired: \n";
  uint32_t num_queens;
  std::cin >> num_queens;
  std::vector<uint32_t> board(num_queens); 
  std::fill(std::begin(board), std::end(board), 0);
  queens(0, num_queens,board);

  return 0;
}
