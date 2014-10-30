#include "model.h"

#include <QFile>
#include <QDebug>
#include <QStringList>
#include <QtOpenGL>

#include "opengl/textures.h"
#include "material.h"

QMap<QString,Model*> Model::model_;

QString ReadValidLine(QTextStream &in);

Model::Model()
{
}

QStringList Model::load(QString file_name)
{
  QStringList openedObjects;

  qDebug() << "opening model (.obj) file:" << file_name;
  QFile file(file_name);

  if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
    qWarning() << "Failed to open file!" << file_name;
    return openedObjects;
  }

  QTextStream in(&file);

  Model *model = NULL;

  QVector<QVector3D> vertex_;
  QVector<QVector3D> normal_;
  QVector<QVector2D> texture_;

  while(!in.atEnd()){
    QString line = ReadValidLine(in);

    if(line.startsWith("o ")){
      if(!model_.contains(line.mid(2))){
        model_.insert(line.mid(2),new Model());
        model = model_[line.mid(2)];
        model->valid_ = true;
        openedObjects.push_back(line.mid(2));
      }else{
        model = NULL;
      }
    }else if(line.startsWith("mtllib ")){
      QString mtl_name = line.mid(7);
      Material::load(mtl_name);
    }if(model!=NULL){
      if(line.startsWith("v ")){
        // Vertex
        QStringList s = line.split(' ',QString::KeepEmptyParts);
        if(s.size()==4){
          vertex_.push_back(QVector3D(s[1].toFloat(),s[2].toFloat(),s[3].toFloat()));
        }else{
          model->valid_ = false;
        }
      } else if(line.startsWith("vt ")){
        // Vertex Texture
        QStringList s = line.split(' ',QString::KeepEmptyParts);
        if(s.size()==3){
          texture_.push_back(QVector2D(s[1].toFloat(),s[2].toFloat()));
        }else{
          model->valid_ = false;
        }
      }else if(line.startsWith("vn ")){
        // Vertex Normal
        QStringList s = line.split(' ',QString::KeepEmptyParts);
        if(s.size()==4){
          normal_.push_back(QVector3D(s[1].toFloat(),s[2].toFloat(),s[3].toFloat()));
        }else{
          model->valid_ = false;
        }
      }else if(line.startsWith("f ")){
        QStringList s = line.split(' ',QString::KeepEmptyParts);
        if(s.size()==4){
          QStringList s1 = s[1].split("/",QString::KeepEmptyParts);
          QStringList s2 = s[2].split("/",QString::KeepEmptyParts);
          QStringList s3 = s[3].split("/",QString::KeepEmptyParts);

          model->face_.push_back(Face());
          Face *face = &(model->face_.last());
          if( (s1.size()==3 && s2.size()==3 && s3.size()==3) ){
            // vertex info
            face->v[0] = vertex_[s1[0].toInt()-1];
            face->v[1] = vertex_[s2[0].toInt()-1];
            face->v[2] = vertex_[s3[0].toInt()-1];

            // texture info
            face->t[0] = texture_[s1[1].toInt()-1];
            face->t[1] = texture_[s2[1].toInt()-1];
            face->t[2] = texture_[s3[1].toInt()-1];

            // normal info
            face->n[0] = normal_[s1[2].toInt()-1];
            face->n[1] = normal_[s2[2].toInt()-1];
            face->n[2] = normal_[s3[2].toInt()-1];
          }
        }
      }else if(line.startsWith("usemtl ")){
        QString mtl_name = line.mid(7);
        model->material_ = mtl_name;
      }
    }
  }

  qDebug() << "Finished loading model.";
  return openedObjects;
}

void Model::setMaterial()
{
  if(!valid_) return;

  Material *mtl = Material::get(material_);
  if(mtl != NULL){
    mtl->apply_material();
  }
}

void Model::setTexture()
{
  if(!valid_) return;

  Material *mtl = Material::get(material_);
  if(mtl != NULL){
    mtl->apply_texture();
  }
}

void Model::draw() const
{
  if(!valid_) return;

  glBegin(GL_TRIANGLES);

  for(int f=0;f<face_.size();f++){
    for(int i=0;i<3;i++){
      const QVector2D &tex = face_[f].t[i];
      glTexCoord2f(tex.x(),tex.y());
      const QVector3D &norm = face_[f].n[i];
      glNormal3f(norm.x(),norm.y(),norm.z());
      const QVector3D &vert = face_[f].v[i];
      glVertex3f(vert.x(),vert.y(),vert.z());
    }
  }
  glEnd();
}

Model *Model::get(QString model_name)
{
  if(model_.contains(model_name)){
    return model_[model_name];
  }else{
    qWarning() << "Failed to get model:" << model_name;
    return NULL;
  }
}

QStringList Model::getList()
{
  QStringList list;

  for(QMap<QString,Model*>::iterator it = model_.begin(); it!= model_.end(); it++){
    list.push_back(it.key());
  }

  list.sort();

  return list;
}
