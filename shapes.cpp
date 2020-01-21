#include <iostream>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "header.h"
using namespace std ;


void draw_circle(float x , float y){
    float radius = 0.003 ;
    float x2,y2;
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_TRIANGLE_FAN);
        for (float angle=1.0f;angle<361.0f;angle+=0.2)
        {
            x2 = x + sin(angle)*radius;
            y2 = y + cos(angle)*radius;
            glVertex2f(x2,y2);
        }
    glEnd();
    glDisable(GL_POINT_SMOOTH) ;
}

void drawLine(float x , float y , float vgap , float hgap){
    GLfloat lineVertices[] = {
        x  , y , 0 ,
        x + vgap , y + hgap , 0 
    };
    glVertexPointer(3 , GL_FLOAT , 0 , lineVertices) ;
    glDrawArrays(GL_LINES , 0 , 2) ;
}

void display_tree(node *root , float x , float y ,float vgap , float hgap){
    if (root->left != nullptr){
        glLineWidth(5);
        glColor3f(0.0f, 0.0f, 0.0f);
        glRasterPos3f(x - vgap/2, y - hgap/2,0.0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0');
        glColor3f(0.0f, 1.0f, 0.0f);
        drawLine(x , y , -vgap , -hgap) ;
        display_tree(root->left , x - vgap , y - hgap , vgap /2  , hgap / 2) ;
    }
    if(root->right != nullptr){
        glColor3f(0.0f, 0.0f, 0.0f);
        glRasterPos3f(x+vgap/2, y-hgap/2,0.0);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '1');
        glColor3f(0.0f, 0.0f, 1.0f);
        drawLine(x , y , vgap , -hgap) ;
        display_tree(root->right , x + vgap , y - hgap , vgap / 2  , hgap / 2 ) ;
    }
    glColor3f(1.0f, 0.0f, 0.0f);
    draw_circle(x , y) ;
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(x, y,0.0);
    for(char *s = &root->c.at(0) ; *s != '\0' ; s++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *s);

} 
