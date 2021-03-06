/**

GDevelop - Network Extension
Copyright (c) 2010-2015 Florian Rival (Florian.Rival@gmail.com)
This project is released under the MIT License.
*/

#include "GDCpp/ExtensionBase.h"
#include "GDCore/Tools/Version.h"
#include "GDCpp/CommonTools.h"
#include "NetworkAutomatism.h"
#include "NetworkManager.h"

#include <SFML/Network.hpp>

/**
 * \brief This class declares information about the extension.
 */
class Extension : public ExtensionBase
{
public:

    /**
     * Constructor of an extension declares everything the extension contains: objects, actions, conditions and expressions.
     */
    Extension()
    {
        SetExtensionInformation("Network",
                              _("Network features"),
                              _("Built-in extension allowing to exchange data on the network between games."),
                              "Florian Rival",
                              "Open source (MIT License)");

        #if defined(GD_IDE_ONLY)

        AddAction("AddRecipient",
                       _("Add a recipient"),
                       _("Add the computer with the corresponding IP Adress as a recipient of sent data."),
                       _("Add _PARAM0_ to recipients"),
                       _("Network: Sending"),
                       "CppPlatform/Extensions/networkicon24.png",
                       "CppPlatform/Extensions/networkicon.png")

            .AddParameter("string", _("Recipient IP address."))
            .AddParameter("expression", _("Recipient port (Default : 50001)"), "", true)

            .SetFunctionName("GDpriv::NetworkExtension::AddRecipient").SetIncludeFile("Network/NetworkManagerFunctions.h");

        AddAction("RemoveAllRecipients",
                       _("Delete all recipients"),
                       _("Clear the list of the recipients of sent data"),
                       _("Clear the list of recipients"),
                       _("Network: Sending"),
                       "CppPlatform/Extensions/networkicon24.png",
                       "CppPlatform/Extensions/networkicon.png")

            .SetFunctionName("GDpriv::NetworkExtension::RemoveAllRecipients").SetIncludeFile("Network/NetworkManagerFunctions.h");


        AddAction("ListenToPort",
                       _("Initialize data reception"),
                       _("Initialize the network so as to be able te receive data from other computers."),
                       _("Initialize data reception"),
                       _("Network: Reception"),
                       "CppPlatform/Extensions/networkicon24.png",
                       "CppPlatform/Extensions/networkicon.png")

            .AddParameter("expression", _("Listening port (Default : 50001)"), "", true).SetDefaultValue("50001")
            .SetFunctionName("GDpriv::NetworkExtension::ListenToPort").SetIncludeFile("Network/NetworkManagerFunctions.h");

        AddAction("StopListening",
                       _("Stop data reception"),
                       _("Stop data reception."),
                       _("Stop data reception"),
                       _("Network: Reception"),
                       "CppPlatform/Extensions/networkicon24.png",
                       "CppPlatform/Extensions/networkicon.png")

            .SetFunctionName("GDpriv::NetworkExtension::ActStopListening").SetIncludeFile("Network/NetworkManagerFunctions.h");

        AddAction("SendValue",
                       _("Send a value"),
                       _("Send a value to recipients"),
                       _("Send value _PARAM1_ with title _PARAM0_ to recipients"),
                       _("Network: Sending"),
                       "CppPlatform/Extensions/networkicon24.png",
                       "CppPlatform/Extensions/networkicon.png")

            .AddParameter("string", _("Group"))
            .AddParameter("expression", _("Value"))

            .SetFunctionName("GDpriv::NetworkExtension::SendValue").SetIncludeFile("Network/NetworkManagerFunctions.h");

        AddAction("SendString",
                       _("Send a text"),
                       _("Send a text to recipients"),
                       _("Send text _PARAM1_ with title _PARAM0_ to recipients"),
                       _("Network: Sending"),
                       "CppPlatform/Extensions/networkicon24.png",
                       "CppPlatform/Extensions/networkicon.png")

            .AddParameter("string", _("Group"))
            .AddParameter("string", _("Text"))

            .SetFunctionName("GDpriv::NetworkExtension::SendString").SetIncludeFile("Network/NetworkManagerFunctions.h");

        AddAction("ReceivePackets",
                       _("Receive waiting data"),
                       _("Receive data sent by other computers.\nYou can then access to them with the appropriate expressions."),
                       _("Receive data"),
                       _("Network: Reception"),
                       "CppPlatform/Extensions/networkicon24.png",
                       "CppPlatform/Extensions/networkicon.png")

            .SetFunctionName("GDpriv::NetworkExtension::ReceivePackets").SetIncludeFile("Network/NetworkManagerFunctions.h");

        AddAction("ResetReceivedData",
                       _("Delete all received data stored in memory"),
                       _("Delete every received data stored in memory"),
                       _("Delete every received data stored in memory"),
                       _("Network: Reception"),
                       "CppPlatform/Extensions/networkicon24.png",
                       "CppPlatform/Extensions/networkicon.png")

            .SetFunctionName("GDpriv::NetworkExtension::ResetReceivedData").SetIncludeFile("Network/NetworkManagerFunctions.h");

        AddStrExpression("GetReceivedDataString", _("Get the text of a data"), _("Get the text contained in a data"), _("Network: Reception"), "CppPlatform/Extensions/networkicon.png")
            .AddParameter("string", _("Name of the data containing the text to get"))

            .SetFunctionName("GDpriv::NetworkExtension::GetReceivedDataString").SetIncludeFile("Network/NetworkManagerFunctions.h");


        AddExpression("GetReceivedDataValue", _("Get the value of a data"), _("Get the value contained in a data"), _("Network: Reception"), "CppPlatform/Extensions/networkicon.png")
            .AddParameter("string", _("Name of the data containing the text to get"))

            .SetFunctionName("GDpriv::NetworkExtension::GetReceivedDataValue").SetIncludeFile("Network/NetworkManagerFunctions.h");


        AddStrExpression("GetLastError", _("Last error occured"), _("Get the text describing the last error which occured."), _("Network: Errors"), "res/error.png")

            .SetFunctionName("GDpriv::NetworkExtension::GetLastError").SetIncludeFile("Network/NetworkManagerFunctions.h");


        AddStrExpression("GetPublicAddress", _("IP address"), _("Allow to get the public IP Address of the computer."), _("Network"), "CppPlatform/Extensions/networkicon.png")
            .AddParameter("expression", _("Maximum time to wait before getting the address ( in seconds ) ( 0 = no timeout )"), "", true)

            .SetFunctionName("GDpriv::NetworkExtension::GetPublicAddress").SetIncludeFile("Network/NetworkManagerFunctions.h");


        AddStrExpression("GetLocalAddress", _("Local IP address ( local/LAN )"), _("Allow to get the public IP Address of the computer."), _("Network"), "CppPlatform/Extensions/networkicon.png")

            .SetFunctionName("GDpriv::NetworkExtension::GetLocalAddress").SetIncludeFile("Network/NetworkManagerFunctions.h");


        AddAction("GenerateObjectNetworkId",
                       _("Generate objects' identifiers"),
                       _("Generate automatically identifiers for these objects.\nNote that this action must be preferably used at the start of the scene for example, so as to be sure objects\nhave the same unique identifiers on the different computers."),
                       _("Generate unique network identifiers for _PARAM0_"),
                       _("Automatism Automatic Network Updater"),
                       "CppPlatform/Extensions/networkicon24.png",
                       "CppPlatform/Extensions/networkicon.png")

            .AddParameter("objectList", _("Object"))
            .AddParameter("automatism", _("Automatism"), "NetworkAutomatism", false)
            .SetFunctionName("NetworkAutomatism::GenerateObjectNetworkIdentifier").SetIncludeFile("Network/NetworkAutomatism.h");

        #endif

        {
            gd::AutomatismMetadata & aut = AddAutomatism("NetworkAutomatism",
                  _("Automatic network update"),
                  _("NetworkUpdater"),
                  _("Allows to automatically synchronize the objects of a game on the network."),
                  "",
                  "CppPlatform/Extensions/networkicon32.png",
                  "NetworkAutomatism",
                  std::shared_ptr<gd::Automatism>(new NetworkAutomatism),
                  std::shared_ptr<gd::AutomatismsSharedData>(new SceneNetworkDatas));

            #if defined(GD_IDE_ONLY)
            aut.SetIncludeFile("Network/NetworkAutomatism.h");

            aut.AddAction("SetAsSender",
                           _("Set to send data"),
                           _("The automatism will send the data of the objects.\nBe sure to have generated identifiers for these objects before."),
                           _("Set _PARAM0_ to send data"),
                           _("Automatism Automatic Network Updater"),
                           "CppPlatform/Extensions/networkicon24.png",
                           "CppPlatform/Extensions/networkicon.png")
                .AddParameter("object", _("Object"))
                .AddParameter("automatism", _("Automatism"), "NetworkAutomatism", false)
                .SetFunctionName("SetAsSender").SetIncludeFile("Network/NetworkAutomatism.h");

            aut.AddAction("SetAsReceiver",
                           _("Set to receive data"),
                           _("The automatism will receive the data and will update the objects.\nBe sure to have generated identifiers for these objects before."),
                           _("Set _PARAM0_ to receive data"),
                           _("Automatism Automatic Network Updater"),
                           "CppPlatform/Extensions/networkicon24.png",
                           "CppPlatform/Extensions/networkicon.png")
                .AddParameter("object", _("Object"))
                .AddParameter("automatism", _("Automatism"), "NetworkAutomatism", false)
                .SetFunctionName("SetAsReceiver").SetIncludeFile("Network/NetworkAutomatism.h");

            aut.AddAction("SetIdentifier",
                           _("Change object's identifier"),
                           _("Each object need a unique identifier, the same on all computers, so as to be identified and updated"),
                           _("Set identifier of _PARAM0_ to _PARAM2_"),
                           _("Automatism Automatic Network Updater"),
                           "CppPlatform/Extensions/networkicon24.png",
                           "CppPlatform/Extensions/networkicon.png")
                .AddParameter("object", _("Object"))
                .AddParameter("automatism", _("Automatism"), "NetworkAutomatism", false)
                .AddParameter("expression", _("Identifier"))
                .SetFunctionName("SetIdentifier").SetIncludeFile("Network/NetworkAutomatism.h");

            aut.AddExpression("GetIdentifier", _("Get the identifier of the object"), _("Get the identifier of the object"), _("Automatism Automatic Network Updater"), "res/texteicon.png")
                .AddParameter("object", _("Object"))
                .AddParameter("automatism", _("Automatism"), "NetworkAutomatism", false)
                .SetFunctionName("GetIdentifier").SetIncludeFile("Network/NetworkAutomatism.h");
            #endif
        }

        GD_COMPLETE_EXTENSION_COMPILATION_INFORMATION();
    };

    #if defined(GD_IDE_ONLY)
    bool HasDebuggingProperties() const { return true; };

    void GetPropertyForDebugger(unsigned int propertyNb, std::string & name, std::string & value) const
    {
        if ( propertyNb == 0 )
        {
            name = _("List of recipients");
            const std::vector< std::pair<sf::IpAddress, short unsigned int> > & list = NetworkManager::Get()->GetRecipientsList();
            for (unsigned int i = 0;i<list.size();++i)
                value += list[i].first.toString()+ToString(_(" Port: "))+ToString(list[i].second)+"; ";
        }
    }

    bool ChangeProperty(unsigned int propertyNb, std::string newValue)
    {
        if ( propertyNb == 0 ) return false;
    }

    unsigned int GetNumberOfProperties() const
    {
        return 1;
    }
    #endif
};

/**
 * Used by GDevelop to create the extension class
 * -- Do not need to be modified. --
 */
extern "C" ExtensionBase * GD_EXTENSION_API CreateGDExtension() {
    return new Extension;
}
