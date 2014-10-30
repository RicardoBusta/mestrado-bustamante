#include "material.h"

#include "opengl/textures.h"
#include "opengl/common.h"

QMap<QString,Material> Material::material_;

Material::Material():
  invalid_(true)
{
}

void Material::load(QString file_name)
{
  qDebug() << "opening material file:" << file_name;
  QFile file(file_name);

  QVector<Material> output;

  if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
    //qWarning() << "Failed to open file:" << file_name;
    file.setFileName(":/material/"+file_name);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
      qWarning() << "Failed to open file: :/material/"+file_name;
      return;
    }
  }

  QTextStream in(&file);

  Material *mtl = NULL;

  bool skip = false;
  while(!in.atEnd()){
    QString line = ReadValidLine(in);

    if(line.startsWith("newmtl ")){
      QString mtl_name = line.mid(7);
      if(material_.contains(mtl_name)){
        skip=true;
      }else{
        material_.insert(mtl_name,Material());
        mtl = &material_[mtl_name];
        mtl->name_ = mtl_name;
        mtl->invalid_ = false;
        skip = false;
      }
    }else if(mtl!=NULL && skip!=true){

      if(line.startsWith("Ns ")){
        QStringList s = line.split(" ");
        if(s.size()==2){
          mtl->shininess_ = s[1].toFloat();
        }else{
          mtl->invalid_ = true;
        }
      }else if(line.startsWith("Ka ")){
        QStringList s = line.split(" ");
        if(s.size()==4){
          mtl->ambient_ = QVector3D(s[1].toFloat(),s[2].toFloat(),s[3].toFloat());
        }else{
          mtl->invalid_ = true;
        }
      }else if(line.startsWith("Kd ")){
        QStringList s = line.split(" ");
        if(s.size()==4){
          mtl->diffuse_ = QVector3D(s[1].toFloat(),s[2].toFloat(),s[3].toFloat());
        }else{
          mtl->invalid_ = true;
        }
      }else if(line.startsWith("Ks ")){
        QStringList s = line.split(" ");
        if(s.size()==4){
          mtl->specular_= QVector3D(s[1].toFloat(),s[2].toFloat(),s[3].toFloat());
        }else{
          mtl->invalid_ = true;
        }
      }else if(line.startsWith("Ni ")){

      }else if(line.startsWith("d ") || line.startsWith("Tr ")){
        QStringList s = line.split(" ");
        if(s.size()==2){
          mtl->transparency_= s[1].toFloat();
        }else{
          mtl->invalid_ = true;
        }
      }else if(line.startsWith("illum ")){
        QStringList s = line.split(" ");
        if(s.size()==2){
          mtl->illum_ = s[1].toInt();
        }else{
          mtl->invalid_ = true;
        }
      }else if(line.startsWith("map_Kd ")){
        mtl->texture_ = line.mid(7);
      }
    }
  }
  qDebug() << "Finished loading material.";
}

void Material::apply_material() const
{
  if(invalid_) return;

  glColor3f(1,1,1);
}

void Material::apply_texture() const
{
  if(invalid_) return;

  Textures::instance()->setTexture(texture_);
}

Material *Material::get(QString mtl_name)
{
  return &material_[mtl_name];
}

QStringList Material::getList()
{
  QStringList list;

  for(QMap<QString,Material>::iterator it = material_.begin(); it!= material_.end(); it++){
    list.push_back(it.key());
  }

  list.sort();

  return list;
}
