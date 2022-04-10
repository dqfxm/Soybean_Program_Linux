/****************************************************************************
** Meta object code from reading C++ file 'program_test.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Soybean_Info_System/program_test.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'program_test.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Program_Test_t {
    QByteArrayData data[12];
    char stringdata0[231];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Program_Test_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Program_Test_t qt_meta_stringdata_Program_Test = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Program_Test"
QT_MOC_LITERAL(1, 13, 9), // "Send_Addr"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "Addr"
QT_MOC_LITERAL(4, 29, 17), // "on_OK_Btn_clicked"
QT_MOC_LITERAL(5, 47, 29), // "on_Switch_to_back_Btn_clicked"
QT_MOC_LITERAL(6, 77, 30), // "on_Switch_to_Slash_Btn_clicked"
QT_MOC_LITERAL(7, 108, 24), // "on_Save_Conf_Btn_clicked"
QT_MOC_LITERAL(8, 133, 25), // "on_Load__Conf_Btn_clicked"
QT_MOC_LITERAL(9, 159, 23), // "on_time_out_Btn_clicked"
QT_MOC_LITERAL(10, 183, 23), // "on_savefile_Btn_clicked"
QT_MOC_LITERAL(11, 207, 23) // "on_hik_disp_Btn_clicked"

    },
    "Program_Test\0Send_Addr\0\0Addr\0"
    "on_OK_Btn_clicked\0on_Switch_to_back_Btn_clicked\0"
    "on_Switch_to_Slash_Btn_clicked\0"
    "on_Save_Conf_Btn_clicked\0"
    "on_Load__Conf_Btn_clicked\0"
    "on_time_out_Btn_clicked\0on_savefile_Btn_clicked\0"
    "on_hik_disp_Btn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Program_Test[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   62,    2, 0x08 /* Private */,
       5,    0,   63,    2, 0x08 /* Private */,
       6,    0,   64,    2, 0x08 /* Private */,
       7,    0,   65,    2, 0x08 /* Private */,
       8,    0,   66,    2, 0x08 /* Private */,
       9,    0,   67,    2, 0x08 /* Private */,
      10,    0,   68,    2, 0x08 /* Private */,
      11,    0,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Program_Test::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Program_Test *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Send_Addr((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->on_OK_Btn_clicked(); break;
        case 2: _t->on_Switch_to_back_Btn_clicked(); break;
        case 3: _t->on_Switch_to_Slash_Btn_clicked(); break;
        case 4: _t->on_Save_Conf_Btn_clicked(); break;
        case 5: _t->on_Load__Conf_Btn_clicked(); break;
        case 6: _t->on_time_out_Btn_clicked(); break;
        case 7: _t->on_savefile_Btn_clicked(); break;
        case 8: _t->on_hik_disp_Btn_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Program_Test::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Program_Test::Send_Addr)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Program_Test::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_Program_Test.data,
    qt_meta_data_Program_Test,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Program_Test::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Program_Test::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Program_Test.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Program_Test::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Program_Test::Send_Addr(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
