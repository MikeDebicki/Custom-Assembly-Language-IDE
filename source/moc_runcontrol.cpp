/****************************************************************************
** Meta object code from reading C++ file 'runcontrol.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "runcontrol.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'runcontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RunControl_t {
    QByteArrayData data[8];
    char stringdata0[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RunControl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RunControl_t qt_meta_stringdata_RunControl = {
    {
QT_MOC_LITERAL(0, 0, 10), // "RunControl"
QT_MOC_LITERAL(1, 11, 30), // "send_rdi_command_to_mainwindow"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 25), // "send_output_to_mainwindow"
QT_MOC_LITERAL(4, 69, 7), // "message"
QT_MOC_LITERAL(5, 77, 29), // "connect_program_to_runcontrol"
QT_MOC_LITERAL(6, 107, 29), // "connect_program_to_mainwindow"
QT_MOC_LITERAL(7, 137, 9) // "errorText"

    },
    "RunControl\0send_rdi_command_to_mainwindow\0"
    "\0send_output_to_mainwindow\0message\0"
    "connect_program_to_runcontrol\0"
    "connect_program_to_mainwindow\0errorText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RunControl[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    1,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   38,    2, 0x08 /* Private */,
       6,    1,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void RunControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RunControl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_rdi_command_to_mainwindow(); break;
        case 1: _t->send_output_to_mainwindow((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->connect_program_to_runcontrol(); break;
        case 3: _t->connect_program_to_mainwindow((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RunControl::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RunControl::send_rdi_command_to_mainwindow)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RunControl::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RunControl::send_output_to_mainwindow)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RunControl::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_RunControl.data,
    qt_meta_data_RunControl,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RunControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RunControl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RunControl.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RunControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void RunControl::send_rdi_command_to_mainwindow()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void RunControl::send_output_to_mainwindow(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
