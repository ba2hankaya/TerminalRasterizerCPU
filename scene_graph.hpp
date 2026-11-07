#ifndef SCENEGRAPHDEF
#define SCENEGRAPHDEF

#include <stdexcept>
#include <vector>
#include "object.hpp"

class SceneGraph
{
public:
    int addObject(Object* obj, int parentIndex = -1)
    {
        if(obj == nullptr)
        {
            throw std::invalid_argument("Scene object must not be null.");
        }
        if(parentIndex < -1 || (parentIndex >= 0 && static_cast<size_t>(parentIndex) >= objects.size()))
        {
            throw std::out_of_range("Parent index is out of range.");
        }
        objects.push_back(obj);
        _parentIndices.push_back(parentIndex);
        return objects.size() - 1;
    };
    void updateDirty()
    {
        // addObject requires parents to exist, so this order is parent-first.
        for(size_t i = 0; i < objects.size(); ++i)
        {
            const int parentIndex = _parentIndices[i];
            objects[i]->UpdateDirty(parentIndex == -1 ? nullptr : objects[parentIndex]);
        }
    };
    std::vector<Object*> getAllObjects() const
    {
        return objects;
    };
    std::vector<int> parentIndices() const 
    {
        return _parentIndices;
    };
private:
    std::vector<Object*> objects;
    std::vector<int> _parentIndices;
};

#endif // SCENEGRAPHDEF
