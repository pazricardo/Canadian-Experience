/**
 * @file Picture.h
 * @author Ricardo Paz
 *
 *
 */

#ifndef CANADIANEXPERIENCE_PICTURE_H
#define CANADIANEXPERIENCE_PICTURE_H

#include "Timeline.h"

class PictureObserver;
class Actor;

/**
 * The picture we are drawing.
 *
 * There will be one picture object that contains all of
 * our actors, which then contains the drawables.
 */
class Picture {
private:
    /// The picture size
    wxSize mSize = wxSize(1500, 800);

    /// The observers of this picture
    std::vector<PictureObserver *> mObservers;

    /// The Actors of this picture
    std::vector<std::shared_ptr<Actor>> mActors;

    /// The animation timeline
    Timeline mTimeline;

public:
    /**
     * Constructor
     */
    Picture() {}

    /// Copy Constructor (Disabled)
    Picture(const Picture &) = delete;
    /// Assignment Operator (Disabled)
    void operator=(const Picture &) = delete;

    /**
     * Get the picture size
     * @return Picture size in pixels
     */
    wxSize GetSize() {return mSize;}

    /**
     * Set the picture size
     * @param size Picture size in pixels
     */
    void SetSize(wxSize size) {mSize = size;}

    void AddObserver(PictureObserver *observer);
    void RemoveObserver(PictureObserver *observer);
    void UpdateObservers();
    void AddActor(std::shared_ptr<Actor> actor);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /** Iterator that iterates over the picture actors */
    class Iter
    {
    public:
        /** Constructor
         * @param picture the picture we are iterating over
         * @param pos Position in the collection
         */
        Iter(Picture* picture, int pos) : mPicture(picture), mPos(pos) {}

        /**
         * Compare two iterators
         * @param other The other iterator we are conparing to
         * @return true if this position is not equal to the other position
         */
        bool operator != (const Iter& other) const
        {
            return mPos != other.mPos;
        }

        /**
        * Get value at current position
        * @return Value at mPos in the collection
        */
        std::shared_ptr<Actor> operator *() const {return mPicture->mActors[mPos];}

        /**
         * Increment the iterator
         * @return Reference to this iterator
         */
        const Iter& operator++()
        {
            mPos++;
            return *this;
        }

    private:
        /// Picture we are iterating over
        Picture* mPicture;
        /// Position that we are in during the iteration
        int mPos;
    };

    /**
     * Get an iterator for the beginning of the collection
     * @return Iter object at position 0
     */
    Iter begin() { return Iter(this, 0); }

    /**
     * Get an iterator for the end of the collection
     * @return Iter object at position past the end
     */
    Iter end() { return Iter(this, mActors.size()); }


    /**
     * Get a pointer to the Timeline object
     * @return Pointer to the Timeline object
     */
    Timeline *GetTimeline() {return &mTimeline;}

    void SetAnimationTime(double time);
};

#endif //CANADIANEXPERIENCE_PICTURE_H
