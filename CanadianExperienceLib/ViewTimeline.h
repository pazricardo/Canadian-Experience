/**
 * @file ViewTimeline.h
 * @author Charles B. Owen
 * @author Ricardo Paz
 *
 * View class for the timeline area of the screen.
 */

#ifndef CANADIANEXPERIENCE_VIEWTIMELINE_H
#define CANADIANEXPERIENCE_VIEWTIMELINE_H

#include <wx/graphics.h>
#include "PictureObserver.h"


/**
 * View class for the timeline area of the screen.
 */
class ViewTimeline final : public wxScrolledCanvas, public PictureObserver {
private:
    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnPaint(wxPaintEvent& event);
    void OnEditTimelineProperties(wxCommandEvent& event);
    void OnSetKeyframe(wxCommandEvent& event);
    void OnDeleteKeyframe(wxCommandEvent& event);

    /// Bitmap image for the pointer
    std::unique_ptr<wxImage> mPointerImage;

    /// Graphics bitmap to display
    wxGraphicsBitmap mPointerBitmap;

    /// The path to the image directory
    std::wstring mImagesDir;

    /// Flag to indicate we are moving the pointer
    bool mMovingPointer = false;

    /// Time where the pointer is at
    double mTime;

public:
    static const int Height = 90;      ///< Height to make this window

    ViewTimeline(wxFrame* parent, std::wstring imageDir);
    void UpdateObserver() override;

    void DrawPointer(std::shared_ptr<wxGraphicsContext> graphics);
};


#endif //CANADIANEXPERIENCE_VIEWTIMELINE_H
