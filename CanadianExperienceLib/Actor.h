/**
 * @file Actor.h
 * @author Ricardo Paz
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ACTOR_H
#define CANADIANEXPERIENCE_ACTOR_H

#include "Drawable.h"
#include "Picture.h"
#include "AnimChannelPosition.h"

/**
 * Class for actors in our drawings.
 *
 * An actor is some graphical object that consists of
 * one or more parts. Actors can be animated.
 */
class Actor {
private:
    /// Name of the Actor
    std::wstring mName;
    /// Enabled status
    bool mEnabled = true;
    /// Position of the Actor
    wxPoint mPosition = wxPoint(0,0);
    /// We can click on the Actor
    bool mClickable = true;
    /// The root drawable
    std::shared_ptr<Drawable> mRoot;
    /// The drawables in drawing order
    std::vector<std::shared_ptr<Drawable>> mDrawablesInOrder;
    /// Picture Actor is a part of
    Picture *mPicture = nullptr;
    /// The animation channel for animating the position of the actor
    AnimChannelPosition mChannel;

public:
    /// Constructor (disabled)
    Actor() = delete;
    /// Destructor
    virtual ~Actor() {};
    /// Copy Constructor (Disabled)
    Actor(const Actor &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const Actor &) = delete;

    Actor(const std::wstring &name);

    void SetRoot(std::shared_ptr<Drawable> root);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    std::shared_ptr<Drawable> HitTest(wxPoint pos);

    void AddDrawable(std::shared_ptr<Drawable> drawable);

    /**
     * Get the actor name
     * @return Actor name
     * */
    std::wstring GetName() const { return mName; }

    /**
     * Actor is enabled
     * @return enabled status
     */
    bool IsEnabled() const { return mEnabled; }

    /**
     * Set Actor enabled
     * @param enabled New enabled status
     */
    void SetEnabled(bool enabled) { mEnabled = enabled; }

    /**
     * Get the actor Position
     * @return Actor Position
     * */
    const wxPoint& GetPosition() const {return mPosition;}

    /**
     * Set the actor Position
     * @param position
     * */
    void SetPosition(const wxPoint& position) {mPosition = position;}

    /**
     * Get the actor enabled status
     * @return Actor enabled status
     * */
    bool IsClickable() const {return mClickable;}

    /**
     * Set the actor enabled status
     * @param clickable
     * */
    void SetClickable(bool clickable) {mClickable = clickable;}

    /**
     * Get the Picture the actor is a part of
     * @return mPicture
     * */
    Picture* GetPicture() {return mPicture;}

    void SetPicture(Picture *picture);

    void SetKeyframe();

    void GetKeyframe();

    /**
     * Gets the channel for the position
     * @return
     */
    AnimChannelPosition* GetPositionChannel() {return &mChannel;}

    void DeleteKeyframe();
};

#endif //CANADIANEXPERIENCE_ACTOR_H
