/**
 * @file HeadTop.h
 * @author Ricardo Paz
 *
 *
 */

#ifndef CANADIANEXPERIENCE_HEADTOP_H
#define CANADIANEXPERIENCE_HEADTOP_H

#include "ImageDrawable.h"
#include "AnimChannelPosition.h"


/**
 * Creates the movable Head top for an actor
 */
class HeadTop : public ImageDrawable {
private:
    /// True if the Head belongs to Harold
    bool mIsHarold = false;

    /// The animation channel for animating the position of the actor
    AnimChannelPosition mChannel;

public:
    HeadTop(const std::wstring &name, const std::wstring &filename);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Determines whether the drawable can move from the Parent
     * @return true if it can
     */
    bool IsMovable() override {return true;}

    wxPoint TransformPoint(wxPoint p);

    void Face(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Set the HeadTop true when it is part of Harold
     */
    void IsHarold() {mIsHarold = true;}

    void SetKeyframe() override;

    void GetKeyframe() override;

    void SetTimeline(Timeline* timeline);
};

#endif //CANADIANEXPERIENCE_HEADTOP_H
