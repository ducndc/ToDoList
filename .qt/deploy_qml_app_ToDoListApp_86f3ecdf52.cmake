include("/home/ont/Documents/ToDoList/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/ToDoListApp-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase;qtdeclarative;qtdeclarative;qtdeclarative;qtdeclarative;qtdeclarative;qtdeclarative;qtdeclarative;qtdeclarative;qtdeclarative")

qt6_deploy_qml_imports(TARGET ToDoListApp PLUGINS_FOUND plugins_found)
qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/ont/Documents/ToDoList/ToDoListApp
    ADDITIONAL_MODULES ${plugins_found}
    GENERATE_QT_CONF
)