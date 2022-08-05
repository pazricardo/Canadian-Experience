/**
 * @file TimelineDlg.h
 * @author Ricardo Paz
 *
 *
 */

#ifndef CANADIANEXPERIENCE_TIMELINEDLG_H
#define CANADIANEXPERIENCE_TIMELINEDLG_H

class Timeline;

/**
 * Timeline dialog box
 */
class TimelineDlg final : public wxDialog {
private:
    /// Timeline the Dlg is a part of
    Timeline* mTimeline;

    /// Number of frames in the animation
    int mNumberOfFrames;

    /// Frame Rate in the animation
    int mFrameRate;

    void OnOK(wxCommandEvent& event);


public:
    TimelineDlg(wxWindow* parent, Timeline* timeline);

};

#endif //CANADIANEXPERIENCE_TIMELINEDLG_H
