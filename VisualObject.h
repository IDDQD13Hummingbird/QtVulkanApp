#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <QVulkanWindow>
#include <vector>
#include "Vertex.h"
#include "Utilities.h"

class VisualObject
{
public:
    VisualObject();

    void move(float x, float y = 0.0f, float z = 0.0f);
    void scale(float s);
    void scale2(float x, float y);
    void scale3(float x, float y, float z);
    void rotate(float t, float x, float y, float z);


	//Setters and Getters
    inline std::vector<Vertex> getVertices() { return mVertices; }
    inline VkBuffer& getVBuffer() { return mVertexBuffer.mBuffer; }
    inline VkDeviceMemory& getVBufferMemory() { return mVertexBuffer.mBufferMemory; }
	inline VkDeviceMemory& getIBufferMemory() { return mIndexBuffer.mBufferMemory; }
    inline void setVBuffer(VkBuffer bufferIn) { mVertexBuffer.mBuffer = bufferIn; }
    inline void setVBufferMemory(VkDeviceMemory bufferMemoryIn) { mVertexBuffer.mBufferMemory = bufferMemoryIn; }
    inline VkBuffer& getIBuffer() { return mIndexBuffer.mBuffer; }
    inline void setIBuffer(VkBuffer bufferIn) { mIndexBuffer.mBuffer = bufferIn; }
    inline void setIBufferMemory(VkDeviceMemory bufferMemoryIn) { mIndexBuffer.mBufferMemory = bufferMemoryIn; }
    inline void setName(std::string name) { mName = name; }
    inline std::string getName() const { return mName; }
    inline int getDrawType() const { return drawType; }
    inline int getTexture() const { return textureType; }
    inline void pickTexture(int tex){ textureType = tex; }
    inline QMatrix4x4 getMatrix() const {return mMatrix;}
	inline std::vector<Vertex> getVertices() const { return mVertices; }
    inline std::vector<uint32_t> getIndices() const { return mIndices; }
    inline uint32_t getIndex(int i) const { return mIndices[i]; }
    inline int getIndicesSize() const { return sizeof(mIndices); }

    QVector3D getPosition();
    void setPosition(float x, float y, float z);
    void setPositionbyVector(const QVector3D &newPosition);

    bool isColliding(QVector3D Position, float Radius);
    inline float getRadius() const {return mRadius;}
    bool isWithinRange(QVector3D Position, float Range);

protected:
    std::vector<Vertex> mVertices;
    std::vector<uint32_t> mIndices;
    QMatrix4x4 mMatrix;
    std::string mName;
    QVector3D mPosition;
	BufferHandle mVertexBuffer;
	BufferHandle mIndexBuffer;
    //VkPrimitiveTopology mTopology{ VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST }; //not used


    float mRadius = 0.25;

    int drawType{ 0 }; // 0 = fill, 1 = line
    enum drawType {
      fill = 0,
      line = 1,
      color = 3
    };

    int textureType{ 0 }; // 0 = hund, 1 = loss, 2 = orange, 3 = pink
    enum textureType
    {
        Hund = 0,
        Loss = 1,
        Orange = 2,
        Pink = 4
    };
};

#endif // VISUALOBJECT_H

