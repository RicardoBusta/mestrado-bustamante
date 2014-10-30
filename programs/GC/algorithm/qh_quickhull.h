#ifndef QH_QUICKHULL_H
#define QH_QUICKHULL_H

class QuickHull
{
public:
  QuickHull();

  void reset();

  int last_vertex_input_size_;
  long current_processed_face_;

};

#endif // QH_QUICKHULL_H
