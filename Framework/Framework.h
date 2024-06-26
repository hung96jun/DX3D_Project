#pragma once

#include "Math/Vector.h"
#include "Math/Transformation.h"
#include "Math/Math.h"

#include "Framework/Buffers/VertexBuffer.h"
#include "Framework/Buffers/IndexBuffer.h"
#include "Framework/Buffers/ConstBuffer.h"
#include "Framework/Buffers/GlobalBuffer.h"

#include "Systems/D3D.h"
#include "Systems/Keyboard.h"
#include "Systems/Mouse.h"
#include "Systems/Time.h"

#include "Viewer/Camera.h"
#include "Viewer/Projection.h"
#include "Viewer/Perspective.h"
#include "Viewer/Viewport.h"
#include "Viewer/Orthographic.h"
#include "Viewer/FreeCamera.h"

#include "Renders/Context.h"
#include "Renders/VertexLayout.h"
#include "Renders/Shaders/Shader.h"
#include "Renders/Shaders/VertexShader.h"
#include "Renders/Shaders/PixelShader.h"
#include "Renders/Texture.h"
#include "Renders/Material.h"

//#include "Meshes/Shape.h"
//#include "Meshes/BoxShape.h"
//#include "Meshes/CylinderShape.h"
//#include "Meshes/SphereShape.h"
//#include "Meshes/QuadShape.h"

#include "Framework/Scene.h"

#include "Framework/Managers/ShaderManager.h"
#include "Framework/Managers/SceneManager.h"

#include "Utilities/BinaryFile.h"
#include "Utilities/Utility.h"
#include "Utilities/tinyxml2.h"
#include "Utilities/Debug.h"
#include "Utilities/Defines.h"