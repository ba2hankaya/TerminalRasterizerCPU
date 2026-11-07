#ifndef COLORDEF
#define COLORDEF

class Color
{
    private:
    float r;
    float g;
    float b;
    float a;

    public:
    Color(float r = 0, float g = 0, float b = 0, float a = 1)
    {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a; //probably not going to use, but for forward compatibility
    }
};

#endif