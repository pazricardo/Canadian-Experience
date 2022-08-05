/**
 * @file AnimChannelPosition.h
 * @author Ricardo Paz
 *
 *
 */

#ifndef CANADIANEXPERIENCELIB_ANIMCHANNELPOSITION_H
#define CANADIANEXPERIENCELIB_ANIMCHANNELPOSITION_H

#include "AnimChannel.h"

/**
 * Animation channel for position.
 */
class AnimChannelPosition : public AnimChannel{
private:
    /// Point
    wxPoint mPoint = wxPoint(0, 0);

public:
    /// Constructor
    AnimChannelPosition() {};
    /// Copy constructor (disabled)
    AnimChannelPosition(const AnimChannelPosition &) = delete;
    /// Assignment operator
    void operator=(const AnimChannelPosition &) = delete;
    /**
     * Gets the point
     * @return
     */
    wxPoint GetPoint() {return mPoint;}

    void SetKeyframe(wxPoint point);

protected:
    /// Class that represents a keyframe
    class KeyframePoint : public Keyframe
    {
    private:
        /// Point
        wxPoint mPoint;
        /// The channel this keyframe is associated with
        AnimChannelPosition *mChannel;

    public:
        /**
         * Gets the point of the keyframe
         * @return
         */
        wxPoint GetPoint() {return mPoint;}

        /// Use this keyframe as keyframe 1
        void UseAs1() override { mChannel->mKeyframe1 = this; }

        /// Use this keyframe as keyfraem 2
        void UseAs2() override { mChannel->mKeyframe2 = this; }

        /// Use this keyframe as the angle
        void UseOnly() override { mChannel->mPoint = mPoint; }

        /**
         * Constructor
         * @param channel The channel we are for
         * @param point The point for the keyframe
         */
        KeyframePoint(AnimChannelPosition *channel, wxPoint point) :
                Keyframe(channel), mChannel(channel), mPoint(point) {}

        /// Default Constructor
        KeyframePoint() = delete;
        /// Copy constructor (disabled)
        KeyframePoint(const KeyframePoint &) = delete;
        /// Assignment operator
        void operator=(const KeyframePoint &) = delete;
    };

    void Tween(double t) override;

private:
    /// The first angle keyframe
    KeyframePoint *mKeyframe1 = nullptr;

    /// The second angle keyframe
    KeyframePoint *mKeyframe2 = nullptr;
};

#endif CANADIANEXPERIENCELIB_ANIMCHANNELPOSITION_H
