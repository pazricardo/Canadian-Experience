/**
 * @file HeadTop.cpp
 * @author Ricardo Paz
 */

#include "pch.h"
#include "HeadTop.h"
#include "Timeline.h"

/**
 * Constructor
 * @param name
 * @param filename
 */
HeadTop::HeadTop(const std::wstring &name, const std::wstring &filename) : ImageDrawable(name, filename)
{

}

/**
 * Draw the image drawable
 * @param graphics Graphics context to draw on
 */
void HeadTop::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    ImageDrawable::Draw(graphics);

    if(mIsHarold)
    {
        Face(graphics);
    }


}

/** Transform a point from a location on the bitmap to
*  a location on the screen.
* @param  p Point to transform
* @returns Transformed point
*/
wxPoint HeadTop::TransformPoint(wxPoint p)
{
    // Make p relative to the image center
    p = p - GetCenter();

    // Rotate as needed and offset
    return RotatePoint(p, mPlacedR) + mPlacedPosition;
}

/**
 * Creates the face for Harold
 * @param graphics Graphics object to draw on
 */
void HeadTop::Face(std::shared_ptr<wxGraphicsContext> graphics)
{
    wxPen pen(*wxBLACK, 3);
    graphics->SetPen(pen);

    graphics->PushState();
    // Eyebrows
    wxPoint p = TransformPoint(wxPoint(25, 60));
    wxPoint p2 = TransformPoint(wxPoint(45, 60));
    wxPoint p3 = TransformPoint(wxPoint(65, 60));
    wxPoint p4 = TransformPoint(wxPoint(85, 60));


    // Left eyebrow
    graphics->StrokeLine(p.x, p.y, p2.x, p2.y);
    // Right eyebrow
    graphics->StrokeLine(p3.x, p3.y, p4.x, p4.y);
    graphics->PopState();


    // Eyes
    wxPoint e1 = TransformPoint(wxPoint(35, 75));
    wxPoint e2 = wxPoint(40, 0);

    float wid = 15.0f;
    float hit = 20.0f;

    auto path = graphics->CreatePath();
    auto path2 = graphics->CreatePath();
    graphics->PushState();
    wxBrush brush = wxBrush(*wxWHITE);
    graphics->SetBrush(brush);

    // Left Eye
    graphics->Translate(e1.x, e1.y);
    graphics->Rotate(-mPlacedR);
    graphics->DrawEllipse(-wid/2, -hit/2, wid, hit);
    path.AddEllipse(-wid/2, -hit/2, wid, hit);
    graphics->FillPath(path);

    // Right Eye
    graphics->Translate(e2.x, e2.y);
    graphics->DrawEllipse(-wid/2, -hit/2, wid, hit);
    path2.AddEllipse(-wid/2, -hit/2, wid, hit);
    graphics->FillPath(path2);

    graphics->PopState();
}

/**
 * Sets the keyframe for the position of the head
 */
void HeadTop::SetKeyframe()
{
    Drawable::SetKeyframe();
    mChannel.SetKeyframe(GetPosition());

}

/**
 * Gets the Keyframe for the headtop
 */
void HeadTop::GetKeyframe()
{
    Drawable::GetKeyframe();
    if (mChannel.IsValid())
    {
        SetPosition(mChannel.GetPoint());
    }
}


/**
 * Sets the timeline the headtop is a part of
 * @param timeline
 */
void HeadTop::SetTimeline(Timeline* timeline)
{
    Drawable::SetTimeline(timeline);
    timeline->AddChannel(&mChannel);
}
