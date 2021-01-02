#include "glwidget.h"
#include "ui_glwidget.h"
#include "QImage"
#include <QMouseEvent>


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

void GLWidget::mousePressEvent(QMouseEvent *e)
{
    timer.start(12, this);
    mousePressPosition = QVector2D(e->localPos());
}

void GLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
    timer.stop();

}

void GLWidget::timerEvent(QTimerEvent *)
{
    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Request an update
        update();
    }

}

void GLWidget::initializeGL()
{
    m_shader = new QOpenGLShaderProgram();
    m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shader/vshader.glsl");
    m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shader/fshader.glsl");
    if (m_shader->link()) {
        qDebug("Shaders link success.");
    } else {
        qDebug("Shaders link failed!");
    }
    m_shader->bind();

    m_vao = new QOpenGLVertexArrayObject();
    m_vao->create();
    m_vao->bind();


    m_vbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vbo->create();
    m_vbo->bind();
    m_vbo->allocate(VERTEX_DATA, 4*3*3* sizeof(GLfloat));

    glFunction = context()->functions();
    glFunction->glEnableVertexAttribArray(0);
    glFunction->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
    m_vbo->release();




    m_cbo = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_cbo->create();
    m_cbo->bind();
    m_cbo->allocate(COLOR_DATA, 4*3*3* sizeof(GLfloat));


    glFunction = context()->functions();
    glFunction->glEnableVertexAttribArray(1);
    glFunction->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);
    m_cbo->release();


    m_vao->release();


}




void GLWidget::resizeGL(int w, int h)
{
    aspectRatio = (float)w/h;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(45.0f, aspectRatio, 1.1f, 100.0f);

}


void GLWidget::paintGL()
{
    glFunction = context()->functions();
    glFunction->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFunction->glClearColor(0.0f, 0.2f, 0.0f, 1.0f);


    m_vao->bind();
    m_shader->bind();
    QMatrix4x4 matrix;

    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);
    matrix.scale(2);
    m_shader->setUniformValue(m_shader->uniformLocation("MVP"), projection*matrix);

    glFunction->glDrawArrays(GL_TRIANGLES, 0, 12);

    m_shader->release();
    m_vao->release();

}
