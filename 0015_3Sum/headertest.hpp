

struct TestClass
{


    auto addNoTemplate(int i, int j) -> int;

    
    auto addWithAuto(auto i, auto j) -> int
    {
        return i + j;
    }

    //{
    //    return i+j;
    //}

    //template<typename T> 
    //auto addTemplate(T t1, T t2) -> T;

    
    //auto addAuto(auto t1, auto t2) -> int;
};

