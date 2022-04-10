/****************************************************************************
** Meta object code from reading C++ file 'ThreadObject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Soybean_Info_System/ThreadObject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ThreadObject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ThreadObject_t {
    QByteArrayData data[22];
    char stringdata0[359];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ThreadObject_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ThreadObject_t qt_meta_stringdata_ThreadObject = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ThreadObject"
QT_MOC_LITERAL(1, 13, 7), // "message"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 4), // "info"
QT_MOC_LITERAL(4, 27, 8), // "progress"
QT_MOC_LITERAL(5, 36, 7), // "present"
QT_MOC_LITERAL(6, 44, 10), // "sendtomain"
QT_MOC_LITERAL(7, 55, 11), // "send_to_plc"
QT_MOC_LITERAL(8, 67, 17), // "All_Dev_Cap_Start"
QT_MOC_LITERAL(9, 85, 16), // "All_Dev_Cap_Stop"
QT_MOC_LITERAL(10, 102, 24), // "startThreadSlot_camara_1"
QT_MOC_LITERAL(11, 127, 24), // "startThreadSlot_camara_2"
QT_MOC_LITERAL(12, 152, 24), // "startThreadSlot_camara_3"
QT_MOC_LITERAL(13, 177, 24), // "startThreadSlot_Kinect_1"
QT_MOC_LITERAL(14, 202, 24), // "startThreadSlot_Kinect_2"
QT_MOC_LITERAL(15, 227, 24), // "startThreadSlot_Kinect_3"
QT_MOC_LITERAL(16, 252, 26), // "startThreadSlot_AIKinect_1"
QT_MOC_LITERAL(17, 279, 19), // "startThreadSlot_PLC"
QT_MOC_LITERAL(18, 299, 14), // "rec_from_pyrun"
QT_MOC_LITERAL(19, 314, 9), // "recivecls"
QT_MOC_LITERAL(20, 324, 17), // "allow_detect_loop"
QT_MOC_LITERAL(21, 342, 16) // "stop_detect_loop"

    },
    "ThreadObject\0message\0\0info\0progress\0"
    "present\0sendtomain\0send_to_plc\0"
    "All_Dev_Cap_Start\0All_Dev_Cap_Stop\0"
    "startThreadSlot_camara_1\0"
    "startThreadSlot_camara_2\0"
    "startThreadSlot_camara_3\0"
    "startThreadSlot_Kinect_1\0"
    "startThreadSlot_Kinect_2\0"
    "startThreadSlot_Kinect_3\0"
    "startThreadSlot_AIKinect_1\0"
    "startThreadSlot_PLC\0rec_from_pyrun\0"
    "recivecls\0allow_detect_loop\0"
    "stop_detect_loop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ThreadObject[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       4,    1,  102,    2, 0x06 /* Public */,
       6,    1,  105,    2, 0x06 /* Public */,
       7,    1,  108,    2, 0x06 /* Public */,
       8,    0,  111,    2, 0x06 /* Public */,
       9,    0,  112,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,  113,    2, 0x0a /* Public */,
      11,    0,  114,    2, 0x0a /* Public */,
      12,    0,  115,    2, 0x0a /* Public */,
      13,    0,  116,    2, 0x0a /* Public */,
      14,    0,  117,    2, 0x0a /* Public */,
      15,    0,  118,    2, 0x0a /* Public */,
      16,    0,  119,    2, 0x0a /* Public */,
      17,    0,  120,    2, 0x0a /* Public */,
      18,    1,  121,    2, 0x0a /* Public */,
      20,    0,  124,    2, 0x0a /* Public */,
      21,    0,  125,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Int,
    QMetaType::Int,

       0        // eod
};

void ThreadObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ThreadObject *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->message((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->progress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sendtomain((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->send_to_plc((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->All_Dev_Cap_Start(); break;
        case 5: _t->All_Dev_Cap_Stop(); break;
        case 6: _t->startThreadSlot_camara_1(); break;
        case 7: _t->startThreadSlot_camara_2(); break;
        case 8: _t->startThreadSlot_camara_3(); break;
        case 9: _t->startThreadSlot_Kinect_1(); break;
        case 10: _t->startThreadSlot_Kinect_2(); break;
        case 11: _t->startThreadSlot_Kinect_3(); break;
        case 12: _t->startThreadSlot_AIKinect_1(); break;
        case 13: _t->startThreadSlot_PLC(); break;
        case 14: _t->rec_from_pyrun((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: { int _r = _t->allow_detect_loop();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 16: { int _r = _t->stop_detect_loop();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ThreadObject::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadObject::message)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ThreadObject::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadObject::progress)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ThreadObject::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadObject::sendtomain)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ThreadObject::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadObject::send_to_plc)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ThreadObject::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadObject::All_Dev_Cap_Start)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ThreadObject::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadObject::All_Dev_Cap_Stop)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ThreadObject::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ThreadObject.data,
    qt_meta_data_ThreadObject,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ThreadObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ThreadObject::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ThreadObject.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ThreadObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void ThreadObject::message(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ThreadObject::progress(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ThreadObject::sendtomain(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ThreadObject::send_to_plc(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ThreadObject::All_Dev_Cap_Start()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ThreadObject::All_Dev_Cap_Stop()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
