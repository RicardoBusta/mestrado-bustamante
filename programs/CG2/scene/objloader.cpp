#include "objloader.h"

#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QFile>
#include <QDebug>
#include <QStringList>

ObjLoader::ObjLoader()
{
}

SceneObject ObjLoader::LoadObj(QString filename, QMap<QString, Ric::Material> *mtl_map)
{
  SceneObject object;

  qDebug() << "load start" << filename;

  QFile file(filename);
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
    qDebug() << "Failed to open file!";
    object.child_objects_.clear();
    return object;
  }

  QTextStream in(&file);

  QVector<QVector3D> v;
  QVector<QVector2D> vt;
  QVector<QVector3D> vn;
  bool fail = false;

  int vert_count = 0;
  SceneObject *obj = NULL;
  while(!in.atEnd()){
    QString line = ReadValidLine(in);
    if(line.startsWith("o "))
      // A new object appeared. Will clear up the previous one and start again.
    {
      qDebug() << line;
      if( obj!=NULL && vert_count > 0 ){
        obj->center_/=vert_count;
        //        qDebug() << "mip" << __LINE__;
      }
      //    qDebug() << "mip" << __LINE__;
      fail = false;
      //      v.clear();
      //      vt.clear();
      //      vn.clear();
      object.child_objects_.push_back(SceneObject());
      obj = & (object.child_objects_.last());
      obj->name = line.mid(2);
      vert_count = 0;
      obj->center_ = QVector3D(0,0,0);
    }else if(fail == true){
      // skip this line, object already failed. wait for next "o"
    }else if(line.startsWith("v "))
      // Vertex Reading
    {
      QStringList s = line.split(' ',QString::KeepEmptyParts);
      if(s.size()==4){
        v.push_back(QVector3D(s[1].toFloat(),s[2].toFloat(),s[3].toFloat()));
        //        UpdateMaxAndMin(max_v,min_v,v.last());
        //                qDebug() << "v[" << v.size()-1 << "]" << v.last();
        obj->center_ += v.last();
        vert_count++;
      }else{
        fail = true;
      }
    } else if(line.startsWith("vt "))
      // Vertex Texture Coord Reading
    {
      QStringList s = line.split(' ',QString::KeepEmptyParts);
      if(s.size()==3){
        //        qDebug() << s[1].toFloat() << s[2].toFloat();
        vt.push_back(QVector2D(s[1].toFloat(),s[2].toFloat()));
        //                qDebug() << "vt[" << vt.size()-1 << "]" << vt.last();
      }else
      {
        fail = true;
      }
    }else if(line.startsWith("vn "))
      // Vertex Normal Reading
    {
      QStringList s = line.split(' ',QString::KeepEmptyParts);
      if(s.size()==4){
        vn.push_back(QVector3D(s[1].toFloat(),s[2].toFloat(),s[3].toFloat()));
        //                qDebug() << "vn[" << vn.size()-1 << "]" << vn.last();
      }else{
        fail = true;
      }
    }else if(line.startsWith("f "))
      // Face Reading
    {
      if(obj == NULL) continue;
      QStringList s = line.split(' ',QString::KeepEmptyParts);
      if(s.size()==4){
        QStringList s1 = s[1].split("/",QString::KeepEmptyParts);
        QStringList s2 = s[2].split("/",QString::KeepEmptyParts);
        QStringList s3 = s[3].split("/",QString::KeepEmptyParts);
        if( (s1.size()>=1 && s2.size()>=1 && s3.size()>=1) &&
            (s1.size()<=3 && s2.size()<=3 && s3.size()<=3) ){
          Ric::Vector v0(v[s1[0].toInt()-1]);
          Ric::Vector v1(v[s2[0].toInt()-1]);
          Ric::Vector v2(v[s3[0].toInt()-1]);
          //                        qDebug() << "f " << s1[0].toInt() << s2[0].toInt() << s1[0].toInt();
          obj->faces_.push_back(TriangleFace(v0,v1,v2,obj->material_));

          if(s1[2]!="" && s2[2]!="" && s3[2]!=""){
            Ric::Vector vn0(vn[s1[2].toInt()-1]);
            Ric::Vector vn1(vn[s2[2].toInt()-1]);
            Ric::Vector vn2(vn[s3[2].toInt()-1]);
            obj->faces_.last().setNormals(vn0,vn1,vn2);
          }

          if(s1[1]!="" && s2[1]!="" && s3[1]!=""){
            //          qDebug() << vt.size() << s1[2].toInt()-1;
            Ric::Vector vt0(vt[s1[1].toInt()-1]);
            Ric::Vector vt1(vt[s2[1].toInt()-1]);
            Ric::Vector vt2(vt[s3[1].toInt()-1]);
            obj->faces_.last().setTexCoords(vt0,vt1,vt2);
          }
          //            qDebug() << obj->faces_.last().v0();
        }else{
          fail = true;
        }
      }else{
        fail = true;
      }
    }else if(line.startsWith("usemtl ")){
      QStringList s = line.split(' ',QString::KeepEmptyParts);
      if(s.size()==2){
        if(mtl_map != NULL && mtl_map->contains(s[1])){
          obj->material_ = (*mtl_map)[s[1]];
        }else{
          obj->material_ = Ric::Material::Create(0xffffffff);
        }
      }
    }else
      // Line will be ignored
    {
      //qDebug() << line;
      // do nothing
    }
  }
  //  qDebug() << "built_scene_size" << object.child_objects_.size();

  // Create bounding box

  //  qDebug() << "mip" << __LINE__;

  //object.faces_ += CreateBoundingBox(min_v,max_v);
  qDebug() << "generate?";
  object.GenerateBoundingVolumeRec();

  return object;
}

QMap<QString, Ric::Material> ObjLoader::LoadMtl(QString filename)
{
  qDebug() << "load mtl";
  QMap<QString,Ric::Material> mtl_map;
  QFile file(filename);
  if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
    qDebug() << "Failed to open file!";
    return mtl_map;
  }

  QTextStream in(&file);

  Ric::Material *mtl = NULL;

  bool fail = false;

  while(!in.atEnd()){
    QString line = ReadValidLine(in);

    if(line.startsWith("newmtl ")){
      qDebug() << line;
      QStringList s = line.split(" ");
      mtl_map[s[1]] = Ric::Material();
      mtl = &mtl_map[s[1]];

      fail = false;
    }else if(fail == true){
      // do nothing
    }else if(line.startsWith("Ka ")){
      //      qDebug() << line;
      QStringList s = line.split(" ");
      if(s.size()==4){
        mtl->SetAmbient(s[1].toFloat(),s[2].toFloat(),s[3].toFloat());
        //        qDebug() << mtl->ambient();
      }else{
        fail = true;
      }
    }else if(line.startsWith("Kd ")){
      //      qDebug() << line;
      QStringList s = line.split(" ");
      if(s.size()==4){
        mtl->SetDiffuse(s[1].toFloat(),s[2].toFloat(),s[3].toFloat());
        //        qDebug() << mtl->diffuse();
      }else{
        fail = true;
      }
    }else if(line.startsWith("Ks ")){
      //      qDebug() << line;
      QStringList s = line.split(" ");
      if(s.size()==4){
        mtl->SetSpecular(s[1].toFloat(),s[2].toFloat(),s[3].toFloat());
        //        qDebug() << mtl->specular();
      }else{
        fail = true;
      }

    }else if(line.startsWith("Ni ")){
      QStringList s = line.split(" ");
      if(s.size()==2){
        mtl->SetRefraction(s[1].toDouble());
        qDebug() << "mtl_refraction" << mtl->refraction();
      }
    }else if(line.startsWith("r ")){
      QStringList s = line.split(" ");
      if(s.size()==2){
        mtl->SetReflection(s[1].toDouble());
        qDebug() << "mtl_reflection" << mtl->reflection();
      }
    }else if(line.startsWith("Tr ") || line.startsWith("d ")){
      QStringList s = line.split(" ");
      if(s.size()==2){
        mtl->SetTransparency(1.0-s[1].toDouble());
        qDebug() << "mtl_transparency" << mtl->transparency();
      }
    }else if(line.startsWith("map_Kd ")){
      qDebug() << line << line.mid(QString("map_Kd ").size());
      mtl->SetDifTexture(line.mid(QString("map_Kd ").size()).toStdString());
    }else if(line.startsWith("enviro_map")){
      qDebug() << "ENVIRO_MAP";
      mtl->SetEnviroMap(true);
    }else if(line.startsWith("enviro")){
      qDebug() << "ENVIRO";
      mtl->SetEnviro(true);
    }else if(line.startsWith("islight")){
      qDebug() << "ISLIGHT";
      mtl->SetIsLight(true);
    }else{

    }
  }
}

QString ObjLoader::ReadValidLine(QTextStream &in)
{
  QString out = in.readLine();
  while(out.startsWith('#')){
    //    qDebug() << out;
    out = in.readLine();
  }
  return out;
}

void ObjLoader::UpdateMaxAndMin(QVector3D &max, QVector3D &min, const Ric::Vector &v)
{
  if(max.x() < v.x()){
    max.setX(v.x());
  }

  if(min.x() > v.x()){
    min.setX(v.x());
  }

  if(max.y() < v.y()){
    max.setY(v.y());
  }

  if(min.y() > v.y()){
    min.setY(v.y());
  }

  if(max.z() < v.z()){
    max.setZ(v.z());
  }

  if(min.z() > v.z()){
    min.setZ(v.z());
  }
}

QVector<TriangleFace> ObjLoader::CreateBoundingBox(const QVector3D &min_v, const QVector3D &max_v)
{
  QVector<TriangleFace> faces;

  Ric::Vector p0 = Ric::Vector(min_v.x(),min_v.y(),max_v.z());
  Ric::Vector p1 = Ric::Vector(max_v.x(),min_v.y(),max_v.z());
  Ric::Vector p2 = Ric::Vector(max_v.x(),max_v.y(),max_v.z());
  Ric::Vector p3 = Ric::Vector(min_v.x(),max_v.y(),max_v.z());

  Ric::Vector p4 = Ric::Vector(min_v.x(),min_v.y(),min_v.z());
  Ric::Vector p5 = Ric::Vector(max_v.x(),min_v.y(),min_v.z());
  Ric::Vector p6 = Ric::Vector(max_v.x(),max_v.y(),min_v.z());
  Ric::Vector p7 = Ric::Vector(min_v.x(),max_v.y(),min_v.z());

  //  Ric::Vector p0 = Ric::Vector(-10,-1,1);
  //  Ric::Vector p1 = Ric::Vector(+10,-1,1);
  //  Ric::Vector p2 = Ric::Vector(+10,+1,1);
  //  Ric::Vector p3 = Ric::Vector(-10,+1,1);

  //  Ric::Vector p4 = Ric::Vector(-10,-1,-1);
  //  Ric::Vector p5 = Ric::Vector(+10,-1,-1);
  //  Ric::Vector p6 = Ric::Vector(+10,+1,-1);
  //  Ric::Vector p7 = Ric::Vector(-10,+1,-1);

  faces.push_back(TriangleFace(p0,p1,p2,Ric::Material::Create(0xffffffff)));
  faces.push_back(TriangleFace(p0,p2,p3,Ric::Material::Create(0xffffffff)));

  faces.push_back(TriangleFace(p4,p6,p5,Ric::Material::Create(0xffffffff)));
  faces.push_back(TriangleFace(p4,p7,p6,Ric::Material::Create(0xffffffff)));

  faces.push_back(TriangleFace(p0,p3,p7,Ric::Material::Create(0xffffffff)));
  faces.push_back(TriangleFace(p0,p7,p4,Ric::Material::Create(0xffffffff)));

  faces.push_back(TriangleFace(p1,p5,p6,Ric::Material::Create(0xffffffff)));
  faces.push_back(TriangleFace(p1,p6,p2,Ric::Material::Create(0xffffffff)));

  faces.push_back(TriangleFace(p1,p0,p4,Ric::Material::Create(0xffffffff)));
  faces.push_back(TriangleFace(p1,p4,p5,Ric::Material::Create(0xffffffff)));

  faces.push_back(TriangleFace(p3,p2,p6,Ric::Material::Create(0xffffffff)));
  faces.push_back(TriangleFace(p3,p6,p7,Ric::Material::Create(0xffffffff)));

  //  qDebug() << "faces_size" << faces.size();

  return faces;
}
