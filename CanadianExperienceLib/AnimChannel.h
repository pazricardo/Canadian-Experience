/**
 * @file AnimChannel.h
 * @author Ricardo Paz
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNEL_H
#define CANADIANEXPERIENCE_ANIMCHANNEL_H

class Timeline;

/**
 * Base class for animation channels
 *
 * This class provides basic functionality and a polymorphic
 * representation for animation channels.
 */
class AnimChannel {
private:
    /// Name of Channel
    std::wstring mName;
    /// First keyframe to tween
    int mKeyframe1 = -1;
    /// Second keyframe of tween
    int mKeyframe2 = -1;
    /// The timeline object
    Timeline *mTimeline = nullptr;

public:
    /// Copy constructor (disabled)
    AnimChannel(const AnimChannel &) = default;

    /// Assignment operator
    void operator=(const AnimChannel &) = delete;

    /// Destructor (virtual)
    virtual ~AnimChannel() {};

    bool IsValid();

    void SetFrame(int currFrame);

    /**
     * Gets the name of channel
     * @return
     */
    std::wstring GetName() const {return mName;}

    /**
     * Sets the name of the channel
     * @param name
     */
    void SetName(std::wstring name) {mName = name;}

    /**
     * Gets the timeline of the channel
     * @return
     */
    Timeline* GetTimeline() {return mTimeline;}

    /**
     * Sets the timeline for the channel
     * @param timeline
     */
    void SetTimeline(Timeline* timeline) {mTimeline = timeline;}

    void DeleteKeyframe();

protected:
    /// Default constructor
    AnimChannel() { };

    /// Class that represents a keyframe
    class Keyframe
    {
    private:
        /// The channel this keyframe is associated with
        AnimChannel *mChannel;
    protected:
        /// Frame the keyframe is on
        int mFrame;

        /**
         * Constructor
         * @param channel Channel we are associated with
         */
        Keyframe(AnimChannel *channel) : mChannel(channel) {}

    public:
        /// Constructor (disabled)
        Keyframe() = delete;
        /// Destructor
        virtual ~Keyframe() {};
        /// Copy Constructor (Disabled)
        Keyframe(const Keyframe &) = delete;
        /// Assignment Operator (Disabled)
        void operator=(const Keyframe &) = delete;

        /**
         * Use as first keyframe
         */
        virtual void UseAs1() {};

        /**
         * Use as second keyframe
         */
        virtual void UseAs2() {};
        /**
         * Use as only keyframe
         */
        virtual void UseOnly() {};

        /**
         * Get the frame of the keyframe
         * @return
         */
        int GetFrame() {return mFrame;}

        /**
         * Set the frame for the keyframe
         * @param frame
         */
        void SetFrame(int frame) {mFrame = frame;}

    };

    void InsertKeyframe(std::shared_ptr<Keyframe> keyframe);

    /**
     * Tweens the motion from Keyframe1 to Keyframe2
     * @param t
     */
    virtual void Tween(double t) {};

private:
    /// The collection of keyframes for this channel
    std::vector<std::shared_ptr<Keyframe>> mKeyframes;

};

#endif //CANADIANEXPERIENCE_ANIMCHANNEL_H
