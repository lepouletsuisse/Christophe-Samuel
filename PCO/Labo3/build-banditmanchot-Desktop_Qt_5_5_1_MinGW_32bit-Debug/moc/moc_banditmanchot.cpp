/****************************************************************************
** Meta object code from reading C++ file 'banditmanchot.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ressources/banditmanchot.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'banditmanchot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BanditManchot_t {
    QByteArrayData data[16];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BanditManchot_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BanditManchot_t qt_meta_stringdata_BanditManchot = {
    {
QT_MOC_LITERAL(0, 0, 13), // "BanditManchot"
QT_MOC_LITERAL(1, 14, 13), // "keyPressEvent"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 10), // "QKeyEvent*"
QT_MOC_LITERAL(4, 40, 5), // "event"
QT_MOC_LITERAL(5, 46, 4), // "clef"
QT_MOC_LITERAL(6, 51, 4), // "stop"
QT_MOC_LITERAL(7, 56, 5), // "piece"
QT_MOC_LITERAL(8, 62, 6), // "vandal"
QT_MOC_LITERAL(9, 69, 8), // "setValue"
QT_MOC_LITERAL(10, 78, 1), // "n"
QT_MOC_LITERAL(11, 80, 5), // "value"
QT_MOC_LITERAL(12, 86, 10), // "setMessage"
QT_MOC_LITERAL(13, 97, 4), // "mess"
QT_MOC_LITERAL(14, 102, 10), // "setJackpot"
QT_MOC_LITERAL(15, 113, 7) // "jackpot"

    },
    "BanditManchot\0keyPressEvent\0\0QKeyEvent*\0"
    "event\0clef\0stop\0piece\0vandal\0setValue\0"
    "n\0value\0setMessage\0mess\0setJackpot\0"
    "jackpot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BanditManchot[] = {

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
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    2,   61,    2, 0x0a /* Public */,
      12,    1,   66,    2, 0x0a /* Public */,
      14,    1,   69,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::Int,   15,

       0        // eod
};

void BanditManchot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BanditManchot *_t = static_cast<BanditManchot *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 1: _t->clef(); break;
        case 2: _t->stop(); break;
        case 3: _t->piece(); break;
        case 4: _t->vandal(); break;
        case 5: _t->setValue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->setMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->setJackpot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject BanditManchot::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BanditManchot.data,
      qt_meta_data_BanditManchot,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BanditManchot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BanditManchot::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BanditManchot.stringdata0))
        return static_cast<void*>(const_cast< BanditManchot*>(this));
    return QDialog::qt_metacast(_clname);
}

int BanditManchot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_Sender_t {
    QByteArrayData data[9];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Sender_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Sender_t qt_meta_stringdata_Sender = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Sender"
QT_MOC_LITERAL(1, 7, 12), // "sig_setValue"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 1), // "n"
QT_MOC_LITERAL(4, 23, 5), // "value"
QT_MOC_LITERAL(5, 29, 14), // "sig_setMessage"
QT_MOC_LITERAL(6, 44, 4), // "mess"
QT_MOC_LITERAL(7, 49, 14), // "sig_setJackpot"
QT_MOC_LITERAL(8, 64, 7) // "jackpot"

    },
    "Sender\0sig_setValue\0\0n\0value\0"
    "sig_setMessage\0mess\0sig_setJackpot\0"
    "jackpot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Sender[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       5,    1,   34,    2, 0x06 /* Public */,
       7,    1,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void Sender::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Sender *_t = static_cast<Sender *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_setValue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->sig_setMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->sig_setJackpot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Sender::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Sender::sig_setValue)) {
                *result = 0;
            }
        }
        {
            typedef void (Sender::*_t)(const QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Sender::sig_setMessage)) {
                *result = 1;
            }
        }
        {
            typedef void (Sender::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Sender::sig_setJackpot)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject Sender::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Sender.data,
      qt_meta_data_Sender,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Sender::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Sender::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Sender.stringdata0))
        return static_cast<void*>(const_cast< Sender*>(this));
    return QObject::qt_metacast(_clname);
}

int Sender::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Sender::sig_setValue(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Sender::sig_setMessage(const QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Sender::sig_setJackpot(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
