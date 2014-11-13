#ifndef SAFPLUS7SCROLLEDWINDOW_H
#define SAFPLUS7SCROLLEDWINDOW_H

#include <wx/window.h>
#include <wx/scrolwin.h>
#include <wx/laywin.h>
#include <cairo.h>
#include <librsvg/rsvg.h>

class SAFplus7EditorPanel;

class SAFplus7ScrolledWindow : public wxScrolledWindow
{
    public:
        SAFplus7ScrolledWindow(wxWindow* parent, wxWindowID id);
        virtual ~SAFplus7ScrolledWindow();

        void paintEvent(wxPaintEvent &evt);
        void mouseMoved(wxMouseEvent &event);
        void mouseDown(wxMouseEvent &event);
        void mouseWheelMoved(wxMouseEvent& event);
        void mouseReleased(wxMouseEvent& event);
        void rightClick(wxMouseEvent& event);
        void mouseLeftWindow(wxMouseEvent& event);
        void keyPressed(wxKeyEvent& event);
        void keyReleased(wxKeyEvent& event);
        void OnSize(wxSizeEvent &evt);

        long cur_posx; //Get current posX
        long cur_posy; //Get current posY

        SAFplus7EditorPanel* m_parentPanel;
        bool m_isDirty;
        void cairoTestDraw(cairo_t *cr);

    protected:
        RsvgHandle* icon;
    private:
        DECLARE_EVENT_TABLE()
};

#endif // SAFPLUS7SCROLLEDWINDOW_H