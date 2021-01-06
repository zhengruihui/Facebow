#include "glwidget.h"
#include "ui_glwidget.h"
#include "math.h"


GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::QLWidget)
{
    ui->setupUi(this);

    scaleFactor = 0.8;

    cameraEye = QVector3D(0.0f, 0.0f, 100.0f);
    cameraCenter = QVector3D(0.0f, 0.0f, 0.0f);
    cameraUp = QVector3D(0.0f, 1.0f, 0.0f);

    lightPos = QVector3D(0.0f, 0.0f, 1.0f);
    eulerRotationX = 0.0f;
    eulerRotationY = 0.0f;
    eulerRotationZ = 0.0f;
    moveX = 0.0f;
    moveY = 0.0f;
    moveZ = 0.0f;

    rotateVector = QVector3D(1.0f, 0.0f, 0.0f);

    node = new Node();

    node->loadStlModel(":/Model/skull1.stl");
    node->loadStlModel(":/Model/skull2.stl");


}

GLWidget::~GLWidget()
{
    delete ui;
}



void GLWidget::initializeGL()
{
    QOpenGLFunctions *glFunctions = this->context()->functions();
    glFunctions->glEnable(GL_DEPTH_TEST);   // 三维绘图的关键！
    m_shader = new QOpenGLShaderProgram();
    m_shader->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shader/vshader.glsl");
    m_shader->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shader/fshader.glsl");
    if (m_shader->link()) {
        qDebug("Shaders link success.");
    } else {
        qDebug("Shaders link failed!");
    }


    skull1_vao = new QOpenGLVertexArrayObject();
    skull1_vao->create();
    skull1_vao->bind();

    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vbo->create();
    m_vbo->bind();

    m_vbo->allocate(node->getVertexVector(SKULL1INDEX).data(), node->getVertexVector(SKULL1INDEX).size() * sizeof(GLfloat));
    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
    glFunctions->glEnableVertexAttribArray(0);
    m_vbo->release();

    m_nbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_nbo->create();
    m_nbo->bind();
    m_nbo->allocate(node->getNormalData(SKULL1INDEX).data(), node->getNormalData(SKULL1INDEX).size()*sizeof(GLfloat));
    glFunctions->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
    glFunctions->glEnableVertexAttribArray(1);
    m_nbo->release();
    skull1_vao->release();



//    skull2_vao = new QOpenGLVertexArrayObject();
//    skull2_vao->create();
//    skull2_vao->bind();

//    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
//    m_vbo->create();
//    m_vbo->bind();
//    m_vbo->allocate(node->getVertexVector(SKULL2INDEX).data(), node->getVertexVector(SKULL2INDEX).size() * sizeof(GLfloat));
//    glFunctions->glEnableVertexAttribArray(0);
//    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
//    m_vbo->release();

//    m_nbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
//    m_nbo->create();
//    m_nbo->bind();
//    m_nbo->allocate(node->getNormalData(SKULL2INDEX).data(), node->getNormalData(SKULL2INDEX).size()*sizeof(GLfloat));
//    glFunctions->glEnableVertexAttribArray(1);
//    glFunctions->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
//    m_nbo->release();
//    skull2_vao->release();


}




void GLWidget::resizeGL(int w, int h)
{
    aspectRatio = (float)w/h;
}






void GLWidget::paintGL()
{
    QOpenGLFunctions *glFunctions = this->context()->functions();
    glFunctions->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFunctions->glClearColor(0.0f, 0.2f, 0.0f, 1.0f);


    QMatrix4x4 vpMatri;
    vpMatri.perspective(45.0f, aspectRatio, 0.1f, 100.0f);
    vpMatri.lookAt(cameraEye,cameraCenter,cameraUp);





    //paint skull1
    skull1_vao->bind();

    QMatrix4x4 mMatriSkull1;
    mMatriSkull1.scale(scaleFactor);
    mMatriSkull1.rotate(-90.0f, QVector3D(1.0f, 0.0f, 0.0f));
    m_shader->bind();
    m_shader->setUniformValue(m_shader->uniformLocation("view"), vpMatri);
    m_shader->setUniformValue(m_shader->uniformLocation("model"), mMatriSkull1);
    m_shader->setUniformValue(m_shader->uniformLocation("lightPos"), QVector3D(0.0f, 0.0f, -220.0f));
    m_shader->setUniformValue(m_shader->uniformLocation("lightColor"), QVector3D(1.0f, 1.0f, 1.0f));
    m_shader->setUniformValue(m_shader->uniformLocation("objectColor"), QVector3D(0.1f, 0.1f, 0.1f));
    m_shader->setUniformValue(m_shader->uniformLocation("viewPos"), QVector3D(0.0f, 0.0f, 100.0f));


    glFunctions->glDrawArrays(GL_TRIANGLES, 0, node->getVertexVector(SKULL1INDEX).size()/3);

    skull1_vao->release();




    //paint skull2
//    skull2_vao->bind();
//    QMatrix4x4 mMatriSkull2;
//    mMatriSkull2.scale(scaleFactor);
//    mMatriSkull2.translate(QVector3D(moveX, moveY, moveZ));
//    mMatriSkull2.rotate(-90.0f, QVector3D(1.0f, 0.0f, 0.0f));
//    mMatriSkull2.rotate(eulerRotationX, QVector3D(1.0f, 0.0f, 0.0f));
//    mMatriSkull2.rotate(eulerRotationY, QVector3D(0.0f, 1.0f, 0.0f));
//    mMatriSkull2.rotate(eulerRotationZ, QVector3D(0.0f, 0.0f, 1.0f));

//    m_shader->setUniformValue(m_shader->uniformLocation("modelMat"), mMatriSkull2);
//    glFunctions->glDrawArrays(GL_TRIANGLES, 0, node->getVertexVector(SKULL2INDEX).size()/3);


    m_shader->release();
//    skull2_vao->release();


    qDebug() << "paintGL";
}

void GLWidget::cameraPerspectiveLookAt(float angle)
{
    float radius = 100.0f;

    angle = angle/180*3.14;

    float x = radius*sin(angle);
    float z = radius*cos(angle);

    cameraEye = QVector3D(x, 0.0f, z);
}



void GLWidget::on_pushButton_clicked()
{
    scaleFactor += 0.02;
    cameraPerspectiveLookAt(15);
    update();
}

void GLWidget::changeSkullPos(float x, float y, float z, float pitch, float yaw, float roll)
{
    moveX = x;
    moveY = y;
    moveZ = z;
    eulerRotationX = pitch;
    eulerRotationY = yaw;
    eulerRotationZ = roll;
    update();
}
