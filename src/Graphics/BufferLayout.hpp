#pragma once
#include "EngineApi.hpp"
#include "KnightEnginepch.h"

enum class EDataType : uint8_t {
    Float = 0,
    Int, Int2, Int3, Int4,
    UInt, Bool,
    Float2, Float3, Float4,
    Mat2, Mat3, Mat4
};

constexpr uint32_t GetSize(EDataType type) {
    switch (type) {
    case EDataType::Float:   return 4;
    case EDataType::Float2:  return 4 * 2;
    case EDataType::Float3:  return 4 * 3;
    case EDataType::Float4:  return 4 * 4;
    case EDataType::Mat2:    return 4 * 2 * 2;
    case EDataType::Mat3:    return 4 * 3 * 3;
    case EDataType::Mat4:    return 4 * 4 * 4;
    case EDataType::Int:     return 4;
    case EDataType::Int2:    return 4 * 2;
    case EDataType::Int3:    return 4 * 3;
    case EDataType::Int4:    return 4 * 4;
    case EDataType::UInt:    return 4;
    case EDataType::Bool:    return 1;
    default: return 0;
    }
}

constexpr uint32_t GetComponentCount(EDataType type) {
    switch (type) {
    case EDataType::Float:   return 1;
    case EDataType::Float2:  return 2;
    case EDataType::Float3:  return 3;
    case EDataType::Float4:  return 4;
    case EDataType::Mat2:    return 2 * 2;
    case EDataType::Mat3:    return 3 * 3;
    case EDataType::Mat4:    return 4 * 4;
    case EDataType::Int:     return 1;
    case EDataType::Int2:    return 2;
    case EDataType::Int3:    return 3;
    case EDataType::Int4:    return 4;
    case EDataType::UInt:    return 1;
    case EDataType::Bool:    return 1;
    default: return 0;
    }
}

struct Element {
    std::string Name;
    EDataType Type;
    uint32_t Size;
    uint32_t Offset;
    bool Normalized;

    Element(EDataType type, const std::string& name, bool normalized = false)
        : Name(name), Type(type), Size(GetSize(type)), Offset(0), Normalized(normalized) {
    }

    uint32_t GetComponentCount() const {
        return ::GetComponentCount(Type);
    }
};

class KNIGHT_ENGINE_API BufferLayout {
public:
    BufferLayout() = default;

    BufferLayout(std::initializer_list<Element> elements)
        : m_Elements(elements) {
        CalculateOffsetsAndStride();
    }

    void AddElement(const Element& element) {
        m_Elements.push_back(element);
        CalculateOffsetsAndStride(); // Recalculate offsets and stride
    }

    const std::vector<Element>& GetElements() const { return m_Elements; }
    uint32_t GetStride() const { return m_Stride; }
  
private:
    std::vector<Element> m_Elements;
    uint32_t m_Stride = 0;

    void CalculateOffsetsAndStride() {
        uint32_t offset = 0;
        m_Stride = 0;
        for (auto& element : m_Elements) {
            element.Offset = offset;
            offset += element.Size;
            m_Stride += element.Size;
        }
    }
};
