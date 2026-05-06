#pragma once

namespace LabScene
{
    class Lab : public Scene
    {
    public:
        Lab();

        void Start();
        void Update();
        void Render() const;
        void OnPause(bool);
        void OnCleanup();
    };

};