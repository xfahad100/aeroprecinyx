
ENABLE_LANGUAGE(CXX)

#Add qt-gui files
SET(SRC_OBJS
     jsbsim.cpp
     main.cpp
     MainWindow.cpp
     autopilot/PID_v1.cpp
     QFI/LayoutSquare.cpp
     QFI/qfi_PFD.cpp
     QFI/WidgetPFD.cpp
   )

SET(SRC_HDRS
     jsbsim.h
     MainWindow.h
     QFI/LayoutSquare.h
     QFI/qfi_ADI.h
     QFI/qfi_PFD.h
     QFI/WidgetPFD.h
   )

# Generate QT Files
SET(GUI_FILES
     MainWindow.ui
     QFI/WidgetPFD.ui
   )

SET(RCS_FILES
     qtjsbsim.qrc
   )

QT4_WRAP_UI(UI_SRC ${GUI_FILES})
QT4_WRAP_CPP(MOC_SRC ${SRC_HDRS})
QT4_ADD_RESOURCES(RCC_SRC ${RCS_FILES})

ADD_EXECUTABLE( qtjsbsim ${SRC_OBJS} ${MOC_SRC} ${UI_SRC} ${RCC_SRC} )
TARGET_LINK_LIBRARIES( qtjsbsim ${QT_LIBRARIES} ${PLIB_LIBRARIES} )
