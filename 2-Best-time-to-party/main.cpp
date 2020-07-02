#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iterator>
#include <iostream>
#include <vector>

template<typename ForwardIt>
void best_time_to_party_impl(ForwardIt first, ForwardIt last, std::forward_iterator_tag)
{
  using vect_type = decltype(first->first);
  std::vector< vect_type > arrive_time;
  std::vector< vect_type > leave_time;

  while(first != last){
      arrive_time.emplace_back((*first).first); 
      leave_time.emplace_back((*first).second); 
      std::advance(first,1);
  }

  std::make_heap(std::begin(arrive_time), std::end(arrive_time), std::greater<>());
  std::make_heap(std::begin(leave_time), std::end(leave_time), std::greater<>());

  uint32_t best_time = 0;
  uint32_t max_num_celeb = 0;
  uint32_t num_celeb = 0;
  while(arrive_time.size() != 0) { // once the arrive time has reached 0, we don't need to continue
    if(arrive_time[0] <= leave_time[0]){
      ++num_celeb;
      if(num_celeb > max_num_celeb){
        max_num_celeb = num_celeb;
        best_time = arrive_time[0];
      }
      std::pop_heap(std::begin(arrive_time),std::end(arrive_time), std::greater<>());
      arrive_time.pop_back();
    } else {
      assert(num_celeb != 0); 
      --num_celeb;
      std::pop_heap(std::begin(leave_time),std::end(leave_time), std::greater<>());
      leave_time.pop_back();
    } 
  }
  std::cout << "Best time to party is " << best_time << " with amount of celebs = " << max_num_celeb << '\n';
}


template<typename T>
void best_time_to_party(T first, T last)
{
  return best_time_to_party_impl(first, last, typename std::iterator_traits<T>::iterator_category());
}

int main()
{
  std::array<std::pair<uint32_t,uint32_t>, 5> arr = {{{6,8}, {7,10}, {10,12},{4,9},{10,11}}} ;
  best_time_to_party(std::begin(arr), std::end(arr));
  return 0;
}
