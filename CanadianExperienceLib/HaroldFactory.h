/**
 * @file HaroldFactory.h
 * @author Ricardo Paz
 *
 *
 */

class Actor;

#ifndef CANADIANEXPERIENCE_HAROLDFACTORY_H
#define CANADIANEXPERIENCE_HAROLDFACTORY_H

/**
 * Factory class that builds the Harold character
 */
class HaroldFactory {
private:

public:
    std::shared_ptr<Actor> Create(std::wstring imagesDir);


};

#endif //CANADIANEXPERIENCE_HAROLDFACTORY_H
