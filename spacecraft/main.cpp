//
//  main.cpp
//  spacecraft
//
//  Created by LUE on 16/08/2022.
//

#include <GLUT/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include<math.h>

using namespace std;
const float DEG2RAD = 3.14159/180.0;
float sc=1, h=0;
int sz=7;
int starc1=255,starc2=255,starc3=255,sky1=31,sky2=63,sky3=96,back1=38,back2=77,back3=115;
GLfloat light_ambient[] = {0.20,0.0,0.50, 0.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = {-0.10, 0.0,0.0750, 1.0};
GLfloat shininess[]      = {128};

//GLfloat shininess[]      = {128};
//int sky1=31,sky2=63,sky3=96;
float xpos = -1;
float cloud_move1 = 0.95, DogMove = 0.0, dogMoveright = 0.0, light = 2.0; float SpaceLoaction;
GLuint myTexture1, myTexture2;
char t1_path[] = "/Users/nd3/Desktop/11.bmp";
char t2_path[] = "/Users/nd3/Desktop/22.bmp";


GLuint LoadTexture(const char* filename, int width, int height)
{
   GLuint texture;
   unsigned char* data;
   FILE* file;

   //The following code will read in our RAW file
   file = fopen(filename, "rb");

   if (file == NULL)
   {
       cout << "Unable to open the image file" << endl << "Program will exit :(" << endl;
       exit(0);
       return 0;
   }

   data = (unsigned char*)malloc(width * height * 3);
   fread(data, width * height * 3, 1, file);

   fclose(file);


   // reorder the image colors to RGB not BGR
   for (int i = 0; i < width * height; ++i)
   {
       int index = i * 3;
       unsigned char B, R;
       B = data[index];
       R = data[index + 2];

       data[index] = R;
       data[index + 2] = B;

   }

   glGenTextures(1, &texture);            //generate the texture with the loaded data
   glBindTexture(GL_TEXTURE_2D, texture); //bind the texture to it's array

   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //set texture environment parameters

   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MODULATE);
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MODULATE);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
   /////////////////////////////////////////

   free(data); //free the texture array


   return texture; //return whether it was successfull
}
void init() {
   myTexture1 = LoadTexture(t1_path, 568,402);
   myTexture2 = LoadTexture(t2_path, 660, 700);
  
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}
void idle() {
   if (xpos <= 1) {
       xpos += 0.005;
   }
   else {
       xpos = xpos - 2;
   }
   glutPostRedisplay();
}
void midPointEllipse(float xradius, float yradius, float q)
{
   glBegin(GL_POLYGON);

   for(int i=0; i < 360; i++)
   {
        //convert degrees into radians
       float degInRad = i*DEG2RAD/q;
       glVertex2f(cos(degInRad)*xradius,sin(degInRad)*yradius);
   }
   glEnd();
}
void space1(){

   glPushMatrix();
       glTranslatef(0,h,0);
       glScalef(sc,sc,1);
   glColor3f(0.274, 0, 0.235);//...........................Flying soccer
   glPushMatrix();
       glTranslatef(0.75,-0.5,0);
       glScalef(0.08,0.08,1);
       midPointEllipse(4, 0.5, 1);
   glPopMatrix();

   glPushMatrix();
       glTranslatef(0.75,-0.5,0);
       glBegin(GL_POLYGON);
       for(int i=0;i<200;i++)
           {
               glColor3ub(0,180,180);
               float pi=3.1416/2;
               float A=(i*2*pi)/200;
               float r=0.17;
               float x = r * cos(A);
               float y = r * sin(A);
               glVertex2f(x,y);
           }

       glEnd();
   glPopMatrix();

       glBegin(GL_TRIANGLES);

       glColor3ub(255,255,255);
       glVertex2f(0.53f,-0.6f);
       glVertex2f(0.57f,-0.6f);
       glVertex2f(0.555f,-0.51f);

       glVertex2f(0.93f,-0.6f);
       glVertex2f(0.97f,-0.6f);
       glVertex2f(0.955f,-0.51f);

       glVertex2f(0.73f,-0.59f);
       glVertex2f(0.77f,-0.59f);
       glVertex2f(0.755f,-0.51f);

       glEnd();

       glPointSize(sz);
       glBegin(GL_POINTS);

       glColor3ub(255,255,0);
       glVertex2f(0.53f,-0.51f);
       glVertex2f(0.63f,-0.515f);
       glVertex2f(0.73f,-0.52f);
       glVertex2f(0.83f,-0.52f);
       glVertex2f(0.93f,-0.515f);
       glVertex2f(1.03f,-0.51f);

       glEnd();
   glPopMatrix();




}
void blding(){
  glBegin(GL_POLYGON);//..........................................building
  glColor3f(0.345, 0.270, 0.396);

   glVertex2f(-1.0f,-0.25f);
   glVertex2f(-1.0f,0.2f);
   glVertex2f(-0.98f,0.2f);
   glVertex2f(-0.98f,0.15f);
   glVertex2f(-0.95f,0.18f);
   glVertex2f(-0.92f,0.15f);
   glVertex2f(-0.92f,0.3f);
   glVertex2f(-0.89f,0.3f);
   glVertex2f(-0.89f,0.27f);
   glVertex2f(-0.86f,0.27f);
   glVertex2f(-0.86f,0.25f);
   glVertex2f(-0.83f,0.25f);
   glVertex2f(-0.83f,0.2f);
   glVertex2f(-0.8f,0.23f);
   glVertex2f(-0.77f,0.2f);
   glVertex2f(-0.74f,0.2f);
   glVertex2f(-0.74f,0.35f);
   glVertex2f(-0.7f,0.35f);
   glVertex2f(-0.7f,0.2f);
   glVertex2f(-0.67f,0.2f);
   glVertex2f(1.0f,-0.25f);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2f(-0.67f,-0.2f);
   glVertex2f(-0.67f,0.4f);
   glVertex2f(-0.61f,0.4f);
   glVertex2f(-0.61f,0.3f);
   glVertex2f(-0.55f,0.3f);
   glVertex2f(-0.55f,0.25f);
   glVertex2f(-0.53f,0.25f);
   glVertex2f(-0.51f,0.2f);
   glVertex2f(-0.46f,0.2f);
   glVertex2f(1.0f,-0.25f);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2f(-0.46f,-0.2f);
   glVertex2f(-0.46f,0.5f);
   glVertex2f(-0.35f,0.5f);
   glVertex2f(-0.35f,0.25f);
   glVertex2f(-0.3f,0.25f);
   glVertex2f(1.0f,-0.25f);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2f(-0.3f,-0.2f);
   glVertex2f(-0.3f,0.5f);
   glVertex2f(-0.25f,0.5f);
   glVertex2f(-0.25f,0.53f);
   glVertex2f(-0.23f,0.53f);
   glVertex2f(-0.23f,0.25f);
   glVertex2f(-0.23f,0.4f);
   glVertex2f(-0.14f,0.4f);
   glVertex2f(-0.14f,0.25f);
   glVertex2f(-0.1f,0.25f);
   glVertex2f(-0.1f,0.2f);
   glVertex2f(-0.05f,0.2f);
   glVertex2f(1.0f,-0.25f);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2f(-0.05f,-0.2f);
   glVertex2f(-0.05f,0.5f);
   glVertex2f(0.05f,0.5f);
   glVertex2f(0.05f,0.25f);
   glVertex2f(1.0f,-0.25f);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2f(0.3f,-0.2f);
   glVertex2f(0.3f,0.5f);
   glVertex2f(0.25f,0.5f);
   glVertex2f(0.25f,0.53f);
   glVertex2f(0.23f,0.53f);
   glVertex2f(0.23f,0.25f);
   glVertex2f(0.23f,0.4f);
   glVertex2f(0.14f,0.4f);
   glVertex2f(0.14f,0.25f);
   glVertex2f(0.1f,0.25f);
   glVertex2f(0.1f,0.2f);
   glVertex2f(0.05f,0.2f);
   glVertex2f(1.0f,-0.25f);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2f(0.46f,-0.2f);
   glVertex2f(0.46f,0.5f);
   glVertex2f(0.35f,0.5f);
   glVertex2f(0.35f,0.25f);
   glVertex2f(0.3f,0.25f);
   glVertex2f(1.0f,-0.25f);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2f(0.67f,-0.2f);
   glVertex2f(0.67f,0.4f);
   glVertex2f(0.61f,0.4f);
   glVertex2f(0.61f,0.3f);
   glVertex2f(0.55f,0.3f);
   glVertex2f(0.55f,0.25f);
   glVertex2f(0.53f,0.25f);
   glVertex2f(0.51f,0.2f);
   glVertex2f(0.46f,0.2f);
   glVertex2f(1.0f,-0.25f);
   glEnd();

   glBegin(GL_POLYGON);
   glVertex2f(1.0f,-0.2f);
   glVertex2f(1.0f,0.2f);
   glVertex2f(0.98f,0.2f);
   glVertex2f(0.98f,0.15f);
   glVertex2f(0.95f,0.18f);
   glVertex2f(0.92f,0.15f);
   glVertex2f(0.92f,0.3f);
   glVertex2f(0.89f,0.3f);
   glVertex2f(0.89f,0.27f);
   glVertex2f(0.86f,0.27f);
   glVertex2f(0.86f,0.25f);
   glVertex2f(0.83f,0.25f);
   glVertex2f(0.83f,0.2f);
   glVertex2f(0.8f,0.23f);
   glVertex2f(0.77f,0.2f);
   glVertex2f(0.74f,0.2f);
   glVertex2f(0.74f,0.35f);
   glVertex2f(0.7f,0.35f);
   glVertex2f(0.7f,0.2f);
   glVertex2f(0.67f,0.2f);
   glVertex2f(1.0f,-0.59f);
    

   glEnd();

}
void stars() {
   glEnable(GL_POINT_SMOOTH);
   glPointSize(0.090);
   glBegin(GL_POINTS);
   glColor3f(0.996, 0.949, 0.925);
   glVertex2f(0.9, 0.9);
   glVertex2f(-0.9, 0.9);
   glVertex2f(0.8, 0.5);
   glVertex2f(-0.8, 0.5);
   glVertex2f(0.5, 0.7);
   glVertex2f(-0.5, 0.7);
   glVertex2f(0.0, 0.5);
   glVertex2f(0.0, 0.8);
   //
   glVertex2f(0.9, -0.9);
   glVertex2f(-0.9, -0.9);
   glVertex2f(0.8, -0.5);
   glVertex2f(-0.8, -0.5);
   glVertex2f(0.5, -0.7);
   glVertex2f(-0.5, -0.7);
   glVertex2f(0.0, -0.5);
   glVertex2f(0.0, -0.8);
   //
   glVertex2f(0.0, 0.3);
   glVertex2f(0.0, 0.1);
   glVertex2f(0.2, 0.3);
   glVertex2f(-0.2, 0.3);
   glVertex2f(0.1, 0.1);
   glVertex2f(-0.1, 0.1);
   glVertex2f(-0.2, 0.6);
   glVertex2f(-0.3, 0.2);
   glVertex2f(-0.4, 0.5);
   //
   glVertex2f(0.0, -0.3);
   glVertex2f(0.0, -0.1);
   glVertex2f(0.2, -0.3);
   glVertex2f(-0.2, -0.3);
   glVertex2f(0.1, -0.1);
   glVertex2f(-0.1, -0.1);
   glVertex2f(-0.2, -0.6);
   glVertex2f(-0.3, -0.2);
   glVertex2f(-0.4, -0.5);
   //
   glVertex2f(0.5, 0.3);
   glVertex2f(-0.5, 0.3);
   glVertex2f(0.3, 0.6);
   glVertex2f(-0.5, 0.35);
   glVertex2f(0.7, 0.4);
   glVertex2f(-0.8, 0.2);
   glVertex2f(-0.5, 0.9);
   glVertex2f(0.5, 0.9);
   //
   glVertex2f(0.5, -0.3);
   glVertex2f(-0.5, -0.3);
   glVertex2f(0.3, -0.6);
   glVertex2f(-0.5, -0.35);
   glVertex2f(0.7, -0.4);
   glVertex2f(-0.8, -0.2);
   glVertex2f(-0.5, -0.9);
   glVertex2f(0.5, -0.9);
   //
   glVertex2f(-0.45, -0.3);
   glVertex2f(0.25, -0.33);
   glVertex2f(-0.15, -0.4);
   glVertex2f(0.3, -0.2);
   glVertex2f(-0.35, -0.35);
   glVertex2f(0.7, -0.5);
   glVertex2f(-0.2, -0.9);
   glVertex2f(-0.1, -0.9);

   glVertex2f(-0.1, 0.4);
   glVertex2f(-0.2, 0.4);
   glVertex2f(-0.2, 0.4);
   glVertex2f(-0.8, 0.4);
   glVertex2f(-0.5, 0.4);
   glVertex2f(0.0, -0.4);
   glEnd();

}
void moon() {
   glEnable(GL_POINT_SMOOTH); {
       glPointSize(50.0);
       glBegin(GL_POINTS);
       // glColor3f(1,1,1);
       glVertex2f(0.7, 0.7);
       glEnd();
   }
}


void shootingstar() {
   glBegin(GL_LINE_STRIP); {
       glColor3f(1, 1, 1);
       glVertex2f(0.6, 0.5);
       glVertex2f(0.55, 0.45);
       glVertex2f(0.55, 0.45);
       glEnd();
   }
   glBegin(GL_LINE_STRIP); {
       glColor3f(1, 1, 1);
       glVertex2f(-0.8, 0.7);
       glVertex2f(-0.85, 0.75);
       glVertex2f(-0.85, 0.75);
       glEnd();
   }
   glBegin(GL_LINE_STRIP); {
       glColor3f(1, 1, 1);
       glVertex2f(-0.25, 0.1);
       glVertex2f(-0.35, 0.050);
       glEnd();
   }

}


void starry() {
   glBegin(GL_LINES); {
       glColor3f(1.0f, 1.0f, 1.0f);
       glVertex2f(-0.67f, 0.0f);
       glVertex2f(-0.63f, 0.0f);
       glEnd();
   }
   glBegin(GL_LINES); {
       glColor3f(1.0f, 1.0f, 1.0f);
       glVertex2f(-0.65f, 0.030f);
       glVertex2f(-0.65f, -0.03f);
       glEnd();
   }
   glBegin(GL_LINES); {
       glColor3f(1.0f, 1.0f, 1.0f);
       glVertex2f(-0.31f, 0.6f);
       glVertex2f(-0.35f, 0.6f);
       glEnd();
   }
   glBegin(GL_LINES); {
       glColor3f(1.0f, 1.0f, 1.0f);
       glVertex2f(-0.33f, 0.63f);
       glVertex2f(-0.33f, 0.57f);
       glEnd();
   }
   glBegin(GL_LINES); {
       glColor3f(1.0f, 1.0f, 1.0f);
       glVertex2f(0.4f, 0.2f);
       glVertex2f(0.44f, 0.2f);
       glEnd();
   }

   glBegin(GL_LINES); {
       glColor3f(1.0f, 1.0f, 1.0f);
       glVertex2f(0.42f, 0.22f);
       glVertex2f(0.42f, 0.16f);
       glEnd();
   }

   glBegin(GL_LINES); {
       glColor3f(1.0f, 1.0f, 1.0f);
       glVertex2f(0.2f, 0.6f);
       glVertex2f(0.24f, 0.6f);
       glEnd();
   }

   glBegin(GL_LINES);
   glColor3f(1.0f, 1.0f, 1.0f);
   glVertex2f(0.22f, 0.62f);
   glVertex2f(0.22f, 0.57f);
   glEnd();

   glBegin(GL_LINES); {
       glColor3f(1.0f, 1.0f, 1.0f);
       glVertex2f(-0.71f, 0.3f);
       glVertex2f(-0.74f, 0.3f);
       glEnd();
   }
   glBegin(GL_LINES); {
       glColor3f(1.0f, 1.0f, 1.0f);
       glVertex2f(-0.72f, 0.32f);
       glVertex2f(-0.72f, 0.27f);
       glEnd();
   }

}

void clouds() {
   glEnable(GL_POINT_SMOOTH); {
       glPointSize(25.0);
       glBegin(GL_POINTS);
       glColor3f(1, 1, 1);
       glVertex2f(-0.93, 0.3);
       glVertex2f(-0.89, 0.3);
       glVertex2f(-0.89, 0.32);
       glVertex2f(-0.85, 0.3);
       glEnd();
   }
   glEnable(GL_POINT_SMOOTH); {
       glPointSize(25.0);
       glBegin(GL_POINTS);
       glColor3f(1, 1, 1);
       glVertex2f(-0.63, 0.6);
       glVertex2f(-0.6, 0.6);
       glVertex2f(-0.59, 0.63);
       glVertex2f(-0.55, 0.6);
       glEnd();
   }
   glEnable(GL_POINT_SMOOTH); {
       glPointSize(25.0);
       glBegin(GL_POINTS);
       glColor3f(1, 1, 1);
       glVertex2f(0.69, 0.1);
       glVertex2f(0.61, 0.1);
       glVertex2f(0.65, 0.13);
       glVertex2f(0.65, 0.1);
       glEnd();
   }
   glEnable(GL_POINT_SMOOTH); {
       glPointSize(25.0);
       glBegin(GL_POINTS);
       glColor3f(1, 1, 1);
       glVertex2f(0.33, 0.4);
       glVertex2f(0.28, 0.4);
       glVertex2f(0.289, 0.43);
       glVertex2f(0.24, 0.4);
       glEnd();
   }
}
void tree()
{
   glPushMatrix();
   glBegin(GL_POLYGON);
   glColor3f(0.286, 0.180, 0.172); // color brown
   glVertex2f(0.33, -0.28); // 1
   glVertex2f(0.24, -0.28); // 2
   glVertex2f(0.24, 0.50); // 3
   glVertex2f(0.33, 0.50); // 4
   glEnd();

   glBegin(GL_POLYGON);
   glColor3f(0.384, 0.458, 0.184); // color green
   glVertex2f(250, 0); // 1
   glVertex2f(380, 0); // 2
   glVertex2f(322, 100); // 3
   glEnd();

   glPopMatrix();
}
void TreeNode1()
{
   glPushMatrix();
   glBegin(GL_POLYGON);
   glColor3f(0.478, 0.552, 0.384); // color green
   glVertex2f(0.8, 1.0); // 1
   glVertex2f(0.9, 0.8); // 2
   glVertex2f(0.7, 0.8); // 3
   glEnd();
   glPopMatrix();


}void spaceshiphead()
{
   glPushMatrix();
   glBegin(GL_POLYGON);
   glColor3f(0.541, 0.564, 0.658); // color green
   glVertex2f(0.8, 1.0); // 1
   glVertex2f(0.9, 0.8); // 2
   glVertex2f(0.7, 0.8); // 3
   glEnd();
   glPopMatrix();

}


void lazer() {

   glPushMatrix();
   glBegin(GL_POLYGON);

   glColor3f(0.898, 0.803, 0.874); // color green
   glVertex2f(0.8, 2.3); // 1
   glVertex2f(1, 0.8); // 2
   glVertex2f(0.5, 0.8); // 3
   glEnd();
   glPopMatrix();

}
void fulltree() {

   glPushMatrix();
   glScalef(0.2, 0.2, 0.1);
   glTranslatef(-4.8, -4.2, 0);
   tree();
   glPopMatrix();

   glPushMatrix();
   //glScalef(1,0,0);
   glTranslatef(-1.7, -1.6, -1);
   TreeNode1();
   glPopMatrix();

}
void fulltree1() {
   glPushMatrix();
   //glScalef(1,0,0);
   glTranslatef(-1.7, -1.4, -1);
   TreeNode1();
   glPopMatrix();

}
void window() {
   glPushMatrix();

   glTranslatef(-0.85, -0.55, -1);
   glBegin(GL_POLYGON);
   glColor3f(0.996, 0.949, 0.925);
   glVertex2f(0.03, 0.03); // 1
   glVertex2f(0.07, 0.03); // 2
   glVertex2f(0.07, 0.07); // 3
   glVertex2f(0.03, 0.07); // 3
   glEnd();
   glPopMatrix();

   glPushMatrix();

   glTranslatef(-0.85, -0.6, -1);
   glBegin(GL_POLYGON);
   glColor3f(0.996, 0.949, 0.925);
   glVertex2f(0.03, 0.03); // 1
   glVertex2f(0.07, 0.03); // 2
   glVertex2f(0.07, 0.07); // 3
   glVertex2f(0.03, 0.07); // 3
   glEnd();
   glPopMatrix();

   glPushMatrix();

   glTranslatef(-0.8, -0.55, -1);
   glBegin(GL_POLYGON);
   glColor3f(0.996, 0.949, 0.925);
   glVertex2f(0.03, 0.03); // 1
   glVertex2f(0.07, 0.03); // 2
   glVertex2f(0.07, 0.07); // 3
   glVertex2f(0.03, 0.07); // 3
   glEnd();
   glPopMatrix();

   glPushMatrix();

   glTranslatef(-0.8, -0.6, -1);
   glBegin(GL_POLYGON);
   glColor3f(0.996, 0.949, 0.925);
   glVertex2f(0.03, 0.03); // 1
   glVertex2f(0.07, 0.03); // 2
   glVertex2f(0.07, 0.07); // 3
   glVertex2f(0.03, 0.07); // 3
   glEnd();
   glPopMatrix();
   //down window
   glPushMatrix();

   glTranslatef(-0.8, -0.8, -1);
   glBegin(GL_POLYGON);
   glColor3f(0.996, 0.949, 0.925);
   glVertex2f(0.03, 0.03); // 1
   glVertex2f(0.07, 0.03); // 2
   glVertex2f(0.07, 0.07); // 3
   glVertex2f(0.03, 0.07); // 3
   glEnd();
   glPopMatrix();

   glPushMatrix();

   glTranslatef(-0.8, -0.85, -1);
   glBegin(GL_POLYGON);
   glColor3f(0.996, 0.949, 0.925);
   glVertex2f(0.03, 0.03); // 1
   glVertex2f(0.07, 0.03); // 2
   glVertex2f(0.07, 0.07); // 3
   glVertex2f(0.03, 0.07); // 3
   glEnd();
   glPopMatrix();

   glPushMatrix();

   glTranslatef(-0.85, -0.8, -1);
   glBegin(GL_POLYGON);
   glColor3f(0.996, 0.949, 0.925);
   glVertex2f(0.03, 0.03); // 1
   glVertex2f(0.07, 0.03); // 2
   glVertex2f(0.07, 0.07); // 3
   glVertex2f(0.03, 0.07); // 3
   glEnd();
   glPopMatrix();

   glPushMatrix();

   glTranslatef(-0.85, -0.85, -1);
   glBegin(GL_POLYGON);
   glColor3f(0.996, 0.949, 0.925);
   glVertex2f(0.03, 0.03); // 1
   glVertex2f(0.07, 0.03); // 2
   glVertex2f(0.07, 0.07); // 3
   glVertex2f(0.03, 0.07); // 3
   glEnd();
   glPopMatrix();

   //right window
   glPushMatrix();

   glTranslatef(-0.45, -0.85, -1);
   glBegin(GL_POLYGON);
   glColor3f(0.996, 0.949, 0.925);
   glVertex2f(0.03, 0.03); // 1
   glVertex2f(0.07, 0.03); // 2
   glVertex2f(0.07, 0.07); // 3
   glVertex2f(0.03, 0.07); // 3
   glEnd();
   glPopMatrix();

   glPushMatrix();

   glTranslatef(-0.45, -0.8, -1);
   glBegin(GL_POLYGON);
   glColor3f(0.996, 0.949, 0.925);
   glVertex2f(0.03, 0.03); // 1
   glVertex2f(0.07, 0.03); // 2
   glVertex2f(0.07, 0.07); // 3
   glVertex2f(0.03, 0.07); // 3
   glEnd();
   glPopMatrix();

   glPushMatrix();

   glTranslatef(-0.45, -0.6, -1);
   glBegin(GL_POLYGON);
   glColor3f(0.996, 0.949, 0.925);
   glVertex2f(0.03, 0.03); // 1
   glVertex2f(0.07, 0.03); // 2
   glVertex2f(0.07, 0.07); // 3
   glVertex2f(0.03, 0.07); // 3
   glEnd();
   glPopMatrix();

   glPushMatrix();

   glTranslatef(-0.45, -0.55, -1);
   glBegin(GL_POLYGON);
   glColor3f(0.996, 0.949, 0.925);
   glVertex2f(0.03, 0.03); // 1
   glVertex2f(0.07, 0.03); // 2
   glVertex2f(0.07, 0.07); // 3
   glVertex2f(0.03, 0.07); // 3
   glEnd();
   glPopMatrix();

   //middle window
   glPushMatrix();

   glTranslatef(-0.64, -0.65, -1);
   glBegin(GL_POLYGON);
   glColor3f(0.996, 0.949, 0.925); // color green
   glVertex2f(0.03, 0.03); // 1
   glVertex2f(0.07, 0.03); // 2
   glVertex2f(0.07, 0.07); // 3
   glVertex2f(0.03, 0.07); // 3
   glEnd();
   glPopMatrix();

   //door
   glPushMatrix();

   glTranslatef(-0.74, -1, -1);
   glBegin(GL_POLYGON);
   glColor3f(0.368, 0.227, 0.090);//orange/brown
   glVertex2f(0.1, 0.1); // 1
   glVertex2f(0.2, 0.1); // 2
   glVertex2f(0.2, 0.3); // 3
   glVertex2f(0.1, 0.3); // 3
   glEnd();
   glPopMatrix();




}


void SpaceShip() {
   glEnable(GL_POINT_SMOOTH); {
       glTranslatef(-1, 0, 0);
       glPointSize(25.0);
       glBegin(GL_POINTS);
       glColor3f(0.541, 0.564, 0.658);
       glVertex2f(-0.93, 0.3);
       glVertex2f(-0.89, 0.3);
       glVertex2f(-0.89, 0.32);
       glVertex2f(-0.85, 0.3);
       glEnd();
   }
}
void spaceship()
{
   glPushMatrix();

   glTranslatef(0.0, 0.35, -1);
   glBegin(GL_POLYGON);
   glColor3f(0.541, 0.564, 0.658);//orange/brown
   glVertex2f(-0.1, 0.1); // 1
   glVertex2f(0.3, 0.1); // 2
   glVertex2f(0.2, 0.2); // 3
   glVertex2f(0.0, 0.2); // 3
   glEnd();
   glPopMatrix();
}
void line()
{
   glBegin(GL_LINE_STRIP);
   glColor3f(0, 0, 0);

   glVertex2f(0.2f, 0.0f);
   glVertex2f(0.39f, 0.0f);
   glEnd();

}
void eye()
{

   glEnable(GL_POINT_SMOOTH);
   glPointSize(10.0);
   glBegin(GL_POINTS);
   glColor3f(0.635, 0.749, 0.905);
   glVertex2f(-0.54, 0.3);
   glEnd();

}

void completeSpaceShip()
{

   spaceship();
   //spaceship head
   glPushMatrix();
   glTranslatef(-0.38, 0.00, 0);
   glScalef(0.60, 0.69, 0);
   spaceshiphead();
   glutPostRedisplay();
   glPopMatrix();
   glPushMatrix();
   glTranslatef(0.74, 0.2, 0);
   eye();
   glPopMatrix();
   glPushMatrix();
   glTranslatef(0.67, 0.2, 0);
   eye();
   glPopMatrix();
   glPushMatrix();
   glTranslatef(0.61, 0.2, 0);
   eye();
   glPopMatrix();
   glPushMatrix();
   glTranslatef(0.54, 0.2, 0);
   eye();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-0.2, 0.55, 0);
   line();
   glPopMatrix();
}

void rightBuilding() {

   glPushMatrix();
   //main building
   glTranslatef(0.9, -1.2, 0);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, myTexture2);
   glBegin(GL_POLYGON);
   glColor3f(0.819, 0.686, 0.560); // color green
   glTexCoord2f(0, 0); glVertex2f(0.4, 0.3); // 1
   glTexCoord2f(1, 0); glVertex2f(0.8, 0.3); // 2
   glTexCoord2f(1, 1); glVertex2f(0.8, 0.6); // 3
   glTexCoord2f(0, 1); glVertex2f(0.4, 0.6); // 3
   glEnd();
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
   //RBComponents();

}
void building() {
   glPushMatrix();
   //main building
   glTranslatef(-1.15, -1.2, 0);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, myTexture1);
   glBegin(GL_POLYGON);
   glColor3f(0.925, 0.811, 0.596); // color green
   glTexCoord2f(0, 0); glVertex2f(0.3, 0.3); // 1
   glTexCoord2f(1, 0); glVertex2f(0.8, 0.3); // 2
   glTexCoord2f(1, 1); glVertex2f(0.8, 0.8); // 3
   glTexCoord2f(0, 1); glVertex2f(0.3, 0.8); // 3
   glEnd();
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   SpaceShip();
   rightBuilding();




}
void road() {


   glPushMatrix();


   glTranslatef(1.41, -1.15, -1);
   glBegin(GL_POLYGON);
   glColor3f(0.211, 0.203, 0.254);//orange/brown
   glVertex2f(-2.5, 0.1); // 1
   glVertex2f(-0.2, 0.1); // 2
   glVertex2f(-0.2, 0.25); // 3
   glVertex2f(-2.5, 0.25); // 3
   glEnd();
   glPopMatrix();
}

void dog() {

   //head
   glTranslatef(0.08, 0, 0);

   glEnable(GL_POINT_SMOOTH); {
       glPointSize(35.0);
       glBegin(GL_POINTS);
       glColor3f(0.921, 0.870, 0.815);
       glVertex2f(0.0, -0.8);
       glEnd();
   }


   //ear
   glEnable(GL_POINT_SMOOTH); {
       glPointSize(9.0);
       glBegin(GL_POINTS);
       glColor3f(1, 1, 1);
       glVertex2f(-0.03, -0.74);
       glVertex2f(-0.04, -0.73);
       glEnd();
   }
   //ear
   glEnable(GL_POINT_SMOOTH); {
       glPointSize(9.0);
       glBegin(GL_POINTS);
       glColor3f(1, 1, 1);
       glVertex2f(0.03, -0.74);
       glVertex2f(0.04, -0.73);
       glEnd();
   }
   //body
   glEnable(GL_POINT_SMOOTH); {
       glPointSize(34.0);
       glBegin(GL_POINTS);
       glColor3f(1, 1, 1);
       glVertex2f(0.0, -0.86);
       glEnd();


   }
   //right hand
   glEnable(GL_POINT_SMOOTH); {
       glPointSize(12.0);
       glBegin(GL_POINTS);
       glColor3f(1, 1, 1);
       glVertex2f(-0.06, -0.84);
       glEnd();
   }
   //left hand
   glEnable(GL_POINT_SMOOTH); {
       glPointSize(12.0);
       glBegin(GL_POINTS);
       glColor3f(1, 1, 1);
       glVertex2f(0.06, -0.84);
       glEnd();
   }
   //left leg
   glEnable(GL_POINT_SMOOTH); {
       glPointSize(12.0);
       glBegin(GL_POINTS);
       glColor3f(0.921, 0.870, 0.815);
       glVertex2f(-0.045, -0.9);
       glEnd();
   }
   //right leg
   glEnable(GL_POINT_SMOOTH); {
       glPointSize(12.0);
       glBegin(GL_POINTS);
       glColor3f(0.921, 0.870, 0.815);
       glVertex2f(0.045, -0.9);
       glEnd();
   }
   //right eye
   glEnable(GL_POINT_SMOOTH); {
       glPointSize(3.0);
       glBegin(GL_POINTS);
       glColor3f(0, 0, 0);
       glVertex2f(0.02, -0.8);
       glEnd();
   }
   //left eye
   glEnable(GL_POINT_SMOOTH); {
       glPointSize(3.0);
       glBegin(GL_POINTS);
       glColor3f(0, 0, 0);
       glVertex2f(-0.02, -0.8);
       glEnd();
   }
   //nose
   glEnable(GL_POINT_SMOOTH); {
       glPointSize(3.0);
       glBegin(GL_POINTS);
       glColor3f(0, 0, 0);
       glVertex2f(0.0, -0.82);
       glEnd();
   }

}

void myKeyboardFunc(unsigned char key, int x, int y)
{
   switch (key)
   {
   case 'a':


       cloud_move1 -= 0.05;
       SpaceLoaction = cloud_move1;
       if (SpaceLoaction <=- 0.65)
       {
           light = -0.7;
       }

       glutPostRedisplay();
       break;
   case 's':


       cloud_move1 += 0.05;
       dogMoveright += 0.05;
       light = 2.0;
       glutPostRedisplay();
       break;
   case 'd':
       DogMove += 0.05;
       break;
   case 'l':
       light = -0.7;
       break;

   }



   glutPostRedisplay();
}
void display() {
   init();
   glClearColor(0.435, 0.364, 0.494, 0.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    blding();
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    
   glPushMatrix();
   glTranslatef(xpos, 0, 0);
   clouds();
   glPopMatrix();

   fulltree();

   stars();
   moon();
   shootingstar();
   starry();


   glPushMatrix();
   glTranslatef(-0.8, 0.2, 0);
   stars();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-0.04, 0.02, 0);
   glColor3f(0.435, 0.364, 0.494);
   moon();
   glPopMatrix();


   glPushMatrix();
   glTranslatef(0.3, 0.5, 0);
   shootingstar();
   glPopMatrix();



   glPushMatrix();

   //glBindTexture(GL_TEXTURE_2D, myTexture);
   building();
   glPopMatrix();


   glPushMatrix();
   glTranslatef(0.6, 0, 0);
   fulltree();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.6, -0.16, 0);
   fulltree1();
   glPopMatrix();
   glPushMatrix();
   glTranslatef(0.6, -0.12, 0);
   fulltree1();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(1.65, 0, 0);
   fulltree();
   glPopMatrix();
   glPushMatrix();
   glTranslatef(1.65, -0.16, 0);
   fulltree1();
   glPopMatrix();
   glPushMatrix();
   glTranslatef(1.65, -0.12, 0);
   fulltree1();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(light, -1.7, 0);
   lazer();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0,0.006 , 0);
   road();
   glPopMatrix();
   road();
   glPushMatrix();
   glTranslatef(dogMoveright, DogMove, 0);
   dog();
   glPopMatrix();

 
   glPushMatrix();
    glTranslatef(cloud_move1,0.99, 0.0);
   space1();
   glPopMatrix();


   glPushMatrix();
   glColor3f(1.0, 1.0, 1.0);
   char txt[] = "You can’t escape from aliens";
   glRasterPos3f(-0.5,-0.25, 0);

   for (char* c = txt; *c != '\0'; c++) {
       glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);  // Updates the position
   }
   /*for (auto ch : txt)
   {
       glutStrokeCharacter(GLUT_STROKE_ROMAN, ch);
   }*/
   glPopMatrix();
   glFlush();
   glutSwapBuffers();
}

void reshape(int width, int hight) {
   glViewport(0, 0, 650, 650);

}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);



   glutInitWindowSize(600, 600);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("^^ SpaceCraft In My Dreamy Sky ^^");
   glutDisplayFunc(display);
   glutKeyboardFunc(myKeyboardFunc);
   glutReshapeFunc(reshape);
   glutIdleFunc(idle);
   glutMainLoop();
   return 0;
}
