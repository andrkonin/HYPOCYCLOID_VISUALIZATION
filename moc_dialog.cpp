/****************************************************************************
** Meta object code from reading C++ file 'dialog.h'
**
** Created: Sat Dec 19 10:11:09 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Dialog[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,
      22,    7,    7,    7, 0x0a,
      32,    7,    7,    7, 0x0a,
      40,    7,    7,    7, 0x0a,
      51,    7,    7,    7, 0x0a,
      62,    7,    7,    7, 0x0a,
      75,    7,    7,    7, 0x0a,
      91,    7,    7,    7, 0x0a,
     107,    7,    7,    7, 0x0a,
     115,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Dialog[] = {
    "Dialog\0\0backDefault()\0pmdStop()\0pmdGo()\0"
    "makeslow()\0makefast()\0deleteaxis()\0"
    "deletemcircle()\0deletescircle()\0about()\0"
    "zoom()\0"
};

const QMetaObject Dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog,
      qt_meta_data_Dialog, 0 }
};

const QMetaObject *Dialog::metaObject() const
{
    return &staticMetaObject;
}

void *Dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog))
        return static_cast<void*>(const_cast< Dialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int Dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: backDefault(); break;
        case 1: pmdStop(); break;
        case 2: pmdGo(); break;
        case 3: makeslow(); break;
        case 4: makefast(); break;
        case 5: deleteaxis(); break;
        case 6: deletemcircle(); break;
        case 7: deletescircle(); break;
        case 8: about(); break;
        case 9: zoom(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
