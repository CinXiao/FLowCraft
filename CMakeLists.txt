cmake_minimum_required(VERSION 3.5)

project(FlowCraft VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)

set(PROJECT_SOURCES

        testwidget.cpp
        testwidget.h

        #Main File
            main.cpp

    ##Graphics
            #view
            Graphics/GraphicsView/Graphicsview.h
            Graphics/GraphicsView/Graphicsview.cpp

            #Entity
            Graphics/Entity/RubberEntity.h
            Graphics/Entity/RubberEntity.cpp

            #Item
            Graphics/GraphicsItem/GraphicsItem.h
            Graphics/GraphicsItem/GraphicsItem.cpp

            Graphics/GraphicsItem/GraphicsNode.h
            Graphics/GraphicsItem/GraphicsNode.cpp

            Graphics/GraphicsItem/GraphicsPort.h
            Graphics/GraphicsItem/GraphicsPort.cpp

            Graphics/GraphicsItem/GraphicsChart.h
            Graphics/GraphicsItem/GraphicsChart.cpp

            Graphics/GraphicsItem/GraphicsGroup.h
            Graphics/GraphicsItem/GraphicsGroup.cpp

            Graphics/GraphicsItem/GraphicsPreviewItem.h
            Graphics/GraphicsItem/GraphicsPreviewItem.cpp

            Graphics/GraphicsItem/GraphicsText.h
            Graphics/GraphicsItem/GraphicsText.cpp

            Graphics/GraphicsItem/GraphicsButton.h
            Graphics/GraphicsItem/GraphicsButton.cpp

            Graphics/GraphicsItem/GraphicsSwitchButton.h
            Graphics/GraphicsItem/GraphicsSwitchButton.cpp

            Graphics/GraphicsItem/GraphicsTip.h
            Graphics/GraphicsItem/GraphicsTip.cpp

            Graphics/GraphicsItem/GraphicsPictureBox.h
            Graphics/GraphicsItem/GraphicsPictureBox.cpp

            Graphics/GraphicsItem/GraphicsLable.h
            Graphics/GraphicsItem/GraphicsLable.cpp

            #Info
            Graphics/Info/ItemInfo.h
            Graphics/Info/ItemInfo.cpp

            Graphics/Info/GroupInfo.h
            Graphics/Info/GroupInfo.cpp

            Graphics/Info/NodeInfo.h
            Graphics/Info/NodeInfo.cpp

            Graphics/Info/PortInfo.h
            Graphics/Info/PortInfo.cpp

            Graphics/Info/ChartInfo.h
            Graphics/Info/ChartInfo.cpp

            Graphics/Info/LineInfo.h
            Graphics/Info/LineInfo.cpp

            Graphics/Info/TextInfo.h
            Graphics/Info/TextInfo.cpp

            Graphics/Info/ButtonInfo.h
            Graphics/Info/ButtonInfo.cpp

            Graphics/Info/SwitchButtonInfo.h
            Graphics/Info/SwitchButtonInfo.cpp

            Graphics/Info/PictureBoxInfo.h
            Graphics/Info/PictureBoxInfo.cpp

            Graphics/Info/LabelInfo.h
            Graphics/Info/LabelInfo.cpp

            #Line
            Graphics/GraphicsLine/GraphicsLineItem.h
            Graphics/GraphicsLine/GraphicsLineItem.cpp

            Graphics/GraphicsLine/GraphicsLineItemBeziercurveitem.h
            Graphics/GraphicsLine/GraphicsLineItemBeziercurveitem.cpp

            Graphics/GraphicsLine/GraphicsRubberLine.h
            Graphics/GraphicsLine/GraphicsRubberLine.cpp

    ##Common

        #Factory
        Common/GraphicsFactory/GraphicsFactory.h
        Common/GraphicsFactory/GraphicsFactory.cpp

        Common/GraphicsFactory/GraphicsNodeFactory.h
        Common/GraphicsFactory/GraphicsNodeFactory.cpp

        Common/GraphicsFactory/GraphicsPortFactory.h
        Common/GraphicsFactory/GraphicsPortFactory.cpp

        Common/GraphicsFactory/GraphicsTextFactory.h
        Common/GraphicsFactory/GraphicsTextFactory.cpp

        Common/GraphicsFactory/GraphicsChartFactory.h
        Common/GraphicsFactory/GraphicsChartFactory.cpp

        Common/GraphicsFactory/GraphicsSwitchButtonFactory.h
        Common/GraphicsFactory/GraphicsSwitchButtonFactory.cpp

        Common/GraphicsFactory/GraphicsButtonFactory.h
        Common/GraphicsFactory/GraphicsButtonFactory.cpp

        Common/GraphicsFactory/GraphicsPictureBoxFactory.cpp
        Common/GraphicsFactory/GraphicsPictureBoxFactory.h

        Common/GraphicsFactory/GraphicsLabelFactory.cpp
        Common/GraphicsFactory/GraphicsLabelFactory.h
    ##Entity
          Entity/GraphicsItemInfoConfig.h
          Entity/GraphicsItemInfoConfig.cpp

          Entity/GraphicsNodeControlBlock.h
          Entity/GraphicsNodeControlBlock.cpp

          Entity/GraphicsNodeConnectionControlBlock.h
          Entity/GraphicsNodeConnectionControlBlock.cpp


    ##Utility
       Utility/JsonUtility/JsonUtility.h
       Utility/JsonUtility/JsonUtility.cpp


       Utility/InterpreterUtility/Interpreter.h
       Utility/InterpreterUtility/Interpreter.cpp
    ##Globe
       Globe/DataType.h

       Globe/Enum.h

       Globe/Map.h

       Globe/GraphicsItemCreator.h
       Globe/GraphicsItemCreator.cpp

       Globe/GraphicsItemManager.h
       Globe/GraphicsItemManager.cpp

       Globe/BuiltRunManager.h
       Globe/BuiltRunManager.cpp

       Globe/RuningConfig.h
       Globe/RuningConfig.cpp

       Globe/PortAssignor.h
       Globe/PortAssignor.cpp

       Globe/AudioPlayer.h
       Globe/AudioPlayer.cpp

       Globe/Saver.h
       Globe/Saver.cpp

       Globe/Loader.h
       Globe/Loader.cpp

       
        Globe/GraphicsItemParser.h
        Globe/GraphicsItemParser.cpp
    ##Script
       Script/ScriptObject.h
       Script/ScriptObject.cpp

       Script/CodeLine.h


       Script/Handle/ExpressionParser.h
       Script/Handle/ExpressionParser.cpp

       Script/Handle/Functions/ChartFunction.h
       Script/Handle/Functions/MathFunction.h
       Script/Handle/Functions/NetWorkFunction.h
    ##Resource
        Resource/Resource.qrc

    ##UI

        UI/Editor/MainWindow.h
        UI/Editor/MainWindow.cpp
        UI/Editor/MainWindow.ui



        UI/Launcher/Launcher.h
        UI/Launcher/Launcher.cpp
        UI/Launcher/Launcher.ui

        UI/Launcher/CreatNewProject.h
        UI/Launcher/CreatNewProject.cpp
        UI/Launcher/CreatNewProject.ui

        UI/Widgets/NodeTreeWidget.h
        UI/Widgets/NodeTreeWidget.cpp

        UI/Widgets/CodeEditor/CodeEditor.h
        UI/Widgets/CodeEditor/CodeEditor.cpp

        UI/Widgets/CodeEditor/Highlighter.h
        UI/Widgets/CodeEditor/Highlighter.cpp
        ##ToolWIdget
        UI/Widgets/ToolWidget/nodeeditorwidget.h
        UI/Widgets/ToolWidget/nodeeditorwidget.cpp
        UI/Widgets/ToolWidget/nodeeditorwidget.ui

        UI/Widgets/ToolWidget/SettingWidget.h
        UI/Widgets/ToolWidget/SettingWidget.cpp
        UI/Widgets/ToolWidget/SettingWidget.ui


        UI/Widgets/ToolWidget/TemplateItemWidget.h
        UI/Widgets/ToolWidget/TemplateItemWidget.cpp
        UI/Widgets/ToolWidget/TemplateItemWidget.ui

        UI/Widgets/ToolWidget/ProjectItem.h
        UI/Widgets/ToolWidget/ProjectItem.cpp
        UI/Widgets/ToolWidget/ProjectItem.ui


    #qtpropertybrowser
        qtpropertybrowser/qtbuttonpropertybrowser.h
        qtpropertybrowser/qtbuttonpropertybrowser.cpp

        qtpropertybrowser/qteditorfactory.h
        qtpropertybrowser/qteditorfactory.cpp

        qtpropertybrowser/qtgroupboxpropertybrowser.h
        qtpropertybrowser/qtgroupboxpropertybrowser.cpp

        qtpropertybrowser/qtpropertybrowser.h
        qtpropertybrowser/qtpropertybrowser.cpp

        qtpropertybrowser/qtpropertybrowserutils_p.h
        qtpropertybrowser/qtpropertybrowserutils.cpp

        qtpropertybrowser/qtpropertymanager.h
        qtpropertybrowser/qtpropertymanager.cpp


        qtpropertybrowser/qttreepropertybrowser.h
        qtpropertybrowser/qttreepropertybrowser.cpp

        qtpropertybrowser/qtvariantproperty.cpp
        qtpropertybrowser/qtvariantproperty.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(FlowCraft
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET FlowCraft APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(FlowCraft SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(FlowCraft
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(FlowCraft PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(FlowCraft PRIVATE Qt6::Multimedia)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.FlowCraft)
endif()
set_target_properties(FlowCraft PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS FlowCraft
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(FlowCraft)
endif()
