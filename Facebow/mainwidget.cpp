#include "mainwidget.h"
#include <GL/glu.h>


MainWidget::~MainWidget()
{

}








void MainWidget::initializeGL()
{

    glClearColor(0, 0, 0, 1);

    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0 );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );


    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

}




void MainWidget::resizeGL(int w, int h)
{


    glViewport( 100, 20, (GLint)w, (GLint)h );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}
//! [5]

void MainWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glTranslatef( -1.5,  0.0, -6.0 );

    glBegin( GL_TRIANGLES );
      glColor3f( 1.0, 0.0, 0.0 );
      glVertex3f(  0.0,  1.0,  0.0 );
      glColor3f( 0.0, 1.0, 0.0 );
      glVertex3f( -1.0, -1.0,  0.0 );
      glColor3f( 0.0, 0.0, 1.0 );
      glVertex3f(  1.0, -1.0,  0.0 );

    glEnd();


    glFlush();



}
