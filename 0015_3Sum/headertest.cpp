
#include "headertest.hpp"



//auto TestClass::addNoTemplate(int i, int j) -> int
//{
//    return i + j;
//}

//template<typename T> 
//auto TestClass::addTemplate(T t1, T t2) -> T
//{
//    return t1 + t2;
//}


auto TestClass::addAuto(auto t1, auto t2) -> int
{
    return t1 + t2;
}

auto TestClass::addNoTemplate(int i, int j) -> int
{
    //return addAuto(i,j);
    return i + j;
}
