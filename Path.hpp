#ifndef LAB4_PATH
#define LAB4_PATH
#include "DynamicArray.hpp"

class Path
{
private:
    DynamicArray<int> distances;
    DynamicArray<int> path;
public:
    Path() = default;
    
    Path(DynamicArray<int>& distances_, DynamicArray<int>& path_)
    {
        distances = distances_;
        path = path_;
    }
    
    DynamicArray<int> GetDistances()
    {
        return distances;
    }
    
    DynamicArray<int> GetPath()
    {
        return path;
    }
};


#endif //LAB4_PATH
