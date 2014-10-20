#ifndef BUSTA_GLWIDGETSCENE_H
#define BUSTA_GLWIDGETSCENE_H

namespace Busta{

class GLWidgetScene
{
public:
  GLWidgetScene();

  virtual void init();
  virtual void release();
  virtual void initGL();
  virtual void paintGL();
  virtual void projection();

  float rotx_;
  float roty_;

  float zoom_;
};

}

#endif // BUSTA_GLWIDGETSCENE_H
