/**
 * @file ViewTimeline.cpp
 * @author Charles B. Owen
 * @author Ricardo Paz
 */

#include "pch.h"

#include <wx/dcbuffer.h>
#include <wx/xrc/xmlres.h>
#include <sstream>
#include <wx/stdpaths.h>
#include <memory>

#include "ViewTimeline.h"
#include "Picture.h"
#include "TimelineDlg.h"
#include "Actor.h"



/// Y location for the top of a tick mark
const int TickTop = 15;

/// The spacing between ticks in the timeline
const int TickSpacing = 4;

/// The length of a short tick mark
const int TickShort = 10;

/// The length of a long tick mark
const int TickLong = 20;

/// Size of the tick mark labels
const int TickFontSize = 15;

/// Space to the left of the scale
const int BorderLeft = 10;

/// Space to the right of the scale
const int BorderRight = 10;

/// Filename for the pointer image
const std::wstring PointerImageFile = L"/pointer.png";



/**
 *  * Constructor
 * @param parent The main wxFrame object
 * @param imagesDir
 */
ViewTimeline::ViewTimeline(wxFrame* parent, std::wstring imagesDir) :
    wxScrolledCanvas(parent,
            wxID_ANY,
            wxDefaultPosition,
            wxSize(100, Height),
            wxBORDER_SIMPLE), mImagesDir(imagesDir)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &ViewTimeline::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &ViewTimeline::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &ViewTimeline::OnLeftUp, this);
    Bind(wxEVT_MOTION, &ViewTimeline::OnMouseMove, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ViewTimeline::OnEditTimelineProperties, this,
            XRCID("EditTimelineProperties"));

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnSetKeyframe, this, XRCID("SetKeyframe"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnDeleteKeyframe, this, XRCID("DeleteKeyframe"));


    mPointerImage = std::make_unique<wxImage>(mImagesDir + PointerImageFile, wxBITMAP_TYPE_ANY);
}


/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void ViewTimeline::OnPaint(wxPaintEvent& event)
{
    // Gets scrolling dimensions
    auto size = GetPicture()->GetSize();
    int numFrames = GetPicture()->GetTimeline()->GetNumFrames();
    int frameRate = GetPicture()->GetTimeline()->GetFrameRate();

    double width = BorderLeft + BorderRight + (numFrames * TickSpacing);

    SetVirtualSize(width, size.GetHeight());
    SetScrollRate(1, 0);

    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

    wxPen pen(*wxBLACK);
    graphics->SetPen(pen);

    wxFont font(wxSize(TickFontSize, TickFontSize),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxBLACK);


    for(int i = 0; i<numFrames; i++ )
    {
        int leftBorder = BorderLeft + TickSpacing * i;
        if(i % frameRate == 0)
        {
            graphics->StrokeLine(leftBorder, TickTop, leftBorder, TickTop + TickLong);
            // Convert the tick number to seconds in a string
            std::wstringstream str;
            str << i / frameRate;
            std::wstring wstr = str.str();

            double w;
            double h;
            graphics->GetTextExtent(wstr, &w, &h);
            graphics->DrawText(wstr, leftBorder - w/2, TickTop + TickLong);
        } else {
            graphics->StrokeLine(leftBorder, TickTop, leftBorder, TickTop + TickShort);
        }
    }

    DrawPointer(graphics);

}

/**
 * Handle the left mouse button down event
 * @param event
 */
void ViewTimeline::OnLeftDown(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    int x = click.x;

    // Get the timeline
    Timeline *timeline = GetPicture()->GetTimeline();
    int pointerX = (int)(timeline->GetCurrentTime() *
            timeline->GetFrameRate() * TickSpacing + BorderLeft);

    mMovingPointer = x >= pointerX - mPointerImage->GetWidth() / 2 &&
            x <= pointerX + mPointerImage->GetWidth() / 2;
}

/**
* Handle the left mouse button up event
* @param event
*/
void ViewTimeline::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
    mMovingPointer = false;
}

/**
* Handle the mouse move event
* @param event
*/
void ViewTimeline::OnMouseMove(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());
    int posx = click.x;
    posx = posx - BorderLeft;

    Timeline *timeline = GetPicture()->GetTimeline();
    int numFrames = timeline->GetNumFrames();
    int frameRate = timeline->GetFrameRate();
    double totalTime = (double)(numFrames/frameRate);
    double spacing = TickSpacing * frameRate;
    mTime = (double)(posx/spacing);

    if(mTime < 0)
    {
        GetPicture()->SetAnimationTime(0);
        GetPicture()->UpdateObservers();
    }
    else if(mTime > totalTime)
    {
        GetPicture()->SetAnimationTime(totalTime);
        GetPicture()->UpdateObservers();
    }
    else if(mMovingPointer)
    {
        GetPicture()->SetAnimationTime(mTime);
        GetPicture()->UpdateObservers();
    }

}

/**
 * Force an update of this window when the picture changes.
 */
void ViewTimeline::UpdateObserver()
{
    Refresh();
    Update();
}

/**
 * Handle an Edit>Timeline Properties... menu option
 * @param event The menu event
 */
void ViewTimeline::OnEditTimelineProperties(wxCommandEvent& event)
{
    TimelineDlg dlg(this->GetParent(), GetPicture()->GetTimeline());
    if(dlg.ShowModal() == wxID_OK)
    {
        // The dialog box has changed the Timeline settings
        GetPicture()->UpdateObservers();
    }
}

/**
 * Draws the pointer on the timeline
 * @param graphics
 */
void ViewTimeline::DrawPointer(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(mPointerBitmap.IsNull())
    {
        mPointerBitmap = graphics->CreateBitmapFromImage(*mPointerImage);
    }
    int curFrame = GetPicture()->GetTimeline()->GetCurrentFrame();
    auto spacing = TickSpacing * curFrame;
    int x = (BorderLeft/2) + spacing;
    int y = TickTop;

    graphics->PushState();
    graphics->DrawBitmap(mPointerBitmap,
            x, y,
            mPointerImage->GetWidth(),
            mPointerImage->GetHeight());

    graphics->PopState();
}

/**
 * Changed the mode to rotate
 * @param event
 */
void ViewTimeline::OnSetKeyframe(wxCommandEvent& event)
{
    auto picture = GetPicture();
    for (auto actor : *picture)
    {
        actor->SetKeyframe();
    }
}

/**
 * Changed the mode to rotate
 * @param event
 */
void ViewTimeline::OnDeleteKeyframe(wxCommandEvent& event)
{
    auto picture = GetPicture();

    for (auto actor : *picture)
    {
        actor->DeleteKeyframe();
    }

    picture->SetAnimationTime(mTime);
    picture->UpdateObservers();
}