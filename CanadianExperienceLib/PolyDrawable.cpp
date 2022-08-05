/**
 * @file PolyDrawable.cpp
 * @author Ricardo Paz
 */

#include "pch.h"
#include "PolyDrawable.h"

/**
 * Constructor
 * @param name The drawable name
 */
PolyDrawable::PolyDrawable(const std::wstring &name) : Drawable(name)
{
}

/**
 * Draw the polydrawable
 * @param graphics Graphics context to draw on
 */
void PolyDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(!mPoints.empty()) {

        mPath = graphics->CreatePath();
        mPath.MoveToPoint(RotatePoint(mPoints[0], mPlacedR) + mPlacedPosition);
        for (auto i = 1; i<mPoints.size(); i++)
        {
            mPath.AddLineToPoint(RotatePoint(mPoints[i], mPlacedR) + mPlacedPosition);
        }
        mPath.CloseSubpath();

        wxBrush brush(mColor);
        graphics->SetBrush(brush);
        graphics->FillPath(mPath);
    }
}

/**
 * Test to see if we clicked on the polygon.
 * @param point Position to test
 * @return True if clicked on
 */
bool PolyDrawable::HitTest(wxPoint point)
{
    return mPath.Contains(point.x, point.y);
}

/**
 * Adds a point to the polygon
 * @param point
 */
void PolyDrawable::AddPoint(wxPoint point)
{
    mPoints.push_back(point);
}