#include "glwidget.h"
#include "ui_glwidget.h"
#include "math.h"
#include "devicesystem.h"

GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::QLWidget),
    parent(parent)
{
    ui->setupUi(this);

    scaleFactor = 0.8f;
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

    QObject::connect(DeviceSystem::getInstance(), &DeviceSystem::facebowPosChanged, this,  &GLWidget::on_facebowPosChanged, Qt::QueuedConnection);

}

GLWidget::~GLWidget()
{
    delete ui;
}



void GLWidget::initializeGL()
{
    QOpenGLFunctions *glFunctions = this->context()->functions();

    glFunctions->glEnable(GL_DEPTH_TEST);
    glFunctions->glEnable(GL_LIGHTING);
    glFunctions->glEnable(GL_COLOR_MATERIAL);
    glFunctions->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFunctions->glClearColor(0.27f, 0.27f, 0.29f, 1.0f);//#454449  //#25242a

    m_shader = new QOpenGLShaderProgram();
    m_shader->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shader/vshader.glsl");
    m_shader->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shader/fshader.glsl");
    if (!m_shader->link())
    {
        qDebug("Shaders link failed!");
    }


    node->loadBinModel("skull1", vPointsSkull1, tPointsSkull1, nPointsSkull1);

    skull1_vao = new QOpenGLVertexArrayObject();
    skull1_vao->create();
    skull1_vao->bind();

    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vbo->create();
    m_vbo->bind();
    m_vbo->allocate(vPointsSkull1.data(), vPointsSkull1.size());
    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
    glFunctions->glEnableVertexAttribArray(0);
    m_vbo->release();

    m_nbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_nbo->create();
    m_nbo->bind();
    m_nbo->allocate(nPointsSkull1.data(), nPointsSkull1.size());
    glFunctions->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
    glFunctions->glEnableVertexAttribArray(1);
    m_nbo->release();
    skull1_vao->release();



    node->loadBinModel("skull2", vPointsSkull2, tPointsSkull2, nPointsSkull2);

    skull2_vao = new QOpenGLVertexArrayObject();
    skull2_vao->create();
    skull2_vao->bind();

    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vbo->create();
    m_vbo->bind();
    m_vbo->allocate(vPointsSkull2.data(), vPointsSkull2.size());
    glFunctions->glEnableVertexAttribArray(0);
    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
    m_vbo->release();

    m_nbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_nbo->create();
    m_nbo->bind();
    m_nbo->allocate(nPointsSkull2.data(), nPointsSkull2.size());
    glFunctions->glEnableVertexAttribArray(1);
    glFunctions->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
    m_nbo->release();
    skull2_vao->release();


}




void GLWidget::resizeGL(int w, int h)
{
    aspectRatio = (float)w/h;
}


void GLWidget::paintGL()
{
    QOpenGLFunctions *glFunctions = context()->functions();
    glFunctions->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFunctions->glClearColor(0.27f, 0.27f, 0.29f, 1.0f);


    QMatrix4x4 projectionMatri;
    projectionMatri.perspective(45.0f, aspectRatio, 0.1f, 100.0f);

    QMatrix4x4 viewMatri;
    viewMatri.lookAt(cameraEye,cameraCenter,cameraUp);


    m_shader->bind();
    m_shader->setUniformValue("projection", projectionMatri);
    m_shader->setUniformValue("view", viewMatri);
    m_shader->setUniformValue("viewPos", QVector3D(0.0f, 0.0f, 100.0f));




    //paint skull1
    skull1_vao->bind();



    QMatrix4x4 modelMatri1;
    modelMatri1.scale(scaleFactor);
    modelMatri1.rotate(0.0f, QVector3D(1.0f, 0.0f, 0.0f));


    m_shader->setUniformValue("material.ambient", QVector3D(0.7f, 0.7f, 0.7f));
    m_shader->setUniformValue("material.diffuse", QVector3D(0.7f, 0.7f, 0.7f));
    m_shader->setUniformValue("material.specular", QVector3D(0.1f, 0.1f, 0.1f));
    m_shader->setUniformValue("material.shininess", 10.0f);

    m_shader->setUniformValue("light.ambient", QVector3D(0.7f, 0.7f, 0.7f));
    m_shader->setUniformValue("light.diffuse", QVector3D(0.7f, 0.7f, 0.7f));
    m_shader->setUniformValue("light.specular", QVector3D(0.1f, 0.1f, 0.1f));
    m_shader->setUniformValue("light.position", QVector3D(0.0f, 0.0f, 100.0f));
    m_shader->setUniformValue("model", modelMatri1);

    glFunctions->glDrawArrays(GL_TRIANGLES, 0, vPointsSkull1.size()/12);

    skull1_vao->release();




    //paint skull2
    skull2_vao->bind();
    QMatrix4x4 modelMatri2;
    modelMatri2.scale(scaleFactor);
    modelMatri2.translate(QVector3D(moveX, moveY, moveZ));
    modelMatri2.rotate(eulerRotationX, QVector3D(1.0f, 0.0f, 0.0f));
    modelMatri2.rotate(eulerRotationY, QVector3D(0.0f, 1.0f, 0.0f));
    modelMatri2.rotate(eulerRotationZ, QVector3D(0.0f, 0.0f, 1.0f));


    m_shader->setUniformValue("material.ambient", QVector3D(0.7f, 0.7f, 0.7f));
    m_shader->setUniformValue("material.diffuse", QVector3D(0.7f, 0.7f, 0.7f));
    m_shader->setUniformValue("material.specular", QVector3D(0.1f, 0.1f, 0.1f));
    m_shader->setUniformValue("material.shininess", 10.0f);

    m_shader->setUniformValue("light.ambient", QVector3D(0.7f, 0.7f, 0.7f));
    m_shader->setUniformValue("light.diffuse", QVector3D(0.7f, 0.7f, 0.7f));
    m_shader->setUniformValue("light.specular", QVector3D(0.1f, 0.1f, 0.1f));
    m_shader->setUniformValue("light.position", QVector3D(0.0f, 0.0f, 100.0f));
    m_shader->setUniformValue("model", modelMatri2);

    glFunctions->glDrawArrays(GL_TRIANGLES, 0, vPointsSkull2.size()/12);

    skull2_vao->release();
    m_shader->release();

//    qDebug() << "paintSkull";

}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y() > 0){
         scaleFactor += 0.1f;
    }else{
        scaleFactor>0.2f? scaleFactor -= 0.1f : 0.2f;
    }
    parent->update();

}

void GLWidget::cameraPerspectiveLookAt(float angle)
{
    float radius = 100.0f;

    angle = angle/180.0f*3.14;

    float x = radius*sin(angle);
    float z = radius*cos(angle);

    cameraEye = QVector3D(x, 0.0f, z);
    parent->update();
}

void GLWidget::cameraPerspectiveLookAtTop()
{
    float radius = 100.0f;
    float angle = 75;

    angle = angle/180.0f*3.14;

    float y = radius*sin(angle);
    float z = radius*cos(angle);

    cameraEye = QVector3D(0.0f, y,  z);
    parent->update();
}

void GLWidget::zoomIn()
{
    scaleFactor += 0.1f;
    parent->update();
}

void GLWidget::zoomOut()
{
    scaleFactor>0.2f? scaleFactor -= 0.1f : 0.2f;
    parent->update();
}

void GLWidget::normal()
{
    scaleFactor = 0.8f;
    parent->update();
}


void GLWidget::on_facebowPosChanged(float x, float y, float z, float c, float p, float r)
{

//    static float offsetX = 18.0f;
//    static float offsetY = 120.0f;
//    static float offsetZ = 18.0f;

//    static float offsetC = 177.0f;
//    static float offsetP = -8.0f;
//    static float offsetR = -24.0f;

//    moveX = x + offsetX;
//    moveY = y + offsetY;
//    moveZ = z + offsetZ;
//    eulerRotationX = p + offsetP;
//    eulerRotationY = c + offsetC;
//    eulerRotationZ = r + offsetR;
//    parent->update();


//    static float offsetC = 177.0f;
//    static float offsetP = -8.0f;
//    static float offsetR = -24.0f;


    moveX = x/100;
    moveY = y/100;
    moveZ = z/100;
    eulerRotationX = p/100;
    eulerRotationY = c/100;
    eulerRotationZ = r/100;
    parent->update();

//    qDebug() << x << y << z << c << p << r;
}
