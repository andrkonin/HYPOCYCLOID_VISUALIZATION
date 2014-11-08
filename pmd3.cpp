#include "pmd3.h"

PMD3::PMD3(QWidget *parent)
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
    dt=0.0;

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
    Z=1.0;
}


void PMD3::backDefault()
{
    scale=20;
    far=-10.0;
    volume=1.0;
    rotationX=0.0;
    rotationY=0.0;
    rotationZ=0.0;
    updateGL();
}
void PMD3::zoom()
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



void PMD3::deleteaxis()
{
    axis=!axis;
    updateGL();
}

void PMD3::deletemcircle()
{
    mcircle=!mcircle;
    updateGL();
}

void PMD3::deletescircle()
{
    scircle=!scircle;
    updateGL();
}


void PMD3::getData(float M_,float m1_,float m2_,float m3_,float m4_,float R_)
{
    M=M_;
    m1=m1_;
    m2=m2_;
    m3=m3_;
    m4=m4_;
    R=R_;
    updateGL();
}


void PMD3::InitializeGL()
{
    qglClearColor(Qt::black);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void PMD3::resizeGL(int width,int height)
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x=GLfloat(width)/height;
    glFrustum(-x,x,-1.0,1.0,4.0,15.0);
    glMatrixMode(GL_MODELVIEW);
}

void PMD3::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
}

void PMD3::mousePressEvent(QMouseEvent *event)
{

    lastPos=event->pos();

}

void PMD3::mouseMoveEvent(QMouseEvent *event)
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

void PMD3::mouseDoubleClickEvent(QMouseEvent *event)
{
    stop=!stop;
}

void PMD3::wheelEvent(QWheelEvent *event)
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

void PMD3::draw()
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

    double alpha;
    double beta;
    double a,h,g,b;
    double an,bn;
    a=m1;
    h=m2;
    g=m3;
    b=m4;

    double a1,a2,xx,yy;
    /*
    if (((a*a-h*h)-(b*b-g*g))==0.0)
    beta=-3.14159265358/2.0;
    //beta=0.0;
    else
    beta=atan2((2.0*(g*b+a*h)),((a*a-h*h)-(b*b-g*g)));

    beta=beta/2.0;

    if ((b*cos(beta)-g*sin(beta))==0.0)
    alpha=3.14159265358/2.0;
    //alpha=0.0;
    else
    alpha=atan2((a*sin(beta)-h*cos(beta)),
               (b*cos(beta)-g*sin(beta)));
    */
    beta=atan2(2.0*(g*b+a*h),((a*a-h*h)-(b*b-g*g)));
    beta/=2.0;
    alpha=atan2((a*sin(beta)-h*cos(beta)),(b*cos(beta)-g*sin(beta)));
    if (sin(alpha)!=0.0)
    {
        a1=(b*sin(beta)+g*cos(beta))/(sin(alpha));
        a2=(a*sin(beta)-h*cos(beta))/(sin(alpha));
    }
    else
    {
        a1=(a*cos(beta)+h*sin(beta))/(cos(alpha));
        a2=(b*cos(beta)-g*sin(beta))/(cos(alpha));
    }
    //printf("alpha=%f\nbeta=%f\n",alpha,beta);
    int i;
    double points[720][3];
    if (scircle)
    {
    glBegin(GL_LINE_LOOP);

    for (i=0;i<360;i+=2)
    {
        points[i][0]=R*cos(i/57.295779513);
        points[i][1]=R*sin(i/57.295779513);
        an=a1*points[i][0]*cos(alpha)-a2*points[i][1]*sin(alpha);
        bn=a1*points[i][0]*sin(alpha)+a2*points[i][1]*cos(alpha);
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
    float t=0.0;
    cx=(R-r)*cos(M*t);
    cy=(R-r)*sin(M*t);
    an=a1*cx*cos(alpha)-a2*cy*sin(alpha);
    bn=a1*cx*sin(alpha)+a2*cy*cos(alpha);
    //cx=an;
    //cy=bn;

    glColor3d(0,191,255);
    /*Moving circle*/
    if (mcircle)
    {
     glPointSize(5);

    glBegin(GL_POINTS);
    glVertex3f(an/Z,bn/Z,0.0);
    glEnd();
        
        glBegin(GL_LINE_STRIP);
    
    
    
    for (i=360;i<720;i++)
    {
        points[i][0]=cx+r*cos(i/57.295779513);
        points[i][1]=cy+r*sin(i/57.295779513);
        an=a1*points[i][0]*cos(alpha)-a2*points[i][1]*sin(alpha);
        bn=a1*points[i][0]*sin(alpha)+a2*points[i][1]*cos(alpha);
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


    glColor3d(0,255,0);
    glBegin(GL_LINE_STRIP);
    /*
      a - m1
      h - m2
      g - m3
      b - m4
    */

    for (i=1;i<20000;i++)
    {
        t+=dt;

        xx=(R-M*R)*cos(M*t)+M*R*cos(t-M*t);
        yy=(R-M*R)*sin(M*t)-M*R*sin(t-M*t);
       
        an=a1*xx*cos(alpha)-a2*yy*sin(alpha);

        bn=a1*xx*sin(alpha)+a2*yy*cos(alpha);
        if (an<0.0) mx=-1.0*an;
        else mx=an;
        if (bn<0.0) my=-1.0*bn;
        else my=bn;
        if (mx>maxX) maxX=mx;
        if (my>maxY) maxY=my;
        glVertex3f(an/Z,bn/Z,0.0);

        //rotationX+=dt;
        //rotationY+=dt;
    }
    glEnd();

    glPopMatrix();

}
int PMD3::faceAtPosition(const QPoint &pos)
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

