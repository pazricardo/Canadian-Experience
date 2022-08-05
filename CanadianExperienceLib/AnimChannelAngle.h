/**
 * @file AnimChannelAngle.h
 * @author Ricardo Paz
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNELANGLE_H
#define CANADIANEXPERIENCE_ANIMCHANNELANGLE_H

#include "AnimChannel.h"

/**
 * Animation channel for angles.
 */
class AnimChannelAngle : public AnimChannel {
private:
    /// Angle of the animation
    double mAngle = 0;

public:
    /// Default constructor
    AnimChannelAngle() { };

    /// Copy constructor (disabled)
    AnimChannelAngle(const AnimChannelAngle &) = delete;

    /// Assignment operator
    void operator=(const AnimChannelAngle &) = delete;

    /// Destructor (virtual)
    virtual ~AnimChannelAngle() {};

    void SetKeyframe(double angle);

    /**
     * Gets the angle
     * @return
     */
    double GetAngle() {return mAngle;}

protected:
    /// Class that represents a keyframe
    class KeyframeAngle : public Keyframe
    {
    private:
        /// Angle for Keyframe
        double mAngle;
        /// The channel this keyframe is associated with
        AnimChannelAngle *mChannel;

    public:
        /**
         * Constructor
         * @param channel The channel we are for
         * @param angle The angle for the keyframe
         */
        KeyframeAngle(AnimChannelAngle *channel, double angle) :
                Keyframe(channel), mChannel(channel), mAngle(angle) {};

        /// Constructor (disabled)
        KeyframeAngle() = delete;
        /// Destructor
        virtual ~KeyframeAngle() {};
        /// Copy Constructor (Disabled)
        KeyframeAngle(const KeyframeAngle &) = delete;
        /// Assignment Operator (Disabled)
        void operator=(const KeyframeAngle &) = delete;

        /// Use this keyframe as keyframe 1
        void UseAs1() override { mChannel->mKeyframe1 = this; }

        /// Use this keyframe as keyfraem 2
        void UseAs2() override { mChannel->mKeyframe2 = this; }

        /// Use this keyframe as the angle
        void UseOnly() override { mChannel->mAngle = mAngle; }

        /**
         * Gets the angle of the keyframe
         * @return
         */
        double GetAngle() {return mAngle;}

    };

    void Tween(double t) override;

private:
    /// The first angle keyframe
    KeyframeAngle *mKeyframe1 = nullptr;

    /// The second angle keyframe
    KeyframeAngle *mKeyframe2 = nullptr;

};

#endif //CANADIANEXPERIENCE_ANIMCHANNELANGLE_H
