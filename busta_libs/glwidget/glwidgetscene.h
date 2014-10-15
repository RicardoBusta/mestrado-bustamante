#ifndef BUSTA_GLWIDGETSCENE_H
#define BUSTA_GLWIDGETSCENE_H

namespace Busta{

class GLWidgetScene
{
public:
  GLWidgetScene();

  virtual void init();
  virtual void paint();
  virtual void projection();

  float rotx;
  float roty;
};

}

#endif // BUSTA_GLWIDGETSCENE_H
