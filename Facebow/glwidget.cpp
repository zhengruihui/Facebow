#include "glwidget.h"
#include "ui_glwidget.h"



GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::QLWidget)
{
    ui->setupUi(this);

    node = new Node();
    //node->loadObjModel(":/Model/skull.obj");

    node->loadStlModel(":/Model/skull.stl");
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

    m_vbo->allocate(node->getVertexVector("skull").data(), node->getVertexVector("skull").size() * sizeof(GLfloat));
    f->glEnableVertexAttribArray(0);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
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
    mvp.scale(0.04);
    m_shader->setUniformValue(m_shader->uniformLocation("MVP"), mvp);
    f->glDrawArrays(GL_TRIANGLES, 0, node->getVertexVector("skull").size());
    m_shader->release();
    m_vao->release();
}

