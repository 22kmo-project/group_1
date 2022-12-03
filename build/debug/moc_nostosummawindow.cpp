/****************************************************************************
** Meta object code from reading C++ file 'nostosummawindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../nostosummawindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nostosummawindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_nostoSummaWindow_t {
    QByteArrayData data[16];
    char stringdata0[263];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_nostoSummaWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_nostoSummaWindow_t qt_meta_stringdata_nostoSummaWindow = {
    {
QT_MOC_LITERAL(0, 0, 16), // "nostoSummaWindow"
QT_MOC_LITERAL(1, 17, 24), // "on_pushButton20e_clicked"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 24), // "on_pushButton40e_clicked"
QT_MOC_LITERAL(4, 68, 24), // "on_pushButton60e_clicked"
QT_MOC_LITERAL(5, 93, 25), // "on_pushButton100e_clicked"
QT_MOC_LITERAL(6, 119, 25), // "on_pushButton200e_clicked"
QT_MOC_LITERAL(7, 145, 25), // "on_pushButton500e_clicked"
QT_MOC_LITERAL(8, 171, 9), // "nostoSlot"
QT_MOC_LITERAL(9, 181, 14), // "QNetworkReply*"
QT_MOC_LITERAL(10, 196, 5), // "reply"
QT_MOC_LITERAL(11, 202, 11), // "balanceSlot"
QT_MOC_LITERAL(12, 214, 22), // "on_suljeButton_clicked"
QT_MOC_LITERAL(13, 237, 10), // "countMoney"
QT_MOC_LITERAL(14, 248, 7), // "balance"
QT_MOC_LITERAL(15, 256, 6) // "amount"

    },
    "nostoSummaWindow\0on_pushButton20e_clicked\0"
    "\0on_pushButton40e_clicked\0"
    "on_pushButton60e_clicked\0"
    "on_pushButton100e_clicked\0"
    "on_pushButton200e_clicked\0"
    "on_pushButton500e_clicked\0nostoSlot\0"
    "QNetworkReply*\0reply\0balanceSlot\0"
    "on_suljeButton_clicked\0countMoney\0"
    "balance\0amount"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_nostoSummaWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    1,   70,    2, 0x08 /* Private */,
      11,    1,   73,    2, 0x08 /* Private */,
      12,    0,   76,    2, 0x08 /* Private */,
      13,    2,   77,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double,   14,   15,

       0        // eod
};

void nostoSummaWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<nostoSummaWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton20e_clicked(); break;
        case 1: _t->on_pushButton40e_clicked(); break;
        case 2: _t->on_pushButton60e_clicked(); break;
        case 3: _t->on_pushButton100e_clicked(); break;
        case 4: _t->on_pushButton200e_clicked(); break;
        case 5: _t->on_pushButton500e_clicked(); break;
        case 6: _t->nostoSlot((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 7: _t->balanceSlot((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 8: _t->on_suljeButton_clicked(); break;
        case 9: _t->countMoney((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject nostoSummaWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_nostoSummaWindow.data,
    qt_meta_data_nostoSummaWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *nostoSummaWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *nostoSummaWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_nostoSummaWindow.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int nostoSummaWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
