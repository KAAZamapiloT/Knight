#pragma once
#include "EngineApi.hpp"
#include"utils/Math.hpp"
namespace Knight {
	enum class ECameraType{Orthographic,Prespective };
	class KNIGHT_ENGINE_API Camera
	{
	public:
		using MAT4x4 = glm::mat4x4;
		using Quat = glm::quat;
		using vec3 = glm::vec3;
		
		void SetPosition(const vec3 position);
		void SetUpVector(const vec3 vektor);
		void SetForwardVector(const vec3 vektor);
		void SetType(ECameraType Type);
		void SetScale(float scale);
		void resize(float aspect);
		void RotateFirstPerson(float DeltaYaw,float DeltaPitch);
		void RotateAroundTarget(float DelataYaw, float DeltaPitch);

		inline ECameraType GetType() { return m_Type; }
		inline vec3 GetPosition() { return m_Position; }
		inline vec3 GetForwardVector() { return m_ForwardVector; }
		inline vec3 GetUpVector() { return m_UpVector; }
		MAT4x4  GetProjectionMatrix() { return ProjectionMatrix; }
		MAT4x4  GetViewMatrix() { return ViewMatrix; }
		MAT4x4  GetViewxProjection() { return ViewMatrix * ProjectionMatrix; }
		Quat GetRoationQuaternion() { return Rotation; }
	private:
		void UpdateView();
		void UpdateProjection();
		vec3 m_Position;
		vec3 m_UpVector;
		vec3 m_ForwardVector;
		MAT4x4 ViewMatrix;
		MAT4x4 ProjectionMatrix;
		float FOV;
		float Aspect;
		float NearView;
		float FarView;
		float OrthoScale;
		ECameraType m_Type;
		Quat Rotation;
	};
}

//make them better mathematically i dont think this impl can work properly for now i need som better way to represent it 
