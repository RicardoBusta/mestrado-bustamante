#ifndef TEXTURECONTAINER_H
#define TEXTURECONTAINER_H

#include <QMap>
#include <QString>
#include <QImage>

class TextureContainer
{
public:
  static TextureContainer* instance();
  static void Clear();

  const QImage *get(QString name);
private:
  TextureContainer(){}

  QMap<QString,QImage*> map;
};

#endif // TEXTURECONTAINER_H
