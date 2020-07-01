#include <array>
#include <iterator>
#include <iostream>

template<class ForwardIterator>
void conform_all_impl(ForwardIterator first,  ForwardIterator last, std::forward_iterator_tag)
{
  ForwardIterator it = first;
  ForwardIterator prev = first;
  std::advance(it,1);
  while(it != last){
    if(*it != *first){
        if(*it != *prev){
          std::cout << "Guys starting from index = " << std::distance(first,it);  
        } 
        ForwardIterator next = std::next(it);
        if(next == last || *next != *it) {
          std::cout << " and ending at index = " << std::distance(first,it) << " flip caps \n"; 
        } 
    } 
    std::advance(it,1); 
    std::advance(prev,1); 
  }
}


template<typename T>
void conform_all(T first, T last)
{
 conform_all_impl(first, last, typename std::iterator_traits<T>::iterator_category());
}

int main()
{
  std::array<bool,10> arr = {true, false, false, true, false, false, false, true, false, true};
  conform_all(std::begin(arr), std::end(arr));
  return 0;
}
