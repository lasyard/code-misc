#define WIN32_LEAN_AND_MEAN
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <windows.h>

#pragma warning(disable : 4305 4244) /* disable double to float warning */

#define PI 3.1415926

/* Parameter of logo */
#define WIDTH  2.5                       /* Size of square */
#define RADIUS 5.0                       /* Radius of logo */
#define SLICE  500                       /* Number of slices */
#define VISION 10.0                      /* Size of visual field */
#define DIAG   (sqrt(2.0) * WIDTH / 2.0) /* Half diagonal size of square */

#define LIMIT_MOVE(m, var, negLimit, negNew, posLimit, posNew)                                                         \
    do {                                                                                                               \
        if (m) {                                                                                                       \
            (var) += (GLfloat)(m);                                                                                     \
            if ((var) < (negLimit)) {                                                                                  \
                (var) = (negNew);                                                                                      \
            } else if ((var) > (posLimit)) {                                                                           \
                (var) = (posNew);                                                                                      \
            }                                                                                                          \
        }                                                                                                              \
    } while (0)

/* Window */
static int g_width;
static int g_height;

/* Diplay list */
static GLuint g_list1;

/* Spinning Speed */
static int g_speed = 1;

/*
 * To draw a logo
 */

static void glInitLogo()
{
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glCullFace(GL_FRONT);
    glShadeModel(GL_SMOOTH);
    /* Set projection */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-VISION * (GLfloat)g_width / (GLfloat)g_height,
            VISION * (GLfloat)g_width / (GLfloat)g_height,
            -VISION,
            VISION,
            -100,
            100);
}

static void vertexPair(float theta, float phi)
{
    glColor4f((1.0 + sin(theta / 4.0)) / 2.0,
              (1.0 + sin(theta / 4.0 + 2.0 * PI / 3.0)) / 2.0,
              (1.0 + sin(theta / 4.0 + 4.0 * PI / 3.0)) / 2.0,
              1.0);
    glVertex3f((RADIUS + DIAG * cos(phi + PI / 4.0)) * cos(theta),
               (RADIUS + DIAG * cos(phi + PI / 4.0)) * sin(theta),
               DIAG * sin(phi + PI / 4.0));
    glVertex3f((RADIUS + DIAG * cos(phi + 3.0 * PI / 4.0)) * cos(theta),
               (RADIUS + DIAG * cos(phi + 3.0 * PI / 4.0)) * sin(theta),
               DIAG * sin(phi + 3.0 * PI / 4.0));
}

static void glDrawLogo()
{
    int i;
    float theta, phi;
    glBegin(GL_QUAD_STRIP);
    phi = 0.0;
    for (i = 0; i < 4 * SLICE; i++) {
        theta = (float)i * 2.0 * PI / (float)SLICE + PI / 6.0;
        phi = (float)i * 1.5 * PI / (float)SLICE;
        vertexPair(theta, phi);
    }
    vertexPair(PI / 6.0, 0.0);
    glEnd();
}

void glInit(int w, int h)
{
    g_width = w;
    g_height = h;
    /* Set clear color and depth */
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepth(1.0);
    /* Enable depth test */
    glEnable(GL_DEPTH_TEST);
    /* Set viewport */
    glViewport(0, 0, (GLint)w, (GLint)h);
    /* Set draw properties */
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    /* Enable vertex array */
    glEnableClientState(GL_VERTEX_ARRAY);
    /* Set diplay list 1 (for logo) */
    g_list1 = glGenLists(1);
    glNewList(g_list1, GL_COMPILE);
    glDrawLogo();
    glEndList();
    glInitLogo();
}

void glDraw()
{
    static GLfloat angle = 0.0;
    /* Clear background */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Set model view matrix */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    LIMIT_MOVE(g_speed, angle, 0.0, 359.0, 359.0, 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glCallList(g_list1);
    glFlush();
}

void setSpinSpeed(int v)
{
    g_speed = v;
}
