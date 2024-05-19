

struct TestClass
{
    //template<typename T> 
    //auto add(T t1, T t2) -> T;

    auto addNoTemplate(int i, int j) -> int;

    //template<typename T> 
    //auto addTemplate(T t1, T t2) -> T;

    
    auto addAuto(auto t1, auto t2) -> int;
};

