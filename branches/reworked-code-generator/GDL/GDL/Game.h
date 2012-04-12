/** \file
 *  Game Develop
 *  2008-2012 Florian Rival (Florian.Rival@gmail.com)
 */

#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "GDL/Scene.h"
#include "GDL/ListVariable.h"
#include "GDL/Dossier.h"
#include "GDL/Image.h"
#include "GDL/LoadingScreen.h"
#include "GDL/ResourcesManager.h"
class Object;
class ExternalEvents;
#if !defined(GD_NO_DYNAMIC_EXTENSIONS)
namespace GDpriv
{
class SourceFile;
}
#endif

/**
 * \brief Represent a game.
 * Game contains all data of a game, from scenes to properties like game's name.
 */
class GD_API Game
{
    public:
        Game();
        Game(const Game&);
        virtual ~Game() {};

        Game& operator=(const Game & rhs);

        std::string name; ///< Game name
        std::string author; ///< Game author name
        int windowWidth; ///< Default window width
        int windowHeight; ///< Default window height
        int maxFPS; ///< Maximum Frame Per Seconds, -1 for unlimited
        int minFPS; ///< Minimum Frame Per Seconds ( slow down game if FPS are below this number )
        bool verticalSync; ///< If true, must activate vertical synchronization.
        bool portable; ///< True if the game was saved as a portable game file
        bool fullscreen; ///< True if the game is displayed full screen

        vector < std::string > extensionsUsed; ///< List of extensions used

        LoadingScreen loadingScreen; ///< Data concerning the loading screen

        ResourcesManager resourceManager; ///< Contains all resources used by the project

        std::vector < boost::shared_ptr<Scene> >             scenes; ///< List of all scenes
        std::vector < boost::shared_ptr<Object> >            globalObjects; ///< Global objects
        std::vector < ObjectGroup >                          objectGroups; ///< Global objects groups

        ListVariable variables; ///< Initial global variables

        #if defined(GD_IDE_ONLY)
        std::vector < boost::shared_ptr<ExternalEvents> >    externalEvents; ///< List of all externals events

        std::string gameFile; ///< File of the game
        std::vector < string > imagesChanged; ///< Images that have been changed and which have to be reloaded

        std::string winExecutableFilename; ///< Windows executable name
        std::string winExecutableIconFile; ///< Icon for Windows executable
        std::string linuxExecutableFilename;  ///< Linux executable name
        std::string macExecutableFilename;  ///< Mac executable name
        #endif

        #if !defined(GD_NO_DYNAMIC_EXTENSIONS)
        bool useExternalSourceFiles; ///< True if game used external source files, and thus dynamic extensions.
        #if defined(GD_IDE_ONLY)
        std::vector < boost::shared_ptr<GDpriv::SourceFile> >        externalSourceFiles; ///< List of C++ source files used.
        #endif
        #endif

    private:

        /**
         * Initialize from another game. Used by copy-ctor and assign-op.
         * Don't forget to update me if members were changed !
         */
        void Init(const Game & game);
};

#endif // GAME_H