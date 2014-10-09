#ifndef ANIMATION_H
#define ANIMATION_H

class Object;

class Animation
{
public:
  Animation();

  void step();
  void transform();
protected:
  virtual void step_spec()=0;
  virtual void transform_spec()=0;
};

#endif // ANIMATION_H
