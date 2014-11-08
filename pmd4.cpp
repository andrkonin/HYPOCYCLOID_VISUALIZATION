#include "pmd4.h"

PMD4::PMD4(QWidget *parent)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
    rotationX=0.0;
    rotationY=0.0;
    rotationZ=0.0;
    faceColors[0]=Qt::red;
    faceColors[1]=Qt::green;
    faceColors[2]=Qt::blue;
    faceColors[3]=Qt::yellow;

    stop=false;
    ok=false;
    scale=20;
    far=-10.0;
    middle=far;
    volume=1.0;
    time=50;
    mcircle=true;
    scircle=true;
    axis=true;
    zoomflag=false;
    M=5.0;
    m1=1.0;
    m2=0.0;
    m3=0.0;
    m4=1.0;
    d=3.0;
    R=0.25;
    t=0.0;
    dt=0.05;
    k=0;
    curpoint=0;
    Z=1.0;
}

void PMD4::backDefault()
{
    scale=20;
    far=-10.0;
    volume=1.0;
    rotationX=0.0;
    rotationY=0.0;
    rotationZ=0.0;
    updateGL();
}

void PMD4::zoom()
{
    zoomflag=!zoomflag;
    float max;
    if (zoomflag)
    {
        if (maxX>2.0||maxY>2.0)
        {
            if (maxX>maxY) max=maxX;
            else max=maxY;
            Z=max/2.0;
        }
    }
    else Z=1.0;
    updateGL();
}



void PMD4::deleteaxis()
{
    axis=!axis;
    updateGL();
}

void PMD4::deletemcircle()
{
    mcircle=!mcircle;
    updateGL();
}

void PMD4::deletescircle()
{
    scircle=!scircle;
    updateGL();
}


void PMD4::getData(float M_,float m1_,float m2_,float m3_,float m4_,float R_)
{
    M=M_;
    m1=m1_;
    m2=m2_;
    m3=m3_;
    m4=m4_;
    R=R_;
    curpoint=0;
    updateGL();
}

void PMD4::changeSpeed(int flag)
{
    if (flag<0)
        dt/=1.5;
    else
        dt*=1.5;
}

void PMD4::InitializeGL()
{
    qglClearColor(Qt::black);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void PMD4::resizeGL(int width,int height)
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x=GLfloat(width)/height;
    glFrustum(-x,x,-1.0,1.0,4.0,15.0);
    glMatrixMode(GL_MODELVIEW);
}

void PMD4::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}

void PMD4::mousePressEvent(QMouseEvent *event)
{

    lastPos=event->pos();

}

void PMD4::mouseMoveEvent(QMouseEvent *event)
{

    float rx;
    float ry;
    GLfloat dx=GLfloat(event->x() - lastPos.x())/width();
    GLfloat dy=GLfloat(event->y() - lastPos.y())/height();
    if (event->buttons()&Qt::LeftButton)
    {
        rx=rotationX-180*dy;
        ry=rotationY-180*dx;

        rotationX=rx;

        rotationY=ry;
        updateGL();
    }
    else if (event->buttons()&Qt::RightButton)
    {
        rotationX+=180*dy;
        rotationZ+=180*dx;
        updateGL();
    }
    lastPos=event->pos();

}

void PMD4::mouseDoubleClickEvent(QMouseEvent *event)
{
    stop=!stop;
}

void PMD4::wheelEvent(QWheelEvent *event)
{


    if (event->delta()>0)
    {
        if (far<-4.0)
            far++;
    }
    else
        if (far>-14.0) far--;
    updateGL();

}

void PMD4::draw()
{
    maxX=0.0;
    maxY=0.0;
    float mx,my;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0,0.0,far);
    glRotatef(rotationX,1.0,0.0,0.0);
    glRotatef(rotationY,0.0,1.0,0.0);
    glRotatef(rotationZ,0.0,0.0,1.0);

    glPushMatrix();

    //Drawing axes
    if (axis)
    {
    QColor color;
    glColor3d(255,255,255);
    glBegin(GL_LINES);
    glVertex3f(-1.0*d,0.0,0.0);
    glVertex3f(d,0.0,0.0);
    glVertex3f(0.0,-1.0*d,0.0);
    glVertex3f(0.0,d,0.0);
    glVertex3f(0.0,0.0,-1.0*d);
    glVertex3f(0.0,0.0,d);
    glEnd();
    QFont serifFont("Times", 8, QFont::Normal);
    color.setRgb(255,255,255);
    qglColor(color);
    renderText(d,0.0,0.0,"X",serifFont,2000);
    renderText(0.0,d,0.0,"Y",serifFont,2000);
    renderText(0.0,0.0,d,"Z",serifFont,2000);
    renderText(0.0,0.0,0.0,"0",serifFont,2000);
    }
    glColor3d(255,255,0);

    int i;
    float a,b,an,bn;
    double points[720][3];
    if (scircle)
    {
    glBegin(GL_LINE_LOOP);
    for (i=0;i<360;i+=2)
    {
        points[i][0]=R*cos(i/57.295779513);
        points[i][1]=R*sin(i/57.295779513);
        an=m1*points[i][0]+m2*points[i][1];
        bn=m3*points[i][0]+m4*points[i][1];
        points[i][0]=an;
        points[i][1]=bn;
        if (points[i][0]<0.0) mx=-1.0*points[i][0];
        else mx=points[i][0];
        if (points[i][1]<0.0) my=-1.0*points[i][1];
        else my=points[i][1];
        if (mx>maxX) maxX=mx;
        if (my>maxY) maxY=my;
        points[i][2]=0.0;
        glVertex3f(points[i][0]/Z,points[i][1]/Z,points[i][2]/Z);
    }
    glEnd();
    }
    float r=M*R;
    float cx,cy;
    cx=(R-r)*cos(M*t);
    cy=(R-r)*sin(M*t);
    //an=m1*cx+m2*cy;
    // bn=m3*cx+m4*cy;
    //cx=an;
    //cy=bn;
    glColor3d(0,191,255);
    if (mcircle)
    {
    glBegin(GL_LINE_LOOP);
    for (i=360;i<720;i++)
    {
        points[i][0]=cx+r*cos(i/57.295779513);
        points[i][1]=cy+r*sin(i/57.295779513);
        an=m1*points[i][0]+m2*points[i][1];
        bn=m3*points[i][0]+m4*points[i][1];
        points[i][0]=an;
        points[i][1]=bn;
        if (points[i][0]<0.0) mx=-1.0*points[i][0];
        else mx=points[i][0];
        if (points[i][1]<0.0) my=-1.0*points[i][1];
        else my=points[i][1];
        if (mx>maxX) maxX=mx;
        if (my>maxY) maxY=my;
        points[i][2]=0;
        glVertex3f(points[i][0]/Z,points[i][1]/Z,points[i][2]/Z);
    }
    glEnd();
    }


    a=(R-M*R)*cos(M*t)+M*R*cos(t-M*t);
    b=(R-M*R)*sin(M*t)-M*R*sin(t-M*t);
    an=m1*a+m2*b;
    bn=m3*a+m4*b;
    a=an;
    b=bn;
    if (a<0.0) mx=-1.0*a;
    else mx=a;
    if (b<0.0) my=-1.0*b;
    else my=b;
    if (mx>maxX) maxX=mx;
    if (my>maxY) maxY=my;
    if (mcircle)
    {
    an=m1*cx+m2*cy;
    bn=m3*cx+m4*cy;
    cx=an;
    cy=bn;
    glBegin(GL_LINES);
    glVertex3f(cx/Z,cy/Z,0.0);
    glVertex3f(a/Z,b/Z,0.0);
    glEnd();

    glPointSize(5);

    glBegin(GL_POINTS);
    glVertex3f(cx/Z,cy/Z,0.0);
    glEnd();
    }
    glColor3d(0,255,0);
    glBegin(GL_POINTS);
    glVertex3f(a/Z,b/Z,0.0);
    glBegin(GL_LINES);
    glEnd();

    if (curpoint+1<20000)
    {
        float a,b;
        glBegin(GL_LINE_STRIP);
        a=(R-M*R)*cos(M*t)+M*R*cos(t-M*t);
        b=(R-M*R)*sin(M*t)-M*R*sin(t-M*t);
        an=m1*a+m2*b;
        bn=m3*a+m4*b;
        a=an;
        b=bn;
        if (a<0.0) mx=-1.0*a;
        else mx=a;
        if (b<0.0) my=-1.0*b;
        else my=b;
        if (mx>maxX) maxX=mx;
        if (my>maxY) maxY=my;
        hypoc[curpoint][0]=a;
        hypoc[curpoint][1]=b;
        curpoint++;
        for (i=0;i<curpoint;i++)
            glVertex3f(hypoc[i][0]/Z,hypoc[i][1]/Z,0.0);
        glEnd();
        //rotationX+=dt;
        //rotationY+=dt;
    }

    if (!stop)
    {
        t+=dt;
    }

    glPopMatrix();

}
int PMD4::faceAtPosition(const QPoint &pos)
{
    const int MaxSize=512;
    GLuint buffer[MaxSize];
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT,viewport);
    glSelectBuffer(MaxSize,buffer);
    glRenderMode(GL_SELECT);
    glInitNames();
    glPushName(0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPickMatrix(GLdouble(pos.x()),
                  GLdouble(viewport[3]-pos.y()),
                  5.0,5.0,viewport);
    GLfloat x=GLfloat(width())/height();
    glFrustum(-x,x,-1.0,1.0,4.0,15.0);
    draw();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    if (!glRenderMode(GL_RENDER))
        return -1;
    return buffer[3];
}


