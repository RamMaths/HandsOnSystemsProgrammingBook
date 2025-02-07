#include <typeinfo>
#include <iostream>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <cxxabi.h>

template<typename T>
std::string type_name() 
{
  int status;
  std::string name = typeid(T).name();

  auto demangled_name = abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status);

  if(status == 0) {
    name = demangled_name;
    std::free(demangled_name);
  }

  return name;
}

template<typename T1, typename T2>
void
are_equal()
{
  #define red "\033[1;31m"
  #define reset "\033[0m"

  std::cout << type_name<T1>() << " vs " << type_name<T2>() << '\n';

  if(sizeof(T1) == sizeof(T2)) {
    std::cout << " - size: both == " << sizeof(T1) << '\n';
  } else {
    std::cout << red " - size: "
              << sizeof(T1)
              << " != "
              << sizeof(T2)
              << reset "\n";
  }

  if(type_name<T1>() == type_name<T2>()) {
    std::cout << " - name: both == " << type_name<T1>() << '\n';
  } else {
    std::cout << red " - name: "
              << type_name<T1>()
              << " != "
              << type_name<T2>()
              << reset "\n";
  }
}

int main() {
  are_equal<uint8_t, int8_t>();
  return 0;
}
