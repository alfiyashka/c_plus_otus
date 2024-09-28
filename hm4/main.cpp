#include <iostream>
#include <vector>
#include <list>
#include <type_traits>


using namespace std;

/**
* /brief used to define a template type that it's container or not
*
*/
namespace check_type
{
  template<typename T>
  struct is_container: std::false_type {
  };

  template<typename T, typename Alloc>
  struct is_container<std::vector<T, Alloc>>: std::true_type 
  {
  };

  template<typename T, typename Alloc>
  struct is_container<std::list<T, Alloc>>: std::true_type 
  {
  };

  template<typename T>
  struct is_container<std::vector<T>>: std::true_type
  {
  };

  template<typename T>
  struct is_container<std::list<T>>: std::true_type
  {
  };
  
}


/**
* /brief used to check a tuple if it's elements have same type
*
*/
template<typename Head, typename...Tail>
constexpr bool all_same(const std::tuple<Head,Tail...>&){
    return (std::is_same_v<Head,Tail> && ...);
}


namespace printer
{

  /**
  * /brief common function to print value if it's type is not container 
  *
  */
  template <typename T, typename enable_if<!check_type::is_container<T>::value>::type* = nullptr>
  void print_ip(T t)
  {
    std::cout<< t << std::endl;
  }

  /**
  * /brief prints container values
  *
  */
  template <typename T, typename enable_if<check_type::is_container<T>::value>::type* = nullptr>
  void print_ip(T cont)
  {
    std::string separator;
    for(auto item : cont)
    {
      std::cout << separator << std::to_string(item);
      separator = ".";
    }
    std::cout<< std::endl;

  }

  /**
  * /brief print int8_t value as ip
  *
  */
  template <>
  void print_ip(const int8_t t)
  {
    unsigned char unsignedNumber = static_cast<unsigned int8_t>(t);
    std::cout<< std::to_string(unsignedNumber) << std::endl;
  }

 /**
  * /brief print int16_t value as ip
  *
  */
  template <>
  void print_ip<>(const int16_t t)
  {
    unsigned char part1 = t >> 8;
    unsigned char part2 = t & 0xff;
    std::cout<< std::to_string(part1) <<"."<< std::to_string(part2) << std::endl;
  }

 /**
  * /brief print int32_t value as ip
  *
  */
  template <>
  void print_ip(const int32_t t)
  {
    unsigned char part1 = (t & 0xff000000) >> 24;
    unsigned char part2 = (t & 0xff0000) >> 16;
    unsigned char part3 = (t & 0xff00) >> 8;
    unsigned char part4 = t & 0xff;

    std::cout<< std::to_string(part1) << "."
      << std::to_string(part2) << "." 
      << std::to_string(part3) << "."
      << std::to_string(part4) << std::endl;
  }

 /**
  * /brief print int64_t value as ip
  *
  */
  template <>
  void print_ip(const int64_t t)
  {
    unsigned char part1 = (t & 0xff00000000000000) >> 56;
    unsigned char part2 = (t & 0xff000000000000) >> 48;
    unsigned char part3 = (t & 0xff0000000000) >> 40;
    unsigned char part4 = (t & 0xff00000000) >> 32;
    unsigned char part5 = (t & 0xff000000) >> 24;
    unsigned char part6 = (t & 0xff0000) >> 16;
    unsigned char part7 = (t & 0xff00) >> 8;
    unsigned char part8 = t & 0xff;

    std::cout << std::to_string(part1) << "."
      << std::to_string(part2) << "." 
      << std::to_string(part3) << "."
      << std::to_string(part4) << "."
      << std::to_string(part5) << "."
      << std::to_string(part6) << "." 
      << std::to_string(part7) << "."
      << std::to_string(part8) << std::endl;
  }

 /**
  * /brief prints tuple ip (index of tuple calculates on compile time)
  *
  */
  template<class TupType, size_t... I>
  void printTuple(const TupType& _tup, std::index_sequence<I...>)
  {
    (..., (std::cout << (I == 0? "" : ".") << std::get<I>(_tup)));
    std::cout << std::endl;
  }

 /**
  * /brief checks that tuple has elements with same type and prints tuple ip 
  *
  */
  template <typename ... ARGS>
  void print_ip(const std::tuple<ARGS...> t)
  {
    static_assert(all_same(t));
    printTuple(t, std::make_index_sequence<sizeof...(ARGS)>());
  }
}

int main()
{ 
  // result
  printer::print_ip( int8_t{-1} ); // 255
  printer::print_ip( int16_t{0} ); // 0.0
  printer::print_ip( int32_t{2130706433} ); // 127.0.0.1
  printer::print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
  printer::print_ip( std::string{"Hello, World!"} ); // Hello, World!
  printer::print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
  printer::print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
  printer::print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
  return 0;
}
