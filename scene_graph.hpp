#ifndef SCENEGRAPHDEF
#define SCENEGRAPHDEF

#include <stdexcept>
#include <vector>
#include "object.hpp"

class SceneGraph
{
public:
    int addObject(const Object* obj, int parentIndex = -1)
    {
        if(parentIndex >= 0 && parentIndex < objects.size())
        {
            objects.push_back(*obj);
            _parentIndices.push_back(parentIndex);
            return objects.size() - 1;
        }
        else if (parentIndex == -1)
        {
            objects.push_back(*obj);
            _parentIndices.push_back(-1);
            return objects.size() - 1;
        }
        else
        {
            throw std::out_of_range("Parent index is out of range.");
        }

    };
    void updateDirty()
    {
        for(int i = 0; i < objects.size(); ++i)
        {
            if(i == 0)
            {
                objects[i].UpdateDirty();
            }
            else
            {
                objects[i].UpdateDirty(&objects[parentIndices()[i]]);
            }
        }
    };
    std::vector<Object> getAllObjects() const
    {
        return objects;
    };
    std::vector<int> parentIndices() const 
    {
        return _parentIndices;
    };
private:
    std::vector<Object> objects;
    std::vector<int> _parentIndices;
};

#endif // SCENEGRAPHDEF