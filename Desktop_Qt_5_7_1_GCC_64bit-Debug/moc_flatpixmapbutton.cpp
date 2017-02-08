/****************************************************************************
** Meta object code from reading C++ file 'flatpixmapbutton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../flatpixmapbutton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flatpixmapbutton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FlatPixmapButton_t {
    QByteArrayData data[6];
    char stringdata0[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FlatPixmapButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FlatPixmapButton_t qt_meta_stringdata_FlatPixmapButton = {
    {
QT_MOC_LITERAL(0, 0, 16), // "FlatPixmapButton"
QT_MOC_LITERAL(1, 17, 11), // "sendClicked"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 9), // "sendEnter"
QT_MOC_LITERAL(4, 40, 9), // "sendLeave"
QT_MOC_LITERAL(5, 50, 12) // "updateAnimal"

    },
    "FlatPixmapButton\0sendClicked\0\0sendEnter\0"
    "sendLeave\0updateAnimal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlatPixmapButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void FlatPixmapButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FlatPixmapButton *_t = static_cast<FlatPixmapButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendClicked(); break;
        case 1: _t->sendEnter(); break;
        case 2: _t->sendLeave(); break;
        case 3: _t->updateAnimal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FlatPixmapButton::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FlatPixmapButton::sendClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (FlatPixmapButton::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FlatPixmapButton::sendEnter)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (FlatPixmapButton::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FlatPixmapButton::sendLeave)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject FlatPixmapButton::staticMetaObject = {
    { &BasicWidget::staticMetaObject, qt_meta_stringdata_FlatPixmapButton.data,
      qt_meta_data_FlatPixmapButton,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FlatPixmapButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlatPixmapButton::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FlatPixmapButton.stringdata0))
        return static_cast<void*>(const_cast< FlatPixmapButton*>(this));
    return BasicWidget::qt_metacast(_clname);
}

int FlatPixmapButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasicWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void FlatPixmapButton::sendClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void FlatPixmapButton::sendEnter()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void FlatPixmapButton::sendLeave()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
