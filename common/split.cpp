#include "split.hpp"

prohorova::Matrix prohorova::split(const prohorova::CompositeShape& compositeShape)
{
  if(!compositeShape.getSize())
  {
    return Matrix();
  }
  Matrix matrix;
  matrix.add(compositeShape[0], 0);
  for (size_t i = 1; i < compositeShape.getSize(); i++)
  {
    bool nextLayer = false;
    for (size_t layer = 0; layer < matrix.getRows(); layer++)
    {
      nextLayer = false;
      for (size_t column = 0; column < matrix[layer].getSize(); column++)
      {
        if (matrix[layer][column]->intersects(compositeShape[i]))
        {
          nextLayer = true;
          break;
        }
      }
      if (!nextLayer)
      {
        matrix.add(compositeShape[i], layer);
        break;
      }
    }
    if (nextLayer)
    {
      matrix.add(compositeShape[i], matrix.getRows());
    }
  }
  return matrix;
}
