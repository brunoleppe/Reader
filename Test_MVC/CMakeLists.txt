add_library(MVC
#        Figures/Figure.cpp
#        Figures/Figure.h
#        Figures/Label.cpp
#        Figures/Label.h
#        Figures/Drawable.h
#        Figures/Composite.h
#        Figures/Box.cpp
#        Figures/Box.h
#        Figures/TextBox.cpp
#        Figures/TextBox.h
#        Figures/Window.h
#        Figures/MenuWindow.cpp
#        Figures/MenuWindow.h
#        Figures/make_unique.h
#        Figures/ItemBox.cpp
#        Figures/ItemBox.h

        Input/input_cpp.h
        Input/input.cpp
        DataTypes/ControllerInputEvent.h
        DataTypes/Item.cpp
        DataTypes/Item.h
        DataTypes/Observer.h
        DataTypes/ItemList.cpp
        DataTypes/ItemList.h
        DataTypes/LabelItem.cpp
        DataTypes/LabelItem.h
        DataTypes/Bitmap.h
        DataTypes/BitmapItem.cpp
        DataTypes/BitmapItem.h
        DataTypes/ItemList.cpp
        DataTypes/LogoItem.cpp
        DataTypes/LogoItem.h
        DataTypes/string.h
        DataTypes/vector.h
        DataTypes/queue.h
        DataTypes/list.h

        InputController.h
        InputController.cpp
        TestStateMachine.h
        TestStateMachine.cpp
        Factory.h

        MVC/States/StateMachine.h
        MVC/States/StateLogo.h
        MVC/Process/StateMainLogo.cpp
        MVC/Process/StateMainLogo.h
        MVC/States/StateMenu.h
        MVC/Process/StateTransactionTypeMenu.cpp
        MVC/Process/StateTransactionTypeMenu.h
        MVC/States/StateInput.h
        MVC/ViewModels/InputViewModel.h
        MVC/Process/StateInputTest1.cpp
        MVC/Process/StateInputTest1.h
        MVC/Process/StateInputTest2.cpp
        MVC/Process/StateInputTest2.h
        MVC/ViewModels/LogoViewModel.h
        MVC/ViewModels/ViewModel.h
        MVC/Views/LogoView.h
        MVC/Views/InputView.h
        MVC/Views/View.h
        )