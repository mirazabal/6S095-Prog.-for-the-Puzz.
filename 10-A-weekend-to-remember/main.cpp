#include <map>
#include <iostream>
#include <vector>

enum class Color {
  red,
  blue
};

bool contains(std::map<const char*, Color>& coloring, const char* key)
{
  auto it = coloring.find(key);
  if(it == std::end(coloring)) 
    return false;

  return true;
}

static
bool is_bipartite(const std::map<const char*, const std::vector<const char*>>& graph, const char* vertex, Color color, std::map<const char*, Color>& coloring)
{
  if(contains(coloring, vertex)){
    if(coloring[vertex] == color)
      return true;
    return false;
  } 
  coloring[vertex] = color;
  Color new_color = color == Color::blue? Color::red : Color::blue;

  auto v = graph.at(vertex); // need to return a const reference, [] does not work
  for(auto n : v){
   if(is_bipartite(graph,n,new_color, coloring) == false)
     return false;
  }
  return true;
}

int main()
{
  std::map<const char*, const std::vector<const char*>> graph = { {"A",{"B"} },
                                                            {"B",{"A","C"}},
                                                            {"C",{"B","D"}},
                                                            {"D",{"C","E","F"}},
                                                            {"E",{"D"}},
                                                            {"F",{"G","H","I"}},
                                                            {"G",{"F"}},
                                                            {"H",{"F"}},
                                                            {"I",{"F"}},
                                                                };
  std::map<const char*, Color> coloring;
  if(is_bipartite(graph, "A", Color::red, coloring)){
    std::cout << "Coloring possible \n";
    for(const auto& [key, value]: coloring){
      std::cout << key << " with color " <<  (value == Color::red ? "red" : "blue") << '\n' ;  
    } 
  
  } else {
    std::cout << "Coloring not possible ! \n";  
  }

  return 0;
}
