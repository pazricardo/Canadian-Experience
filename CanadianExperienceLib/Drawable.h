/**
 * @file Drawable.h
 * @author Ricardo Paz
 *
 *
 */

#ifndef CANADIANEXPERIENCE_DRAWABLE_H
#define CANADIANEXPERIENCE_DRAWABLE_H

#include "AnimChannelAngle.h"

class Actor;
class Timeline;

/**
 * Abstract base class for drawable elements of our picture.
 *
 * A drawable is one part of an actor. Drawable parts can be moved
 * independently.
 */
class Drawable {
private:
    /// The position of this drawable relative to its parent
    wxPoint mPosition = wxPoint(0,0);
    /// The drawable name
    std::wstring mName;
    /// The rotation of this drawable relative to its parent
    double mRotation = 0;
    /// The actor using this drawable
    Actor *mActor = nullptr;
    /// Child of drawable
    std::vector<std::shared_ptr<Drawable>> mChildren;
    /// Parent of drawable
    Drawable *mParent = nullptr;
    /// The animation channel for animating the angle of this drawable
    AnimChannelAngle mChannel;

public:
    /// Constructor (disabled)
    Drawable() = delete;
    /// Destructor
    virtual ~Drawable() {};
    /// Copy Constructor (Disabled)
    Drawable(const Drawable &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const Drawable &) = delete;

    void SetActor(Actor *actor);

    /**
     * Draw the image drawable (virtual)
     * @param graphics Graphics context to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) = 0;
    void Place(wxPoint offset, double rotate);
    void AddChild(std::shared_ptr<Drawable> child);

    /**
     * Test to see if we clicked on the image.
     * @param point
     * @return True if clicked on
     */
    virtual bool HitTest(wxPoint point) = 0;

    /**
     * Determines whether the drawable can move from the Parent
     * @return true if it can
     */
    virtual bool IsMovable() {return false;};
    void Move(wxPoint delta);

    /**
     * Set the drawable position
     * @param pos The new drawable position
     */
    void SetPosition(wxPoint pos) { mPosition = pos; }

    /**
     * Get the drawable position
     * @return The drawable position
     */
    wxPoint GetPosition() const { return mPosition; }

    /**
     * Set the rotation angle in radians
    * @param r The new rotation angle in radians
     */
    void SetRotation(double r) { mRotation = r; }

    /**
     * Get the rotation angle in radians
     * @return The rotation angle in radians
     */
    double GetRotation() const { return mRotation; }

    /**
     * Get the drawable name
     * @return The drawable name
     */
    std::wstring GetName() const { return mName; }

    /**
     * Gets the parent of the Drawable
     * @return mParent
     */
    Drawable* GetParent() { return mParent;}

    /**
     * Sets the parent for the drawable
     * @param parent
     */
    void SetParent(Drawable* parent) {mParent = parent;}

    virtual void SetTimeline(Timeline* timeline);

    /**
     * The angle animation channel
     * @return Pointer to animation channel
     */
    AnimChannelAngle *GetAngleChannel() { return &mChannel; }

    virtual void SetKeyframe();

    virtual void GetKeyframe();

    virtual void DeleteKeyframe();


protected:
    /// The actual postion in the drawing
    wxPoint mPlacedPosition = wxPoint(0,0);
    /// The actual rotation in the drawing
    double mPlacedR = 0;

    Drawable(std::wstring name);
    wxPoint RotatePoint(wxPoint point, double angle);
};

#endif //CANADIANEXPERIENCE_DRAWABLE_H
