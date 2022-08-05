/**
 * @file ImageDrawable.h
 * @author Ricardo Paz
 *
 *
 */

#ifndef CANADIANEXPERIENCE_IMAGEDRAWABLE_H
#define CANADIANEXPERIENCE_IMAGEDRAWABLE_H

#include "Drawable.h"

/**
 * A drawable based on images.
 *
 * This class has an image to draw the drawable
 */
class ImageDrawable : public Drawable {
private:
    /// Center of the image
    wxPoint mCenter = wxPoint(0,0);
public:
    ImageDrawable(const std::wstring &name, const std::wstring &filename);

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    bool HitTest(wxPoint pos) override;

    /**
     * Gets the center point of the image
     * @return center point of image
     */
    wxPoint GetCenter() const {return mCenter;}

    /**
     * Sets the center point of the image
     * @param center
     */
    void SetCenter(wxPoint center) {mCenter = center;}

protected:
    /// The image we are drawing
    std::unique_ptr<wxImage> mImage;

    /// The graphics bitmap we will use
    wxGraphicsBitmap mBitmap;

};

#endif //CANADIANEXPERIENCE_IMAGEDRAWABLE_H
