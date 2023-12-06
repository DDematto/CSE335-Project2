/**
 * @file PictureFactory.h
 * @author Charles Owen
 *
 * A factory class that builds our picture.
 */

#ifndef CANADIANEXPERIENCE_PICTUREFACTORY_H
#define CANADIANEXPERIENCE_PICTUREFACTORY_H

class Picture;
class MachineDrawable;

/**
 * A factory class that builds our picture.
 */
class PictureFactory
{
private:
    /// The Picture Created for this Factory
    std::shared_ptr<Picture> mPicture = std::make_shared<Picture>();

    std::wstring mImagesDir;

public:
    PictureFactory(std::wstring resourcesDir);

    void AddMachine(const std::shared_ptr<MachineDrawable> &machine, wxPoint position);

    std::shared_ptr<Picture> AddActors();
};

#endif //CANADIANEXPERIENCE_PICTUREFACTORY_H
