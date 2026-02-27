#include"Application.h"

namespace eng
{
    void Application::RegisterTypes()
    {
     
    }
    void Application::SetNeedsToBeClosed(bool value)
    {
        m_needsTobeClosed = value;

    }
    bool Application::NeedToBeClosed() const
    {
        return m_needsTobeClosed;
    }
}