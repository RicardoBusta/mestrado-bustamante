#ifndef QH_FACE_H
#define QH_FACE_H

#include <QVector3D>
#include <QSet>

class QhFace
{
public:
  QhFace();

  bool is_valid_;
  long vertex_index_[3];
  long neighbour_faces[3];
  QVector3D normal_;
  QVector3D plane_offset_;
  long furthest_vertex_;
  QSet<long> outside_set_;
};

#endif // QH_FACE_H
