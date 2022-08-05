/**
 * @file PictureFactory.h
 * @author Ricardo Paz
 *
 *
 */

class Picture;

#ifndef CANADIANEXPERIENCE_PICTUREFACTORY_H
#define CANADIANEXPERIENCE_PICTUREFACTORY_H

/**
 * A factory class that builds our picture.
 */
class PictureFactory {
private:

public:
    std::shared_ptr<Picture> Create(std::wstring imagesDir);


};

#endif //CANADIANEXPERIENCE_PICTUREFACTORY_H
