/** \file
 *  Game Develop
 *  2008-2012 Florian Rival (Florian.Rival@gmail.com)
 */

#if defined(GD_IDE_ONLY)

#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "GDCore/Events/Instruction.h"
class Game;
class MainEditorCommand;
class wxWindow;
class EventsEditorItemsAreas;
class EventsEditorSelection;
class Scene;
class Instruction;
class TiXmlElement;
class Game;
class EventsCodeGenerator;
class EventsCodeGenerationContext;
class wxDC;

class BaseEvent;
typedef boost::shared_ptr<BaseEvent> BaseEventSPtr;

/**
 * @brief An event is an item of an event list.
 * Events are not instance of Base Event, but instance of a derived class.
 */
class GD_CORE_API BaseEvent
{
public:
    BaseEvent();
    virtual ~BaseEvent();
    virtual BaseEventSPtr Clone() { return boost::shared_ptr<BaseEvent>(new BaseEvent(*this));}

    /**
     * Generate event's code.
     * Implementation example :
     * \code
        std::string outputCode;

        outputCode += codeGenerator.GenerateConditionsListCode(game, scene, conditions, context);

        std::string ifPredicat;
        for (unsigned int i = 0;i<conditions.size();++i)
        {
            if (i!=0) ifPredicat += " && ";
            ifPredicat += "condition"+ToString(i)+"IsTrue";
        }

        if ( !ifPredicat.empty() ) outputCode += "if (" +ifPredicat+ ")\n";
        outputCode += "{\n";
        outputCode += codeGenerator.GenerateActionsListCode(game, scene, actions, context);
        if ( !events.empty() ) //Sub events
        {
            outputCode += "\n{\n";
            outputCode += codeGenerator.GenerateEventsListCode(game, scene, events, context);
            outputCode += "}\n";
        }

        outputCode += "}\n";

        return outputCode;
     * \endcode
     */
    virtual std::string GenerateEventCode(Game & game, Scene & scene, EventsCodeGenerator & codeGenerator, EventsCodeGenerationContext & context) {return "";};

    /**
     * Derived class have to redefine this function, so as to return true, if they are executable.
     */
    virtual bool IsExecutable() const {return false;};

    /**
     * Derived class have to redefine this function, so as to return true, if they have sub events.
     */
    virtual bool CanHaveSubEvents() const {return false;}

    /**
     * Return the sub events, if applicable.
     */
    virtual const std::vector < BaseEventSPtr > & GetSubEvents() const {return badSubEvents;};

    /**
     * Return the sub events, if applicable.
     */
    virtual std::vector < BaseEventSPtr > & GetSubEvents() {return badSubEvents;};

    /**
     * Set if the event if disabled or not
     */
    void SetDisabled(bool disable = true) { disabled = disable; }

    /**
     * True if event is disabled
     */
    bool IsDisabled() const { return disabled; }

    /**
     * Called before events are compiled
     */
    virtual void Preprocess(const Game & game, const Scene & scene, std::vector < BaseEventSPtr > & eventList, unsigned int indexOfTheEventInThisList) {};


    /**
     * Event must be able to return all conditions std::vector they have.
     * Used to preprocess the conditions.
     */
    virtual std::vector < std::vector<Instruction>* > GetAllConditionsVectors() { std::vector < std::vector<Instruction>* > noConditions; return noConditions; };

    /**
     * Event must be able to return all actions std::vector they have.
     * Used to preprocess the actions.
     */
    virtual std::vector < std::vector<Instruction>* > GetAllActionsVectors() { std::vector < std::vector<Instruction>* > noActions; return noActions; };

    /**
     * Event must be able to return all expressions they have.
     * Used to preprocess the expressions.
     */
    virtual std::vector < GDExpression* > GetAllExpressions() { std::vector < GDExpression* > noExpr; return noExpr;};

    /**
     * Save event to XML
     */
    virtual void SaveToXml(TiXmlElement * eventElem) const {}

    /**
     * Load event from XML
     */
    virtual void LoadFromXml(const TiXmlElement * eventElem) {}

    std::string GetType() const { return type; };
    void SetType(std::string type_) { type = type_; };

    /**
     * Called by event editor to draw the event.
     */
    virtual void Render(wxDC & dc, int x, int y, unsigned int width, EventsEditorItemsAreas & areas, EventsEditorSelection & selection) {return;}

    /**
     * Must return the height of the event when rendered
     */
    virtual unsigned int GetRenderedHeight(unsigned int width) const {return 0;};

    /**
     * Used by EditEvent to describe what sort of changes have been made to the event
     * \see BaseEvent::EditEvent
     */
    enum EditEventReturnType
    {
        ChangesMade,
        Cancelled,
        ChangesMadeButNoNeedForEventsRecompilation
    };

    /**
     * Called when the user want to edit the event
     */
    virtual EditEventReturnType EditEvent(wxWindow* parent_, Game & game_, Scene & scene_, MainEditorCommand & mainEditorCommand_) { return ChangesMade; };

    bool            folded; ///< Here as it must be saved. Used by events editor
    mutable bool    eventHeightNeedUpdate; ///<Automatically set to true/false by the events editor

    boost::weak_ptr<BaseEvent> originalEvent; ///< Pointer only used for profiling events, so as to remember the original event from which it has been copied.
    unsigned long int totalTimeDuringLastSession; ///< Total time used by the event during the last run. Used for profiling.
    float percentDuringLastSession; ///< Total time used by the event during the last run. Used for profiling.


protected:
    mutable unsigned int    renderedHeight;

private:
    bool                    disabled; ///<True if the event is disabled and must not be executed
    std::string             type; ///<Type of the event. Must be assigned at the creation. Used for saving the event for instance.

    static std::vector <BaseEventSPtr> badSubEvents;
};

/**
 * Clone an event and insert a reference to the original event into the newly created event.
 * Used for profiling events for example.
 */
BaseEventSPtr GD_CORE_API CloneRememberingOriginalEvent(BaseEventSPtr event);

/**
 * Helper function for copying std::vector of shared_ptr of events
 */
std::vector < BaseEventSPtr > GD_CORE_API CloneVectorOfEvents(const std::vector < BaseEventSPtr > & events);

#endif // EVENT_H

#endif