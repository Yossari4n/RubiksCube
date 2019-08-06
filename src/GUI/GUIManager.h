#ifndef GUIManager_h
#define GUIManager_h

#include "IWidget.h"

#include <vector>

class GUIManager {
public:

    void RegisterWidget(IWidget* widget);
    void UnregisterWidget(IWidget* widget);

private:
    std::vector<IWidget*> m_Widgets;
};

#endif