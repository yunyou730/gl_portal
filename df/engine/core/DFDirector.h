#pragma once

namespace df {

class Renderer;
class Director
{
public:
    Director();
    ~Director();
    
    void DrawScene(Renderer* renderer);
    
    
};
}
