#include "glwidget.h"
#include "ui_glwidget.h"
#include "QImage"


GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::QLWidget)
{
    ui->setupUi(this);

    node = new Node();
    node->loadObjModel(":/Model/skull.obj");

    const GLfloat VERTEX_INIT_DATA[] = {
           //face 1
           -0.5f, 0.0f, -0.2887f,
           0.5f, 0.0f, -0.2887f,
           0.0f, 0.0f, 0.5774f,
           //face 2
           -0.5f, 0.0f, -0.2887f,
           0.5f, 0.0f, -0.2887f,
           0.0f, 0.8165f, 0.0f,
           //face 3
           -0.5f, 0.0f, -0.2887f,
           0.0f, 0.0f, 0.5774f,
           0.0f, 0.8165f, 0.0f,
           //face 4
           0.5f, 0.0f, -0.2887f,
           0.0f, 0.0f, 0.5774f,
           0.0f, 0.8165f, 0.0f,
       };
    const GLfloat COLOR_INIT_DATA[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
       };
    memcpy(this->vertexData, VERTEX_INIT_DATA, sizeof(this->vertexData));
    memcpy(this->colorBuffer, COLOR_INIT_DATA, sizeof(this->colorBuffer));



}

GLWidget::~GLWidget()
{
    delete ui;
}



void GLWidget::initializeGL()
{
    QOpenGLFunctions *f = this->context()->functions();
    f->glEnable(GL_DEPTH_TEST);   // 三维绘图的关键！
    m_shader = new QOpenGLShaderProgram();
    m_shader->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shader/vshader.glsl");
    m_shader->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shader/fshader.glsl");
    if (m_shader->link()) {
        qDebug("Shaders link success.");
    } else {
        qDebug("Shaders link failed!");
    }
    m_vao = new QOpenGLVertexArrayObject();
    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    //m_cbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vao->create();
    m_vao->bind();
    m_vbo->create();
    m_vbo->bind();
    //m_vbo->allocate(this->vertexData, 4 * 3 * 3 * sizeof(GLfloat));


//    m_vbo->allocate(this->vertexData, 4 * 3 * 3 * sizeof(GLfloat));
//    f->glEnableVertexAttribArray(0);
//    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,4*sizeof(GLfloat), 0);

    QVector<float> mv = node->getVertexVector("Group53615");

    m_vbo->allocate(mv.data(), mv.size() * sizeof(GLfloat));
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,4*sizeof(GLfloat), 0);
    m_vbo->release();

//    m_cbo->create();
//    m_cbo->bind();
//    m_cbo->allocate(this->colorBuffer, 4*3*3*sizeof(GLfloat));
//    f->glEnableVertexAttribArray(1);
//    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
//    m_cbo->release();
    m_vao->release();


}




void GLWidget::resizeGL(int w, int h)
{
    aspectRatio = (float)w/h;


}


void GLWidget::paintGL()
{
    QOpenGLFunctions *f = this->context()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    f->glClearColor(0.0f, 0.2f, 0.0f, 1.0f);
    m_vao->bind();
    m_shader->bind();
    QMatrix4x4 mvp;
    mvp.perspective(45.0f, aspectRatio, 0.1f, 100.0f);
    mvp.lookAt(QVector3D(0.0f, 3.0f, 0.0f),
               QVector3D(0.0f, 0.0f, 0.0f),
               QVector3D(1.0f, 0.0f, 0.0f));
    mvp.scale(0.01);
    m_shader->setUniformValue(m_shader->uniformLocation("MVP"), mvp);
    //f->glDrawArrays(GL_TRIANGLES, 0, 12);

    f->glDrawArrays(GL_QUADS, 0, node->getVertexVector("Group53615").size()/4);
    m_shader->release();
    m_vao->release();
}

