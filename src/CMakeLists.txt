
ENABLE_LANGUAGE(CXX)

SET(SRC_OBJS
     jsbsim.cpp
     main.cpp
     MainWindow.cpp
     viewer.cpp
     debugtable.cpp
     autopilot/PID_v1.cpp
     QFI/LayoutSquare.cpp
     QFI/qfi_PFD.cpp
     QFI/WidgetPFD.cpp
   )

SET(SRC_HDRS
     jsbsim.h
     MainWindow.h
     viewer.h
     debugtable.h
     QFI/LayoutSquare.h
     QFI/qfi_ADI.h
     QFI/qfi_PFD.h
     QFI/WidgetPFD.h
   )

SET(GUI_FILES
     MainWindow.ui
     viewer.ui
     debugtable.ui
     QFI/WidgetPFD.ui
   )

SET(RCS_FILES
     qtjsbsim.qrc
     icons.qrc
     hud.qrc
   )

QT5_WRAP_UI(UI_SRC ${GUI_FILES})
QT5_WRAP_CPP(MOC_SRC ${SRC_HDRS})
QT5_ADD_RESOURCES(RCC_SRC ${RCS_FILES})

ADD_EXECUTABLE( qtjsbsim ${SRC_OBJS} ${MOC_SRC} ${UI_SRC} ${RCC_SRC} )
TARGET_LINK_LIBRARIES( qtjsbsim ${PLIB_LIBRARIES} )
QT5_USE_MODULES(qtjsbsim Gui Network Svg WebKit WebKitWidgets)
