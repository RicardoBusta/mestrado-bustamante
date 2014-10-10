#include "textures.h"

#include <QString>

#include "programs/CG1/opengl/scene.h"
#include "programs/CG1/opengl/opengl.h"

Textures *Textures::instance_ = NULL;
QString Textures::current_texture_ = "";

Textures::Textures():
  gl_widget_(NULL)
{
}

Textures *Textures::instance()
{
  if( NULL == instance_ ){
    instance_ = new Textures();
  }
  return instance_;
}

void Textures::setTexture(QString texture)
{
  if( !tex_map_.contains(texture) ){
    qDebug() << "Loading texture:" << texture;
    QImage tex = QImage(texture);
    if(tex.isNull()){
      //qDebug() << "Failed to open image file first time. attempt other directory." << texture;
      tex = QImage(":/texture/"+texture);
      if(tex.isNull()){
        qWarning() << "Failed to open image file." << texture;
        return;
      }
    }
    tex_map_.insert(texture,bindTexture(tex));
    tex_size_.insert(texture,tex.width());
  }

  if( tex_map_.contains(texture) && texture != current_texture_ ){
    glBindTexture(GL_TEXTURE_2D,tex_map_[texture]);
    current_texture_ = texture;
  }
}

void Textures::set3DTexture(QString texture)
{
  if( !tex_map_.contains(texture) ){
    qDebug() << "Loading 3D texture:" << texture;

    QImage tex = QImage(texture);
    if(tex.isNull()){
      tex = QImage(":/texture/"+texture);
      if(tex.isNull()){
        qWarning() << "Failed to open image file." << texture;
        return;
      }
      if(tex.height() != tex.width() * tex.width()){
        qDebug() << "Image Height is not Width * Width. It should be a \"Cube\" Image";
        return;
      }
    }

    // If indexed color, color index 0 will be transparent.
    if(tex.format() == QImage::Format_Indexed8){
      tex.setColor(0,0x00000000);
    }

    GLuint textureID;
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_3D,textureID);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    const UINT64 tex_side = tex.width();
    const UINT64 tex_size = tex_side * tex_side * tex_side;

    GLubyte* tex_data = new GLubyte[tex_size*4];

    for(int i=0; i<tex_size; i++){
      tex_data[4*i+0] = qRed(tex.pixel(i%tex_side,i/tex_side));
      tex_data[4*i+1] = qGreen(tex.pixel(i%tex_side,i/tex_side));
      tex_data[4*i+2] = qBlue(tex.pixel(i%tex_side,i/tex_side));
      tex_data[4*i+3] = qAlpha(tex.pixel(i%tex_side,i/tex_side));
    }

    OpenGL::instance()->texImage3D(GL_TEXTURE_3D,0,GL_RGBA,tex_side,tex_side,tex_side,0,GL_RGBA,GL_UNSIGNED_BYTE,tex_data);
    delete [] tex_data;

    tex_map_.insert(texture,textureID);
    tex_size_.insert(texture,tex.width());
  }

  if( tex_map_.contains(texture) && texture != current_texture_ ){
    glBindTexture(GL_TEXTURE_3D,tex_map_[texture]);
    current_texture_ = texture;
  }
}

void Textures::setGlWidget(QGLWidget *gl_widget)
{
  gl_widget_ = gl_widget;
}

QStringList Textures::getList()
{
  QStringList list;

  if(instance()!=NULL){
    for(QMap<QString,int>::iterator it = instance()->tex_map_.begin(); it!= instance()->tex_map_.end(); it++){
      list.push_back(it.key());
    }
  }

  list.sort();

  return list;
}

int Textures::getTextureSize(QString texture)
{
  if(tex_size_.contains(texture)){
    return tex_size_[texture];
  }else{
    return -1;
  }
}

GLuint Textures::bindTexture(const QImage &tex)
{
  if(NULL == gl_widget_){
    qWarning() << "No QGLWidget set up.";
    return 0;
  }
  return gl_widget_->bindTexture(tex);
}
