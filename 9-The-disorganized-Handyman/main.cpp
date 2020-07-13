#include <algorithm>
#include <array>
#include <iostream>
#include <utility>

template<typename T>
T partition(T first, T last)
{
  using Value = typename std::iterator_traits<T>::value_type;
  T pivot = first; 
  first = std::find_if(first,last,[=](auto val){return val > *pivot;});

  if(first == last){ 
    std::iter_swap(pivot,std::prev(last));     
    return first;
  }

  for(auto i = std::next(first); i != last; ++i){
    if(*i < *pivot){
      std::iter_swap(first,i);     
      ++first; 
    } 
  }
  T border = std::prev(first);
  std::iter_swap(pivot, border);
  return border;
}

template<typename T>
void q_sort(T first, T last)
{
  if(first == last || first+1 == last)
    return;

  auto pivot = partition(first,last);
  if(pivot == last)
    return;
  q_sort(first, pivot);
  q_sort(pivot+1, last);
}

int main()
{
  std::array<int32_t, 16> arr = {2,-6,7,123,-56,34,90,-25,324,54,-2,43,21,34,67,-543}; 
  q_sort(std::begin(arr), std::end(arr));
  for(auto v : arr){
    std::cout << v << " ";  
  }
  std::cout << '\n'; 
  return 0;
}

