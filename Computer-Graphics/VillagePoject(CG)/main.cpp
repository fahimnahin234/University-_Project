#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include<cstdio>
//cloud
GLfloat cloudPos = 0.0f;
GLfloat cloudPos2 = 0.0f;
GLfloat cloudSpeed = 0.35f;
//cart
GLfloat cartPos = 0.0f;
GLfloat cartSpeed = 12.5f;
//persons
GLfloat p1Pos = 0.0f, p1Speed = 0.15f;
GLfloat p2Pos = 0.0f, p2Speed = 0.20f;
GLfloat p3Pos = 0.0f, p3Speed = -0.18f;
GLfloat p4Pos = 0.0f, p4Speed = -0.12f;
GLfloat p5Pos = 0.0f, p5Speed = -0.22f;
GLfloat wheelRotation = 0.0f;
// Sun / Moon
bool isDay = true;
int dayTimer = 0;
bool paused = false;
bool isMuted = false;
bool stallLightOn = true;
#define PI 3.14159265358979323846
void renderBitmapString(float x, float y, float z, void *font, char *string)
{
    char *c;
    glRasterPos3f(x, y, z);

    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}
void SpecialInput(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            cloudSpeed += 0.1f;
            break;

        case GLUT_KEY_DOWN:
            cloudSpeed -= 0.1f;
            break;

        case GLUT_KEY_LEFT:
            cloudSpeed = -0.35f;
            break;

        case GLUT_KEY_RIGHT:
            cloudSpeed = 0.35f;
            break;
    }

    glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'a':
        case 'A':
            cartSpeed -= 1.0f;
            break;
        case 'd':
        case 'D':
            cartSpeed = 1.0f;
            break;
        case 'w':
        case 'W':
            cartSpeed += 0.10f;
            break;
        case 's':
        case 'S':
            cartSpeed -= 0.10f;
            break;
    }
// Break / Resume
    if(key == ' ')
    {
        paused = !paused;
    }
    // Manual Day / Night
    if(key == 'n' || key == 'N')
    {
        isDay = !isDay;
        dayTimer = 0;
    }
   // Audio Mute / Unmute
if(key == 'm' || key == 'M')
{
    isMuted = !isMuted;

    if(isMuted)
        PlaySound(NULL, 0, 0);   // Mute
    else
        PlaySound(TEXT("freesound_community-street-market-67330.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); // Unmute
}
// Stall Light ON / OFF
if(key == 'l' || key == 'L')
{
    stallLightOn = !stallLightOn;
}



    glutPostRedisplay();
}
void update(int value)
{
  // cloud
    cloudPos += cloudSpeed;
    cloudPos2 += cloudSpeed;
    if(cloudPos > 60.0f)
        cloudPos = -60.0f;
    if(cloudPos < -60.0f)
        cloudPos = 60.0f;
    if(cloudPos2 > 60.0f)
        cloudPos2 = -60.0f;
    if(cloudPos2 < -60.0f)
        cloudPos2 = 60.0f;
   if(!paused)
{
    cartPos += cartSpeed * 0.04f;
    wheelRotation -= cartSpeed * 8.0f;
    if(cartPos > 60.0f)
        cartPos = -60.0f;
    if(cartPos < -60.0f)
        cartPos = 60.0f;
}
        //day/night
if(!paused)
    {
        // Automatic Day / Night
        dayTimer++;

        if(dayTimer > 100)
        {
            isDay = !isDay;
            dayTimer = 0;
        }
    }
    //persons
    p1Pos += p1Speed;
    if(p1Pos > 80.0f)
        p1Pos = -80.0f;
   p2Pos += p2Speed;
if(p2Pos > 55.0f)
    p2Pos = -55.0f;
    p3Pos += p3Speed;
    if(p3Pos < -60.0f)
        p3Pos = 60.0f;
    p4Pos += p4Speed;
    if(p4Pos < -60.0f)
        p4Pos = 60.0f;
    p5Pos += p5Speed;
    if(p5Pos < -60.0f)
        p5Pos = 60.0f;
    glutPostRedisplay();
    glutTimerFunc(100, update, 0);
}
void display()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    int triangleAmount = 100;
    GLfloat twicePi = 2.0f * PI;
    // Sky
    if(isDay)
        glColor3f(0.13f,0.72f,0.92f);
    else
        glColor3f(0.03f,0.05f,0.15f);
    glBegin(GL_QUADS);
    glVertex2f(-50.0f,10.0f);
    glVertex2f(50.0f,10.0f);
    glVertex2f(50.0f,50.0f);
    glVertex2f(-50.0f,50.0f);
    glEnd();
    // Sun / Moon
    GLfloat sunx = 32.0f;
    GLfloat suny = 33.0f;
    GLfloat sunr = 5.0f;
    if(isDay)
        glColor3f(1.0f,0.75f,0.15f);
    else
        glColor3f(0.90f,0.90f,0.85f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(sunx,suny);
    for(int i=0;i<=triangleAmount;i++)
    {
        glVertex2f(
            sunx + sunr*cos(i*twicePi/triangleAmount),
            suny + sunr*sin(i*twicePi/triangleAmount)
        );
    }
    glEnd();
    // Ground
    if(isDay)
{
    glColor3f(0.62f,0.66f,0.28f);
}
else
{
    glColor3f(0.12f,0.18f,0.08f);
}
    glBegin(GL_QUADS);
    glVertex2f(-50.0f,-50.0f);
    glVertex2f(50.0f,-50.0f);
    glVertex2f(50.0f,10.0f);
    glVertex2f(-50.0f,10.0f);
    glEnd();
    // Cloud 1
    glPushMatrix();
    glTranslatef(cloudPos,0.0f,0.0f);
    if(isDay)
{
    glColor3f(1.0f,1.0f,1.0f);
}
else
{
    glColor3f(0.25f,0.28f,0.35f);
}
    GLfloat cx1=-37.5f,cy1=42.5f,cr1=2.5f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx1,cy1);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            cx1+cr1*cos(i*twicePi/triangleAmount),
            cy1+cr1*sin(i*twicePi/triangleAmount)
        );
    glEnd();
    GLfloat cx2=-34.0f,cy2=43.5f,cr2=3.0f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx2,cy2);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            cx2+cr2*cos(i*twicePi/triangleAmount),
            cy2+cr2*sin(i*twicePi/triangleAmount)
        );
    glEnd();
    GLfloat cx3=-30.0f,cy3=42.5f,cr3=2.5f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx3,cy3);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            cx3+cr3*cos(i*twicePi/triangleAmount),
            cy3+cr3*sin(i*twicePi/triangleAmount)
        );
    glEnd();
    glPopMatrix();
    // Cloud 2
    glPushMatrix();
    glTranslatef(cloudPos2,0.0f,0.0f);
    if(isDay)
{
    glColor3f(1.0f,1.0f,1.0f);
}
else
{
    glColor3f(0.25f,0.28f,0.35f);
}
    GLfloat cx4=27.5f,cy4=45.0f,cr4=2.5f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx4,cy4);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            cx4+cr4*cos(i*twicePi/triangleAmount),
            cy4+cr4*sin(i*twicePi/triangleAmount)
        );
    glEnd();
    GLfloat cx5=31.5f,cy5=46.0f,cr5=3.0f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx5,cy5);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            cx5+cr5*cos(i*twicePi/triangleAmount),
            cy5+cr5*sin(i*twicePi/triangleAmount)
        );
    glEnd();
    GLfloat cx6=35.5f,cy6=45.0f,cr6=2.5f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx6,cy6);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            cx6+cr6*cos(i*twicePi/triangleAmount),
            cy6+cr6*sin(i*twicePi/triangleAmount)
        );
    glEnd();
    glPopMatrix();
    // Mountains
    glColor3f(0.38f, 0.45f, 0.30f);  // normal
    glBegin(GL_TRIANGLES);
    glVertex2f(-34.0f,2.5f);
    glVertex2f(-7.0f,2.5f);
    glVertex2f(-20.5f,38.0f);
    glEnd();
    glColor3f(0.52f, 0.60f, 0.36f);  // sunlight
    glBegin(GL_TRIANGLES);
    glVertex2f(-20.0f,2.5f);
    glVertex2f(20.0f,2.5f);
    glVertex2f(0.0f,42.0f);
    glEnd();
    glColor3f(0.22f, 0.30f, 0.20f);  // shadow
    glBegin(GL_TRIANGLES);
    glVertex2f(1.0f,2.5f);
    glVertex2f(38.0f,2.5f);
    glVertex2f(19.5f,38.0f);
    glEnd();
    // Road
    if(isDay)
{
    glColor3f(0.86f,0.70f,0.45f);
}
else
{
    glColor3f(0.08f,0.08f,0.08f);
}
    glBegin(GL_QUADS);
    glVertex2f(-50.0f,-8.0f);
    glVertex2f(50.0f,-8.0f);
    glVertex2f(50.0f,1.0f);
    glVertex2f(-50.0f,1.0f);
    glEnd();
    // Tree line
   glColor3f(0.25f,0.42f,0.22f);
    glBegin(GL_POLYGON);
    glVertex2f(-50.0f,1.0f);
    glVertex2f(50.0f,1.0f);
    glVertex2f(50.0f,8.0f);
    glVertex2f(45.0f,16.0f);
    glVertex2f(40.0f,9.0f);
    glVertex2f(35.0f,15.0f);
    glVertex2f(30.0f,8.5f);
    glVertex2f(25.0f,17.0f);
    glVertex2f(20.0f,7.5f);
    glVertex2f(15.0f,14.0f);
    glVertex2f(10.0f,9.5f);
    glVertex2f(5.0f,16.5f);
    glVertex2f(0.0f,8.0f);
    glVertex2f(-5.0f,15.0f);
    glVertex2f(-10.0f,8.5f);
    glVertex2f(-15.0f,17.0f);
    glVertex2f(-20.0f,7.5f);
    glVertex2f(-25.0f,14.0f);
    glVertex2f(-30.0f,9.5f);
    glVertex2f(-35.0f,16.0f);
    glVertex2f(-40.0f,8.0f);
    glVertex2f(-45.0f,15.0f);
    glVertex2f(-50.0f,8.5f);
    glEnd();
// Tree 1
if(isDay)
{
    glColor3f(0.42f,0.26f,0.14f);
}
else
{
    glColor3f(0.16f,0.10f,0.06f);
}
glBegin(GL_QUADS);
glVertex2f(-37.0f,1.0f);
glVertex2f(-34.5f,1.0f);
glVertex2f(-34.5f,14.0f);
glVertex2f(-37.0f,14.0f);
glEnd();
// Tree 1 - Triangle Leaves
if(isDay)
{
    glColor3f(0.1f,0.5f,0.1f);
}
else
{
    glColor3f(0.03f,0.15f,0.04f);
}
glBegin(GL_TRIANGLES);
// Bottom leaf - wide
glVertex2f(-35.75f,14.0f);
glVertex2f(-45.0f,14.0f);
glVertex2f(-35.75f,27.0f);
glVertex2f(-35.75f,14.0f);
glVertex2f(-26.5f,14.0f);
glVertex2f(-35.75f,27.0f);
// Middle leaf
glVertex2f(-35.75f,20.0f);
glVertex2f(-42.5f,20.0f);
glVertex2f(-35.75f,32.0f);
glVertex2f(-35.75f,20.0f);
glVertex2f(-29.0f,20.0f);
glVertex2f(-35.75f,32.0f);
// Top leaf - narrow
glVertex2f(-35.75f,26.0f);
glVertex2f(-40.0f,26.0f);
glVertex2f(-35.75f,37.0f);
glVertex2f(-35.75f,26.0f);
glVertex2f(-31.5f,26.0f);
glVertex2f(-35.75f,37.0f);
glEnd();
// Tree 2
if(isDay)
{
    glColor3f(0.42f,0.26f,0.14f);
}
else
{
    glColor3f(0.16f,0.10f,0.06f);
}
glBegin(GL_QUADS);
glVertex2f(-1.5f,1.0f);
glVertex2f(0.5f,1.0f);
glVertex2f(0.5f,12.0f);
glVertex2f(-1.5f,12.0f);
glEnd();
// Tree 2 - Triangle Leaves
if(isDay)
{
    glColor3f(0.1f,0.5f,0.1f);
}
else
{
    glColor3f(0.03f,0.15f,0.04f);
}
glBegin(GL_TRIANGLES);
// Bottom - wide
glVertex2f(-0.5f,12.0f);
glVertex2f(-10.0f,12.0f);
glVertex2f(-0.5f,25.0f);
glVertex2f(-0.5f,12.0f);
glVertex2f(9.0f,12.0f);
glVertex2f(-0.5f,25.0f);
// Middle
glVertex2f(-0.5f,18.0f);
glVertex2f(-7.5f,18.0f);
glVertex2f(-0.5f,30.0f);
glVertex2f(-0.5f,18.0f);
glVertex2f(6.5f,18.0f);
glVertex2f(-0.5f,30.0f);
// Top - narrow
glVertex2f(-0.5f,24.0f);
glVertex2f(-4.5f,24.0f);
glVertex2f(-0.5f,35.0f);
glVertex2f(-0.5f,24.0f);
glVertex2f(3.5f,24.0f);
glVertex2f(-0.5f,35.0f);
glEnd();
// Tree 3
if(isDay)
{
    glColor3f(0.42f,0.26f,0.14f);
}
else
{
    glColor3f(0.16f,0.10f,0.06f);
}
glBegin(GL_QUADS);
glVertex2f(18.5f,1.0f);
glVertex2f(20.5f,1.0f);
glVertex2f(20.5f,12.0f);
glVertex2f(18.5f,12.0f);
glEnd();
// Tree 3 - Triangle Leaves
if(isDay)
{
    glColor3f(0.1f,0.5f,0.1f);
}
else
{
    glColor3f(0.03f,0.15f,0.04f);
}
glBegin(GL_TRIANGLES);
// Bottom - wide
glVertex2f(19.5f,12.0f);
glVertex2f(12.0f,12.0f);
glVertex2f(19.5f,24.0f);
glVertex2f(19.5f,12.0f);
glVertex2f(27.0f,12.0f);
glVertex2f(19.5f,24.0f);
// Middle
glVertex2f(19.5f,17.0f);
glVertex2f(14.0f,17.0f);
glVertex2f(19.5f,28.0f);
glVertex2f(19.5f,17.0f);
glVertex2f(25.0f,17.0f);
glVertex2f(19.5f,28.0f);
// Top - narrow
glVertex2f(19.5f,22.0f);
glVertex2f(16.5f,22.0f);
glVertex2f(19.5f,33.0f);
glVertex2f(19.5f,22.0f);
glVertex2f(22.5f,22.0f);
glVertex2f(19.5f,33.0f);

glEnd();
    // Path
    if(isDay)
{
    glColor3f(0.86f,0.70f,0.45f);
}
else
{
    glColor3f(0.08f,0.08f,0.08f);
}
    glBegin(GL_QUADS);
    glVertex2f(-20.5f,-50.0f);
    glVertex2f(20.5f,-50.0f);
    glVertex2f(4.0f,1.0f);
    glVertex2f(-4.0f,1.0f);
    glEnd();
    // CART - travels along the road
    glPushMatrix();
    glTranslatef(cartPos,-5.5f,0.0f);
// Left Wheel
glPushMatrix();
glTranslatef(-2.6f,-1.0f,0.0f);
glRotatef(wheelRotation,0.0f,0.0f,1.0f);
glColor3f(0.08f,0.08f,0.08f);
glBegin(GL_TRIANGLE_FAN);
glVertex2f(0.0f,0.0f);
for(int i=0;i<=triangleAmount;i++)
    glVertex2f(1.4f*cos(i*twicePi/triangleAmount),
               1.4f*sin(i*twicePi/triangleAmount));
glEnd();
glColor3f(0.35f,0.22f,0.10f);
glBegin(GL_TRIANGLE_FAN);
glVertex2f(0.0f,0.0f);
for(int i=0;i<=triangleAmount;i++)
    glVertex2f(0.5f*cos(i*twicePi/triangleAmount),
               0.5f*sin(i*twicePi/triangleAmount));
glEnd();
// ---- CROSS PATTERN SPOKES ----
glColor3f(0.9f,0.9f,0.9f);
glLineWidth(2.0f);
glBegin(GL_LINES);
glVertex2f(0.0f,-1.3f);
glVertex2f(0.0f,1.3f);
glVertex2f(-1.3f,0.0f);
glVertex2f(1.3f,0.0f);
glEnd();
glPopMatrix();
   // Right Wheel
glPushMatrix();
glTranslatef(2.6f,-1.0f,0.0f);
glRotatef(wheelRotation,0.0f,0.0f,1.0f);
glColor3f(0.08f,0.08f,0.08f);
glBegin(GL_TRIANGLE_FAN);
glVertex2f(0.0f,0.0f);
for(int i=0;i<=triangleAmount;i++)
    glVertex2f(1.4f*cos(i*twicePi/triangleAmount),
               1.4f*sin(i*twicePi/triangleAmount));
glEnd();
glColor3f(0.35f,0.22f,0.10f);
glBegin(GL_TRIANGLE_FAN);
glVertex2f(0.0f,0.0f);
for(int i=0;i<=triangleAmount;i++)
    glVertex2f(0.5f*cos(i*twicePi/triangleAmount),
               0.5f*sin(i*twicePi/triangleAmount));
glEnd();
// ---- CROSS PATTERN SPOKES ----
glColor3f(0.9f,0.9f,0.9f);
glLineWidth(2.0f);
glBegin(GL_LINES);
glVertex2f(0.0f,-1.3f);
glVertex2f(0.0f,1.3f);
glVertex2f(-1.3f,0.0f);
glVertex2f(1.3f,0.0f);
glEnd();
glPopMatrix();
    // Axle
    glColor3f(0.20f,0.20f,0.20f);
    glBegin(GL_QUADS);
    glVertex2f(-2.6f,-1.25f);
    glVertex2f(2.6f,-1.25f);
    glVertex2f(2.6f,-0.85f);
    glVertex2f(-2.6f,-0.85f);
    glEnd();
    // Cart bed
    glColor3f(0.55f,0.35f,0.16f);
    glBegin(GL_QUADS);
    glVertex2f(-4.0f,0.3f);
    glVertex2f(4.0f,0.3f);
    glVertex2f(3.5f,2.5f);
    glVertex2f(-3.5f,2.5f);
    glEnd();
    // Side rail
    glColor3f(0.40f,0.24f,0.10f);
    glBegin(GL_QUADS);
    glVertex2f(-3.5f,2.5f);
    glVertex2f(3.5f,2.5f);
    glVertex2f(3.5f,2.9f);
    glVertex2f(-3.5f,2.9f);
    glEnd();
    // Plank lines
    glColor3f(0.40f,0.24f,0.10f);
    glBegin(GL_LINES);
    glVertex2f(-2.5f,0.5f); glVertex2f(-2.2f,2.3f);
    glVertex2f(-1.0f,0.5f); glVertex2f(-0.7f,2.3f);
    glVertex2f(0.5f,0.5f);  glVertex2f(0.8f,2.3f);
    glVertex2f(2.0f,0.5f);  glVertex2f(2.3f,2.3f);
    glEnd();
    // Driver - torso
    glColor3f(0.15f,0.45f,0.40f);
    glBegin(GL_QUADS);
    glVertex2f(-1.3f,2.9f);
    glVertex2f(1.1f,2.9f);
    glVertex2f(0.9f,5.5f);
    glVertex2f(-1.1f,5.5f);
    glEnd();
    // Driver - arm holding reins
    glBegin(GL_QUADS);
    glVertex2f(-1.3f,5.0f);
    glVertex2f(-0.9f,5.0f);
    glVertex2f(-3.0f,3.0f);
    glVertex2f(-3.3f,3.0f);
    glEnd();
    // Driver - hand
    glColor3f(0.62f,0.45f,0.32f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-3.15f,3.0f);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(-3.15f+0.35f*cos(i*twicePi/triangleAmount),3.0f+0.35f*sin(i*twicePi/triangleAmount));
    glEnd();
    // Driver - neck
    glColor3f(0.55f,0.40f,0.28f);
    glBegin(GL_QUADS);
    glVertex2f(-0.4f,5.5f);
    glVertex2f(0.4f,5.5f);
    glVertex2f(0.35f,6.1f);
    glVertex2f(-0.35f,6.1f);
    glEnd();
    // Driver - head
    glColor3f(0.62f,0.45f,0.32f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f,7.2f);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(0.0f+1.25f*cos(i*twicePi/triangleAmount),7.2f+1.25f*sin(i*twicePi/triangleAmount));
    glEnd();
    glPopMatrix();
    // PERSON 2 - BLUE SHIRT
glPushMatrix();
glTranslatef(p2Pos,20.0f,0.0f);
    glColor3f(0.10f,0.25f,0.12f);
    glBegin(GL_QUADS);
    glVertex2f(-13.8f,-21.0f);
    glVertex2f(-12.9f,-21.0f);
    glVertex2f(-12.9f,-16.0f);
    glVertex2f(-13.8f,-16.0f);
    glVertex2f(-12.1f,-21.0f);
    glVertex2f(-11.2f,-21.0f);
    glVertex2f(-11.2f,-16.0f);
    glVertex2f(-12.1f,-16.0f);
    glEnd();
    glColor3f(0.05f,0.05f,0.05f);
    glBegin(GL_QUADS);
    glVertex2f(-14.0f,-21.5f);
    glVertex2f(-12.8f,-21.5f);
    glVertex2f(-12.8f,-21.0f);
    glVertex2f(-14.0f,-21.0f);
    glVertex2f(-12.2f,-21.5f);
    glVertex2f(-11.0f,-21.5f);
    glVertex2f(-11.0f,-21.0f);
    glVertex2f(-12.2f,-21.0f);
    glEnd();
    glColor3f(0.15f,0.30f,0.75f);
    glBegin(GL_QUADS);
    glVertex2f(-14.1f,-16.0f);
    glVertex2f(-10.9f,-16.0f);
    glVertex2f(-11.1f,-12.7f);
    glVertex2f(-13.9f,-12.7f);
    glVertex2f(-14.9f,-15.8f);
    glVertex2f(-14.1f,-15.8f);
    glVertex2f(-13.90f,-13.5f);
    glVertex2f(-14.65f,-13.5f);
    glVertex2f(-10.9f,-15.8f);
    glVertex2f(-10.1f,-15.8f);
    glVertex2f(-10.35f,-13.5f);
    glVertex2f(-11.10f,-13.5f);
    glEnd();
    glColor3f(0.62f,0.45f,0.32f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-14.5f,-15.8f);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            -14.5f+0.35f*cos(i*twicePi/triangleAmount),
            -15.8f+0.35f*sin(i*twicePi/triangleAmount)
        );
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-10.5f,-15.8f);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            -10.5f+0.35f*cos(i*twicePi/triangleAmount),
            -15.8f+0.35f*sin(i*twicePi/triangleAmount)
        );
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-13.0f,-12.7f);
    glVertex2f(-12.0f,-12.7f);
    glVertex2f(-12.15f,-11.8f);
    glVertex2f(-12.85f,-11.8f);
    glEnd();
    glColor3f(0.62f,0.45f,0.32f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-12.5f,-10.5f);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            -12.5f+1.25f*cos(i*twicePi/triangleAmount),
            -10.5f+1.25f*sin(i*twicePi/triangleAmount)
        );
    glEnd();
    glPopMatrix();
// PERSON 4 - GREEN SHIRT
glPushMatrix();
glTranslatef(p4Pos,10.0f,0.0f);
glColor3f(0.16f,0.25f,0.12f);
glBegin(GL_QUADS);
glVertex2f(15.2f,-22.0f);
glVertex2f(16.1f,-22.0f);
glVertex2f(16.1f,-17.0f);
glVertex2f(15.2f,-17.0f);
glVertex2f(16.9f,-22.0f);
glVertex2f(17.8f,-22.0f);
glVertex2f(17.8f,-17.0f);
glVertex2f(16.9f,-17.0f);
glEnd();
glColor3f(0.05f,0.05f,0.05f);
glBegin(GL_QUADS);
glVertex2f(15.0f,-22.5f);
glVertex2f(16.2f,-22.5f);
glVertex2f(16.2f,-22.0f);
glVertex2f(15.0f,-22.0f);
glVertex2f(16.8f,-22.5f);
glVertex2f(18.0f,-22.5f);
glVertex2f(18.0f,-22.0f);
glVertex2f(16.8f,-22.0f);
glEnd();
glColor3f(0.15f,0.55f,0.20f);
glBegin(GL_QUADS);
glVertex2f(14.9f,-17.0f);
glVertex2f(18.1f,-17.0f);
glVertex2f(17.9f,-13.7f);
glVertex2f(15.1f,-13.7f);
glVertex2f(14.1f,-16.8f);
glVertex2f(14.9f,-16.8f);
glVertex2f(15.10f,-14.5f);
glVertex2f(14.35f,-14.5f);
glVertex2f(18.1f,-16.8f);
glVertex2f(18.9f,-16.8f);
glVertex2f(18.65f,-14.5f);
glVertex2f(17.90f,-14.5f);
glEnd();
glColor3f(0.62f,0.45f,0.32f);
glBegin(GL_TRIANGLE_FAN);
glVertex2f(14.5f,-16.8f);
for(int i=0;i<=triangleAmount;i++)
    glVertex2f(
        14.5f+0.35f*cos(i*twicePi/triangleAmount),
        -16.8f+0.35f*sin(i*twicePi/triangleAmount)
    );
glEnd();
glBegin(GL_TRIANGLE_FAN);
glVertex2f(18.5f,-16.8f);
for(int i=0;i<=triangleAmount;i++)
    glVertex2f(
        18.5f+0.35f*cos(i*twicePi/triangleAmount),
        -16.8f+0.35f*sin(i*twicePi/triangleAmount)
    );
glEnd();
glBegin(GL_QUADS);
glVertex2f(15.9f,-13.7f);
glVertex2f(16.9f,-13.7f);
glVertex2f(16.75f,-12.8f);
glVertex2f(16.05f,-12.8f);
glEnd();
glColor3f(0.62f,0.45f,0.32f);
glBegin(GL_TRIANGLE_FAN);
glVertex2f(16.5f,-11.5f);
for(int i=0;i<=triangleAmount;i++)
    glVertex2f(
        16.5f+1.25f*cos(i*twicePi/triangleAmount),
        -11.5f+1.25f*sin(i*twicePi/triangleAmount)
    );
glEnd();
glPopMatrix();
    glPopMatrix();
        // Left stall
    glColor3f(0.50f,0.32f,0.18f);
    glBegin(GL_QUADS);
    glVertex2f(-31.0f,-15.0f);
    glVertex2f(-50.0f,-15.0f);
    glVertex2f(-50.0f,2.5f);
    glVertex2f(-31.0f,2.5f);
    glEnd();
    glColor3f(0.15f,0.10f,0.08f);
    glBegin(GL_QUADS);
    glVertex2f(-34.0f,-15.0f);
    glVertex2f(-39.0f,-15.0f);
    glVertex2f(-39.0f,-2.5f);
    glVertex2f(-34.0f,-2.5f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(-43.0f,-15.0f);
    glVertex2f(-48.0f,-15.0f);
    glVertex2f(-48.0f,-2.5f);
    glVertex2f(-43.0f,-2.5f);
    glEnd();
    // Left roof
    glColor3f(0.75f,0.15f,0.10f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-29.0f,2.5f);
    glVertex2f(-52.0f,2.5f);
    glVertex2f(-40.5f,15.0f);
    glEnd();
    // Right stall
    glColor3f(0.50f,0.32f,0.18f);
    glBegin(GL_QUADS);
    glVertex2f(31.0f,-15.0f);
    glVertex2f(50.0f,-15.0f);
    glVertex2f(50.0f,2.5f);
    glVertex2f(31.0f,2.5f);
    glEnd();
    glColor3f(0.15f,0.10f,0.08f);
    glBegin(GL_QUADS);
    glVertex2f(34.0f,-15.0f);
    glVertex2f(39.0f,-15.0f);
    glVertex2f(39.0f,-2.5f);
    glVertex2f(34.0f,-2.5f);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(43.0f,-15.0f);
    glVertex2f(48.0f,-15.0f);
    glVertex2f(48.0f,-2.5f);
    glVertex2f(43.0f,-2.5f);
    glEnd();
    // Right roof
    glColor3f(0.75f,0.15f,0.10f);
    glBegin(GL_TRIANGLES);
    glVertex2f(29.0f,2.5f);
    glVertex2f(52.0f,2.5f);
    glVertex2f(40.5f,15.0f);
    glEnd();
// STALL GATE LIGHT - NIGHT
if(!isDay)
{
    // LEFT STALL - GATE 1 LIGHT
   if(stallLightOn)
{
    glColor3f(1.0f, 1.0f, 0.3f);   // Light ON
}
else
{
    glColor3f(0.15f, 0.15f, 0.15f); // Light OFF
}
    glBegin(GL_QUADS);
    glVertex2f(-34.0f,-15.0f);
    glVertex2f(-39.0f,-15.0f);
    glVertex2f(-39.0f,-2.5f);
    glVertex2f(-34.0f,-2.5f);
    glEnd();
    // LEFT STALL - GATE 2 LIGHT
   if(stallLightOn)
{
    glColor3f(1.0f, 1.0f, 0.3f);   // Light ON
}
else
{
    glColor3f(0.15f, 0.15f, 0.15f); // Light OFF
}
    glBegin(GL_QUADS);
    glVertex2f(-43.0f,-15.0f);
    glVertex2f(-48.0f,-15.0f);
    glVertex2f(-48.0f,-2.5f);
    glVertex2f(-43.0f,-2.5f);
    glEnd();
    // RIGHT STALL - GATE 1 LIGHT
    if(stallLightOn)
{
    glColor3f(1.0f, 1.0f, 0.3f);   // Light ON
}
else
{
    glColor3f(0.15f, 0.15f, 0.15f); // Light OFF
}
    glBegin(GL_QUADS);
    glVertex2f(34.0f,-15.0f);
    glVertex2f(39.0f,-15.0f);
    glVertex2f(39.0f,-2.5f);
    glVertex2f(34.0f,-2.5f);
    glEnd();
    // RIGHT STALL - GATE 2 LIGHT
if(stallLightOn)
{
    glColor3f(1.0f, 1.0f, 0.3f);   // Light ON
}
else
{
    glColor3f(0.15f, 0.15f, 0.15f); // Light OFF
}    glBegin(GL_QUADS);
    glVertex2f(43.0f,-15.0f);
    glVertex2f(48.0f,-15.0f);
    glVertex2f(48.0f,-2.5f);
    glVertex2f(43.0f,-2.5f);
    glEnd();
}
    // LEFT STALL BANNER
glColor3f(0.20f,0.10f,0.05f);
glBegin(GL_QUADS);
glVertex2f(-48.5f,-1.0f);
glVertex2f(-32.5f,-1.0f);
glVertex2f(-32.5f,3.0f);
glVertex2f(-48.5f,3.0f);
glEnd();

glColor3f(1.0f,0.85f,0.20f);
renderBitmapString(
    -46.5f,
    0.2f,
    0.0f,
    GLUT_BITMAP_HELVETICA_18,
    (char*)"   FRUIT STALL"
);
// RIGHT STALL BANNER
glColor3f(0.20f,0.10f,0.05f);
glBegin(GL_QUADS);
glVertex2f(32.5f,-1.0f);
glVertex2f(48.5f,-1.0f);
glVertex2f(48.5f,3.0f);
glVertex2f(32.5f,3.0f);
glEnd();

glColor3f(1.0f,0.85f,0.20f);
renderBitmapString(
    34.5f,
    0.2f,
    0.0f,
    GLUT_BITMAP_HELVETICA_18,
    (char*)"FOOD STALL"
);
   // Palm tree left
if(isDay)
    glColor3f(0.65f,0.40f,0.15f);
else
    glColor3f(0.30f,0.18f,0.07f);
glBegin(GL_QUADS);
glVertex2f(-49.0f,-50.0f);
glVertex2f(-47.0f,-50.0f);
glVertex2f(-44.0f,37.5f);
glVertex2f(-46.0f,37.5f);
glEnd();
if(isDay)
    glColor3f(0.10f,0.50f,0.10f);
else
    glColor3f(0.04f,0.20f,0.05f);
// Leaf - upper right
glBegin(GL_POLYGON);
glVertex2f(-45.0f,37.5f);
glVertex2f(-41.0f,39.0f);
glVertex2f(-36.0f,42.5f);
glVertex2f(-42.0f,38.0f);
glEnd();
// Leaf - upper left
glBegin(GL_POLYGON);
glVertex2f(-45.0f,37.5f);
glVertex2f(-49.0f,39.0f);
glVertex2f(-52.5f,42.5f);
glVertex2f(-48.0f,38.0f);
glEnd();
// Leaf - top
glBegin(GL_POLYGON);
glVertex2f(-45.0f,37.5f);
glVertex2f(-43.0f,41.0f);
glVertex2f(-40.0f,46.0f);
glVertex2f(-44.0f,39.5f);
glEnd();
// Leaf - lower right (cross)
glBegin(GL_POLYGON);
glVertex2f(-45.0f,37.5f);
glVertex2f(-41.0f,36.0f);
glVertex2f(-37.0f,33.0f);
glVertex2f(-42.5f,36.5f);
glEnd();
// Leaf - lower left (cross)
glBegin(GL_POLYGON);
glVertex2f(-45.0f,37.5f);
glVertex2f(-49.0f,36.0f);
glVertex2f(-53.0f,33.0f);
glVertex2f(-47.5f,36.5f);
glEnd();
// Palm tree right
if(isDay)
    glColor3f(0.42f,0.26f,0.14f);
else
    glColor3f(0.20f,0.12f,0.07f);
glBegin(GL_QUADS);
glVertex2f(47.0f,-50.0f);
glVertex2f(49.0f,-50.0f);
glVertex2f(46.0f,37.5f);
glVertex2f(44.0f,37.5f);
glEnd();
if(isDay)
    glColor3f(0.10f,0.50f,0.10f);
else
    glColor3f(0.04f,0.20f,0.05f);
// Leaf - upper left
glBegin(GL_POLYGON);
glVertex2f(45.0f,37.5f);
glVertex2f(41.0f,39.0f);
glVertex2f(36.0f,42.5f);
glVertex2f(42.0f,38.0f);
glEnd();
// Leaf - upper right
glBegin(GL_POLYGON);
glVertex2f(45.0f,37.5f);
glVertex2f(49.0f,39.0f);
glVertex2f(52.5f,42.5f);
glVertex2f(48.0f,38.0f);
glEnd();
// Leaf - top
glBegin(GL_POLYGON);
glVertex2f(45.0f,37.5f);
glVertex2f(43.0f,41.0f);
glVertex2f(40.0f,46.0f);
glVertex2f(44.0f,39.5f);
glEnd();
// Leaf - lower left (cross)
glBegin(GL_POLYGON);
glVertex2f(45.0f,37.5f);
glVertex2f(41.0f,36.0f);
glVertex2f(37.0f,33.0f);
glVertex2f(42.5f,36.5f);
glEnd();
// Leaf - lower right (cross)
glBegin(GL_POLYGON);
glVertex2f(45.0f,37.5f);
glVertex2f(49.0f,36.0f);
glVertex2f(53.0f,33.0f);
glVertex2f(47.5f,36.5f);
glEnd();
    // Left grass
    glColor3f(0.20f,0.55f,0.15f);
    glBegin(GL_POLYGON);
    glVertex2f(-50.0f,-50.0f);
    glVertex2f(-49.0f,-42.0f);
    glVertex2f(-47.5f,-50.0f);
    glVertex2f(-46.5f,-40.0f);
    glVertex2f(-45.0f,-50.0f);
    glVertex2f(-44.0f,-41.5f);
    glVertex2f(-42.5f,-50.0f);
    glVertex2f(-41.5f,-43.0f);
    glVertex2f(-40.0f,-50.0f);
    glEnd();
    // Right grass
    glBegin(GL_POLYGON);
    glVertex2f(40.0f,-50.0f);
    glVertex2f(41.5f,-43.0f);
    glVertex2f(42.5f,-50.0f);
    glVertex2f(44.0f,-41.5f);
    glVertex2f(45.0f,-50.0f);
    glVertex2f(46.5f,-40.0f);
    glVertex2f(47.5f,-50.0f);
    glVertex2f(49.0f,-42.0f);
    glVertex2f(50.0f,-50.0f);
    glEnd();
    // LEFT BIG VEGETABLE BASKET
    GLfloat basketLeftX = -27.5f;
    GLfloat basketLeftY = -42.5f;
    // ---------- Basket Body ----------
    if(isDay)
    glColor3f(0.65f,0.40f,0.15f);
else
    glColor3f(0.30f,0.18f,0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(basketLeftX - 9.0f, basketLeftY + 3.0f);
    glVertex2f(basketLeftX + 9.0f, basketLeftY + 3.0f);
    glVertex2f(basketLeftX + 8.0f, basketLeftY - 4.0f);
    glVertex2f(basketLeftX + 6.0f, basketLeftY - 8.0f);
    glVertex2f(basketLeftX + 3.0f, basketLeftY - 10.0f);
    glVertex2f(basketLeftX - 3.0f, basketLeftY - 10.0f);
    glVertex2f(basketLeftX - 6.0f, basketLeftY - 8.0f);
    glVertex2f(basketLeftX - 8.0f, basketLeftY - 4.0f);
    glEnd();
    // ---------- Basket Top Rim ----------
    glColor3f(0.35f, 0.18f, 0.06f);
    glBegin(GL_POLYGON);
    glVertex2f(basketLeftX - 9.8f, basketLeftY + 3.5f);
    glVertex2f(basketLeftX + 9.8f, basketLeftY + 3.5f);
    glVertex2f(basketLeftX + 9.0f, basketLeftY + 1.0f);
    glVertex2f(basketLeftX - 9.0f, basketLeftY + 1.0f);
    glEnd();
    // ---------- Basket Vertical Lines ----------
    glColor3f(0.30f, 0.15f, 0.05f);
    for(int basketLine = -7; basketLine <= 7; basketLine += 2)
    {
        GLfloat lineX = basketLeftX + basketLine;
        glBegin(GL_QUADS);
        glVertex2f(lineX - 0.3f, basketLeftY + 2.5f);
        glVertex2f(lineX + 0.3f, basketLeftY + 2.5f);
        glVertex2f(lineX + 0.5f, basketLeftY - 8.0f);
        glVertex2f(lineX - 0.5f, basketLeftY - 8.0f);
        glEnd();
    }
    // ---------- Basket Horizontal Lines ----------
    glColor3f(0.35f, 0.18f, 0.06f);
    for(int basketRow = 0; basketRow < 3; basketRow++)
    {
        GLfloat rowY = basketLeftY - 1.0f - basketRow * 3.0f;
        glBegin(GL_LINE_STRIP);
        glVertex2f(basketLeftX - 8.0f, rowY);
        glVertex2f(basketLeftX - 4.0f, rowY - 0.5f);
        glVertex2f(basketLeftX, rowY - 0.7f);
        glVertex2f(basketLeftX + 4.0f, rowY - 0.5f);
        glVertex2f(basketLeftX + 8.0f, rowY);
        glEnd();
    }
    //                    VEGETABLES
    // ---------- Tomato 1 ----------
    GLfloat leftVegX1 = -31.0f;
    GLfloat leftVegY1 = -40.5f;
    GLfloat leftVegR1 = 2.1f;
    glColor3f(0.90f, 0.08f, 0.05f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(leftVegX1, leftVegY1);
    for(int i = 0; i <= triangleAmount; i++)
    {
        GLfloat angle = i * twicePi / triangleAmount;
        glVertex2f(
            leftVegX1 + leftVegR1 * cos(angle),
            leftVegY1 + leftVegR1 * sin(angle)
        );
    }
    glEnd();
    // ---------- Tomato 2 ----------
    GLfloat leftVegX2 = -26.0f;
    GLfloat leftVegY2 = -40.0f;
    GLfloat leftVegR2 = 2.2f;
    glColor3f(0.95f, 0.12f, 0.05f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(leftVegX2, leftVegY2);
    for(int i = 0; i <= triangleAmount; i++)
    {
        GLfloat angle = i * twicePi / triangleAmount;
        glVertex2f(
            leftVegX2 + leftVegR2 * cos(angle),
            leftVegY2 + leftVegR2 * sin(angle)
        );
    }
    glEnd();
    // ---------- Tomato 3 ----------
    GLfloat leftVegX3 = -21.5f;
    GLfloat leftVegY3 = -40.8f;
    GLfloat leftVegR3 = 2.0f;
    glColor3f(0.82f, 0.05f, 0.03f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(leftVegX3, leftVegY3);
    for(int i = 0; i <= triangleAmount; i++)
    {
        GLfloat angle = i * twicePi / triangleAmount;
        glVertex2f(
            leftVegX3 + leftVegR3 * cos(angle),
            leftVegY3 + leftVegR3 * sin(angle)
        );
    }
    glEnd();
    // ---------- Green Vegetable 1 ----------
    GLfloat leftGreenX1 = -33.0f;
    GLfloat leftGreenY1 = -42.0f;
    glColor3f(0.15f, 0.55f, 0.08f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(leftGreenX1, leftGreenY1);
    for(int i = 0; i <= triangleAmount; i++)
    {
        GLfloat angle = i * twicePi / triangleAmount;
        glVertex2f(
            leftGreenX1 + 1.8f * cos(angle),
            leftGreenY1 + 2.2f * sin(angle)
        );
    }
    glEnd();
    // ---------- Green Vegetable 2 ----------
    GLfloat leftGreenX2 = -22.0f;
    GLfloat leftGreenY2 = -42.0f;
    glColor3f(0.20f, 0.65f, 0.10f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(leftGreenX2, leftGreenY2);
    for(int i = 0; i <= triangleAmount; i++)
    {
        GLfloat angle = i * twicePi / triangleAmount;
        glVertex2f(
            leftGreenX2 + 1.8f * cos(angle),
            leftGreenY2 + 2.2f * sin(angle)
        );
    }
    glEnd();
    //                       CARROTS
    // ---------- Carrot 1 ----------
    GLfloat leftCarrotX1 = -28.5f;
    GLfloat leftCarrotY1 = -43.0f;
    glColor3f(1.0f, 0.45f, 0.03f);
    glBegin(GL_TRIANGLES);
    glVertex2f(leftCarrotX1 - 1.1f, leftCarrotY1 + 2.0f);
    glVertex2f(leftCarrotX1 + 1.1f, leftCarrotY1 + 2.0f);
    glVertex2f(leftCarrotX1, leftCarrotY1 - 2.2f);
    glEnd();
    // ---------- Carrot 2 ----------
    GLfloat leftCarrotX2 = -24.5f;
    GLfloat leftCarrotY2 = -43.0f;
    glColor3f(1.0f, 0.50f, 0.04f);
    glBegin(GL_TRIANGLES);
    glVertex2f(leftCarrotX2 - 1.1f, leftCarrotY2 + 2.0f);
    glVertex2f(leftCarrotX2 + 1.1f, leftCarrotY2 + 2.0f);
    glVertex2f(leftCarrotX2, leftCarrotY2 - 2.2f);
    glEnd();
    // ---------- Carrot Leaves ----------
    glColor3f(0.08f, 0.45f, 0.05f);
    glBegin(GL_TRIANGLES);
    // Carrot 1 leaves
    glVertex2f(leftCarrotX1 - 0.5f, leftCarrotY1 + 2.0f);
    glVertex2f(leftCarrotX1, leftCarrotY1 + 3.7f);
    glVertex2f(leftCarrotX1 + 0.5f, leftCarrotY1 + 2.0f);
    // Carrot 2 leaves
    glVertex2f(leftCarrotX2 - 0.5f, leftCarrotY2 + 2.0f);
    glVertex2f(leftCarrotX2, leftCarrotY2 + 3.7f);
    glVertex2f(leftCarrotX2 + 0.5f, leftCarrotY2 + 2.0f);
    glEnd();
    // BIG VEGETABLE BASKET
    GLfloat basketX = 2.5f;
    GLfloat basketY = -46.0f;
    // ---------- Basket Body ----------
    if(isDay)
    glColor3f(0.65f,0.40f,0.15f);
else
    glColor3f(0.30f,0.18f,0.07f);
    glBegin(GL_POLYGON);
    // Top-left
    glVertex2f(basketX - 11.0f, basketY + 3.0f);
    // Top-right
    glVertex2f(basketX + 11.0f, basketY + 3.0f);
    // Right side
    glVertex2f(basketX + 9.5f, basketY - 5.0f);
    glVertex2f(basketX + 7.0f, basketY - 9.0f);
    // Bottom
    glVertex2f(basketX + 3.5f, basketY - 11.0f);
    glVertex2f(basketX - 3.5f, basketY - 11.0f);
    // Left side
    glVertex2f(basketX - 7.0f, basketY - 9.0f);
    glVertex2f(basketX - 9.5f, basketY - 5.0f);
    glEnd();
    // ---------- Basket Top / Rim ----------
    glColor3f(0.38f, 0.20f, 0.07f);
    glBegin(GL_POLYGON);
    glVertex2f(basketX - 12.0f, basketY + 3.5f);
    glVertex2f(basketX + 12.0f, basketY + 3.5f);
    glVertex2f(basketX + 11.0f, basketY + 1.0f);
    glVertex2f(basketX - 11.0f, basketY + 1.0f);
    glEnd();
    // ---------- Basket Vertical Strips ----------
    glColor3f(0.30f, 0.15f, 0.05f);
    for(int k = -8; k <= 8; k += 2)
    {
        GLfloat stripX = basketX + k;
        glBegin(GL_QUADS);
        glVertex2f(stripX - 0.35f, basketY + 2.5f);
        glVertex2f(stripX + 0.35f, basketY + 2.5f);
        glVertex2f(stripX + 0.55f, basketY - 8.5f);
        glVertex2f(stripX - 0.55f, basketY - 8.5f);
        glEnd();
    }
    // ---------- Basket Horizontal Strips ----------
    glColor3f(0.35f, 0.18f, 0.06f);
    for(int j = 0; j < 3; j++)
    {
        GLfloat stripY = basketY - 1.0f - j * 3.0f;
        glBegin(GL_LINE_STRIP);
        glVertex2f(basketX - 10.0f + j * 0.5f, stripY);
        glVertex2f(basketX - 5.0f, stripY - 0.5f);
        glVertex2f(basketX, stripY - 0.7f);
        glVertex2f(basketX + 5.0f, stripY - 0.5f);
        glVertex2f(basketX + 10.0f - j * 0.5f, stripY);
        glEnd();
    }
    //                 VEGETABLES
    // ---------- Tomato Left ----------
    GLfloat vegX1 = -5.0f;
    GLfloat vegY1 = -43.0f;
    GLfloat vegR1 = 2.3f;
    glColor3f(0.90f, 0.08f, 0.05f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(vegX1, vegY1);
    for(int i = 0; i <= triangleAmount; i++)
    {
        GLfloat angle = i * twicePi / triangleAmount;
        glVertex2f(
            vegX1 + vegR1 * cos(angle),
            vegY1 + vegR1 * sin(angle)
        );
    }
    glEnd();
    // ---------- Tomato Center ----------
    GLfloat vegX2 = 1.0f;
    GLfloat vegY2 = -42.0f;
    GLfloat vegR2 = 2.5f;
    glColor3f(0.95f, 0.12f, 0.05f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(vegX2, vegY2);
    for(int i = 0; i <= triangleAmount; i++)
    {
        GLfloat angle = i * twicePi / triangleAmount;
        glVertex2f(
            vegX2 + vegR2 * cos(angle),
            vegY2 + vegR2 * sin(angle)
        );
    }
    glEnd();
    // ---------- Tomato Right ----------
    GLfloat vegX3 = 6.5f;
    GLfloat vegY3 = -43.0f;
    GLfloat vegR3 = 2.2f;
    glColor3f(0.82f, 0.05f, 0.03f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(vegX3, vegY3);
    for(int i = 0; i <= triangleAmount; i++)
    {
        GLfloat angle = i * twicePi / triangleAmount;
        glVertex2f(
            vegX3 + vegR3 * cos(angle),
            vegY3 + vegR3 * sin(angle)
        );
    }
    glEnd();
    //                  GREEN VEGETABLES
    //  Green Vegetable Left
    GLfloat greenX1 = -8.0f;
    GLfloat greenY1 = -45.0f;
    glColor3f(0.15f, 0.55f, 0.08f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(greenX1, greenY1);
    for(int i = 0; i <= triangleAmount; i++)
    {
        GLfloat angle = i * twicePi / triangleAmount;
        glVertex2f(
            greenX1 + 2.0f * cos(angle),
            greenY1 + 2.4f * sin(angle)
        );
    }
    glEnd();
    //  Green Vegetable Right
    GLfloat greenX2 = 9.0f;
    GLfloat greenY2 = -45.0f;
    glColor3f(0.20f, 0.65f, 0.10f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(greenX2, greenY2);
    for(int i = 0; i <= triangleAmount; i++)
    {
        GLfloat angle = i * twicePi / triangleAmount;
        glVertex2f(
            greenX2 + 2.0f * cos(angle),
            greenY2 + 2.4f * sin(angle)
        );
    }
    glEnd();
    //                     CARROTS
    //  Carrot 1
    GLfloat carrotX1 = -2.5f;
    GLfloat carrotY1 = -45.0f;
    glColor3f(1.0f, 0.45f, 0.03f);
    glBegin(GL_TRIANGLES);
    glVertex2f(carrotX1 - 1.2f, carrotY1 + 2.0f);
    glVertex2f(carrotX1 + 1.2f, carrotY1 + 2.0f);
    glVertex2f(carrotX1, carrotY1 - 2.5f);
    glEnd();
    // Carrot 2
    GLfloat carrotX2 = 4.0f;
    GLfloat carrotY2 = -45.0f;
    glColor3f(1.0f, 0.50f, 0.04f);
    glBegin(GL_TRIANGLES);
    glVertex2f(carrotX2 - 1.2f, carrotY2 + 2.0f);
    glVertex2f(carrotX2 + 1.2f, carrotY2 + 2.0f);
    glVertex2f(carrotX2, carrotY2 - 2.5f);
    glEnd();
    // Carrot Leaves
    glColor3f(0.08f, 0.45f, 0.05f);
    glBegin(GL_TRIANGLES);
    // carrot 1 leaves
    glVertex2f(carrotX1 - 0.6f, carrotY1 + 2.0f);
    glVertex2f(carrotX1, carrotY1 + 4.0f);
    glVertex2f(carrotX1 + 0.6f, carrotY1 + 2.0f);
    // carrot 2 leaves
    glVertex2f(carrotX2 - 0.6f, carrotY2 + 2.0f);
    glVertex2f(carrotX2, carrotY2 + 4.0f);
    glVertex2f(carrotX2 + 0.6f, carrotY2 + 2.0f);
    glEnd();
    // PERSON 1 - YELLOW SHIRT
    glPushMatrix();
    glTranslatef(p1Pos,0.0f,0.0f);
    // Legs
    glColor3f(0.10f,0.25f,0.12f);
    glBegin(GL_QUADS);
    glVertex2f(-26.3f,-22.0f);
    glVertex2f(-25.4f,-22.0f);
    glVertex2f(-25.4f,-17.0f);
    glVertex2f(-26.3f,-17.0f);
    glVertex2f(-24.6f,-22.0f);
    glVertex2f(-23.7f,-22.0f);
    glVertex2f(-23.7f,-17.0f);
    glVertex2f(-24.6f,-17.0f);
    glEnd();
    // Feet
    glColor3f(0.05f,0.05f,0.05f);
    glBegin(GL_QUADS);
    glVertex2f(-26.5f,-22.5f);
    glVertex2f(-25.3f,-22.5f);
    glVertex2f(-25.3f,-22.0f);
    glVertex2f(-26.5f,-22.0f);
    glVertex2f(-24.7f,-22.5f);
    glVertex2f(-23.5f,-22.5f);
    glVertex2f(-23.5f,-22.0f);
    glVertex2f(-24.7f,-22.0f);
    glEnd();
    // Shirt
    glColor3f(0.98f,0.80f,0.15f);
    glBegin(GL_QUADS);
    glVertex2f(-26.6f,-17.0f);
    glVertex2f(-23.4f,-17.0f);
    glVertex2f(-23.6f,-13.7f);
    glVertex2f(-26.4f,-13.7f);
    glEnd();
    // Arms
    glBegin(GL_QUADS);
    glVertex2f(-27.4f,-16.8f);
    glVertex2f(-26.6f,-16.8f);
    glVertex2f(-26.40f,-14.5f);
    glVertex2f(-27.15f,-14.5f);
    glVertex2f(-23.4f,-16.8f);
    glVertex2f(-22.6f,-16.8f);
    glVertex2f(-22.85f,-14.5f);
    glVertex2f(-23.60f,-14.5f);
    glEnd();
    // Hands
    glColor3f(0.62f,0.45f,0.32f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-27.0f,-16.8f);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            -27.0f+0.35f*cos(i*twicePi/triangleAmount),
            -16.8f+0.35f*sin(i*twicePi/triangleAmount)
        );
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-23.0f,-16.8f);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            -23.0f+0.35f*cos(i*twicePi/triangleAmount),
            -16.8f+0.35f*sin(i*twicePi/triangleAmount)
        );
    glEnd();
    // Neck
    glColor3f(0.55f,0.40f,0.28f);
    glBegin(GL_QUADS);
    glVertex2f(-25.4f,-13.7f);
    glVertex2f(-24.6f,-13.7f);
    glVertex2f(-24.65f,-12.8f);
    glVertex2f(-25.35f,-12.8f);
    glEnd();
    // Head
    glColor3f(0.62f,0.45f,0.32f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-25.0f,-11.5f);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            -25.0f+1.25f*cos(i*twicePi/triangleAmount),
            -11.5f+1.25f*sin(i*twicePi/triangleAmount)
        );
    glEnd();
    glPopMatrix();
    // PERSON 5 - RED SHIRT
    glPushMatrix();
    glTranslatef(p5Pos,-3.0f,0.0f);
    glColor3f(0.10f,0.25f,0.12f);
    glBegin(GL_QUADS);
    glVertex2f(29.2f,-22.5f);
    glVertex2f(30.1f,-22.5f);
    glVertex2f(30.1f,-17.5f);
    glVertex2f(29.2f,-17.5f);
    glVertex2f(30.9f,-22.5f);
    glVertex2f(31.8f,-22.5f);
    glVertex2f(31.8f,-17.5f);
    glVertex2f(30.9f,-17.5f);
    glEnd();
    glColor3f(0.05f,0.05f,0.05f);
    glBegin(GL_QUADS);
    glVertex2f(29.0f,-23.0f);
    glVertex2f(30.2f,-23.0f);
    glVertex2f(30.2f,-22.5f);
    glVertex2f(29.0f,-22.5f);
    glVertex2f(30.8f,-23.0f);
    glVertex2f(32.0f,-23.0f);
    glVertex2f(32.0f,-22.5f);
    glVertex2f(30.8f,-22.5f);
    glEnd();
    glColor3f(0.85f,0.15f,0.10f);
    glBegin(GL_QUADS);
    glVertex2f(28.9f,-17.5f);
    glVertex2f(32.1f,-17.5f);
    glVertex2f(31.9f,-14.2f);
    glVertex2f(29.1f,-14.2f);
    glVertex2f(28.1f,-17.3f);
    glVertex2f(28.9f,-17.3f);
    glVertex2f(29.10f,-15.0f);
    glVertex2f(28.35f,-15.0f);
    glVertex2f(32.1f,-17.3f);
    glVertex2f(32.9f,-17.3f);
    glVertex2f(32.65f,-15.0f);
    glVertex2f(31.90f,-15.0f);
    glEnd();
    glColor3f(0.62f,0.45f,0.32f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(28.5f,-17.3f);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            28.5f+0.35f*cos(i*twicePi/triangleAmount),
            -17.3f+0.35f*sin(i*twicePi/triangleAmount)
        );
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(32.5f,-17.3f);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            32.5f+0.35f*cos(i*twicePi/triangleAmount),
            -17.3f+0.35f*sin(i*twicePi/triangleAmount)
        );
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(29.9f,-14.2f);
    glVertex2f(30.9f,-14.2f);
    glVertex2f(30.75f,-13.3f);
    glVertex2f(30.05f,-13.3f);
    glEnd();
    glColor3f(0.62f,0.45f,0.32f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(30.5f,-12.0f);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            30.5f+1.25f*cos(i*twicePi/triangleAmount),
            -12.0f+1.25f*sin(i*twicePi/triangleAmount)
        );
    glEnd();
    glPopMatrix();
// STANDING PERSON - LEFT STALL
// Legs
glColor3f(0.10f,0.25f,0.12f);
glBegin(GL_QUADS);
glVertex2f(-34.0f,-22.0f);
glVertex2f(-33.1f,-22.0f);
glVertex2f(-33.1f,-17.0f);
glVertex2f(-34.0f,-17.0f);
glVertex2f(-32.3f,-22.0f);
glVertex2f(-31.4f,-22.0f);
glVertex2f(-31.4f,-17.0f);
glVertex2f(-32.3f,-17.0f);
glEnd();
// Feet
glColor3f(0.05f,0.05f,0.05f);
glBegin(GL_QUADS);
glVertex2f(-34.2f,-22.5f);
glVertex2f(-33.0f,-22.5f);
glVertex2f(-33.0f,-22.0f);
glVertex2f(-34.2f,-22.0f);
glVertex2f(-32.4f,-22.5f);
glVertex2f(-31.2f,-22.5f);
glVertex2f(-31.2f,-22.0f);
glVertex2f(-32.4f,-22.0f);
glEnd();
// Shirt
glColor3f(0.20f,0.45f,0.75f);
glBegin(GL_QUADS);
glVertex2f(-34.3f,-17.0f);
glVertex2f(-31.1f,-17.0f);
glVertex2f(-31.3f,-13.7f);
glVertex2f(-34.1f,-13.7f);
glEnd();
// Arms
glBegin(GL_QUADS);
glVertex2f(-35.1f,-16.8f);
glVertex2f(-34.3f,-16.8f);
glVertex2f(-34.0f,-14.5f);
glVertex2f(-34.8f,-14.5f);
glVertex2f(-31.1f,-16.8f);
glVertex2f(-30.3f,-16.8f);
glVertex2f(-30.6f,-14.5f);
glVertex2f(-31.4f,-14.5f);
glEnd();
// Hands
glColor3f(0.62f,0.45f,0.32f);
glBegin(GL_TRIANGLE_FAN);
glVertex2f(-34.7f,-16.8f);
for(int i=0;i<=triangleAmount;i++)
    glVertex2f(
        -34.7f+0.35f*cos(i*twicePi/triangleAmount),
        -16.8f+0.35f*sin(i*twicePi/triangleAmount)
    );
glEnd();
glBegin(GL_TRIANGLE_FAN);
glVertex2f(-30.7f,-16.8f);
for(int i=0;i<=triangleAmount;i++)
    glVertex2f(
        -30.7f+0.35f*cos(i*twicePi/triangleAmount),
        -16.8f+0.35f*sin(i*twicePi/triangleAmount)
    );
glEnd();
// Neck
glColor3f(0.55f,0.40f,0.28f);
glBegin(GL_QUADS);
glVertex2f(-33.1f,-13.7f);
glVertex2f(-32.3f,-13.7f);
glVertex2f(-32.35f,-12.8f);
glVertex2f(-33.05f,-12.8f);
glEnd();
// Head
glColor3f(0.62f,0.45f,0.32f);
glBegin(GL_TRIANGLE_FAN);
glVertex2f(-32.7f,-11.5f);
for(int i=0;i<=triangleAmount;i++)
    glVertex2f(
        -32.7f+1.25f*cos(i*twicePi/triangleAmount),
        -11.5f+1.25f*sin(i*twicePi/triangleAmount)
    );
glEnd();
    // PERSON 3 - ORANGE SHIRT
    glPushMatrix();
    glTranslatef(p3Pos,-6.0f,0.0f);
    glColor3f(0.10f,0.25f,0.12f);
    glBegin(GL_QUADS);
    glVertex2f(0.7f,-21.0f);
    glVertex2f(1.6f,-21.0f);
    glVertex2f(1.6f,-16.0f);
    glVertex2f(0.7f,-16.0f);
    glVertex2f(2.4f,-21.0f);
    glVertex2f(3.3f,-21.0f);
    glVertex2f(3.3f,-16.0f);
    glVertex2f(2.4f,-16.0f);
    glEnd();
    glColor3f(0.05f,0.05f,0.05f);
    glBegin(GL_QUADS);
    glVertex2f(0.5f,-21.5f);
    glVertex2f(1.7f,-21.5f);
    glVertex2f(1.7f,-21.0f);
    glVertex2f(0.5f,-21.0f);
    glVertex2f(2.3f,-21.5f);
    glVertex2f(3.5f,-21.5f);
    glVertex2f(3.5f,-21.0f);
    glVertex2f(2.3f,-21.0f);
    glEnd();
    glColor3f(0.85f,0.35f,0.10f);
    glBegin(GL_QUADS);
    glVertex2f(0.4f,-16.0f);
    glVertex2f(3.6f,-16.0f);
    glVertex2f(3.4f,-12.7f);
    glVertex2f(0.6f,-12.7f);
    glVertex2f(-0.4f,-15.8f);
    glVertex2f(0.4f,-15.8f);
    glVertex2f(0.60f,-13.5f);
    glVertex2f(-0.15f,-13.5f);
    glVertex2f(3.6f,-15.8f);
    glVertex2f(4.4f,-15.8f);
    glVertex2f(4.15f,-13.5f);
    glVertex2f(3.40f,-13.5f);
    glEnd();
    glColor3f(0.62f,0.45f,0.32f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f,-15.8f);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            0.0f+0.35f*cos(i*twicePi/triangleAmount),
            -15.8f+0.35f*sin(i*twicePi/triangleAmount)
        );
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(4.0f,-15.8f);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            4.0f+0.35f*cos(i*twicePi/triangleAmount),
            -15.8f+0.35f*sin(i*twicePi/triangleAmount)
        );
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(1.5f,-12.7f);
    glVertex2f(2.5f,-12.7f);
    glVertex2f(2.35f,-11.8f);
    glVertex2f(1.65f,-11.8f);
    glEnd();
    glColor3f(0.62f,0.45f,0.32f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(2.0f,-10.5f);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            2.0f+1.25f*cos(i*twicePi/triangleAmount),
            -10.5f+1.25f*sin(i*twicePi/triangleAmount)
    );
    glEnd();
    glPopMatrix();
// STANDING PERSON - RIGHT STALL
// Legs
glColor3f(0.10f,0.25f,0.12f);
glBegin(GL_QUADS);
glVertex2f(31.4f,-22.0f);
glVertex2f(32.3f,-22.0f);
glVertex2f(32.3f,-17.0f);
glVertex2f(31.4f,-17.0f);
glVertex2f(33.1f,-22.0f);
glVertex2f(34.0f,-22.0f);
glVertex2f(34.0f,-17.0f);
glVertex2f(33.1f,-17.0f);
glEnd();
// Feet
glColor3f(0.05f,0.05f,0.05f);
glBegin(GL_QUADS);
glVertex2f(31.2f,-22.5f);
glVertex2f(32.4f,-22.5f);
glVertex2f(32.4f,-22.0f);
glVertex2f(31.2f,-22.0f);
glVertex2f(33.0f,-22.5f);
glVertex2f(34.2f,-22.5f);
glVertex2f(34.2f,-22.0f);
glVertex2f(33.0f,-22.0f);
glEnd();
// Shirt
glColor3f(0.85f,0.20f,0.15f);
glBegin(GL_QUADS);
glVertex2f(31.1f,-17.0f);
glVertex2f(34.3f,-17.0f);
glVertex2f(34.1f,-13.7f);
glVertex2f(31.3f,-13.7f);
glEnd();
// Arms
glBegin(GL_QUADS);
glVertex2f(30.3f,-16.8f);
glVertex2f(31.1f,-16.8f);
glVertex2f(31.4f,-14.5f);
glVertex2f(30.6f,-14.5f);
glVertex2f(34.3f,-16.8f);
glVertex2f(35.1f,-16.8f);
glVertex2f(34.8f,-14.5f);
glVertex2f(34.0f,-14.5f);
glEnd();
// Hands
glColor3f(0.62f,0.45f,0.32f);
glBegin(GL_TRIANGLE_FAN);
glVertex2f(30.7f,-16.8f);
for(int i=0;i<=triangleAmount;i++)
    glVertex2f(
        30.7f+0.35f*cos(i*twicePi/triangleAmount),
        -16.8f+0.35f*sin(i*twicePi/triangleAmount)
    );
glEnd();
glBegin(GL_TRIANGLE_FAN);
glVertex2f(34.7f,-16.8f);
for(int i=0;i<=triangleAmount;i++)
    glVertex2f(
        34.7f+0.35f*cos(i*twicePi/triangleAmount),
        -16.8f+0.35f*sin(i*twicePi/triangleAmount)
    );
glEnd();
// Neck
glColor3f(0.55f,0.40f,0.28f);
glBegin(GL_QUADS);
glVertex2f(32.3f,-13.7f);
glVertex2f(33.1f,-13.7f);
glVertex2f(33.05f,-12.8f);
glVertex2f(32.35f,-12.8f);
glEnd();
// Head
glColor3f(0.62f,0.45f,0.32f);
glBegin(GL_TRIANGLE_FAN);
glVertex2f(32.7f,-11.5f);
for(int i=0;i<=triangleAmount;i++)
    glVertex2f(
        32.7f+1.25f*cos(i*twicePi/triangleAmount),
        -11.5f+1.25f*sin(i*twicePi/triangleAmount)
    );

glEnd();
    //  SITTING PERSON - NEXT TO BASKET
    // Body (torso)
    glColor3f(0.15f,0.35f,0.65f);
    glBegin(GL_POLYGON);
    glVertex2f(40.3f,-32.0f);
    glVertex2f(44.1f,-32.0f);
    glVertex2f(44.1f,-37.0f);
    glVertex2f(40.3f,-37.0f);
    glEnd();
    // Head
    glColor3f(0.62f,0.45f,0.32f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(42.2f,-30.5f);
    for(int i=0;i<=triangleAmount;i++)
        glVertex2f(
            42.2f+1.5f*cos(i*twicePi/triangleAmount),
            -30.5f+1.5f*sin(i*twicePi/triangleAmount)
        );
    glEnd();
    // Left arm - upper (horizontal, shoulder to elbow)
    glColor3f(0.15f,0.35f,0.65f);
    glBegin(GL_POLYGON);
    glVertex2f(39.7f,-32.6f);
    glVertex2f(40.3f,-32.6f);
    glVertex2f(40.3f,-33.6f);
    glVertex2f(39.7f,-33.6f);
    glEnd();
    // Left arm - lower (vertical, elbow to hand)
    glBegin(GL_POLYGON);
    glVertex2f(39.7f,-33.6f);
    glVertex2f(40.3f,-33.6f);
    glVertex2f(40.3f,-35.0f);
    glVertex2f(39.7f,-35.0f);
    glEnd();
    // Right arm - upper (horizontal, shoulder to elbow)
    glBegin(GL_POLYGON);
    glVertex2f(44.1f,-32.6f);
    glVertex2f(44.7f,-32.6f);
    glVertex2f(44.7f,-33.6f);
    glVertex2f(44.1f,-33.6f);
    glEnd();
    // Right arm - lower (vertical, elbow to hand)
    glBegin(GL_POLYGON);
    glVertex2f(44.1f,-33.6f);
    glVertex2f(44.7f,-33.6f);
    glVertex2f(44.7f,-35.0f);
    glVertex2f(44.1f,-35.0f);
    glEnd();
    // Left hand
    glColor3f(0.62f,0.45f,0.32f);
    glBegin(GL_POLYGON);
    glVertex2f(39.5f,-35.0f);
    glVertex2f(40.5f,-35.0f);
    glVertex2f(40.5f,-35.5f);
    glVertex2f(39.5f,-35.5f);
    glEnd();
    // Right hand
    glBegin(GL_POLYGON);
    glVertex2f(43.9f,-35.0f);
    glVertex2f(44.9f,-35.0f);
    glVertex2f(44.9f,-35.5f);
    glVertex2f(43.9f,-35.5f);
    glEnd();
    // Left leg - thigh (horizontal, hip to knee)
    glColor3f(0.10f,0.25f,0.45f);
    glBegin(GL_POLYGON);
    glVertex2f(39.7f,-35.6f);
    glVertex2f(40.3f,-35.6f);
    glVertex2f(40.3f,-36.6f);
    glVertex2f(39.7f,-36.6f);
    glEnd();
    // Left leg - shin (vertical, knee to foot)
    glBegin(GL_POLYGON);
    glVertex2f(39.7f,-36.6f);
    glVertex2f(40.3f,-36.6f);
    glVertex2f(40.3f,-38.0f);
    glVertex2f(39.7f,-38.0f);
    glEnd();
    // Right leg - thigh (horizontal, hip to knee)
    glBegin(GL_POLYGON);
    glVertex2f(44.1f,-35.6f);
    glVertex2f(44.7f,-35.6f);
    glVertex2f(44.7f,-36.6f);
    glVertex2f(44.1f,-36.6f);
    glEnd();
    // Right leg - shin (vertical, knee to foot)
    glBegin(GL_POLYGON);
    glVertex2f(44.1f,-36.6f);
    glVertex2f(44.7f,-36.6f);
    glVertex2f(44.7f,-38.0f);
    glVertex2f(44.1f,-38.0f);
    glEnd();
    // Left foot
    glColor3f(0.10f,0.07f,0.04f);
    glBegin(GL_POLYGON);
    glVertex2f(39.5f,-38.0f);
    glVertex2f(40.5f,-38.0f);
    glVertex2f(40.5f,-38.5f);
    glVertex2f(39.5f,-38.5f);
    glEnd();
    // Right foot
    glBegin(GL_POLYGON);
    glVertex2f(43.9f,-38.0f);
    glVertex2f(44.9f,-38.0f);
    glVertex2f(44.9f,-38.5f);
    glVertex2f(43.9f,-38.5f);
    glEnd();
    // SMALL BASKET IN FRONT
    glColor3f(0.45f,0.25f,0.10f);
    glBegin(GL_POLYGON);
    glVertex2f(35.5f,-34.0f);
    glVertex2f(39.0f,-34.0f);
    glVertex2f(38.6f,-36.3f);
    glVertex2f(35.9f,-36.3f);
    glEnd();
    // Basket rim
    glColor3f(0.30f,0.15f,0.05f);
    glBegin(GL_POLYGON);
    glVertex2f(35.2f,-33.7f);
    glVertex2f(39.3f,-33.7f);
    glVertex2f(39.0f,-34.3f);
    glVertex2f(35.5f,-34.3f);
    glEnd();
    // Vegetables
    glColor3f(0.85f,0.08f,0.05f);
    glBegin(GL_POLYGON);
    glVertex2f(35.9f,-33.8f);
    glVertex2f(37.0f,-33.2f);
    glVertex2f(37.8f,-33.9f);
    glVertex2f(36.9f,-34.5f);
    glEnd();
    glColor3f(0.20f,0.60f,0.10f);
    glBegin(GL_POLYGON);
    glVertex2f(37.5f,-33.8f);
    glVertex2f(38.5f,-33.1f);
    glVertex2f(39.5f,-33.9f);
    glVertex2f(38.5f,-34.5f);
    glEnd();
    //  SMALL BASKET IN FRONT
    glColor3f(0.45f,0.25f,0.10f);
    glBegin(GL_POLYGON);
    glVertex2f(-29.5f,-14.0f);
    glVertex2f(-26.0f,-14.0f);
    glVertex2f(-26.4f,-16.3f);
    glVertex2f(-29.1f,-16.3f);
    glEnd();
    // Basket rim
    glColor3f(0.30f,0.15f,0.05f);
    glBegin(GL_POLYGON);
    glVertex2f(-29.8f,-13.7f);
    glVertex2f(-25.7f,-13.7f);
    glVertex2f(-26.0f,-14.3f);
    glVertex2f(-29.5f,-14.3f);
    glEnd();
    // Vegetables
    glColor3f(0.85f,0.08f,0.05f);
    glBegin(GL_POLYGON);
    glVertex2f(-29.1f,-13.8f);
    glVertex2f(-28.0f,-13.2f);
    glVertex2f(-27.2f,-13.9f);
    glVertex2f(-28.1f,-14.5f);
    glEnd();
    glColor3f(0.20f,0.60f,0.10f);
    glBegin(GL_POLYGON);
    glVertex2f(-27.5f,-13.8f);
    glVertex2f(-26.5f,-13.1f);
    glVertex2f(-25.5f,-13.9f);
    glVertex2f(-26.5f,-14.5f);
    glEnd();
    glFlush();
}
void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(
        -50.0,50.0,
        -50.0,50.0,
        -1.0,1.0
    );
    glMatrixMode(GL_MODELVIEW);
}
void sound()
{
    if(!isMuted)
    {
        PlaySound(TEXT("freesound_community-street-market-67330.wav"),
                  NULL,
                  SND_ASYNC | SND_FILENAME | SND_LOOP);
    }
}
int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(1080,800);
    glutInitWindowPosition(80,50);
    glutCreateWindow("Village Market Scene");
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(SpecialInput);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(100,update,0);
    sound();
    glutMainLoop();
    return 0;
}
