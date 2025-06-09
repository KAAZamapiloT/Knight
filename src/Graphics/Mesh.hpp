#pragma once
#include "EngineApi.hpp"
#include "Graphics/Material.hpp"

#include <memory>
// Forward declarations to reduce includes
class VertexBuffer;
class IndexBuffer;
class VertexArray;
class Material;
/// @brief Represents the raw geometry of a 3D model along with its material.
///
/// A Mesh holds GPU-side resources needed for rendering: vertex buffer,
/// index buffer, vertex array, and an associated material.
/// It does not store transform data or scene hierarchy.
/// Rendering should be handled externally via a Renderer using this mesh.
class KNIGHT_ENGINE_API Mesh
{
public:
	/// @brief Constructs a Mesh from its GPU resources and associated material.
  /// @param vertexBuffer Shared pointer to the Vertex Buffer Object.
  /// @param indexBuffer Shared pointer to the Index Buffer Object.
  /// @param vertexArray Shared pointer to the Vertex Array Object.
  /// @param material Pointer to the material associated with this mesh.
  /// 
   Mesh(const std::shared_ptr<VertexBuffer>& vertexBuffer,
	const std::shared_ptr<IndexBuffer>& indexBuffer,
		const std::shared_ptr<VertexArray>& vertexArray,
		Material* material)
		: m_VertexBuffer(vertexBuffer), m_IndexBuffer(indexBuffer),
		m_VertexArray(vertexArray), m_Material(material) {
		}


   /// @brief Returns the vertex buffer of the mesh.
   /// @return A shared pointer to the VertexBuffer.
   const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const { return m_VertexBuffer; }

   /// @brief Returns the index buffer of the mesh.
   /// @return A shared pointer to the IndexBuffer.
   const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

   /// @brief Returns the vertex array object of the mesh.
   /// @return A shared pointer to the VertexArray.
   const std::shared_ptr<VertexArray>& GetVertexArray() const { return m_VertexArray; }

   /// @brief Gets the material associated with the mesh.
   /// @return A raw pointer to the Material.
   Material* GetMaterial() { return m_Material; }
private:
	/// Vertex buffer (VBO) holding the geometry's vertices.
	std::shared_ptr<VertexBuffer> m_VertexBuffer;

	/// Index buffer (IBO/EBO) defining triangle connectivity.
	std::shared_ptr<IndexBuffer> m_IndexBuffer;

	/// Vertex array object (VAO) encapsulating vertex attributes.
	std::shared_ptr<VertexArray> m_VertexArray;

	/// Pointer to the material used for shading this mesh.
	Material* m_Material;
	
};

