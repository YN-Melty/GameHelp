#pragma once
#include "Scene/Scene.h"

namespace LabScene
{
    class Lab : public Scene
    {
    public:
        Lab(EngineContext &);

        void Start();
        void Update();
        void Render() const;
        void OnPause(bool);
        void OnCleanup();
    };

};