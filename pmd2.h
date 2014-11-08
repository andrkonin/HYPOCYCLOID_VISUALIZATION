#ifndef PMD2_H
#define PMD2_H

#include <QtOpenGL>

class PMD2 : public QGLWidget
 {
     Q_OBJECT

 public:

    bool stop;
    float m1;
    float m2;
    float m3;
    float m4;
    float M;
    bool mcircle;
    bool scircle;
    bool axis;
    bool zoomflag;
    float maxX;
    float maxY;
    PMD2(QWidget *parent=0);
    QWidget *createWidget(QWidget *parent);

public slots:

    void backDefault();
    void getData(float M_,float m1_,float m2_,float m3_,float m4_,float R_);
    void deleteaxis();
    void deletemcircle();
    void deletescircle();
    void zoom();

protected:

    void InitializeGL();
    void resizeGL(int width,int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:

    void draw();
    int faceAtPosition(const QPoint &pos);

    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;

    int scale;
    float far;
    float volume;
    float middle;
    float d,R;
    QColor faceColors[4];
    QPoint lastPos;
    int time;
    float dt;
    bool ok;
    float t;
    float Z;
};
#endif // PMD2_H
