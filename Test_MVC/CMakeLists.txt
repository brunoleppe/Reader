add_library(MVC
        Figures/Figure.cpp Figures/Figure.h
        Figures/Label.cpp Figures/Label.h
        Figures/Drawable.h
        Figures/Composite.h
        Figures/Box.cpp Figures/Box.h
        Figures/TextBox.cpp Figures/TextBox.h
        Figures/Window.h
        Figures/MenuWindow.cpp Figures/MenuWindow.h
        Figures/ItemBox.cpp Figures/ItemBox.h
        Input/input_cpp.h Input/input.cpp
        MVC/Controller.cpp MVC/Controller.h
        MVC/Model.cpp MVC/Model.h
        MVC/Views/View.h
        MVC/ModelStateService.h
        MVC/MessagePacket.h
        MVC/Views/ViewService.h
        MVC/Views/View.cpp
        MVC/ControllerInputEvent.h
        DataTypes/Item.cpp
        DataTypes/Item.h
        DataTypes/Observer.h
        MVC/Views/ViewService.cpp
        MVC/Views/ViewService.cpp
        DataTypes/ItemList.cpp
        DataTypes/ItemList.h
        DataTypes/LabelItem.cpp
        DataTypes/LabelItem.h
        DataTypes/Bitmap.cpp
        DataTypes/Bitmap.h
        DataTypes/BitmapItem.cpp
        DataTypes/BitmapItem.h
        DataTypes/ItemList.cpp
        MVC/Views/MenuView.cpp
        MVC/Views/MenuView.h
        MVC/Views/LogoView.cpp
        MVC/Views/LogoView.h
        DataTypes/LogoItem.cpp
        DataTypes/LogoItem.h
        DataTypes/StateMachine.h
        InputController.h
        InputController.cpp
        TestStateMachine.h
        TestStateMachine.cpp
        MVC/States/StateTest.h
        MVC/States/StateMenu.h
        MVC/States/StateMenu.cpp
        MVC/States/StateTest.cpp

        MVC/States/StateItems.cpp MVC/States/StateItems.h MVC/States/StateLogos.cpp MVC/States/StateLogos.h)