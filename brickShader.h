#include "shader.h"
#include "listener.h"

class BrickShader : public Shader, public Listener
{
public:
    BrickShader();
    virtual void setShaderUniforms();
    virtual void keyboard(int key, int modifier);

private:
    float mBrickSizes[2];
    float mBrickRatio[2];
};
