#include "glwidget.h"
#include "ui_glwidget.h"
#include "QImage"


const GLfloat VERTEX_DATA[] = {
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

const GLfloat COLOR_DATA[] = {
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

const GLfloat UV_DATA[] = {
    0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
};

GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::QLWidget)
{
    ui->setupUi(this);

}

GLWidget::~GLWidget()
{
    delete ui;
}


void GLWidget::initializeGL()
{

    glFunction = context()->functions();
    glFunction->glEnable(GL_DEPTH_TEST);

    m_shader = new QOpenGLShaderProgram();
    m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shader/vshader.glsl");
    m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shader/fshader.glsl");
    if (m_shader->link()) {
        qDebug("Shaders link success.");
    } else {
        qDebug("Shaders link failed!");
    }
    m_shader->bind();
    m_texture = new QOpenGLTexture(QImage(":/Texture/person.png"));

    m_vao = new QOpenGLVertexArrayObject();
    m_vao->create();
    m_vao->bind();


    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vbo->create();
    m_vbo->bind();
    m_vbo->allocate(VERTEX_DATA, 4*3*3* sizeof(GLfloat));
    glFunction->glEnableVertexAttribArray(0);
    glFunction->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
    m_vbo->release();




    m_cbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_cbo->create();
    m_cbo->bind();
    m_cbo->allocate(COLOR_DATA, 4*3*3* sizeof(GLfloat));
    glFunction->glEnableVertexAttribArray(1);
    glFunction->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
    m_cbo->release();

    m_uvbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_uvbo->create();
    m_uvbo->bind();
    m_uvbo->allocate(UV_DATA, 4 * 3 * 2 * sizeof(GLfloat));
    glFunction->glEnableVertexAttribArray(2);
    glFunction->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), 0);
    m_uvbo->release();


    m_vao->release();


}




void GLWidget::resizeGL(int w, int h)
{
    aspectRatio = (float)w/h;


}


void GLWidget::paintGL()
{
    glFunction = context()->functions();
    glFunction->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFunction->glClearColor(0.0f, 0.2f, 0.0f, 1.0f);


    m_vao->bind();
    m_shader->bind();
    m_texture->bind();

    QMatrix4x4 mvp;
    mvp.perspective(45.0f, aspectRatio, 0.1f, 100.0f);
    mvp.lookAt(QVector3D(0.0f, 3.0f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f));
    mvp.scale(2);
    m_shader->setUniformValue(m_shader->uniformLocation("MVP"), mvp);


    glFunction->glDrawArrays(GL_TRIANGLES, 0, 12);

    m_texture->release();
    m_shader->release();
    m_vao->release();

}

