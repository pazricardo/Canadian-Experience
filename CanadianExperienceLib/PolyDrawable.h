/**
 * @file PolyDrawable.h
 * @author Ricardo Paz
 *
 *
 */

#ifndef CANADIANEXPERIENCE_POLYDRAWABLE_H
#define CANADIANEXPERIENCE_POLYDRAWABLE_H

#include "Drawable.h"

/**
 * A drawable based on polygon images.
 *
 * This class has a list of points and draws a polygon
 * drawable based on those points.
 */
class PolyDrawable : public Drawable{
private:
    /// The polygon color
    wxColour mColor = *wxBLACK;
    /// The array of point objects
    std::vector<wxPoint> mPoints;
    /// Path from the graphics context
    wxGraphicsPath mPath;

public:
    /// Constructor (disabled)
    PolyDrawable() = delete;
    /// Destructor
    virtual ~PolyDrawable() {};
    /// Copy Constructor (Disabled)
    PolyDrawable(const PolyDrawable &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const PolyDrawable &) = delete;

    PolyDrawable(const std::wstring &name);

    /**
     * Gets the color of the polygon
     * @return
     */
    const wxColour& GetColor() const {return mColor;}

    /**
     * Sets the color of the polygon
     * @param color
     */
    void SetColor(wxColour& color) {mColor = color;}

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(wxPoint point) override;
    void AddPoint(wxPoint point);
};

#endif //CANADIANEXPERIENCE_POLYDRAWABLE_H
