/****************************************************************************
** Meta object code from reading C++ file 'bankwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../bankwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'bankwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_bankwindow_t {
    QByteArrayData data[10];
    char stringdata0[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_bankwindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_bankwindow_t qt_meta_stringdata_bankwindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "bankwindow"
QT_MOC_LITERAL(1, 11, 20), // "openNostoSummaWindow"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 8), // "dataSlot"
QT_MOC_LITERAL(4, 42, 14), // "QNetworkReply*"
QT_MOC_LITERAL(5, 57, 5), // "reply"
QT_MOC_LITERAL(6, 63, 22), // "on_saldoButton_clicked"
QT_MOC_LITERAL(7, 86, 26), // "on_tapahtumaButton_clicked"
QT_MOC_LITERAL(8, 113, 22), // "on_nostoButton_clicked"
QT_MOC_LITERAL(9, 136, 29) // "on_kirjauduUlosButton_clicked"

    },
    "bankwindow\0openNostoSummaWindow\0\0"
    "dataSlot\0QNetworkReply*\0reply\0"
    "on_saldoButton_clicked\0"
    "on_tapahtumaButton_clicked\0"
    "on_nostoButton_clicked\0"
    "on_kirjauduUlosButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_bankwindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    1,   45,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,
       8,    0,   50,    2, 0x08 /* Private */,
       9,    0,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void bankwindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<bankwindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openNostoSummaWindow(); break;
        case 1: _t->dataSlot((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 2: _t->on_saldoButton_clicked(); break;
        case 3: _t->on_tapahtumaButton_clicked(); break;
        case 4: _t->on_nostoButton_clicked(); break;
        case 5: _t->on_kirjauduUlosButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject bankwindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_bankwindow.data,
    qt_meta_data_bankwindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *bankwindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *bankwindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_bankwindow.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int bankwindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
