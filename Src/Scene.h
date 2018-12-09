/**
* @file Scene.h
*/
#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

/**
* シーンの基底クラス.
*/
class Scene
{
public:
  Scene() = default;
  virtual ~Scene() = default;

  virtual bool Initialize() = 0;
  virtual void ProcessInput() = 0;
  virtual void Update() = 0;
  virtual void Render() = 0;
  virtual void Finalize() = 0;
};

#endif // SCENE_H_INCLUDED