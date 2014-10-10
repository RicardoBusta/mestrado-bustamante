#include "texturecontainer.h"

#include <QDebug>

TextureContainer *instance_ = NULL;

TextureContainer *TextureContainer::instance()
{
  if(instance_== NULL){
    instance_ = new TextureContainer();
  }
  return instance_;
}

void TextureContainer::Clear()
{
  if(instance != NULL){
    while(!instance_->map.empty()){
      delete instance_->map.first();
      instance_->map.remove(instance_->map.firstKey());
    }

    if(instance_!=NULL){
      delete instance_;
    }
  }
}

const QImage* TextureContainer::get(QString name)
{
  if(name=="") return NULL;
  if(map.contains(name) && map[name]!=NULL && !map[name]->isNull()){
    return map[name];
  }else{
    map[name] = new QImage();
    bool res = map[name]->load(name);
//    map[name] = map[name]->mirrored(false,true);
    qDebug() << "Loading" << name << res;
    if(!res || map[name]->isNull()){
      delete map[name];
      map.remove(name);
      return NULL;
    }
    return map[name];
  }
}
