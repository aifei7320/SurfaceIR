/****************************************************************************
** Meta object code from reading C++ file 'showframe.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../showframe/showframe.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'showframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ShowFrame_t {
    QByteArrayData data[22];
    char stringdata0[283];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ShowFrame_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ShowFrame_t qt_meta_stringdata_ShowFrame = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ShowFrame"
QT_MOC_LITERAL(1, 10, 23), // "on_recordButton_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 22), // "on_colorButton_clicked"
QT_MOC_LITERAL(4, 58, 29), // "on_sourceChangeButton_clicked"
QT_MOC_LITERAL(5, 88, 27), // "on_tempChangeButton_clicked"
QT_MOC_LITERAL(6, 116, 7), // "display"
QT_MOC_LITERAL(7, 124, 7), // "QImage&"
QT_MOC_LITERAL(8, 132, 5), // "image"
QT_MOC_LITERAL(9, 138, 17), // "on_psbAdd_clicked"
QT_MOC_LITERAL(10, 156, 11), // "setDeviceIP"
QT_MOC_LITERAL(11, 168, 19), // "connectionEstablish"
QT_MOC_LITERAL(12, 188, 12), // "displayFrame"
QT_MOC_LITERAL(13, 201, 11), // "delTipLabel"
QT_MOC_LITERAL(14, 213, 9), // "showImage"
QT_MOC_LITERAL(15, 223, 7), // "ushort*"
QT_MOC_LITERAL(16, 231, 10), // "pRecvImage"
QT_MOC_LITERAL(17, 242, 6), // "float*"
QT_MOC_LITERAL(18, 249, 6), // "_pTemp"
QT_MOC_LITERAL(19, 256, 11), // "_centerTemp"
QT_MOC_LITERAL(20, 268, 6), // "_width"
QT_MOC_LITERAL(21, 275, 7) // "_height"

    },
    "ShowFrame\0on_recordButton_clicked\0\0"
    "on_colorButton_clicked\0"
    "on_sourceChangeButton_clicked\0"
    "on_tempChangeButton_clicked\0display\0"
    "QImage&\0image\0on_psbAdd_clicked\0"
    "setDeviceIP\0connectionEstablish\0"
    "displayFrame\0delTipLabel\0showImage\0"
    "ushort*\0pRecvImage\0float*\0_pTemp\0"
    "_centerTemp\0_width\0_height"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShowFrame[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    1,   73,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    1,   77,    2, 0x08 /* Private */,
      11,    0,   80,    2, 0x08 /* Private */,
      12,    0,   81,    2, 0x08 /* Private */,
      13,    0,   82,    2, 0x08 /* Private */,
      14,    5,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 17, QMetaType::Float, QMetaType::UShort, QMetaType::UShort,   16,   18,   19,   20,   21,

       0        // eod
};

void ShowFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ShowFrame *_t = static_cast<ShowFrame *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_recordButton_clicked(); break;
        case 1: _t->on_colorButton_clicked(); break;
        case 2: _t->on_sourceChangeButton_clicked(); break;
        case 3: _t->on_tempChangeButton_clicked(); break;
        case 4: _t->display((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 5: _t->on_psbAdd_clicked(); break;
        case 6: _t->setDeviceIP((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->connectionEstablish(); break;
        case 8: _t->displayFrame(); break;
        case 9: _t->delTipLabel(); break;
        case 10: _t->showImage((*reinterpret_cast< ushort*(*)>(_a[1])),(*reinterpret_cast< float*(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< ushort(*)>(_a[4])),(*reinterpret_cast< ushort(*)>(_a[5]))); break;
        default: ;
        }
    }
}

const QMetaObject ShowFrame::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_ShowFrame.data,
      qt_meta_data_ShowFrame,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ShowFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShowFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ShowFrame.stringdata0))
        return static_cast<void*>(const_cast< ShowFrame*>(this));
    return QLabel::qt_metacast(_clname);
}

int ShowFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
