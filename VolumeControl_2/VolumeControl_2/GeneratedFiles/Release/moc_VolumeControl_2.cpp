/****************************************************************************
** Meta object code from reading C++ file 'VolumeControl_2.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VolumeControl_2.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VolumeControl_2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VolumeControl_2_t {
    QByteArrayData data[12];
    char stringdata0[217];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VolumeControl_2_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VolumeControl_2_t qt_meta_stringdata_VolumeControl_2 = {
    {
QT_MOC_LITERAL(0, 0, 15), // "VolumeControl_2"
QT_MOC_LITERAL(1, 16, 22), // "on_ComboBox1_activated"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 5), // "index"
QT_MOC_LITERAL(4, 46, 22), // "on_ComboBox2_activated"
QT_MOC_LITERAL(5, 69, 22), // "on_ComboBox3_activated"
QT_MOC_LITERAL(6, 92, 22), // "on_ComboBox4_activated"
QT_MOC_LITERAL(7, 115, 23), // "on_Slider1_valueChanged"
QT_MOC_LITERAL(8, 139, 5), // "value"
QT_MOC_LITERAL(9, 145, 23), // "on_Slider2_valueChanged"
QT_MOC_LITERAL(10, 169, 23), // "on_Slider3_valueChanged"
QT_MOC_LITERAL(11, 193, 23) // "on_Slider4_valueChanged"

    },
    "VolumeControl_2\0on_ComboBox1_activated\0"
    "\0index\0on_ComboBox2_activated\0"
    "on_ComboBox3_activated\0on_ComboBox4_activated\0"
    "on_Slider1_valueChanged\0value\0"
    "on_Slider2_valueChanged\0on_Slider3_valueChanged\0"
    "on_Slider4_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VolumeControl_2[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x08 /* Private */,
       4,    1,   57,    2, 0x08 /* Private */,
       5,    1,   60,    2, 0x08 /* Private */,
       6,    1,   63,    2, 0x08 /* Private */,
       7,    1,   66,    2, 0x08 /* Private */,
       9,    1,   69,    2, 0x08 /* Private */,
      10,    1,   72,    2, 0x08 /* Private */,
      11,    1,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void VolumeControl_2::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VolumeControl_2 *_t = static_cast<VolumeControl_2 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_ComboBox1_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_ComboBox2_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_ComboBox3_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_ComboBox4_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_Slider1_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_Slider2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_Slider3_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_Slider4_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VolumeControl_2::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_VolumeControl_2.data,
      qt_meta_data_VolumeControl_2,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *VolumeControl_2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VolumeControl_2::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VolumeControl_2.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int VolumeControl_2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
