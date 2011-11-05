/**

Game Develop - Particle System Extension
Copyright (c) 2010-2011 Florian Rival (Florian.Rival@gmail.com)

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would be
    appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
    misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
    distribution.

*/

#ifndef PARTICLEEMITTEROBJECT_H
#define PARTICLEEMITTEROBJECT_H

#include "GDL/Object.h"
#include "ParticleSystemWrapper.h"
namespace sf
{
    class Texture;
    class Sprite;
};
class Evaluateur;
class ImageManager;
class RuntimeScene;
class Object;
class ExpressionInstruction;
class ObjectsConcerned;
class ImageManager;
class InitialPosition;
#if defined(GD_IDE_ONLY)
class wxBitmap;
class Game;
class wxWindow;
class MainEditorCommand;
class ResourcesMergingHelper;
#endif

/**
 * \brief Particle Emitter Object
 */
class GD_EXTENSION_API ParticleEmitterObject : public Object
{
    public :

        ParticleEmitterObject(std::string name_);
        virtual ~ParticleEmitterObject();
        virtual ObjSPtr Clone() { return boost::shared_ptr<Object>(new ParticleEmitterObject(*this));}

        virtual bool LoadRuntimeResources(const RuntimeScene & scene, const ImageManager & imageMgr );
        virtual bool LoadResources(const RuntimeScene & scene, const ImageManager & imageMgr );
        virtual bool InitializeFromInitialPosition(const InitialPosition & position);

        virtual bool Draw(sf::RenderTarget & renderTarget);

        #if defined(GD_IDE_ONLY)
        virtual bool DrawEdittime(sf::RenderTarget & renderTarget);
        virtual void ExposeResources(ArbitraryResourceWorker & worker);
        virtual bool GenerateThumbnail(const Game & game, wxBitmap & thumbnail);

        virtual void EditObject( wxWindow* parent, Game & game_, MainEditorCommand & mainEditorCommand_ );
        virtual wxPanel * CreateInitialPositionPanel( wxWindow* parent, const Game & game_, const Scene & scene_, const InitialPosition & position );
        virtual void UpdateInitialPositionFromPanel(wxPanel * panel, InitialPosition & position);

        virtual void GetPropertyForDebugger (unsigned int propertyNb, std::string & name, std::string & value) const;
        virtual bool ChangeProperty(unsigned int propertyNb, std::string newValue);
        virtual unsigned int GetNumberOfProperties() const;
        #endif

        virtual void LoadFromXml(const TiXmlElement * elemScene);
        #if defined(GD_IDE_ONLY)
        virtual void SaveToXml(TiXmlElement * elemScene);
        #endif

        virtual void UpdateTime(float timeElapsed);

        virtual void OnPositionChanged();

        virtual float GetWidth() const;
        virtual float GetHeight() const;
        virtual void SetWidth(float ) {};
        virtual void SetHeight(float ) {};

        virtual float GetDrawableX() const;
        virtual float GetDrawableY() const;

        virtual float GetCenterX() const;
        virtual float GetCenterY() const;

        void UpdateRedParameters();
        void UpdateGreenParameters();
        void UpdateBlueParameters();
        void UpdateAlphaParameters();
        void UpdateSizeParameters();
        void UpdateAngleParameters();
        void UpdateLifeTime();
        void RecreateParticleSystem();

        //Getters/Setters
        void SetRendererParam1(float newValue) { rendererParam1 = newValue; };
        void SetRendererParam2(float newValue) { rendererParam2 = newValue; };
        void SetTank(float newValue);
        void SetFlow(float newValue);
        void SetEmitterForceMin(float newValue);
        void SetEmitterForceMax(float newValue);
        void SetEmitterXDirection(float newValue);
        void SetEmitterYDirection(float newValue);
        void SetEmitterZDirection(float newValue);
        void SetEmitterAngleA(float newValue);
        void SetEmitterAngleB(float newValue);
        void SetConeSprayAngle(float newValue) { SetEmitterAngleB(newValue/180.0f*3.14159f); };
        void SetZoneRadius(float newValue);
        void SetParticleGravityX(float newValue);
        void SetParticleGravityY(float newValue);
        void SetParticleGravityZ(float newValue);
        void SetParticleGravityAngle( float newAngleInDegree );
        void SetParticleGravityLength( float newLength );
        void SetFriction(float newValue);

        enum ParticleParameterType {Nothing, Enabled, Mutable, Random};
        void SetRedParameterType(ParticleParameterType type) { redParam = type; };
        void SetGreenParameterType(ParticleParameterType type) { greenParam = type; };
        void SetBlueParameterType(ParticleParameterType type) { blueParam = type; };
        void SetAlphaParameterType(ParticleParameterType type) { alphaParam = type; };
        void SetSizeParameterType(ParticleParameterType type) { sizeParam = type; };
        void SetAngleParameterType(ParticleParameterType type) { angleParam = type; };

        void SetParticleColor1( const std::string & color );
        void SetParticleColor2( const std::string & color );

        void SetParticleRed1(float newValue) { particleRed1= newValue; UpdateRedParameters();};
        void SetParticleRed2(float newValue) { particleRed2= newValue; UpdateRedParameters();};
        void SetParticleGreen1(float newValue) { particleGreen1= newValue; UpdateGreenParameters();};
        void SetParticleGreen2(float newValue) { particleGreen2= newValue; UpdateGreenParameters();};
        void SetParticleBlue1(float newValue) { particleBlue1= newValue; UpdateBlueParameters();};
        void SetParticleBlue2(float newValue) { particleBlue2= newValue; UpdateBlueParameters();};
        void SetParticleAlpha1(float newValue) { particleAlpha1= newValue; UpdateAlphaParameters();};
        void SetParticleAlpha2(float newValue) { particleAlpha2= newValue; UpdateAlphaParameters();};
        void SetParticleSize1(float newValue) { particleSize1= newValue; UpdateSizeParameters();};
        void SetParticleSize2(float newValue) { particleSize2= newValue; UpdateSizeParameters();};
        void SetParticleAngle1(float newValue) { particleAngle1= newValue; UpdateAngleParameters();};
        void SetParticleAngle2(float newValue) { particleAngle2= newValue; UpdateAngleParameters();};
        void SetParticleAlphaRandomness1(float newValue) { particleAlphaRandomness1= newValue; UpdateAlphaParameters();};
        void SetParticleAlphaRandomness2(float newValue) { particleAlphaRandomness2= newValue; UpdateAlphaParameters();};
        void SetParticleSizeRandomness1(float newValue) { particleSizeRandomness1= newValue; UpdateSizeParameters();};
        void SetParticleSizeRandomness2(float newValue) { particleSizeRandomness2= newValue; UpdateSizeParameters();};
        void SetParticleAngleRandomness1(float newValue) { particleAngleRandomness1= newValue; UpdateAngleParameters();};
        void SetParticleAngleRandomness2(float newValue) { particleAngleRandomness2= newValue; UpdateAngleParameters();};
        void SetParticleLifeTimeMin(float newValue) { particleLifeTimeMin= newValue; UpdateLifeTime();};
        void SetParticleLifeTimeMax(float newValue) { particleLifeTimeMax= newValue; UpdateLifeTime();};
        void SetMaxParticleNb(unsigned int newValue) { maxParticleNb = newValue; };

        float GetRendererParam1() const { return rendererParam1; };
        float GetRendererParam2() const { return rendererParam2; };
        float GetTank() const { return tank; };
        float GetFlow() const { return flow; };
        float GetEmitterForceMin() const { return emitterForceMin; };
        float GetEmitterForceMax() const { return emitterForceMax; };
        float GetEmitterXDirection() const { return emitterXDirection; };
        float GetEmitterYDirection() const { return emitterYDirection; };
        float GetEmitterZDirection() const { return emitterZDirection; };
        float GetEmitterAngleA() const { return emitterAngleA; };
        float GetEmitterAngleB() const { return  emitterAngleB; };
        float GetConeSprayAngle() const { return GetEmitterAngleB()*180.0f/3.14159f; };
        float GetZoneRadius() const { return  zoneRadius; };
        float GetParticleGravityX() const { return particleGravityX; };
        float GetParticleGravityY() const { return particleGravityY; };
        float GetParticleGravityZ() const { return particleGravityZ; };
        float GetParticleGravityAngle() const;
        float GetParticleGravityLength() const;
        float GetFriction() const { return friction; };
        float GetParticleLifeTimeMin() const { return particleLifeTimeMin; };
        float GetParticleLifeTimeMax() const { return particleLifeTimeMax; };
        unsigned int GetMaxParticleNb() const { return maxParticleNb; };

        ParticleParameterType GetRedParameterType() const { return redParam; };
        ParticleParameterType GetGreenParameterType() const { return greenParam; };
        ParticleParameterType GetBlueParameterType() const { return blueParam; };
        ParticleParameterType GetAlphaParameterType() const { return alphaParam; };
        ParticleParameterType GetSizeParameterType() const { return sizeParam; };
        ParticleParameterType GetAngleParameterType() const { return angleParam; };

        float GetParticleRed1() const { return particleRed1; };
        float GetParticleRed2() const { return particleRed2; };
        float GetParticleGreen1() const { return particleGreen1; };
        float GetParticleGreen2() const { return particleGreen2; };
        float GetParticleBlue1() const { return particleBlue1; };
        float GetParticleBlue2() const { return particleBlue2; };
        float GetParticleAlpha1() const { return particleAlpha1; };
        float GetParticleAlpha2() const { return particleAlpha2; };
        float GetParticleSize1() const { return particleSize1; };
        float GetParticleSize2() const { return particleSize2; };
        float GetParticleAngle1() const { return particleAngle1; };
        float GetParticleAngle2() const { return particleAngle2; };
        float GetParticleAlphaRandomness1() const { return particleAlphaRandomness1; };
        float GetParticleAlphaRandomness2() const { return particleAlphaRandomness2; };
        float GetParticleSizeRandomness1() const { return particleSizeRandomness1; };
        float GetParticleSizeRandomness2() const { return particleSizeRandomness2; };
        float GetParticleAngleRandomness1() const { return particleAngleRandomness1; };
        float GetParticleAngleRandomness2() const { return particleAngleRandomness2; };

        enum RendererType {Point, Line, Quad};
        void SetRendererType(RendererType type) { rendererType = type; };
        RendererType GetRendererType() const { return rendererType; };

        bool IsRenderingAdditive() { return additive; };
        void SetRenderingAdditive() { additive = true;};
        void SetRenderingAlpha() { additive = false;};

        /** Change texture at runtime
         */
        void SetTexture( RuntimeScene & scene, const std::string & textureParticleName );

        /** Change texture name without changing it effectively at runtime
         */
        void SetParticleTexture(std::string imageName) { textureParticleName = imageName; };
        std::string GetParticleTexture() const { return textureParticleName; };

        bool NoMoreParticles() const {return !hasSomeParticles;};

        #if defined(GD_IDE_ONLY)
        bool particleEditionSimpleMode; ///< User preference related to object's edition
        bool emissionEditionSimpleMode; ///< User preference related to object's edition
        bool gravityEditionSimpleMode; ///< User preference related to object's edition
        #endif

    private:

        void CreateParticleSystem();

        ParticleSystemWrapper particleSystem;

        std::string textureParticleName;
        RendererType rendererType;
        float rendererParam1;
        float rendererParam2;
        bool additive;
        float tank;
        float flow;
        float emitterForceMin;
        float emitterForceMax;
        float emitterXDirection;
        float emitterYDirection;
        float emitterZDirection;
        float emitterAngleA;
        float emitterAngleB;
        float zoneRadius;
        float particleGravityX,particleGravityY,particleGravityZ;
        float friction;
        float particleLifeTimeMin, particleLifeTimeMax;
        ParticleParameterType redParam, greenParam, blueParam, alphaParam, sizeParam, angleParam;
        float particleRed1, particleRed2, particleGreen1, particleGreen2, particleBlue1, particleBlue2, particleAlpha1, particleAlpha2;
        float particleSize1, particleSize2, particleAngle1, particleAngle2;
        float particleAlphaRandomness1, particleAlphaRandomness2;
        float particleSizeRandomness1, particleSizeRandomness2, particleAngleRandomness1, particleAngleRandomness2;
        unsigned int maxParticleNb;

        bool hasSomeParticles;

        //Opacity
        float opacity;

        //Color
        unsigned int colorR;
        unsigned int colorG;
        unsigned int colorB;

        float angle;

        #if defined(GD_IDE_ONLY)
        static sf::Texture edittimeIconImage;
        static sf::Sprite edittimeIcon;
        #endif
};

void DestroyParticleEmitterObject(Object * object);
Object * CreateParticleEmitterObject(std::string name);

#endif // PARTICLEEMITTEROBJECT_H
