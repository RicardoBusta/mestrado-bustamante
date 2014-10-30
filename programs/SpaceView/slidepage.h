#ifndef SLIDEPAGE_H
#define SLIDEPAGE_H

class Object;

class SlidePage
{
public:
  SlidePage(Object *focus);

  Object *focus_object;

  bool draw_orbit;

  SlidePage operator=(const SlidePage &p);
};

#endif // SLIDEPAGE_H
