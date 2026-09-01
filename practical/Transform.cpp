#include "Transform.h"

Transform::Transform(int spriteWidth, int spriteHeight)
{
    rotationCenter = D3DXVECTOR2(spriteWidth*0.5,spriteHeight*0.5);
    scalingCenter = D3DXVECTOR2(spriteWidth * 0.5, spriteHeight * 0.5);
    scaling = D3DXVECTOR2(1, 1);
    rotation = 0;
    scalingRotation = 0;
}
void Transform::Scale(float x, float y) {
    scaling = D3DXVECTOR2(x, y);
}
void Transform::Rotate(float rotation) {
    this->rotation += rotation;
}
D3DXMATRIX Transform::Matrix(D3DXVECTOR2 position) {
    D3DXMatrixTransformation2D(&matrix, &scalingCenter, scalingRotation, &scaling, &rotationCenter, rotation, &position);
    return matrix;
}


