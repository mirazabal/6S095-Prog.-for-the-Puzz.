#include <algorithm>
#include <array>
#include <cassert>
#include <iterator>
#include <iostream>
#include <random>
#include <type_traits>

template < typename C, C beginVal, C endVal>
class Iterator {
  typedef typename std::underlying_type<C>::type val_t;
  int val;
public:
  Iterator(const C & f) : val(static_cast<val_t>(f)) {}
  Iterator() : val(static_cast<val_t>(beginVal)) {}
  Iterator operator++() {
    ++val;
    return *this;
  }
  C operator*() { return static_cast<C>(val); }
  Iterator begin() { return *this; } //default ctor is good
  Iterator end() {
      static const Iterator endIter=++Iterator(endVal); // cache it
      return endIter;
  }
  bool operator==(const Iterator& i) const { return val == i.val; }
  bool operator!=(const Iterator& i) const { return !(*this == i); }
};


enum class Suit
{
  Clubs = 0 , Diamonds, Hearts, Spades
};

const char* SuitToString[4] = { "Clubs" , "Diamonds" , "Hearts" , "Spades"};

enum class CardNumber
{
  Ace = 1 , Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King,
};

const char* CardNumberToString[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};


struct Card
{
  Suit suit;
  CardNumber number;
};

using suitIterator = Iterator<Suit, Suit::Clubs, Suit::Spades>; // suitIterator;
using cardNumberIterator = Iterator<CardNumber, CardNumber::Ace, CardNumber::King>; // cardNumberIterator;

class Deck
{
  std::array<Card, 52> cards;
  std::array<Card, 52>::iterator pos;

  public:
    Deck()
    {
      auto it_cards = std::begin(cards);
      for(Suit s: suitIterator()){
        for(CardNumber n : cardNumberIterator() ){
          *it_cards = {s,n};    
          std::advance(it_cards,1);
        } 
      }
      pos = std::begin(cards);
    }

    void shuflle()
    {
      std::random_device rd;
      std::mt19937 g(rd());
      std::shuffle(pos, cards.end(), g);
    }

    Card get_card()
    {
      Card c = *pos;
      std::advance(pos,1);
      return c;
    }
};

template<typename T>
void encode_card(T first, T last, uint32_t encode)
{
  assert(encode < 7);
  std::sort(first,last, [](auto a, auto b){ 
                           const int a_suit = static_cast<int>(a.suit);
                           const int a_number = static_cast<int>(a.number);
                           const int b_suit = static_cast<int>(b.suit);
                           const int b_number = static_cast<int>(b.number);

                           if(a_suit < b_suit)
                              return true;
                           else if(a_suit == b_suit)
                              return a_number < b_number;
                            else 
                              return false;
                            });
 

  Card smallest = *first;
  Card medium = *std::next(first);
  Card largest = *std::next(std::next(first));

  T second = std::next(first);
  T third = std::next(second);

  if(encode > 4){
    *first = largest;
    if(encode == 5){
      *second = smallest; 
      *third = medium; 
    } else {
      *second = medium; 
      *third = smallest; 
    }
  } else if(encode > 2){
    *first = medium; 
    if(encode == 3){
      *second = smallest; 
      *third = largest;
    } else {
      *second = largest; 
      *third = smallest;
    }
  } else{
    *first = smallest;
    if(encode == 1){
      *second = medium; 
      *third = largest; 
    } else {
      *second = largest; 
      *third = medium;
    }
  }
}

void assert_all_cards_different(std::array<Card,5> arr) // passed by value
{
  std::sort(std::begin(arr), std::end(arr), [](auto a, auto b){ return static_cast<int>(a.suit) < static_cast<int>(b.suit); } ); 
  auto it = std::begin(arr);
  auto next = std::next(it);
  while(next != std::end(arr)){
    if(it->suit == next->suit){
      assert(it->number != next->number && "Card duplicated created!!!"); 
    }
    ++next;
    ++it;
  }
}
uint32_t select_first_last_card(std::array<Card,5>& arr)
{

std::sort(std::begin(arr), std::end(arr), [](auto a, auto b){ return static_cast<int>(a.suit) < static_cast<int>(b.suit); } ); 
  auto it = std::adjacent_find(std::begin(arr), std::end(arr), [](auto a, auto b){return static_cast<int>(a.suit) == static_cast<int>(b.suit); } );
  auto it2 = std::next(it);
  
  // first card to show and last card to hide
  uint32_t encode_number = 0;
  const int it_number = static_cast<int>(it->number);
  const int it2_number = static_cast<int>(it2->number);

  if(it_number > it2_number){
    if(it_number - it2_number < 7){
      if(it == std::begin(arr)){
        std::iter_swap(std::begin(arr),it2); 
        it = it2;
      }
      else
        std::iter_swap(std::begin(arr),it2); 

      std::iter_swap(std::begin(arr) + 4,it);
      encode_number = it_number - it2_number; 
    } else{
      if(it2 == std::begin(arr)){
        std::iter_swap(std::begin(arr),it); 
        it2 = it;
      }
      else 
        std::iter_swap(std::begin(arr),it); 

      std::iter_swap(std::begin(arr)+4  ,it2);
      encode_number = 13 - (it_number - it2_number); 
    } 
  }else{
    if(it2_number - it_number < 7){
      if(std::begin(arr) == it2){
        std::iter_swap(std::begin(arr),it); 
        it2 = it;
      } 
      else
        std::iter_swap(std::begin(arr),it); 

      std::iter_swap(std::begin(arr) + 4,it2);
      encode_number = it2_number - it_number; 
    }else{
      if(std::begin(arr) == it){
        std::iter_swap(std::begin(arr),it2); 
        it = it2;
      }
      else 
        std::iter_swap(std::begin(arr),it2); 

      std::iter_swap(std::begin(arr) + 4,it);
      encode_number = 13 - (it2_number - it_number); 
    }
  }

  assert(arr[0].suit == arr[4].suit && "Error selecting the first and last card from the deck...");
  assert(encode_number < 7 && encode_number > 0);

  return encode_number;
}

void arrange_showing_order(std::array<Card,5 >& arr)
{
  const uint32_t encode_number = select_first_last_card(arr);
  encode_card(std::begin(arr) + 1, std::begin(arr) + 4 , encode_number);

  assert(arr[0].suit == arr[4].suit && "Error selecting the first and last card from the deck...");
  assert(encode_number < 7 && encode_number > 0);
  assert_all_cards_different(arr);
}

int main()
{
  Deck d;
  d.shuflle();
  std::array<Card,5> selected_cards;
  for(int i =0; i < 5; ++i){
    selected_cards[i] = d.get_card(); 
  }
  arrange_showing_order(selected_cards);

  for(int i = 0; i < 4; ++i){
    std::cout << "Suit "  <<  SuitToString[static_cast<int>(selected_cards[i].suit)] <<  " Value " << CardNumberToString[static_cast<int>(selected_cards[i].number) -1] << std::endl;  
  }
  std::cout << "Can you guess the next card? Press Enter button to continue...\n";
  getchar();
  std::cout << "Suit "  <<  SuitToString[static_cast<int>(selected_cards[4].suit)] <<  " Value " << CardNumberToString[static_cast<int>(selected_cards[4].number) -1] << std::endl;  
}
