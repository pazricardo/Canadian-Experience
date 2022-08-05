/**
 * @file AnimChannelPosition.cpp
 * @author Ricardo Paz
 */

#include "pch.h"
#include "AnimChannelPosition.h"

/**
 * Set a keyframe
 *
 * This function allocates a new keyframe and sends it to
 * AnimChannel, which will insert it into the collection of keyframes.
 * @param point point for the keyframe.
 */
void AnimChannelPosition::SetKeyframe(wxPoint point)
{
    // Create a keyframe of the appropriate type
    // Telling it this channel and the angle
    auto keyframe = std::make_shared<KeyframePoint>(this, point);

    // Insert it into the collection
    InsertKeyframe(keyframe);
}

/**
 * Compute an motion that is an interpolation
 * between two keyframes
 *
 * This function is called after Use1 and Use2,
 * so we have pointers to valid keyframes of the
 * type KeyframePosition. This function computes the
 * tweening.
 *
 * @param t A t value. t=0 means keyframe1, t=1 means keyframe2.
 * Other values interpolate between.
 */
void AnimChannelPosition::Tween(double t)
{
    mPoint = wxPoint(int(mKeyframe1->GetPoint().x + t * (mKeyframe2->GetPoint().x - mKeyframe1->GetPoint().x)),
            int(mKeyframe1->GetPoint().y + t * (mKeyframe2->GetPoint().y - mKeyframe1->GetPoint().y)));
}