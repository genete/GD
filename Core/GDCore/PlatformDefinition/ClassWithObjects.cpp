/*
 * GDevelop Core
 * Copyright 2008-2015 Florian Rival (Florian.Rival@gmail.com). All rights reserved.
 * This project is released under the MIT License.
 */
#include <algorithm>
#include "GDCore/PlatformDefinition/ClassWithObjects.h"
#include "GDCore/PlatformDefinition/Project.h"
#include "GDCore/PlatformDefinition/Platform.h"
#include "GDCore/PlatformDefinition/Object.h"
#include "GDCore/Serialization/SerializerElement.h"

namespace gd
{

ClassWithObjects::ClassWithObjects()
{
}

#if defined(GD_IDE_ONLY)
void ClassWithObjects::SerializeObjectsTo(SerializerElement & element) const
{
    element.ConsiderAsArrayOf("object");
    for ( unsigned int j = 0;j < initialObjects.size();j++ )
    {
        initialObjects[j]->SerializeTo(element.AddChild("object"));
    }

}
#endif

void ClassWithObjects::UnserializeObjectsFrom(gd::Project & project, const SerializerElement & element)
{
    initialObjects.clear();
    element.ConsiderAsArrayOf("object", "Objet");
    for (unsigned int i = 0; i < element.GetChildrenCount(); ++i)
    {
        const SerializerElement & objectElement = element.GetChild(i);

        std::string type = objectElement.GetStringAttribute("type");
        std::shared_ptr<gd::Object> newObject =
            project.CreateObject(type, objectElement.GetStringAttribute("name", "", "nom"));

        if ( newObject != std::shared_ptr<gd::Object>() )
        {
            newObject->UnserializeFrom(project, objectElement);
            initialObjects.push_back( newObject );
        }
        else
            std::cout << "WARNING: Unknown object type \"" << type << "\"" << std::endl;
    }
}

bool ClassWithObjects::HasObjectNamed(const std::string & name) const
{
    return ( find_if(initialObjects.begin(), initialObjects.end(), bind2nd(gd::ObjectHasName(), name)) != initialObjects.end() );
}
gd::Object & ClassWithObjects::GetObject(const std::string & name)
{
    return *(*find_if(initialObjects.begin(), initialObjects.end(), bind2nd(gd::ObjectHasName(), name)));
}
const gd::Object & ClassWithObjects::GetObject(const std::string & name) const
{
    return *(*find_if(initialObjects.begin(), initialObjects.end(), bind2nd(gd::ObjectHasName(), name)));
}
gd::Object & ClassWithObjects::GetObject(unsigned int index)
{
    return *initialObjects[index];
}
const gd::Object & ClassWithObjects::GetObject (unsigned int index) const
{
    return *initialObjects[index];
}
unsigned int ClassWithObjects::GetObjectPosition(const std::string & name) const
{
    for (unsigned int i = 0;i<initialObjects.size();++i)
    {
        if ( initialObjects[i]->GetName() == name ) return i;
    }
    return std::string::npos;
}
unsigned int ClassWithObjects::GetObjectsCount() const
{
    return initialObjects.size();
}
#if defined(GD_IDE_ONLY)
gd::Object & ClassWithObjects::InsertNewObject(gd::Project & project, const std::string & objectType, const std::string & name, unsigned int position)
{
    std::shared_ptr<gd::Object> newObject = project.GetCurrentPlatform().CreateObject(objectType, name);
    if (position<initialObjects.size())
        initialObjects.insert(initialObjects.begin()+position, newObject);
    else
        initialObjects.push_back(newObject);

    return *newObject;
}
#endif

gd::Object & ClassWithObjects::InsertObject(const gd::Object & object, unsigned int position)
{
    std::shared_ptr<gd::Object> newObject = std::shared_ptr<gd::Object>(object.Clone());
    if (position<initialObjects.size())
        initialObjects.insert(initialObjects.begin()+position, newObject);
    else
        initialObjects.push_back(newObject);

    return *newObject;
}

void ClassWithObjects::SwapObjects(unsigned int firstObjectIndex, unsigned int secondObjectIndex)
{
    if ( firstObjectIndex >= initialObjects.size() || secondObjectIndex >= initialObjects.size() )
        return;

    std::shared_ptr<gd::Object> temp = initialObjects[firstObjectIndex];
    initialObjects[firstObjectIndex] = initialObjects[secondObjectIndex];
    initialObjects[secondObjectIndex] = temp;
}

void ClassWithObjects::RemoveObject(const std::string & name)
{
    std::vector< std::shared_ptr<gd::Object> >::iterator object = find_if(initialObjects.begin(), initialObjects.end(), bind2nd(ObjectHasName(), name));
    if ( object == initialObjects.end() ) return;

    initialObjects.erase(object);
}

}
