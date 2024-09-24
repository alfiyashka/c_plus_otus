#include <iostream>
#include <map>
#include "src/CustomAllocator.hpp"
#include "src/CustomMap.hpp"
using namespace std;

int factorial (const int number)
{
     if (number <= 1) {
         return 1;
     }
     return number * factorial(number - 1);
}


int main()
{
  const int elementsCount = 10;
  using StdIntsMap = std::map<int, int>;
  StdIntsMap stdMapWithInt;
  for (int i = 0; i < elementsCount; i++)
  {
    stdMapWithInt.insert(StdIntsMap::value_type(i, factorial(i)));
  }

  for (auto intPair : stdMapWithInt)
  {
    std::cout<<intPair.first << " " << intPair.second << std::endl;
  }

  using StdIntsMapWithAllocator = std::map<int, int, std::less<int>,
      CustomAllocator<StdIntsMap::value_type>  >;
  StdIntsMapWithAllocator stdMapWithIntWithAlloc;
  for (int i = 0; i < elementsCount; i++)
  {
    stdMapWithIntWithAlloc.insert(StdIntsMapWithAllocator::value_type(i, factorial(i)));
  }
  
  std::cout<<"Output of ints map with custom allocator" << std::endl;
  for (auto intPair : stdMapWithIntWithAlloc)
  {
    std::cout<<intPair.first << " " << intPair.second << std::endl;
  }

  using CustomIntsMap = CustomMap<int, int>;
  CustomIntsMap customIntsMap;
  for (int i = 0; i < elementsCount; i++)
  {
    customIntsMap.insert(CustomIntsMap::value_type(i, factorial(i)));
  }
  std::cout<<"Output of custom ints map" << std::endl;
  for (auto iter = customIntsMap.begin(); iter != customIntsMap.end(); ++iter)
  {
    std::cout<<iter->getKey()<< " " << iter->getValue() << std::endl;
  }


  using CustomIntsMapWithAlloc = CustomMap<int, int, std::greater<int>, CustomAllocator<CustomNode<int, int> > >;
  CustomIntsMapWithAlloc customIntsMapWithAlloc;
  for (int i = 0; i < elementsCount; i++)
  {
    customIntsMapWithAlloc.insert(CustomIntsMapWithAlloc::value_type(i, factorial(i)));
  }
  std::cout<<"Output of custom ints map with custom allocator" << std::endl;
  for (auto iter = customIntsMapWithAlloc.begin(); iter != customIntsMapWithAlloc.end(); ++iter)
  {
    std::cout<<iter->getKey()<< " " << iter->getValue() << std::endl;
  }

}
