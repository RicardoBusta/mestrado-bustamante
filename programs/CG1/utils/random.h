#ifndef RANDOM_H
#define RANDOM_H

class Random
{
public:

  // [0 .. RAND_MAX]
  static int get();

  // [0.0f .. 1.0f]
  static float getF();

private:
  Random();

  static bool initialized_;
};

#endif // RANDOM_H
