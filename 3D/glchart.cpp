#include "glchart.h"
#include "ui_glchart.h"
#include "math.h"
#include "devicesystem.h"
#include <QPainter>

GLChart::GLChart(QWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::GLChart),
    parent(parent)
{
    ui->setupUi(this);

    scaleFactor = 28.5;

    QObject::connect(DeviceSystem::getInstance(), &DeviceSystem::vertexDataChanged, this,  &GLChart::on_vertexDataChanged, Qt::QueuedConnection);
}

GLChart::~GLChart()
{
    delete ui;
}

void GLChart::paintChart()
{
    DeviceSystem::getInstance()->paintChart();
}

void GLChart::paintChartM(QOpenGLFunctions *glFunctions)
{
    QVector3D cameraEye = QVector3D(2.0f, 0.0f, 2.0f);
    QVector3D cameraCenter = QVector3D(0.0f, 0.0f, 0.0f);
    QVector3D cameraUp = QVector3D(0.0f, 1.0f, 0.0f);

    glFunctions->glEnable(GL_DEPTH_TEST);

    m_shader->bind();

    //绘制坐标系
    m_vaoAxis->bind();
    QMatrix4x4 matriMVPA;
    matriMVPA.perspective(45.0f, aspectRatio, 0.1f, 100.0f);
    matriMVPA.lookAt(cameraEye,cameraCenter,cameraUp);
    m_shader->setUniformValue("MVP", matriMVPA);
    m_shader->setUniformValue("Color", QVector4D(0.62f, 0.62f, 0.62f, 1.0f));
    glFunctions->glLineWidth(1.0);
    glFunctions->glDrawArrays(GL_LINES, 0, VertexAxisBuffer.size()/3);
    m_vaoAxis->release();


    matriMVPA.scale(QVector3D(scaleFactor, scaleFactor, scaleFactor));
    matriMVPA.translate(offsetXF, offsetYF, offsetZF);

    m_vaoS->bind();
    m_shader->setUniformValue("MVP", matriMVPA);
    m_shader->setUniformValue("Color", QVector4D(1.0f, 0.62f, 0.62f, 1.0f));
    glFunctions->glLineWidth(0.5);
    glFunctions->glDrawArrays(GL_LINES, 0, VertexStaticBuffer.size()/3);
    m_vaoS->release();



    //绘制数据
    m_vaoF->bind();
    QMatrix4x4 matriMVPF;
    matriMVPF.perspective(45.0f, aspectRatio, 0.1f, 100.0f);
    matriMVPF.lookAt(cameraEye,cameraCenter,cameraUp);
    matriMVPF.scale(QVector3D(scaleFactor, scaleFactor, scaleFactor));
    matriMVPF.translate(offsetXF, offsetYF);
    m_shader->setUniformValue("MVP", matriMVPF);
    m_shader->setUniformValue("Color", QVector4D(0.0f, 1.0f, 0.0f, 1.0f));
    glFunctions->glLineWidth(1.0);
    glFunctions->glDrawArrays(GL_LINE_STRIP, 0, vertexDataToothSize/3);
    m_vaoF->release();

    m_vaoL->bind();
    QMatrix4x4 matriMVPL;
    matriMVPL.perspective(45.0f, aspectRatio, 0.1f, 100.0f);
    matriMVPL.lookAt(cameraEye,cameraCenter,cameraUp);
    matriMVPL.scale(QVector3D(scaleFactor, scaleFactor, scaleFactor));
    matriMVPL.translate(offsetXL, offsetYL);
    m_shader->setUniformValue("MVP", matriMVPL);
    m_shader->setUniformValue("Color", QVector4D(0.0f, 1.0f, 1.0f, 1.0f));
    glFunctions->glLineWidth(1.0);
    glFunctions->glDrawArrays(GL_LINE_STRIP, 0, vertexLeftCondyleSize/3);
    m_vaoL->release();

    m_vaoR->bind();
    QMatrix4x4 matriMVPR;
    matriMVPR.perspective(45.0f, aspectRatio, 0.1f, 100.0f);
    matriMVPR.lookAt(cameraEye,cameraCenter,cameraUp);
    matriMVPR.scale(QVector3D(scaleFactor, scaleFactor, scaleFactor));
    matriMVPR.translate(offsetXR, offsetYR);
    m_shader->setUniformValue("MVP", matriMVPR);
    m_shader->setUniformValue("Color", QVector4D(1.0f, 1.0f, 0.0f, 1.0f));
    glFunctions->glLineWidth(1.0);
    glFunctions->glDrawArrays(GL_LINE_STRIP, 0, vertexRightCondyletSize/3);
    m_vaoR->release();

    m_shader->release();
//    qDebug() << chartFlag << ": " << scaleFactor << offsetXF << offsetYF << offsetZF;
}

void GLChart::paintChartL(QOpenGLFunctions *glFunctions)
{
    QVector3D cameraEye = QVector3D(-2.0f, 0.0f, 0.0f);
    QVector3D cameraCenter = QVector3D(0.0f, 0.0f, 0.0f);
    QVector3D cameraUp = QVector3D(0.0f, 1.0f, 0.0f);

    glFunctions->glEnable(GL_DEPTH_TEST);

    m_shader->bind();

    //绘制坐标系
    m_vaoAxis->bind();
    QMatrix4x4 matriMVPA;
    matriMVPA.perspective(45.0f, aspectRatio, 0.1f, 100.0f);
    matriMVPA.lookAt(cameraEye, cameraCenter, cameraUp);
    m_shader->setUniformValue("MVP", matriMVPA);
    m_shader->setUniformValue("Color", QVector4D(0.62f, 0.62f, 0.62f, 1.0f));
    glFunctions->glLineWidth(1.0);
    glFunctions->glDrawArrays(GL_LINES, 0, VertexAxisBuffer.size()/3);
    m_vaoAxis->release();

    //绘制数据
    m_vaoL->bind();
    QMatrix4x4 matriMVPL;
    matriMVPL.perspective(45.0f, aspectRatio, 0.1f, 100.0f);
    matriMVPL.lookAt(cameraEye,cameraCenter,cameraUp);
    matriMVPL.scale(QVector3D(1.0f, scaleFactor, scaleFactor));
    matriMVPL.translate(0, offsetYL, offsetZL);
    m_shader->setUniformValue("MVP", matriMVPL);
    m_shader->setUniformValue("Color", QVector4D(0.0f, 1.0f, 1.0f, 1.0f));
    glFunctions->glLineWidth(1.0);
    glFunctions->glDrawArrays(GL_LINE_STRIP, 0, vertexLeftCondyleSize/3);
    m_vaoL->release();

    m_shader->release();

}

void GLChart::paintChartR(QOpenGLFunctions *glFunctions)
{
    QVector3D cameraEye = QVector3D(-2.0f, 0.0f, 0.0f);
    QVector3D cameraCenter = QVector3D(0.0f, 0.0f, 0.0f);
    QVector3D cameraUp = QVector3D(0.0f, 1.0f, 0.0f);

    glFunctions->glEnable(GL_DEPTH_TEST);

    m_shader->bind();

    //绘制坐标系
    m_vaoAxis->bind();
    QMatrix4x4 matriMVPA;
    matriMVPA.perspective(45.0f, aspectRatio, 0.1f, 100.0f);
    matriMVPA.lookAt(cameraEye,cameraCenter,cameraUp);
    m_shader->setUniformValue("MVP", matriMVPA);
    m_shader->setUniformValue("Color", QVector4D(0.62f, 0.62f, 0.62f, 1.0f));
    glFunctions->glLineWidth(1.0);
    glFunctions->glDrawArrays(GL_LINES, 0, VertexAxisBuffer.size()/3);
    m_vaoAxis->release();

    //绘制数据
    m_vaoR->bind();
    QMatrix4x4 matriMVPR;
    matriMVPR.perspective(45.0f, aspectRatio, 0.1f, 100.0f);
    matriMVPR.lookAt(cameraEye,cameraCenter,cameraUp);
    matriMVPR.scale(QVector3D(1.0f, scaleFactor, scaleFactor));
    matriMVPR.translate(0, offsetYR, offsetZR);
    m_shader->setUniformValue("MVP", matriMVPR);
    m_shader->setUniformValue("Color", QVector4D(1.0f, 1.0f, 0.0f, 1.0f));
    glFunctions->glLineWidth(1.0);
    glFunctions->glDrawArrays(GL_LINE_STRIP, 0, vertexRightCondyletSize/3);
    m_vaoR->release();

    m_shader->release();

}

void GLChart::paintChartT(QOpenGLFunctions *glFunctions)
{
    QVector3D cameraEye = QVector3D(0.0f, 2.0f, 0.0f);
    QVector3D cameraCenter = QVector3D(0.0f, 0.0f, 0.0f);
    QVector3D cameraUp = QVector3D(0.0f, 0.0f, -1.0f);

    glFunctions->glEnable(GL_DEPTH_TEST);

    m_shader->bind();

    //绘制坐标系
    m_vaoAxis->bind();
    QMatrix4x4 matriMVPA;
    matriMVPA.perspective(45.0f, aspectRatio, 0.1f, 100.0f);
    matriMVPA.lookAt(cameraEye,cameraCenter,cameraUp);
    m_shader->setUniformValue("MVP", matriMVPA);
    m_shader->setUniformValue("Color", QVector4D(0.62f, 0.62f, 0.62f, 1.0f));
    glFunctions->glLineWidth(1.0);
    glFunctions->glDrawArrays(GL_LINES, 0, VertexAxisBuffer.size()/3);
    m_vaoAxis->release();

    //绘制数据
    m_vaoF->bind();
    QMatrix4x4 matriMVPF;
    matriMVPF.perspective(45.0f, aspectRatio, 0.1f, 100.0f);
    matriMVPF.lookAt(cameraEye,cameraCenter,cameraUp);
    matriMVPF.scale(QVector3D(scaleFactor, 1.0f, scaleFactor));
    matriMVPF.translate(offsetXF, 0, offsetZF);
    m_shader->setUniformValue("MVP", matriMVPF);
    m_shader->setUniformValue("Color", QVector4D(0.0f, 1.0f, 0.0f, 1.0f));
    glFunctions->glLineWidth(1.0);
    glFunctions->glDrawArrays(GL_LINE_STRIP, 0, vertexDataToothSize/3);
    m_vaoF->release();

    m_vaoL->bind();
    QMatrix4x4 matriMVPL;
    matriMVPL.perspective(45.0f, aspectRatio, 0.1f, 100.0f);
    matriMVPL.lookAt(cameraEye,cameraCenter,cameraUp);
    matriMVPL.scale(QVector3D(scaleFactor, 1.0f, scaleFactor));
    matriMVPL.translate(offsetXL, 0, offsetZL);
    m_shader->setUniformValue("MVP", matriMVPL);
    m_shader->setUniformValue("Color", QVector4D(0.0f, 1.0f, 1.0f, 1.0f));
    glFunctions->glLineWidth(1.0);
    glFunctions->glDrawArrays(GL_LINE_STRIP, 0, vertexLeftCondyleSize/3);
    m_vaoL->release();

    m_vaoR->bind();
    QMatrix4x4 matriMVPR;
    matriMVPR.perspective(45.0f, aspectRatio, 0.1f, 100.0f);
    matriMVPR.lookAt(cameraEye,cameraCenter,cameraUp);
    matriMVPR.scale(QVector3D(scaleFactor, 1.0f, scaleFactor));
    matriMVPR.translate(offsetXR, 0, offsetZR);
    m_shader->setUniformValue("MVP", matriMVPR);
    m_shader->setUniformValue("Color", QVector4D(1.0f, 1.0f, 0.0f, 1.0f));
    glFunctions->glLineWidth(1.0);
    glFunctions->glDrawArrays(GL_LINE_STRIP, 0, vertexRightCondyletSize/3);
    m_vaoR->release();

    m_shader->release();

}




void GLChart::mouseMoveEvent(QMouseEvent *event)
{

    if(pressed)
    {
        if(chartFlag == 'M')
        {
            offsetXF = ((float)(event->x() - pressedX)/width()) + oldOffsetXF;
            offsetYF = -((float)(event->y() - pressedY)/height()) + oldOffsetYF;

            offsetXL = ((float)(event->x() - pressedX)/width()) + oldOffsetXL;
            offsetYL = -((float)(event->y() - pressedY)/height()) + oldOffsetYL;

            offsetXR = ((float)(event->x() - pressedX)/width()) + oldOffsetXR;
            offsetYR = -((float)(event->y() - pressedY)/height()) + oldOffsetYR;
        }
        else if(chartFlag == 'L')
        {
            offsetZL = ((float)(event->x() - pressedX)/width()) + oldOffsetZL;
            offsetYL = -((float)(event->y() - pressedY)/height()) + oldOffsetYL;
        }
        else if(chartFlag == 'R')
        {
            offsetZR = ((float)(event->x() - pressedX)/width()) + oldOffsetZR;
            offsetYR = -((float)(event->y() - pressedY)/height()) + oldOffsetYR;

        }
        else if(chartFlag == 'T')
        {
            offsetXF = ((float)(event->x() - pressedX)/width()) + oldOffsetXF;
            offsetZF = ((float)(event->y() - pressedY)/height()) + oldOffsetZF;

            offsetXL = ((float)(event->x() - pressedX)/width()) + oldOffsetXL;
            offsetZL = ((float)(event->y() - pressedY)/height()) + oldOffsetZL;

            offsetXR = ((float)(event->x() - pressedX)/width()) + oldOffsetXR;
            offsetZR = ((float)(event->y() - pressedY)/height()) + oldOffsetZR;
        }


        parent->update();
    }

}

void GLChart::mousePressEvent(QMouseEvent *event)
{
    pressed = true;
    oldOffsetXF = offsetXF;
    oldOffsetYF = offsetYF;
    oldOffsetZF = offsetZF;

    oldOffsetXL = offsetXL;
    oldOffsetYL = offsetYL;
    oldOffsetZL = offsetZL;

    oldOffsetXR = offsetXR;
    oldOffsetYR = offsetYR;
    oldOffsetZR = offsetZR;

    pressedX = event->x();
    pressedY = event->y();
}

void GLChart::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    pressed = false;
}

void GLChart::wheelEvent(QWheelEvent *event)
{
    if(event->angleDelta().y() > 0){
         scaleFactor += 0.5;
    }else{
        scaleFactor -= 0.5;;
    }
    parent->update();
}


void GLChart::initializeGL()
{
    QOpenGLFunctions *glFunctions = this->context()->functions();

    glFunctions->glEnable(GL_DEPTH_TEST);
    glFunctions->glEnable(GL_CULL_FACE);
    glFunctions->glEnable(GL_LIGHTING);
    glFunctions->glEnable(GL_COLOR_MATERIAL);
    glFunctions->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFunctions->glClearColor(0.0, 0.0f, 0.0f, 0.0f);//#454449  //#25242a


    m_shader = new QOpenGLShaderProgram();
    m_shader->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shader/chart_vshader.glsl");
    m_shader->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shader/chart_fshader.glsl");
    if (!m_shader->link())
    {
        qDebug("Shaders link failed!");
    }




    if(objectName() == "openGLWidgetChartMain")
    {
        chartFlag = 'M';
        scaleFactor = 1;
        //AxisX
        VertexAxisBuffer.append(-1.0f);
        VertexAxisBuffer.append(-1.0f);
        VertexAxisBuffer.append(-1.0f);

        VertexAxisBuffer.append(1.0f);
        VertexAxisBuffer.append(-1.0f);
        VertexAxisBuffer.append(-1.0f);

//        VertexAxisBuffer.append(-1.0f);
//        VertexAxisBuffer.append(-0.5f);
//        VertexAxisBuffer.append(-1.0f);

//        VertexAxisBuffer.append(1.0f);
//        VertexAxisBuffer.append(-0.5f);
//        VertexAxisBuffer.append(-1.0f);

//        VertexAxisBuffer.append(-1.0f);
//        VertexAxisBuffer.append(0.0f);
//        VertexAxisBuffer.append(-1.0f);

//        VertexAxisBuffer.append(1.0f);
//        VertexAxisBuffer.append(0.0f);
//        VertexAxisBuffer.append(-1.0f);

//        VertexAxisBuffer.append(-1.0f);
//        VertexAxisBuffer.append(0.5f);
//        VertexAxisBuffer.append(-1.0f);

//        VertexAxisBuffer.append(1.0f);
//        VertexAxisBuffer.append(0.5f);
//        VertexAxisBuffer.append(-1.0f);

//        VertexAxisBuffer.append(-1.0f);
//        VertexAxisBuffer.append(1.0f);
//        VertexAxisBuffer.append(-1.0f);

//        VertexAxisBuffer.append(1.0f);
//        VertexAxisBuffer.append(1.0f);
//        VertexAxisBuffer.append(-1.0f);

        //AxisY
        VertexAxisBuffer.append(-1.0f);
        VertexAxisBuffer.append(-1.0f);
        VertexAxisBuffer.append(-1.0f);

        VertexAxisBuffer.append(-1.0f);
        VertexAxisBuffer.append(1.0f);
        VertexAxisBuffer.append(-1.0f);



        //AxisZ
        VertexAxisBuffer.append(-1.0f);
        VertexAxisBuffer.append(-1.0f);
        VertexAxisBuffer.append(-1.0f);

        VertexAxisBuffer.append(-1.0f);
        VertexAxisBuffer.append(-1.0f);
        VertexAxisBuffer.append(1.0f);

    }
    else
    {

        if(objectName() == "openGLWidgetChartLeft")
        {
            chartFlag = 'L';
        }
        else if(objectName() == "openGLWidgetChartRight")
        {
            chartFlag = 'R';
        }
        else if(objectName() == "openGLWidgetChartTop")
        {

            chartFlag = 'T';
        }

        VertexAxisBuffer.append(-4.0f);
        VertexAxisBuffer.append(0.0f);
        VertexAxisBuffer.append(0.0f);

        VertexAxisBuffer.append(4.0f);
        VertexAxisBuffer.append(0.0f);
        VertexAxisBuffer.append(0.0f);

        VertexAxisBuffer.append(0.0f);
        VertexAxisBuffer.append(-4.0f);
        VertexAxisBuffer.append(0.0f);

        VertexAxisBuffer.append(0.0f);
        VertexAxisBuffer.append(4.0f);
        VertexAxisBuffer.append(0.0f);

        VertexAxisBuffer.append(0.0f);
        VertexAxisBuffer.append(0.0f);
        VertexAxisBuffer.append(-4.0f);

        VertexAxisBuffer.append(0.0f);
        VertexAxisBuffer.append(0.0f);
        VertexAxisBuffer.append(4.0f);
    }






    //绘制坐标系初始化
    m_vaoAxis = new QOpenGLVertexArrayObject();
    m_vaoAxis->create();
    m_vaoAxis->bind();

    m_vboA = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vboA->create();
    m_vboA->bind();

    m_vboA->allocate(VertexAxisBuffer.data(), VertexAxisBuffer.size() * sizeof(GLfloat));
    glFunctions->glEnableVertexAttribArray(0);
    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
    m_vboA->release();
    m_vaoAxis->release();


    m_vaoS = new QOpenGLVertexArrayObject();
    m_vaoS->create();
    m_vaoS->bind();

    m_vboS = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vboS->create();
    m_vboS->bind();

    m_vboS->allocate(VertexStaticBuffer.data(), VertexStaticBuffer.size() * sizeof(GLfloat));
    glFunctions->glEnableVertexAttribArray(0);
    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
    m_vboS->release();
    m_vaoS->release();



    //绘制数据初始化
    m_vaoF = new QOpenGLVertexArrayObject();
    m_vaoF->create();
    m_vaoF->bind();

    m_vboF = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vboF->create();
    m_vboF->bind();

    m_vboF->allocate(VertexDataBuffer.data(), VertexDataBuffer.size() * sizeof(GLfloat));
    glFunctions->glEnableVertexAttribArray(0);
    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
    m_vboF->release();
    m_vaoF->release();



    m_vaoL = new QOpenGLVertexArrayObject();
    m_vaoL->create();
    m_vaoL->bind();

    m_vboL = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vboL->create();
    m_vboL->bind();

    m_vboL->allocate(VertexDataBuffer.data(), VertexDataBuffer.size() * sizeof(GLfloat));
    glFunctions->glEnableVertexAttribArray(0);
    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
    m_vboL->release();
    m_vaoL->release();

    m_vaoR = new QOpenGLVertexArrayObject();
    m_vaoR->create();
    m_vaoR->bind();

    m_vboR = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
    m_vboR->create();
    m_vboR->bind();

    m_vboR->allocate(VertexDataBuffer.data(), VertexDataBuffer.size() * sizeof(GLfloat));
    glFunctions->glEnableVertexAttribArray(0);
    glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
    m_vboR->release();
    m_vaoR->release();
}




void GLChart::resizeGL(int w, int h)
{
    aspectRatio = (float)w/h;
}


void GLChart::paintGL()
{
    QOpenGLFunctions *glFunctions = this->context()->functions();


    glFunctions->glClearColor(0.0, 0.0f, 0.0f, 0.0f);//#454449  //#25242a
    glFunctions->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);




    glFunctions->glDisable(GL_DEPTH_TEST);

    QPainter painter(this);
    painter.setBrush(QBrush(QColor("#454449")));

    painter.drawRect(-1, -1, width()+1, height()+1);



    if(chartFlag == 'M')
    {
        paintChartM(glFunctions);
    }
    else if(chartFlag == 'L')
    {
        painter.drawImage(6, 6, QImage(":/Resources/Chart/left.png"));
        paintChartL(glFunctions);
    }
    else if(chartFlag == 'R')
    {
        painter.drawImage(width() - 35, 6, QImage(":/Resources/Chart/right.png"));
        paintChartR(glFunctions);
    }
    else if(chartFlag == 'T')
    {
        painter.drawImage(6, 6, QImage(":/Resources/Chart/top.png"));
        paintChartT(glFunctions);
    }

}





void GLChart::on_vertexDataChanged(QString  step, QVector<float> vertexTooth, QVector<float> vertexLeftCondyle, QVector<float> vertexRightCondyle)
{
    QOpenGLFunctions *glFunctions = this->context()->functions();
    if(chartFlag == 'M')  //main
    {
        if(step == "OpenClosed")
        {

            VertexStaticBuffer.clear();

            vertexDataToothSize = vertexTooth.size();

            if(vertexDataToothSize>3)
            {

                VertexStaticBuffer.append(vertexTooth[0]);
                VertexStaticBuffer.append(vertexTooth[1]);
                VertexStaticBuffer.append(vertexTooth[2]);

                VertexStaticBuffer.append(vertexLeftCondyle[0]);
                VertexStaticBuffer.append(vertexLeftCondyle[1]);
                VertexStaticBuffer.append(vertexLeftCondyle[2]);



                VertexStaticBuffer.append(vertexLeftCondyle[0]);
                VertexStaticBuffer.append(vertexLeftCondyle[1]);
                VertexStaticBuffer.append(vertexLeftCondyle[2]);

                VertexStaticBuffer.append(vertexRightCondyle[0]);
                VertexStaticBuffer.append(vertexRightCondyle[1]);
                VertexStaticBuffer.append(vertexRightCondyle[2]);

                VertexStaticBuffer.append(vertexRightCondyle[0]);
                VertexStaticBuffer.append(vertexRightCondyle[1]);
                VertexStaticBuffer.append(vertexRightCondyle[2]);

                VertexStaticBuffer.append(vertexTooth[0]);
                VertexStaticBuffer.append(vertexTooth[1]);
                VertexStaticBuffer.append(vertexTooth[2]);

            }



            m_vaoS->bind();
            m_vboS->bind();
            m_vboS->allocate(VertexStaticBuffer.data(), VertexStaticBuffer.size() * sizeof(GLfloat));
            glFunctions->glEnableVertexAttribArray(0);
            glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
            m_vboS->release();
            m_vaoS->release();






            vertexDataToothSize = vertexTooth.size();

            m_vaoF->bind();
            m_vboF->bind();
            m_vboF->allocate(vertexTooth.data(), vertexTooth.size() * sizeof(GLfloat));

            glFunctions->glEnableVertexAttribArray(0);
            glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
            m_vboF->release();

            m_vaoF->release();


            vertexLeftCondyleSize = vertexLeftCondyle.size();
            m_vaoL->bind();
            m_vboL->bind();
            m_vboL->allocate(vertexLeftCondyle.data(), vertexLeftCondyle.size() * sizeof(GLfloat));

            glFunctions->glEnableVertexAttribArray(0);
            glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
            m_vboL->release();

            m_vaoL->release();


            vertexRightCondyletSize = vertexRightCondyle.size();
            m_vaoR->bind();
            m_vboR->bind();
            m_vboR->allocate(vertexRightCondyle.data(), vertexRightCondyle.size() * sizeof(GLfloat));

            glFunctions->glEnableVertexAttribArray(0);
            glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
            m_vboR->release();

            m_vaoR->release();




        }

    }
    else if(chartFlag == 'L')
    {
        if(step == "MoveForward")
        {


            vertexLeftCondyleSize = vertexLeftCondyle.size();

            if(vertexLeftCondyleSize>3)
            {
                offsetXL = -vertexLeftCondyle[0];
                offsetYL = -vertexLeftCondyle[1];
                offsetZL = -vertexLeftCondyle[2];
            }

            m_vaoL->bind();
            m_vboL->bind();
            m_vboL->allocate(vertexLeftCondyle.data(), vertexLeftCondyle.size() * sizeof(GLfloat));

            glFunctions->glEnableVertexAttribArray(0);
            glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
            m_vboL->release();

            m_vaoL->release();
        }

    }
    else if(chartFlag == 'R')
    {
        if(step == "MoveForward")
        {


            vertexRightCondyletSize = vertexRightCondyle.size();
            if(vertexRightCondyletSize>3)
            {
                offsetXR = -vertexRightCondyle[0];
                offsetYR = -vertexRightCondyle[1];
                offsetZR = -vertexRightCondyle[2];
            }

            m_vaoR->bind();
            m_vboR->bind();
            m_vboR->allocate(vertexRightCondyle.data(), vertexRightCondyle.size() * sizeof(GLfloat));

            glFunctions->glEnableVertexAttribArray(0);
            glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
            m_vboR->release();

            m_vaoR->release();


        }


    }
    else if(chartFlag == 'T')
    {
        if(step == "MoveForward")
        {

            vertexDataToothSize = vertexTooth.size();
            if(vertexDataToothSize>3)
            {
                offsetXF = -vertexTooth[0];
                offsetYF = -vertexTooth[1];
                offsetZF = -vertexTooth[2];
            }

            m_vaoF->bind();
            m_vboF->bind();
            m_vboF->allocate(vertexTooth.data(), vertexTooth.size() * sizeof(GLfloat));

            glFunctions->glEnableVertexAttribArray(0);
            glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
            m_vboF->release();

            m_vaoF->release();
        }
        else if(step == "MoveLeft")
        {



            vertexLeftCondyleSize = vertexTooth.size();
            if(vertexLeftCondyleSize>3)
            {
                offsetXL = -vertexTooth[0];
                offsetYL = -vertexTooth[1];
                offsetZL = -vertexTooth[2];
            }

            m_vaoL->bind();
            m_vboL->bind();
            m_vboL->allocate(vertexTooth.data(), vertexTooth.size() * sizeof(GLfloat));

            glFunctions->glEnableVertexAttribArray(0);
            glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
            m_vboL->release();

            m_vaoL->release();

        }
        else if(step == "MoveRight")
        {


            vertexRightCondyletSize = vertexTooth.size();
            if(vertexRightCondyletSize>3)
            {
                offsetXR = -vertexTooth[0];
                offsetYR = -vertexTooth[1];
                offsetZR = -vertexTooth[2];
            }
            m_vaoR->bind();
            m_vboR->bind();
            m_vboR->allocate(vertexTooth.data(), vertexTooth.size() * sizeof(GLfloat));

            glFunctions->glEnableVertexAttribArray(0);
            glFunctions->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3*sizeof(GLfloat), 0);
            m_vboR->release();

            m_vaoR->release();

        }


    }

    parent->update();


}




