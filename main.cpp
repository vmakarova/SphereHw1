#include <iostream>
#include <sstream>
#include <string>


const static std::string SET_UNION = "+";
const static std::string SET_INTERSECTION = "cap";
const static std::string SET_MINUS = "-";
const static size_t BASE_SIZE= 1024;


class MySet {
  int32_t *elements;
  size_t size;
  
public:  
  MySet(size_t size = 0);
  ~MySet();
  MySet(const MySet&) = default;
  MySet& operator=(const MySet&) = default;
  
  MySet(MySet&&) = default;
  MySet& operator=(MySet&&) = default;
  
  MySet myIntersection(const MySet& other);
  MySet operator+(const MySet& other);
  MySet operator-(const MySet& other);
  int32_t operator[] (size_t i) const
  {
      return (i < size) ? elements[i] : 0; 
  }
  
  std::string to_string();
  
  void insert(int32_t elem);
  
};

MySet::MySet(size_t _size)
{
   elements = (int32_t*) malloc((_size == 0 ? 1024 : _size)* sizeof(int32_t));
   size = 0;
}

MySet::~MySet()
{
    free(elements);
}


MySet MySet::operator+(const MySet& other)
{
    MySet answer(size + other.size);
    for (size_t i = 0; i < size; ++i)
        answer.insert(elements[i]);
    for (size_t i = 0; i < other.size; ++i){
        size_t j = 0;
        while (j < size && elements[j] != other[i])
            ++j;
        if (j >= size){
            answer.insert(other[i]);
        }  
    }
    return answer;
}

MySet MySet::operator-(const MySet& other)
{
    MySet answer(size);
    for (size_t i = 0; i < size; ++i){
        size_t j = 0;
        while (j < other.size && other[j] != elements[i])
            ++j;
        if (j >= other.size){
            answer.insert( elements[i]);
        }  
    }
    return answer;
}

MySet MySet::myIntersection(const MySet& other)
{
    MySet answer(size);
    for (size_t i = 0; i < size; ++i){
        size_t j = 0;
        while (j < other.size && other[j] != elements[i])
            ++j;
        if (j < other.size){
            answer.insert(elements[i]);
        }  
    }
    return answer;
}

std::string MySet::to_string()
{
  std::string answer = "{";
  for (size_t i = 0; i < size; i++)
      answer += std::to_string(elements[i]) + " ";
  return answer + "}"; 
}

void MySet::insert(int32_t elem)
{
   elements[size] = elem;
   ++size;
}


int main(int argc, char **argv) {
    std::cout << "Usage: {} for set border, space for separation, " 
              << SET_UNION        << " for union, " 
              << SET_INTERSECTION << " for intersection, "
              << SET_MINUS        << " for minus" << std::endl;
    std::cout << "Template: {1 2 3 } " << SET_UNION << " {4 5 }" << std::endl;
    std::cout << "Answer: {1 2 3 4 5 }." << std::endl;
    std::cout << "ATTENTION! Use space after last set's element and before \"}\"";
    std::string  input_data = "";
    std::getline ( std::cin, input_data);
    size_t pos_begin = input_data.find("{");
    size_t pos_end = input_data.find("}");
    if (pos_begin == input_data.npos || pos_end == input_data.npos){
        std::cout << "incorrect input" << std::endl ; 
        return 0;
    }
    std::string set_string = input_data.substr(pos_begin + 1 , pos_end - pos_begin);
    MySet first(set_string.length());
    std::istringstream iss1(set_string);
    std::string tmp;
    iss1 >> tmp;
    while (tmp != "}"){
        first.insert(std::stoi(tmp));
        iss1 >> tmp;
    }
    pos_begin = input_data.find("{", pos_end + 1);
    
    std::string set_operation = input_data.substr(pos_end, pos_begin);
    
    pos_end = input_data.find("}", pos_begin);
    if (pos_begin == input_data.npos || pos_end == input_data.npos){
        std::cout << "incorrect input" << std::endl ; 
        return 0;
    }
    set_string = input_data.substr(pos_begin + 1 , pos_end - pos_begin);
    MySet second(set_string.length());
    std::istringstream iss2(set_string);
    iss2 >> tmp;
    while (tmp != "}"){
        second.insert(std::stoi(tmp));
        iss2 >> tmp;
    }
    bool no_operation = true;
    if (set_operation.find(SET_UNION) != set_operation.npos){
        std::cout << (first + second).to_string();
        no_operation = false;
    } else if (no_operation && set_operation.find(SET_INTERSECTION) != set_operation.npos) {
        std::cout << (first.myIntersection(second)).to_string();
        no_operation = false;
    } else if (no_operation && set_operation.find(SET_MINUS) != set_operation.npos) {
        std::cout << (first -second).to_string();
        no_operation = false;
    }
    if (no_operation) 
      std::cout << "incorrect input" << std::endl ; 
    return 0;
}
