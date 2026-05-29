
#include <iostream>
#include<bits/stdc++.h>
using namespace std;

enum class type{
    circle = 1,
    square = 2,
    rectangle = 3,
};
class shape{
    public:
    virtual void draw() = 0;
    virtual ~shape(){}
};
class circle:public shape{
    public:
    void draw(){ cout<<"Circle";}
};
class square :public shape{
    public:
    void draw(){ cout<<"Square";}
};

class shapeFactory{
    public:
    static unique_ptr<shape> createShape(type t){
        switch(t){
            case type::circle:
                return make_unique<circle>();
            
           case type::square:
                return make_unique<square>();
            default:
            return nullptr;
        }
    }
};
int main()
{
    
    unique_ptr<shape> s = shapeFactory::createShape(type::circle);
    s->draw();
    //delete s;
    return 0;
}