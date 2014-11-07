#include "glwidget.h"

#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>
#include <QDebug>
#include <iostream>

const bool kUsePerspective = true;
const bool kTransformLight = true;
const bool kEnableLighting = true;

const float kZoomTransform = 1.0f/10000.0f;
const float kRotateTransform = 0.5f;
const Vector4 kLightPosition = Vector4(0,0,0,1);

GLWidget::GLWidget(QWidget *parent) :
  QGLWidget(parent),
  zoom_(10000),
  rotx_(0),
  roty_(0),
  rotz_(0)
{

  /*  Timer que chama periodicamente as funções de atualizar a renderização
      e a função que atualiza a cena.  */
  QTimer *timer = new QTimer(this);
  connect(timer,SIGNAL(timeout()),this,SLOT(updateGL()));
  connect(timer,SIGNAL(timeout()),this,SLOT(stepScene()));
  timer->start(1000/60);

  // Vértices que compõe o cubo.
  vertex_.push_back(GLVertex(Vector4(-1,-1,-1,1),QColor(0,0,0)));
  vertex_.push_back(GLVertex(Vector4(1,-1,-1,1),QColor(255,0,0)));
  vertex_.push_back(GLVertex(Vector4(1,1,-1,1),QColor(255,255,0)));
  vertex_.push_back(GLVertex(Vector4(-1,1,-1,1),QColor(0,255,0)));

  vertex_.push_back(GLVertex(Vector4(-1,-1,1,1),QColor(0,0,255)));
  vertex_.push_back(GLVertex(Vector4(1,-1,1,1),QColor(255,0,255)));
  vertex_.push_back(GLVertex(Vector4(1,1,1,1),QColor(255,255,255)));
  vertex_.push_back(GLVertex(Vector4(-1,1,1,1),QColor(0,255,255)));

  // Lista de indices que compõe as faces do cubo. Cada face tem 2 triangulos.
  // back tri1
  index_.push_back(0);
  index_.push_back(2);
  index_.push_back(1);
  // back tri2
  index_.push_back(0);
  index_.push_back(3);
  index_.push_back(2);
  // front tri1
  index_.push_back(4);
  index_.push_back(5);
  index_.push_back(6);
  // front tri2
  index_.push_back(4);
  index_.push_back(6);
  index_.push_back(7);
  // top tri1
  index_.push_back(2);
  index_.push_back(3);
  index_.push_back(7);
  // top tri2
  index_.push_back(2);
  index_.push_back(7);
  index_.push_back(6);
  // bot tri1
  index_.push_back(0);
  index_.push_back(1);
  index_.push_back(5);
  // bot tri2
  index_.push_back(0);
  index_.push_back(5);
  index_.push_back(4);
  // left tri1
  index_.push_back(0);
  index_.push_back(7);
  index_.push_back(3);
  // left tri2
  index_.push_back(0);
  index_.push_back(4);
  index_.push_back(7);
  // right tri1
  index_.push_back(1);
  index_.push_back(2);
  index_.push_back(5);
  // right tri2
  index_.push_back(2);
  index_.push_back(6);
  index_.push_back(5);
}

void GLWidget::initializeGL()
{
  // Função que executa quando o openGL é Inicializado. Bom para definir os parâmetros desejados.
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void GLWidget::resizeGL(int w, int h)
{
  // Mantém viewport sempre quadrado com o lado igual ao maior valor entre a altura e a largura.
  // Isso significa que parte do viewport está para fora do canvas, logo não será visível.
  float size = qMax(w,h);
  glViewport((w-size)/2,(h-size)/2,size,size);

  // Reinicia a matriz de projeção.
  projection.loadIdentity();

  // Se PROJECTION_PERSPECTIVE estiver definido, o programa usará o frustum. Caso contrário, usará ortho.

  if(kUsePerspective){
    //===Frustum===
    projection.frustum(-0.1f,0.1f,-0.1f,0.1f,0.1f,1000.0f);
    projection.translate(0.f,0.f,-5.0f);
  }else{
    //===Ortho===
    projection.ortho(-3.0f,3.0f,-3.0f,3.0f,3.0f,-3.0f);
  }

  GLenum e;
  while(e = glGetError()){
    qDebug() << "gl error" << e;
  }
}

void GLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  float zoom = float(zoom_)*kZoomTransform;

  // Matriz "View", que representa transformações de camera.
  view.loadIdentity();
  view.scale(zoom);
  view.rotateX(rotx_);
  view.rotateY(roty_);
  view.rotateZ(rotz_);

  // Matriz "Model", que representa transformação dos objetos
  model.loadIdentity();
  model.translate(2,0,0);

  // Calcula matriz final, com todas as transformações concatenadas.
  loadTransform(projection*view*model);

  // Desenhar o modelo.
  glBegin(GL_TRIANGLES);
  // Percorrer de 3 em 3 vértices
  for(int i=0;i+2<index_.size();i+=3){
    // Função que calcula a normal a partir de 3 vértices (normal da face).
    normal(vertex_[index_[i+0]],vertex_[index_[i+1]],vertex_[index_[i+2]]);
    // Desenha os 3 vértices da face.
    vertex(vertex_[index_[i+0]]);
    vertex(vertex_[index_[i+1]]);
    vertex(vertex_[index_[i+2]]);
  }
  glEnd();

  // Matriz "Model", que representa transformação dos objetos
  model.loadIdentity();
  model.translate(-2,0,0);
  model.scale(0.5);

  // Calcula matriz final, com todas as transformações concatenadas.
  loadTransform(projection*view*model);

  glBegin(GL_TRIANGLES);
  for(int i=0;i+2<index_.size();i+=3){
    // Função que calcula a normal a partir de 3 vértices (normal da face).
    normal(vertex_[index_[i+0]],vertex_[index_[i+1]],vertex_[index_[i+2]]);
    // Desenha os 3 vértices da face.
    vertex(vertex_[index_[i+0]]);
    vertex(vertex_[index_[i+1]]);
    vertex(vertex_[index_[i+2]]);
  }
  glEnd();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
  auto_delta_ = QPoint(0,0);
  last_click_ = event->pos();

  event->accept();
}


void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
  // Se arrastar o mouse muito longe, ele fica girando sozinho.
  if(delta_.manhattanLength() > 5){
    auto_delta_ = delta_*0.5;
  }else{
    auto_delta_ = QPoint(0,0);
  }
  event->accept();
}


void GLWidget::wheelEvent(QWheelEvent *event)
{
  zoom_ += event->delta();
  zoom_ = qMax( 100, qMin(50000,zoom_) );
  event->accept();
}


void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
  delta_ = event->pos()-last_click_;
  last_click_ = event->pos();
  if(event->buttons() & Qt::LeftButton){
    rotx_ += delta_.y()*kRotateTransform;
    roty_ += delta_.x()*kRotateTransform;
  }

  event->accept();
}

void GLWidget::vertex(const GLVertex &vertex)
{
  Vector4 transformed = current_mvp_ * vertex.v_;
  // Verifica se a luz está habilitada. Se estiver, usa a função de phong. Se não, usa diretamente a cor do objeto.
  QColor c = kEnableLighting?phong(vertex):vertex.c_;
  glColor3f(c.redF(),c.greenF(),c.blueF());
  glVertex3f(transformed.x(),transformed.y(),transformed.z());
}

void GLWidget::normal(const GLVertex &v1, const GLVertex &v2, const GLVertex &v3)
{
  current_normal_ = Vector4();
}

QColor GLWidget::phong(const GLVertex &vertex)
{
  Vector4 L = current_light_position_-vertex.v_
  const QString kPhongShaderFrag =
      "varying vec3 N; \n"
      "varying vec3 v; \n"
      "varying vec4 t; \n"
      "uniform sampler2D color_texture; \n"
      "void main (void) \n"
      "{ \n"
      "  vec3 L = normalize(gl_LightSource[0].position.xyz - v); \n"
      "  vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0) \n"
      "  vec3 R = normalize(-reflect(L,N)); \n"
      " \n"
      "  //calculate Ambient Term: \n"
      "  vec4 Iamb = gl_FrontLightProduct[0].ambient; \n"
      " \n"
      "  //calculate Diffuse Term: \n"
      "  vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0); \n"
      "  Idiff = clamp(Idiff, 0.0, 1.0); \n"
      " \n"
      "  // calculate Specular Term: \n"
      "  vec4 Ispec = gl_FrontLightProduct[0].specular \n"
      "               * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess); \n"
      "  Ispec = clamp(Ispec, 0.0, 1.0); \n"
      "  // write Total Color: \n"
      "  gl_FragColor = ( gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec ) * texture2D(color_texture,t.st); \n"
      "} \n";
}

void GLWidget::loadTransform(const Matrix4x4 *transform)
{
  current_mvp_ = transform;
}

void GLWidget::stepScene()
{
  rotx_ += auto_delta_.y()*kRotateTransform;
  roty_ += auto_delta_.x()*kRotateTransform;
}

