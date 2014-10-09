#ifndef COLOR_H
#define COLOR_H

class QColor;

namespace Ric{

class Color{
public:
  Color();
  Color(unsigned int c);
  Color(double r, double g, double b);

  unsigned int Argb() const;
  Color Cap();

  Color operator=(const Color &c);

  bool null();
  double r() const;
  double g() const;
  double b() const;

private:
  bool null_;
  double r_;
  double g_;
  double b_;
};

} // namespace

#endif // COLOR_H
