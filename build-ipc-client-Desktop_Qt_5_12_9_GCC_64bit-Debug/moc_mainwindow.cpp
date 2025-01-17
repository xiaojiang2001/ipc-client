/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ipc-client/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[24];
    char stringdata0[330];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "addViewNum"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 5), // "index"
QT_MOC_LITERAL(4, 29, 11), // "pauseSignal"
QT_MOC_LITERAL(5, 41, 10), // "playSignal"
QT_MOC_LITERAL(6, 52, 12), // "recordSignal"
QT_MOC_LITERAL(7, 65, 4), // "flag"
QT_MOC_LITERAL(8, 70, 15), // "slotGetOneImage"
QT_MOC_LITERAL(9, 86, 3), // "idx"
QT_MOC_LITERAL(10, 90, 5), // "image"
QT_MOC_LITERAL(11, 96, 20), // "on_radioBtn1_clicked"
QT_MOC_LITERAL(12, 117, 20), // "on_radioBtn2_clicked"
QT_MOC_LITERAL(13, 138, 20), // "on_radioBtn3_clicked"
QT_MOC_LITERAL(14, 159, 20), // "on_radioBtn4_clicked"
QT_MOC_LITERAL(15, 180, 19), // "on_pauseBtn_clicked"
QT_MOC_LITERAL(16, 200, 20), // "on_replayBtn_clicked"
QT_MOC_LITERAL(17, 221, 19), // "on_photoBtn_clicked"
QT_MOC_LITERAL(18, 241, 19), // "on_startBtn_clicked"
QT_MOC_LITERAL(19, 261, 18), // "on_stopBtn_clicked"
QT_MOC_LITERAL(20, 280, 15), // "showContextMenu"
QT_MOC_LITERAL(21, 296, 3), // "pos"
QT_MOC_LITERAL(22, 300, 16), // "on_errorOccurred"
QT_MOC_LITERAL(23, 317, 12) // "errorMessage"

    },
    "MainWindow\0addViewNum\0\0index\0pauseSignal\0"
    "playSignal\0recordSignal\0flag\0"
    "slotGetOneImage\0idx\0image\0"
    "on_radioBtn1_clicked\0on_radioBtn2_clicked\0"
    "on_radioBtn3_clicked\0on_radioBtn4_clicked\0"
    "on_pauseBtn_clicked\0on_replayBtn_clicked\0"
    "on_photoBtn_clicked\0on_startBtn_clicked\0"
    "on_stopBtn_clicked\0showContextMenu\0"
    "pos\0on_errorOccurred\0errorMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    0,   97,    2, 0x06 /* Public */,
       5,    0,   98,    2, 0x06 /* Public */,
       6,    1,   99,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,  102,    2, 0x08 /* Private */,
      11,    0,  107,    2, 0x08 /* Private */,
      12,    0,  108,    2, 0x08 /* Private */,
      13,    0,  109,    2, 0x08 /* Private */,
      14,    0,  110,    2, 0x08 /* Private */,
      15,    0,  111,    2, 0x08 /* Private */,
      16,    0,  112,    2, 0x08 /* Private */,
      17,    0,  113,    2, 0x08 /* Private */,
      18,    0,  114,    2, 0x08 /* Private */,
      19,    0,  115,    2, 0x08 /* Private */,
      20,    1,  116,    2, 0x08 /* Private */,
      22,    1,  119,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QImage,    9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   21,
    QMetaType::Void, QMetaType::QString,   23,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addViewNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->pauseSignal(); break;
        case 2: _t->playSignal(); break;
        case 3: _t->recordSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slotGetOneImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QImage(*)>(_a[2]))); break;
        case 5: _t->on_radioBtn1_clicked(); break;
        case 6: _t->on_radioBtn2_clicked(); break;
        case 7: _t->on_radioBtn3_clicked(); break;
        case 8: _t->on_radioBtn4_clicked(); break;
        case 9: _t->on_pauseBtn_clicked(); break;
        case 10: _t->on_replayBtn_clicked(); break;
        case 11: _t->on_photoBtn_clicked(); break;
        case 12: _t->on_startBtn_clicked(); break;
        case 13: _t->on_stopBtn_clicked(); break;
        case 14: _t->showContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 15: _t->on_errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::addViewNum)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::pauseSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::playSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::recordSignal)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::addViewNum(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::pauseSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainWindow::playSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MainWindow::recordSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
