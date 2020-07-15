#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <map>

template<typename T>
uint32_t coin_max_impl(T first, T last, std::map<uint32_t, uint32_t>& map)
{
  const uint32_t it_dist = std::distance(first,last);
  if(it_dist == 0)
    return 0;
  if(it_dist == 1)
    return *first;

  // check whether the value already existed
  const auto it = map.find(it_dist);
  if(it != std::end(map))
    return it->second;

  const uint32_t skip = coin_max_impl(std::next(first), last, map); 
  const uint32_t pick = coin_max_impl(std::next(std::next(first)),last, map) + *first;
  const uint32_t max_val = std::max(skip,pick);
  map[it_dist] = max_val;
  
  return max_val;
}

template<typename T>
uint32_t coin_max(T first, T last)
{
  std::map<uint32_t, uint32_t> map;
  return coin_max_impl(first,last,map);
}

int main()
{
//  std::array<uint32_t,7> arr = {14,3,27,4,5,15,1}; 
  std::array<uint32_t,16> arr = {3,15,17,23,11,3,4,5,17,23,34,17,18,14,12,15}; 
  const uint32_t max_val = coin_max(std::begin(arr),std::end(arr)); 
  std::cout << "Coin max value = " << max_val << '\n';
  return 0;
}
