#include <cassert>
#include <cmath>
#include <iostream>

static
uint32_t calculate_radix(double floors, double balls)
{
  return std::ceil(std::pow(floors, 1/balls));
}

static
uint32_t increase_floor(uint32_t radix, uint32_t balls, uint32_t floor)
{
  assert(balls > 0);
  const uint32_t n = std::pow(radix, balls -1); 
  return floor + n;
}

static
void crystall_ball_breaks(uint32_t floors, uint32_t balls)
{
  uint32_t radix = calculate_radix(floors, balls);
  std::cout << "Radix calculated = " << radix << '\n';
  uint32_t lower_limit = 0;
  uint32_t upper_limit = floors;
  uint32_t response = 0;
  uint32_t floor = 0;
  while(true){
    floor = increase_floor( radix, balls, floor); 
    if(floor > floors){
      balls = balls - 1;
      continue;
    }
    
    std::cout << "Did the ball break at floor " << floor << "? type 0 for no or any other number for yes" <<'\n'; 
    std::cin >> response;

    if(response != 0){
      --balls; 
      upper_limit = floor; 
      floor = lower_limit;
    }else {
      lower_limit = floor; 
    }
    
    if(lower_limit + 1 >= upper_limit)
      break;
  }

  std::cout << "Hardness found at floor =  " << lower_limit << '\n';
}



int main()
{
 
  uint32_t floors, balls;
  std::cout << "Please insert the number of floors: \n";
  std::cin >> floors;
  std::cout << "Please insert the number of balls: \n";
  std::cin >> balls;

  crystall_ball_breaks(floors, balls);
  return 0;
}
