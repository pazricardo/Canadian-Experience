/**
 * @file SpartyFactory.h
 * @author Ricardo Paz
 *
 *
 */

#ifndef CANADIANEXPERIENCELIB_SPARTYFACTORY_H
#define CANADIANEXPERIENCELIB_SPARTYFACTORY_H

class Actor;

/**
 * Factory class that builds the Sparty character
 */
class SpartyFactory {
private:

public:
    std::shared_ptr<Actor> Create(std::wstring imagesDir);

};

#endif //CANADIANEXPERIENCELIB_SPARTYFACTORY_H
