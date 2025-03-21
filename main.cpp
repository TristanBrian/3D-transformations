#include <GL/freeglut.h>
#include <iostream>
#include <cmath>

// Transformation parameters
float tx = 0.0, ty = 0.0, tz = 0.0; // Translation
float angle = 0.0, rx = 0.0, ry = 1.0, rz = 0.0; // Rotation
float sx = 1.0, sy = 1.0, sz = 1.0; // Scaling
float shearX = 0.0, shearY = 0.0; // Shearing
bool reflectX = false, reflectY = false, reflectZ = false; // Reflection

// Object selection
int currentObject = 0; // 0: Cube, 1: Pyramid

// Camera parameters
float cameraAngle = 45.0f;

void drawCube() {
    glBegin(GL_QUADS);
    
    // Front face (z = 1)
    glColor3f(1.0, 0.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);
    glColor3f(0.0, 1.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(1.0, 1.0, 1.0);
    glColor3f(1.0, 1.0, 0.0); glVertex3f(-1.0, 1.0, 1.0);

    // Back face (z = -1)
    glColor3f(1.0, 0.0, 1.0); glVertex3f(1.0, -1.0, -1.0);
    glColor3f(0.0, 1.0, 1.0); glVertex3f(-1.0, -1.0, -1.0);
    glColor3f(1.0, 1.0, 1.0); glVertex3f(-1.0, 1.0, -1.0);
    glColor3f(0.0, 0.0, 0.0); glVertex3f(1.0, 1.0, -1.0);

    // Top face (y = 1)
    glColor3f(1.0, 0.5, 0.0); glVertex3f(-1.0, 1.0, 1.0);
    glColor3f(0.0, 1.0, 0.5); glVertex3f(1.0, 1.0, 1.0);
    glColor3f(0.5, 0.0, 1.0); glVertex3f(1.0, 1.0, -1.0);
    glColor3f(1.0, 0.0, 0.5); glVertex3f(-1.0, 1.0, -1.0);

    // Bottom face (y = -1)
    glColor3f(0.5, 0.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);
    glColor3f(0.0, 0.5, 0.0); glVertex3f(1.0, -1.0, 1.0);
    glColor3f(0.0, 0.0, 0.5); glVertex3f(1.0, -1.0, -1.0);
    glColor3f(0.5, 0.5, 0.0); glVertex3f(-1.0, -1.0, -1.0);

    // Left face (x = -1)
    glColor3f(0.0, 0.5, 1.0); glVertex3f(-1.0, -1.0, 1.0);
    glColor3f(1.0, 0.5, 0.0); glVertex3f(-1.0, 1.0, 1.0);
    glColor3f(0.5, 0.0, 1.0); glVertex3f(-1.0, 1.0, -1.0);
    glColor3f(0.0, 1.0, 0.5); glVertex3f(-1.0, -1.0, -1.0);

    // Right face (x = 1)
    glColor3f(0.5, 1.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
    glColor3f(1.0, 0.0, 0.5); glVertex3f(1.0, 1.0, 1.0);
    glColor3f(0.0, 0.5, 0.5); glVertex3f(1.0, 1.0, -1.0);
    glColor3f(0.5, 0.0, 1.0); glVertex3f(1.0, -1.0, -1.0);

    glEnd();
}

void drawPyramid() {
    glBegin(GL_TRIANGLES);
    // Base
    glColor3f(1.0, 0.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);
    glColor3f(0.0, 1.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
    glEnd();
}

void applyTransformations() {
    glTranslatef(tx, ty, tz);
    glRotatef(angle, rx, ry, rz);
    glScalef(sx, sy, sz);

    GLfloat shearMatrix[16] = {
        1.0, shearX, 0.0, 0.0,
        shearY, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    };
    glMultMatrixf(shearMatrix);

    GLfloat reflectMatrix[16] = {
        reflectX ? -1.0f : 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, reflectY ? -1.0f : 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, reflectZ ? -1.0f : 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    glMultMatrixf(reflectMatrix);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(5.0 * cos(cameraAngle * M_PI / 180.0), 5.0, 5.0 * sin(cameraAngle * M_PI / 180.0),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    applyTransformations();

    if (currentObject == 0) drawCube();
    else drawPyramid();

    // Coordinate axes
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); // X
    glVertex3f(0.0, 0.0, 0.0); glVertex3f(2.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0); // Y
    glVertex3f(0.0, 0.0, 0.0); glVertex3f(0.0, 2.0, 0.0);
    glColor3f(0.0, 0.0, 1.0); // Z
    glVertex3f(0.0, 0.0, 0.0); glVertex3f(0.0, 0.0, 2.0);
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w/h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 't': tx += 0.1; break;
        case 'T': tx -= 0.1; break;
        case 'r': angle += 5.0; break;
        case 's': sx += 0.1; sy += 0.1; sz += 0.1; break;
        case 'S': sx = fmax(0.1, sx-0.1); sy = fmax(0.1, sy-0.1); sz = fmax(0.1, sz-0.1); break;
        case 'h': shearX += 0.1; break;
        case 'H': shearY += 0.1; break;
        case 'x': reflectX = !reflectX; break;
        case 'y': reflectY = !reflectY; break;
        case 'z': reflectZ = !reflectZ; break;
        case 'o': currentObject = (currentObject+1)%2; break;
        case 'a': cameraAngle += 5.0; break;
        case 'd': cameraAngle -= 5.0; break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Transformations");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}