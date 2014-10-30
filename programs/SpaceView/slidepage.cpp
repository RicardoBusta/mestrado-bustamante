#include "slidepage.h"

SlidePage::SlidePage(Object *focus=0)
{
  focus_object = focus;
  draw_orbit = false;
}

SlidePage SlidePage::operator=(const SlidePage &p)
{
  focus_object = p.focus_object;
  draw_orbit = draw_orbit;
  return *this;
}
