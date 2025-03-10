/**
 * @file MainFrame.h
 * @author Charles B. Owen
 *
 * The top-level (main) frame of the application
 */
#ifndef _MAINFRAME_H_
#define _MAINFRAME_H_

class ViewEdit;
class ViewTimeline;
class Picture;
class IMachineSystem;

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
    /// View class for our edit window
    ViewEdit *mViewEdit;

    /// View class for the timeline
    ViewTimeline *mViewTimeline;

    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &);
    void OnClose(wxCloseEvent &event);

    /// The resources directory to use
    std::wstring mResourcesDir;

    /// The picture object we are viewing/editing
    std::shared_ptr<Picture> mPicture;

public:
    MainFrame(std::wstring resourcesDir);

    void Initialize();
};

#endif //_MAINFRAME_H_
