#define WIN32_LEAN_AND_MEAN
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <windows.h>

#pragma warning(disable : 4305 4244) /* disable double to float warning */

#define PI     3.1415926
#define Z_NEAR 0.5
#define Z_FAR  100.0

/* Parameter of cube */
#define TEX_HEIGHT 64
#define TEX_WIDTH  64
#define CUBE_NUM   3
#define CUBE_LONG  2.0

/* Parameter of logo */
#define WIDTH  2.5                       /* Size of square */
#define RADIUS 5.0                       /* Radius of logo */
#define SLICE  500                       /* Number of slices */
#define VISION 10.0                      /* Size of visual field */
#define DIAG   (sqrt(2.0) * WIDTH / 2.0) /* Half diagonal size of square */

struct Xyzi {
    int x, y, z;
};
struct Xyzf {
    GLfloat x, y, z;
};
struct Polar {
    GLfloat longitude, latitude, altitude;
};

#define RAD(x) ((x)*PI / 180)

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

#define POLAR2XYZ(po, xyz)                                                                                             \
    do {                                                                                                               \
        (xyz).x = (po).altitude * cos(RAD((po).latitude)) * sin(RAD((po).longitude));                                  \
        (xyz).y = (po).altitude * sin(RAD((po).latitude));                                                             \
        (xyz).z = (po).altitude * cos(RAD((po).latitude)) * cos(RAD((po).longitude));                                  \
    } while (0)

/* Window */
static int g_width;
static int g_height;

/* Diplay list */
static GLuint g_list0;
static GLuint g_list1;

/* Texture */
static GLuint g_tex;
static GLubyte g_texImage[TEX_HEIGHT][TEX_WIDTH][4];

/* Control */
static int g_rotate = 0;
static int g_isLogo = 0;
static struct Xyzf g_shift = {1E-6, 0.0, 0.0};
static struct Xyzi g_start = {0, 0, 0};

/* Camera position control */
static struct Xyzi g_move = {0, 0, 0};

/*
 * To draw a cube
 */

static void makeTexImage()
{
    int i, j;
    GLubyte c;
    for (i = 0; i < TEX_HEIGHT; i++) {
        for (j = 0; j < TEX_WIDTH; j++) {
            c = (i ^ j) & 0x10 ? 0xFF : 0xAA;
            g_texImage[i][j][0] = c;
            g_texImage[i][j][1] = c;
            g_texImage[i][j][2] = c;
            g_texImage[i][j][3] = 0xFF;
        }
    }
}

static void glInitCube()
{
    glEnable(GL_FOG);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glCullFace(GL_BACK);
    glShadeModel(GL_FLAT);
    /* Set projection */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, (GLfloat)g_width / (GLfloat)g_height, Z_NEAR, Z_FAR);
}

static void glDrawSquare(GLfloat r, GLfloat g, GLfloat b)
{
    static GLfloat vData[] = {
        -CUBE_LONG / 2.0,
        -CUBE_LONG / 2.0,
        0,
        +CUBE_LONG / 2.0,
        -CUBE_LONG / 2.0,
        0,
        +CUBE_LONG / 2.0,
        +CUBE_LONG / 2.0,
        0,
        -CUBE_LONG / 2.0,
        +CUBE_LONG / 2.0,
        0,
    };
    static GLint pData[] = {0, 1, 2, 3};
    static GLfloat texSEq[] = {1.0, 0.0, 0.0, 0.0};
    static GLfloat texTEq[] = {0.0, 1.0, 0.0, 0.0};
    glVertexPointer(3, GL_FLOAT, 0, vData);
    glColor4f(r, g, b, 1.0);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, pData);
    glTexGenfv(GL_S, GL_OBJECT_PLANE, texSEq);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, texTEq);
}

static void glDrawCube(GLfloat x, GLfloat y, GLfloat z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    /* Front plane */
    glPushMatrix();
    glTranslatef(0.0, 0.0, CUBE_LONG / 2.0);
    glDrawSquare(1.0, 1.0, 1.0);
    glPopMatrix();
    /* Back plane */
    glPushMatrix();
    glTranslatef(0.0, 0.0, -CUBE_LONG / 2.0);
    glRotatef(180.0, 1.0, 0.0, 0.0);
    glDrawSquare(1.0, 1.0, 0.0);
    glPopMatrix();
    /* Left plane */
    glPushMatrix();
    glTranslatef(-CUBE_LONG / 2.0, 0.0, 0.0);
    glRotatef(-90.0, 0.0, 1.0, 0.0);
    glDrawSquare(1.0, 0.0, 0.0);
    glPopMatrix();
    /* Right plane */
    glPushMatrix();
    glTranslatef(CUBE_LONG / 2.0, 0.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glDrawSquare(1.0, 0.5, 0.0);
    glPopMatrix();
    /* Top plane */
    glPushMatrix();
    glTranslatef(0.0, CUBE_LONG / 2.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glDrawSquare(0.0, 1.0, 0.0);
    glPopMatrix();
    /* Bottom plane */
    glPushMatrix();
    glTranslatef(0.0, -CUBE_LONG / 2.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glDrawSquare(0.0, 0.0, 1.0);
    glPopMatrix();
    /* Restore matrix */
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
}

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
    static GLfloat lightModelAmbient[] = {0.2, 0.2, 0.2, 1.0};
    static GLfloat light0Ambient[] = {0.0, 0.0, 0.0, 1.0};
    static GLfloat light0Diffuse[] = {1.0, 1.0, 1.0, 1.0};
    static GLfloat light1Ambient[] = {0.0, 0.0, 0.0, 1.0};
    static GLfloat light1Diffuse[] = {0.3, 0.3, 0.3, 1.0};
    static GLfloat fogColor[] = {0.1, 0.1, 0.1, 1.0};
    int i, j, k;
    g_width = w;
    g_height = h;
    /* Set fog */
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 0.1);
    glHint(GL_FOG_HINT, GL_DONT_CARE);
    glFogf(GL_FOG_START, Z_NEAR);
    glFogf(GL_FOG_END, Z_FAR);
    /* Set lighting */
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightModelAmbient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diffuse);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    /* Set texturing */
    makeTexImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &g_tex);
    glBindTexture(GL_TEXTURE_2D, g_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEX_WIDTH, TEX_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, g_texImage);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glEnable(GL_TEXTURE_GEN_S);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glEnable(GL_TEXTURE_GEN_T);
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
    /* Set diplay list 0 (for cube) */
    g_list0 = glGenLists(1);
    glNewList(g_list0, GL_COMPILE);
    for (i = 0; i < CUBE_NUM; i++) {
        for (j = 0; j < CUBE_NUM; j++) {
            for (k = 0; k < CUBE_NUM; k++) {
                if (i == 0 || i == CUBE_NUM - 1 || j == 0 || j == CUBE_NUM - 1 || k == 0 || k == CUBE_NUM - 1) {
                    glDrawCube(((GLfloat)i - (GLfloat)(CUBE_NUM - 1) / 2.0) * (CUBE_LONG + 0.1),
                               ((GLfloat)j - (GLfloat)(CUBE_NUM - 1) / 2.0) * (CUBE_LONG + 0.1),
                               ((GLfloat)k - (GLfloat)(CUBE_NUM - 1) / 2.0) * (CUBE_LONG + 0.1));
                }
            }
        }
    }
    glEndList();
    /* Set diplay list 1 (for logo) */
    g_list1 = glGenLists(1);
    glNewList(g_list1, GL_COMPILE);
    glDrawLogo();
    glEndList();
    if (g_isLogo) {
        glInitLogo();
    } else {
        glInitCube();
    }
}

void glDraw()
{
    static struct Polar cameraP = {0.0, 0.0, 20.0};
    static GLfloat light0Pos[] = {0.0, 10.0, 10.0, 1.0};
    static GLfloat light1Pos[] = {10.0, 10.0, 0.0, 1.0};
    static GLfloat angle = 0.0;
    struct Xyzf camera;
    /* Clear background */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Set model view matrix */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    LIMIT_MOVE(g_move.x, cameraP.longitude, 0.0, 359.0, 359.0, 0.0);
    LIMIT_MOVE(g_move.y, cameraP.latitude, -90.0, -90.0, 90.0, 90.0);
    LIMIT_MOVE(g_move.z, cameraP.altitude, Z_NEAR + 10.0, Z_NEAR + 10.0, Z_FAR / 2 + 10.0, Z_FAR / 2 + 10.0);
    POLAR2XYZ(cameraP, camera);
    gluLookAt(camera.x, camera.y, camera.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);
    LIMIT_MOVE(g_rotate, angle, 0.0, 359.0, 359.0, 0.0);
    glRotatef(angle, -g_shift.y, g_shift.x, 1E-6);
    glTranslatef(g_shift.x, g_shift.y, g_shift.z);
    glRotatef(angle, 0.0, 0.0, 1.0);
    if (g_isLogo) {
        glCallList(g_list1);
    } else {
        glCallList(g_list0);
    }
    glFlush();
}

void switchObject()
{
    if (g_isLogo) {
        g_isLogo = 0;
        glInitCube();
    } else {
        g_isLogo = 1;
        glInitLogo();
    }
}

void switchRotate()
{
    g_rotate = !g_rotate;
}

void zoomIn()
{
    g_move.z = 1;
}

void zoomOut()
{
    g_move.z = -1;
}

void zoomStop()
{
    g_move.z = 0;
}

void shiftStart(int x, int y)
{
    g_start.x = x;
    g_start.y = y;
}

void shiftOn(int x, int y)
{
    g_shift.x += (float)(x - g_start.x) / (float)g_width;
    g_shift.y += (float)(g_start.y - y) / (float)g_height;
    g_start.x = x;
    g_start.y = y;
}

void rotateView(int x, int y)
{
    if (x < 5) {
        g_move.x = -1;
    } else if (x > g_width - 5) {
        g_move.x = 1;
    } else {
        g_move.x = 0;
    }
    if (y < 5) {
        g_move.y = 1;
    } else if (y > g_height - 5) {
        g_move.y = -1;
    } else {
        g_move.y = 0;
    }
}
