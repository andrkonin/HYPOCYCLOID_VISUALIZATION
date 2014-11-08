/****************************************************************************
** Meta object code from reading C++ file 'pmd3.h'
**
** Created: Sat Dec 19 10:03:26 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "pmd3.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pmd3.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PMD3[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x0a,
      42,   20,    5,    5, 0x0a,
      87,    5,    5,    5, 0x0a,
     100,    5,    5,    5, 0x0a,
     116,    5,    5,    5, 0x0a,
     132,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PMD3[] = {
    "PMD3\0\0backDefault()\0M_,m1_,m2_,m3_,m4_,R_\0"
    "getData(float,float,float,float,float,float)\0"
    "deleteaxis()\0deletemcircle()\0"
    "deletescircle()\0zoom()\0"
};

const QMetaObject PMD3::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_PMD3,
      qt_meta_data_PMD3, 0 }
};

const QMetaObject *PMD3::metaObject() const
{
    return &staticMetaObject;
}

void *PMD3::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PMD3))
        return static_cast<void*>(const_cast< PMD3*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int PMD3::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: backDefault(); break;
        case 1: getData((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5])),(*reinterpret_cast< float(*)>(_a[6]))); break;
        case 2: deleteaxis(); break;
        case 3: deletemcircle(); break;
        case 4: deletescircle(); break;
        case 5: zoom(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
