#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>
#include <QtCore/qhash.h>
#include <QtCore/qstring.h>

namespace QmlCacheGeneratedCode {
namespace _qt_qml_CustomControls_AmPmButton_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_CustomControls_CustomButton_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_CustomControls_CustomLabel_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_CustomControls_CustomTextArea_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_CustomControls_CustomTextField_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_CustomControls_SwipeDelegateContent_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_CustomControls_TasksListDelegate_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_CustomControls_TimeInput_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_CustomControls_TimeTextField_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/CustomControls/AmPmButton.qml"), &QmlCacheGeneratedCode::_qt_qml_CustomControls_AmPmButton_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/CustomControls/CustomButton.qml"), &QmlCacheGeneratedCode::_qt_qml_CustomControls_CustomButton_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/CustomControls/CustomLabel.qml"), &QmlCacheGeneratedCode::_qt_qml_CustomControls_CustomLabel_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/CustomControls/CustomTextArea.qml"), &QmlCacheGeneratedCode::_qt_qml_CustomControls_CustomTextArea_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/CustomControls/CustomTextField.qml"), &QmlCacheGeneratedCode::_qt_qml_CustomControls_CustomTextField_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/CustomControls/SwipeDelegateContent.qml"), &QmlCacheGeneratedCode::_qt_qml_CustomControls_SwipeDelegateContent_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/CustomControls/TasksListDelegate.qml"), &QmlCacheGeneratedCode::_qt_qml_CustomControls_TasksListDelegate_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/CustomControls/TimeInput.qml"), &QmlCacheGeneratedCode::_qt_qml_CustomControls_TimeInput_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/CustomControls/TimeTextField.qml"), &QmlCacheGeneratedCode::_qt_qml_CustomControls_TimeTextField_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.structVersion = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qmlcache_CustomControls)() {
    ::unitRegistry();
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qmlcache_CustomControls))
int QT_MANGLE_NAMESPACE(qCleanupResources_qmlcache_CustomControls)() {
    return 1;
}
