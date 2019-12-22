#include "brickshader.h"

BrickShader::BrickShader()
{
    //    listActiveUniforms();
    mBrickSizes[0] = 1.0f;
    mBrickSizes[1] = 0.5f;
    // Ratio muss zum Seitenverhältnis der Zeichenfläche und der Bricks passen.
    mBrickRatio[0] = 0.9f;
    mBrickRatio[1] = 0.8f;
}

void BrickShader::setShaderUniforms()
{
    Shader::setShaderUniforms();
    this->shaderProgram()->setUniformValue("BrickStepSize", mBrickSizes[0], mBrickSizes[1]);
    this->shaderProgram()->setUniformValue("BrickRatio", mBrickRatio[0], mBrickRatio[1]);
}

void BrickShader::keyboard(int key, int /*modifier*/)
{
    switch (key)
    {
    case 'b':
        mBrickSizes[0] /= 1.1f;
        mBrickSizes[1] /= 1.1f;
        break;
    case 'B':
        mBrickSizes[0] *= 1.1f;
        mBrickSizes[1] *= 1.1f;
        break;
    default:
        break;
    }
}
