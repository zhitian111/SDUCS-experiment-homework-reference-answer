/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MainWindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "on_login_push_button_clicked",
    "",
    "on_exist_push_button_clicked",
    "on_admin_function_1_button_clicked",
    "on_admin_function_2_button_clicked",
    "on_admin_function_3_button_clicked",
    "on_admin_function_4_button_clicked",
    "on_user_function_1_button_clicked",
    "on_user_function_2_button_clicked",
    "on_user_function_3_button_clicked",
    "on_user_function_4_button_clicked",
    "on_regist_push_button_clicked",
    "on_exit_user_clicked"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x09,    1 /* Protected */,
       3,    0,   87,    2, 0x09,    2 /* Protected */,
       4,    0,   88,    2, 0x09,    3 /* Protected */,
       5,    0,   89,    2, 0x09,    4 /* Protected */,
       6,    0,   90,    2, 0x09,    5 /* Protected */,
       7,    0,   91,    2, 0x09,    6 /* Protected */,
       8,    0,   92,    2, 0x09,    7 /* Protected */,
       9,    0,   93,    2, 0x09,    8 /* Protected */,
      10,    0,   94,    2, 0x09,    9 /* Protected */,
      11,    0,   95,    2, 0x09,   10 /* Protected */,
      12,    0,   96,    2, 0x09,   11 /* Protected */,
      13,    0,   97,    2, 0x09,   12 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'on_login_push_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_exist_push_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_admin_function_1_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_admin_function_2_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_admin_function_3_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_admin_function_4_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_user_function_1_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_user_function_2_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_user_function_3_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_user_function_4_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_regist_push_button_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_exit_user_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_login_push_button_clicked(); break;
        case 1: _t->on_exist_push_button_clicked(); break;
        case 2: _t->on_admin_function_1_button_clicked(); break;
        case 3: _t->on_admin_function_2_button_clicked(); break;
        case 4: _t->on_admin_function_3_button_clicked(); break;
        case 5: _t->on_admin_function_4_button_clicked(); break;
        case 6: _t->on_user_function_1_button_clicked(); break;
        case 7: _t->on_user_function_2_button_clicked(); break;
        case 8: _t->on_user_function_3_button_clicked(); break;
        case 9: _t->on_user_function_4_button_clicked(); break;
        case 10: _t->on_regist_push_button_clicked(); break;
        case 11: _t->on_exit_user_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
